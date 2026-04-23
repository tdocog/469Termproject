#ifndef RRIP_REPL_H_
#define RRIP_REPL_H_

#include "repl_policies.h"

// Static RRIP
class SRRIPReplPolicy : public ReplPolicy {
    protected:
        uint32_t* rrpv;
        uint32_t numLines;
        uint32_t rpvMax;
        uint32_t pendingInsert;
        uint32_t lastVictim;
        bool lastVictimValid;

    public:
        SRRIPReplPolicy(uint32_t _numLines, uint32_t _rpvMax)
            : numLines(_numLines), rpvMax(_rpvMax), pendingInsert((uint32_t)-1),
              lastVictim((uint32_t)-1), lastVictimValid(false) {
            assert(rpvMax > 0);
            rrpv = gm_calloc<uint32_t>(numLines);
            for (uint32_t i = 0; i < numLines; i++) rrpv[i] = rpvMax;
        }

        virtual ~SRRIPReplPolicy() {
            gm_free(rrpv);
        }

        void update(uint32_t id, const MemReq* req) {
            if (pendingInsert == id) {
                rrpv[id] = getInsertRRPV(id, req);
                pendingInsert = (uint32_t)-1;
            } else {
                rrpv[id] = 0;
                onHit(id, req);
            }
        }

        void replaced(uint32_t id) {
            onEvict(id, lastVictim == id && lastVictimValid);
            pendingInsert = id;
        }

        template <typename C> inline uint32_t rank(const MemReq* req, C cands) {
            while (true) {
                for (auto ci = cands.begin(); ci != cands.end(); ci.inc()) {
                    uint32_t id = *ci;
                    if (cc && !cc->isValid(id)) return recordVictim(id, false);
                    if (rrpv[id] >= rpvMax) return recordVictim(id, true);
                }

                for (auto ci = cands.begin(); ci != cands.end(); ci.inc()) {
                    uint32_t id = *ci;
                    if (rrpv[id] < rpvMax) rrpv[id]++;
                }
            }
        }

        DECL_RANK_BINDINGS;

    protected:
        virtual uint32_t getInsertRRPV(uint32_t id, const MemReq* req) {
            return rpvMax - 1;
        }

        virtual void onHit(uint32_t id, const MemReq* req) {}

        virtual void onEvict(uint32_t id, bool valid) {}

    private:
        uint32_t recordVictim(uint32_t id, bool valid) {
            lastVictim = id;
            lastVictimValid = valid;
            return id;
        }
};

class SHiPISeqReplPolicy : public SRRIPReplPolicy {
    private:
        uint32_t* shct;
        uint32_t* signatures;
        uint8_t* outcome;
        uint32_t shctEntries;
        uint32_t shctMask;
        uint32_t shctMax;
        uint32_t shctInit;

        static uint32_t calcShctMax(uint32_t bits) {
            assert(bits > 0 && bits < 32);
            return (1u << bits) - 1;
        }

    public:
        SHiPISeqReplPolicy(uint32_t _numLines, uint32_t _rpvMax, uint32_t _shctEntries,
                uint32_t shctCtrBits, uint32_t _shctInit)
            : SRRIPReplPolicy(_numLines, _rpvMax), shctEntries(_shctEntries),
              shctMask(_shctEntries - 1), shctMax(calcShctMax(shctCtrBits)),
              shctInit(_shctInit) {
            assert(isPow2(shctEntries));
            assert(shctInit <= shctMax);

            shct = gm_calloc<uint32_t>(shctEntries);
            signatures = gm_calloc<uint32_t>(numLines);
            outcome = gm_calloc<uint8_t>(numLines);
            for (uint32_t i = 0; i < shctEntries; i++) shct[i] = shctInit;
        }

        ~SHiPISeqReplPolicy() {
            gm_free(shct);
            gm_free(signatures);
            gm_free(outcome);
        }

    protected:
        uint32_t getInsertRRPV(uint32_t id, const MemReq* req) {
            uint32_t sig = req->signature & shctMask;
            signatures[id] = sig;
            outcome[id] = 0;
            return shct[sig] == 0 ? rpvMax : rpvMax - 1;
        }

        void onHit(uint32_t id, const MemReq* req) {
            uint32_t sig = signatures[id];
            outcome[id] = 1;
            if (shct[sig] < shctMax) shct[sig]++;
        }

        void onEvict(uint32_t id, bool valid) {
            if (valid && !outcome[id]) {
                uint32_t sig = signatures[id];
                if (shct[sig] > 0) shct[sig]--;
            }
            outcome[id] = 0;
        }

};
#endif // RRIP_REPL_H_
