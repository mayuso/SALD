# SALD

OpenGL wrapper / engine. Created mostly for learning and prototyping purposes.

## Examples

*   [**SALD-Sandbox3D**](https://github.com/mayuso/SALD-Sandbox3D) - A 3D sandbox project.
*   [**SALD-Breakout**](https://github.com/mayuso/SALD-Breakout) - A 2D breakout game.

## Usage

### Build from source

Ensure you have CMake and a C++ compiler installed.

**1. Clone the repository**

```bash
git clone https://github.com/mayuso/SALD.git
cd SALD
```

**2. Update submodules**

This project relies on external dependencies included as submodules.

```bash
git submodule update --init --recursive
```

**3. Build and Run (Debug)**

For quick testing or development:

```bash
mkdir build
cd build
cmake ..
cmake --build . --parallel
```

### Install Build

To create an optimized build:

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release --parallel
cmake --install . --config Release
```

## FAQ

**Can you use SALD for your own projects?**
Sure.

**Should you use it?**
Probably not. This is a tiny project and other engines do everything SALD does, but better, and even more.
I'd personally recommend Godot: [Website](https://godotengine.org/), [Repository](https://github.com/godotengine/godot).
