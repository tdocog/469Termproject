# HW4 Performance Summary

Generated: 2026-04-24 16:11:06 CDT

Source: `outputs/hw4/SHiP-ISeq/*/zsim.out`

Only `SHiP-ISeq` output exists in this workspace output directory. Performance below uses the HW4 report formula: `total cycles = cycles + cCycles`, and `IPC = instrs / total cycles`.

See `ship_iseq_vs_lru.md` for the direct comparison against the LRU outputs from the HW4 PDF submission folder.

| Benchmark | Instrs | Total cycles | IPC | L3 miss rate | L3 MPKI | DRAM MPKI | Mem reads | Mem writes |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| bzip2 | 100,002,026 | 120,873,939 | 0.8273 | 16.49% | 3.32 | 5.21 | 331,852 | 189,569 |
| gcc | 100,005,381 | 132,104,309 | 0.7570 | 23.70% | 4.50 | 6.92 | 449,883 | 242,599 |
| hmmer | 100,004,490 | 88,810,513 | 1.1260 | 72.65% | 2.85 | 4.70 | 285,340 | 184,262 |
| libquantum | 100,000,311 | 190,390,691 | 0.5252 | 96.16% | 24.12 | 33.65 | 2,411,531 | 953,058 |
| mcf | 100,000,530 | 654,801,771 | 0.1527 | 60.73% | 62.07 | 76.15 | 6,207,019 | 1,407,895 |
| sjeng | 100,005,078 | 86,667,385 | 1.1539 | 91.25% | 0.37 | 0.48 | 37,198 | 10,719 |

Geomean IPC: 0.6196

Average L3 miss rate: 60.16%

Average L3 MPKI: 16.20

Average DRAM MPKI: 21.18

Completed: `bzip2`, `gcc`, `hmmer`, `libquantum`, `mcf`, `sjeng`

Failed: `milc` failed because `$CPU2006DATA/milc/su3imp.in` was missing.

Not run after failure: `blackscholes_8c_simlarge`, `bodytrack_8c_simlarge`, `cactusADM`, `calculix`, `canneal_8c_simlarge`, `dedup_8c_simlarge`, `fluidanimate_8c_simlarge`, `freqmine_8c_simlarge`, `lbm`, `leslie3d`, `namd`, `soplex`, `streamcluster_8c_simlarge`, `swaptions_8c_simlarge`, `x264_8c_simlarge`, `xalan`
