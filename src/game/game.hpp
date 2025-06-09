#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <map>
#include <vector>

#include "game_interface.hpp"
#include "../systems/input/input_handler.hpp"
#include "../systems/audio/audio_manager.hpp"
#include "../systems/text/text_renderer.hpp"
#include "../systems/texture/texture_manager.hpp"
#include "../systems/grid/grid.hpp"
#include "../systems/sprite-animation/sprite.hpp"
#include "../systems/sprite-animation/sprite_builder.hpp"

class Game : public IGame
{
private:
    static Game* instance;
    const int FPS = 60;
    const int DELAY_TIME = 1000.0f / FPS;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    Grid mainGrid;

    Sprite* fireSprite;
    Sprite* coinSprite;

private:
    Game();
    void update();
    void render();
    void clean();

    void initSystems();
    void loadAssets();

public:
    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    static Game& getInstance();

    bool init();
    void run();
    void quit();
};

#endif