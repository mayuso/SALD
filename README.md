# Build environment

This is just a recommendation, as any modern compiler can do the job well, but I currently work with:

* CMake 3.22.2
* On Windows: Visual Studio 17.1.0 (2022)
* On Linux: GCC 9.3.0

# In Ubuntu / Pop!_OS

### Compile

    sudo apt install xorg-dev libglu1-mesa-dev
	sudo apt install ninja-build

### Debug

    sudo apt install gdb
 
# FAQ

### 1) Can you use SALD for your own projects?

Sure

### 1.1) Should you use it?

Probably not. This is a tiny project and other engines do everything SALD does, but better, and even more. 

I'd personally recommend Godot: [Website](https://godotengine.org/), [Repository](https://github.com/godotengine/godot)
 
# Development

Update submodules:
 
    git submodule update --recursive --remote   

