
# OpenGL Laboratory

## Installation

### Windows

1. Clone the repository locally.
2. Create a `msvc-x64` directory in `dependencies/prebuilt`.
3. Download SFML-3.0.2 for [Visual C++ 17 (2022) 64-bit](https://www.sfml-dev.org/files/SFML-3.0.2-windows-vc17-64-bit.zip).
4. Extract it into the `msvc-x64` directory.
    - `dependencies/prebuilt/msvc-x64/SFML-3.0.2/readme.md` should now exist.
5. Open the `opengl-lab` directory using VS.

### Linux (Ubuntu / Debian-based)

```sh
# 1. Install the build tools
sudo apt install git build-essential cmake ninja-build

# 2. Install the following dependencies
sudo apt install libfreetype-dev libflac-dev libvorbis-dev
# Vorbis, FLAC, Freetype

# 3. Enter a directory where you wish to clone the project
cd ~

# 4. Clone the repository locally and enter the project directory
git clone https://github.com/Rami-Sabbagh/opengl-lab.git
cd opengl-lab

# 5. Generate the build files.
cmake . --preset=linux-debug
# Note: this will take time the first time used because it'll download necessary dependencies.
```

