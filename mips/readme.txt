This code is optimized for fewest cycles by using more registers.

Without forwarding:
- 703 instructions
- 908 cycles
- 100 RAW stalls
- 1.291 CPI

With forwarding:
- 703 instructions
- 808 cycles
- 0 stalls
- 1.149 CPI

Unoptimized, without forwarding:
- 603 instructions
- 1008 cycles
- 300 RAW stalls
- 1.671 CPI

Unoptimized, with forwarding:
- 603 instructions
- 808 cycles
- 100 RAW stalls
- 1.339 CPI