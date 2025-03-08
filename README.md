Stanford CS 144 Networking Lab
==============================

These labs are open to the public under the (friendly) request that to
preserve their value as a teaching tool, solutions not be posted
publicly by anybody.

Website: https://cs144.stanford.edu

To set up the build system: `cmake -S . -B build`

To compile: `cmake --build build`

To run tests: `cmake --build build --target test`

To run speed benchmarks: `cmake --build build --target speed`

To run clang-tidy (which suggests improvements): `cmake --build build --target tidy`

To format code: `cmake --build build --target format`

-----------------------------------------------------

running on macOS 15.3.1, using Ubuntu 24.04 LTS (arm64) virtualized by OrbStack

ByteStream throughput (pop length 4096): 110.49 Gbit/s

ByteStream throughput (pop length 128):  46.51 Gbit/s

ByteStream throughput (pop length 32):   15.51 Gbit/s
