# C++/SDL2 2D Grid-Based Game Engine

A simple 2D grid-based game engine written in C++ using SDL2.
Designed to support classic tile-based environments and facilitate experimentation with AI algorithms, pathfinding, and other gameplay systems.

## Features

- Grid-based world movement
- Basic scene and object management
- SDL2 rendering
- Audio system using SDL2_mixer
- Expandable engine architecture

## Requirements

- C++17 compatible compiler
- SDL2
- SDL2_image
- SDL2_mixer
- SDL2_ttf

## Project Structure

```
/src              -> Source code
/build            -> Compiled output (ignored in git)
/third_party      -> SDL2 and related libraries
script.bat        -> Compile/run helper script
```

## How to Build and Run (Windows)

Use the provided `script.bat`:

```bash
script.bat compile    # Compile the project
script.bat run        # Run the executable
script.bat rebuild    # Clean and recompile
script.bat clean      # Remove the build folder
```

## License

MIT License
