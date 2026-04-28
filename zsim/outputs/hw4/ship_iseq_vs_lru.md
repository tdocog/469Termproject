# SHiP-ISeq vs LRU

Source:

`SHiP-ISeq`: `casim-csce614/zsim/outputs/hw4/SHiP-ISeq/*/zsim.out`

`LRU`: `#933009805_hw4/#933009805_hw4/LRU/*/zsim.out`

The HW4 report PDF says the original full-set SRRIP result was `1.059x` IPC vs LRU and `0.944x` cycles vs LRU. This SHiP-ISeq comparison is only for the 6 benchmarks that completed, so it is a subset comparison.

| Benchmark | LRU IPC | SHiP-ISeq IPC | IPC change | LRU cycles | SHiP-ISeq cycles | Cycle change | LRU L3 MPKI | SHiP-ISeq L3 MPKI | L3 MPKI change |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| bzip2 | 0.8572 | 0.8273 | -3.48% | 116,685,557 | 120,873,939 | +3.59% | 2.85 | 3.32 | +16.31% |
| gcc | 0.7640 | 0.7570 | -0.91% | 130,895,152 | 132,104,309 | +0.92% | 2.78 | 4.50 | +61.62% |
| hmmer | 1.4014 | 1.1260 | -19.65% | 71,364,082 | 88,810,513 | +24.45% | 1.59 | 2.85 | +79.21% |
| libquantum | 0.5114 | 0.5252 | +2.71% | 195,553,652 | 190,390,691 | -2.64% | 25.05 | 24.12 | -3.71% |
| mcf | 0.1249 | 0.1527 | +22.32% | 800,928,786 | 654,801,771 | -18.24% | 81.03 | 62.07 | -23.40% |
| sjeng | 1.1560 | 1.1539 | -0.18% | 86,510,997 | 86,667,385 | +0.18% | 0.36 | 0.37 | +2.72% |

Geomean IPC vs LRU: `0.9938x` (`-0.62%`)

Geomean cycles vs LRU: `1.0061x` (`+0.61%`)

Average L3 MPKI: LRU `18.94`, SHiP-ISeq `16.20` (`-14.46%`)

Average DRAM MPKI: LRU `25.64`, SHiP-ISeq `21.18` (`-17.38%`)

Summary: SHiP-ISeq reduces average L3 and DRAM misses on this completed subset, mostly because `mcf` improves a lot, but it does not beat LRU on overall performance yet. The large `hmmer` regression offsets the wins from `mcf` and `libquantum`.
