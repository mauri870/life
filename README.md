# A simple Conway's game of life

# Installation

```bash
git clone --recurse-submodules https://github.com/mauri870/life.git

# configure and compile
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j $(nproc)
```

![Alt text](./life.png?raw=true "Game of Life")
