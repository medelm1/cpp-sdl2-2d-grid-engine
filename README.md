# C++/SDL2 2D Grid-Based Game Engine

A modular 2D grid-based game engine written in modern C++ using SDL2.  
Built for tile-based gameplay, with a focus on simplicity, extensibility, and experimentation with game systems and algorithms.

## Features

- Grid-based world representation
- Basic scene and object management
- SDL2-based rendering system
- Expandable architecture for future systems (e.g., audio, UI, AI)
- Clean domain-oriented folder structure

## Requirements

- C++17 or higher
- [SDL2](https://github.com/libsdl-org/SDL)
- SDL2_image
- SDL2_mixer
- SDL2_ttf
- CMake (for building)

## Project Structure

```
/include             -> Header files organized by domain
/src                 -> Source files matching header structure
/assets              -> Game assets (images, sounds, etc.)
/build               -> CMake build output (ignored by git)
/lib                 -> Third-party libraries (e.g., SDL2)
/docs                -> Documentation files (in progress)
/CMakeLists.txt      -> Project build configuration
```

## Building the Project

Use CMake to configure and build the project:

```bash
cmake -S . -B build      # Configure the project
cmake --build build      # Build the project
```

You can run the compiled binary from the `build` directory after a successful build.

## License

MIT License
