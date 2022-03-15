# Can I use SALD for my own projects?

Sure

# Should I?

Probably not. This is a tiny project and other engines do a lot more and better. I'd personally recommend Godot: [Website](https://godotengine.org/), [Repository](https://github.com/godotengine/godot)

# Build environment

This is just a recommendation, as any modern compiler can do the job well, but I currently work with:

* CMake 3.22.2
* On Windows: Visual Studio 17.1.0 (2022)
* On Linux: GCC 9.3.0

# In Ubuntu / Pop!_OS

### Compile

    sudo apt install xorg-dev libglu1-mesa-dev

### Debug

    sudo apt install gdb
    
# Development

Update submodules:
 
    git submodule update --recursive --remote   

