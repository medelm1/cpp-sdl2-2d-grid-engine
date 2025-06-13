#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <map>
#include <vector>

#include "IGame.hpp"
#include "input/InputHandler.hpp"
#include "audio/AudioManager.hpp"
#include "graphics/text/TextRenderer.hpp"
#include "graphics/TextureManager.hpp"
#include "grid/Grid.hpp"
#include "GameObject.hpp"

class Game : public IGame
{
private:
    static Game* instance;
    const int FPS = 60;
    const int DELAY_TIME = 1000.0f / FPS;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    GameObject* bee;

    Grid* mainGrid;

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