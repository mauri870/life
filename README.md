# Mauri's Conway's game of life

# Installation

```bash
# initialize vcpkg
(cd external/vcpkg && ./bootstrap-vcpkg.sh)

# configure and compile
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j $(nproc)
```