What is the cycle time for your design from starting reading registers until you get the result updated in the destination? What is the proper timing diagram for each signal and why?

- 2 cycles has passed before the result is updated
- The register take 2 cycles to update as it is the delay of dff
- The ALU take no more cycle so the output is ready immediately after register output.