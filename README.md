# Raw Twin Viewer (QA)

Minimal Qt 6 / QML app for visual inspection of `.raw` buffers:
- Mono8 and Mono10/Mono12/Mono16 shown as 2 bytes/pixel
- Side-by-side view with linked scrolling
- Cell-level diff highlighting (when specs match)
- Optional spec inference from filename tokens: `--Width`, `--Height`, `--PixelFormat`

## Build (Ubuntu 22)

```bash
sudo apt-get update
sudo apt-get install -y cmake ninja-build qt6-base-dev qt6-declarative-dev
cmake -S . -B build -G Ninja
cmake --build build
./build/kaya-sw-camera_qa_studio
```

## Build (Windows)

Use Qt Creator (Qt 6.x kit) and open the folder, or build with CMake using your Qt toolchain.
