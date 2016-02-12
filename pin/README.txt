1. i<1000 = 93950
i<100000 = 588950

2. assembly listing use `trace`
cache hit/miss use `dcache`
instruction count by type use `opcodemix`

3. Without pin: 0.01s user 0.03s system 52% cpu 0.079 total
With pin+inscount0: 0.51s user 0.15s system 92% cpu 0.702 total
Pin overhead: 0.50s

4. Use pinatrace. The result is in matrix.mem.txt