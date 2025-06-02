# cpp_sdl2_2d_grid_engine

A simple 2D grid-based game engine written in C++ using SDL2.  
Designed for building classic tile-based games like RPGs and adventure games (inspired by games like Pokémon and The Legend of Zelda).

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
