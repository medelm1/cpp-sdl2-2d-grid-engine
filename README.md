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

---

## Game Loop

The `Game` class implements the core **game loop** that drives the runtime behavior of your SDL2 game. This loop is defined in the `Game::run()` method.

### Lifecycle Phases

```cpp
Game::run() → while (isRunning) {
    update();   // Game logic
    render();   // Drawing
}
```

### Game Loop Structure

| Phase         | Method         | Description                                                                 |
|---------------|----------------|-----------------------------------------------------------------------------|
| **Init**      | `init()`       | Initializes SDL subsystems, creates window/renderer, and initializes systems. |
| **Run Loop**  | `run()`        | Executes the game loop at a fixed FPS (60 by default).                      |
| **Update**    | `update()`     | Handles input and updates game state. (e.g., input, physics, game logic).   |
| **Render**    | `render()`     | Clears the screen and draws current game state.                            |
| **Clean Up**  | `clean()`      | Releases SDL resources (window, renderer).                                 |
| **Quit**      | `quit()`       | Sets `isRunning = false` to exit the loop.                                 |

### Where to Add Your Game Logic

Here’s where you should initialize, update, and render your entities/systems.

#### System Initialization
In `initSystems()`:

```cpp
// Extend this to init your game-specific systems:
TextRenderer::getInstance().init();     // Example
AudioManager::getInstance().init();     // Hypothetical
```

In `loadAssets()`:

```cpp
// Load textures, audio, etc.
TextureManager::getInstance().load("player", "assets/images/player.png");
```

#### Updating Game State
In `update()`:

```cpp
InputHandler::getInstance().update(this);

// Update your entities/systems
player.update();      // If you have a player object
sprite.update();      // For animations
grid.update();        // If grid needs per-frame logic
```

#### Rendering
In `render()`:

```cpp
SDL_RenderClear(renderer);

// Render entities
grid.render(renderer);       // Example: Draw tiles
player.render(renderer);     // Example: Draw player sprite
text.render(...);            // Example: HUD or score

SDL_RenderPresent(renderer);
```

---

## System Documentation

- **Audio Manager**
- **Input Handler**
- **Grid System**
- **Text Renderer**
- **Texture Manager**
- **Sprite Animation**

### Audio System

The Audio System manages all sound effects and background music using `SDL2_mixer`. It follows the singleton pattern and provides an interface to load, play, and manage audio assets with labeled channels.

__Class: `AudioManager`__

Header: `audio_manager.hpp`  
Source: `audio_manager.cpp`

Singleton Access:

```cpp
AudioManager& audio = AudioManager::getInstance();
```

Public Methods:
```cpp
void init();
void loadSound(const std::string& label, const std::string& filepath);
void playSound(const std::string& label, int loops = 0, int channel = -1);
void stopChannel(int channel);
void stopAll();

void loadMusic(const std::string& label, const std::string& filepath);
void playMusic(const std::string& label, int loops = -1);
void pauseMusic();
void resumeMusic();
void stopMusic();

```

### Input System

The Input System handles keyboard and mouse inputs using SDL events. It provides a singleton interface for polling key and mouse states, tracking the mouse position, and managing key press history.

__Class: `InputHandler`__

Header: `input_handler.hpp`  
Source: `input_handler.cpp`

Singleton Access:
```cpp
InputHandler& input = InputHandler::getInstance();
```

Public Methods:
```cpp
void update();
bool isKeyPressed(SDL_Scancode key);
bool isMouseButtonPressed(Uint8 button);
Vector2D getMousePosition();
```

### Grid System

The Grid System provides a 2D tilemap structure composed of customizable cells. It supports mapping between pixel coordinates and grid coordinates, allows cell replacement and iteration, and integrates drawing utilities for debugging or visualization.

__Class: `Grid`__

Header: `grid.hpp`  
Source: `grid.cpp`

Constructor:
```cpp
Grid(size_t rows, size_t cols, size_t cellSize);
```

Coordinate Mapping:
```cpp
Vector2D getCoordFromIndex(size_t index);
size_t getIndexFromCoord(const Vector2D& coord);

Vector2D getPixelsFromCoord(Vector2D coord);
Vector2D getCoordFromPixels(Vector2D pixels);
Vector2D normalize(Vector2D pixels);
```

Cell Access & Modification:
```cpp
GridCell* getCell(size_t index);
GridCell* getCell(const Vector2D& coord);
void replaceCell(size_t index, GridCell* newCell);
void replaceCell(const Vector2D& coord, GridCell* newCell);
```

Iteration & Query:
```cpp
void forEachCell(std::function<void(size_t, GridCell*)> func);
std::vector<GridCell*> findCells(std::function<bool(size_t, GridCell*)> predicate);
```

Render & Cleanup:
```cpp
void drawLines(SDL_Renderer* renderer);
void clean();
```

### Text Renderer

The Text Renderer renders TTF text using `SDL_ttf`. It maintains a font cache for optimized reuse and allows rendering individual text or multiple text elements with positioning and spacing control.

__Class: `TextRenderer`__

Header: `text_renderer.hpp`  
Source: `text_renderer.cpp`

Singleton Access:
```cpp
TextRenderer& text = TextRenderer::getInstance();
```

Public Methods:
```cpp
void init(SDL_Renderer* renderer, const std::string& fontPath);
void render(TextObject text, Vector2D position);
void renderAll(const std::vector<TextObject>& texts, Vector2D position, Vector2D offset);
```

### Texture Manager

The Texture Manager handles loading, caching, and retrieval of textures using `SDL_image`. It ensures that each texture is loaded only once, and provides cleanup mechanisms to unload specific or all textures. The system follows the singleton pattern.

__Class: `TextureManager`__

Header: `texture_manager.hpp`  
Source: `texture_manager.cpp`

Singleton Access:
```cpp
TextureManager& textures = TextureManager::getInstance();
```

Public Methods:
```cpp
void init(SDL_Renderer* renderer);
void load(const std::string& label, const std::string& filepath);
SDL_Texture* getTexture(const std::string& label);
void unload(const std::string& label);
void unloadAll();
```

### Sprite Animation

The Sprite Animation system manages animated 2D sprites from sprite sheets. It provides functions to control playback (play, pause, resume, stop), adjust scaling, render with optional bounding boxes, and integrate with an animation controller.

__Class: `Sprite`__

Header: `sprite.hpp`  
Source: `sprite.cpp`

Constructor:
```cpp
Sprite(SDL_Texture* texture, GridSize sheetSize, Scale scale, bool boundingBoxEnabled);
```

Public Methods:
```cpp
void setScale(Scale scale);
Scale getScale() const;

void setBoundingBoxEnabled(bool enabled);
bool isBoundingBoxEnabled() const;

void playAnimation(const std::string& animationName);
void pauseAnimation();
void resumeAnimation();
void stopAnimation();

void update();
void render(SDL_Renderer* renderer, Vector2D position);

AnimationController* getAnimationController();
```


## License

MIT License