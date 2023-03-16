# DNVT
Digital Non-secure Voice Terminal Test Code and Switch PCBA Design Files.

This repo contains the PCBA design files for the DNVT test interface boards, four phone switches which run Nick Andre's code, and the crappy support code I wrote to initially reverse engineering DNVTs. 

The Arduino code encodes and decodes Differential Manchester, and the Python scripts determine the codewords. There is also a Python script which decodes differential manchester based on a CSV capture from an oscilloscope. Example files are provided.
