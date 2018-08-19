# diffsync-cpp

This project uses the rsync algorithm to do efficient file transfers.
This project only exists so I can try and keep ontop of C++11,14,17 features whilst I am stuck on 03 in work.
This is not inteded for serious use.

## What's implemented?

Not a lot at the moment. Only Hashes, and the weakhash is a quick dirty implementation.

Up Next:
- File Reading (Possibly using the filesystem TS)
- Hashing the files (Might be able to use the newer threading stuff here)
- Comms between 2 clients
- Designing & imlement a wire protocol
- Transfer hashes from out of date client to in date client
- Building instruction set for the out of date client
- Rebuilding files from an instruction set

... quite a long way to go.

## Requires

- A C++17 compiler
- Conan
- CMake 3.10

## Build Instructions

From the root directory:

```
mkdir build && cd build
conan install .. -s:build_type=Debug
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j
```
