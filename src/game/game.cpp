#include "game.hpp"

Game* Game::instance = nullptr;

Game::Game()
    : window(nullptr), renderer(nullptr), isRunning(false)
{

}

Game::~Game()
{

}

Game& Game::getInstance()
{
    if (instance == nullptr) {
        instance = new Game();
    }

    return *instance;
}

bool Game::init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "Error: SDL initialization failed. SDL Error: " << SDL_GetError() << "\n";
        return false;
    }

    if ((IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)) == 0) {
        std::cerr << "Error: SDL_image initialization failed. IMG Error: " << IMG_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow(
        "CppPlayground - SDL2",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        460,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        std::cerr << "Error: Failed to create SDL window. SDL Error: " << SDL_GetError() << "\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cerr << "Error: Failed to create SDL renderer. SDL Error: " << SDL_GetError() << "\n";
        return false;
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    initSystems();
    loadAssets();

    // play background music
    // AudioManager::getInstance().playMusic("clouds");

    return true;
}

void Game::initSystems()
{
    // Init audio system
    AudioManager::getInstance().init(this);
    AudioManager::getInstance().addChannel("channel_1");
    AudioManager::getInstance().addChannel("channel_2");
    AudioManager::getInstance().addChannel("channel_ui");

    // Init text rendering system
    TextRenderer::getInstance().init(renderer, "assets/fonts/prstartk.ttf");

    TextStyle style = TextStyle(12, {0xFF, 0xFF, 0xFF, 0xFF}, {0x00, 0x00, 0x00, 0xFF});

    text1 = TextObject("Hello from text object", style);

    TextStyle menuItemsStyle = TextStyle(8, {0xFF, 0xFF, 0xFF, 0xFF}, {0x00, 0x00, 0x00, 0xFF});

    menuItems.push_back(TextObject("New Game", menuItemsStyle));
    menuItems.push_back(TextObject("Load Game", menuItemsStyle));
    menuItems.push_back(TextObject("Options", menuItemsStyle));
    menuItems.push_back(TextObject("Quit", menuItemsStyle));
}

void Game::loadAssets()
{
    AudioManager::getInstance().loadMusic("clouds", "assets/sounds/clouds.mp3");
    AudioManager::getInstance().loadSound("fairy-magic-wand", "assets/sounds/fairy-magic-wand.wav");
    AudioManager::getInstance().loadSound("magic-church-bell", "assets/sounds/magic-church-bell.mp3");
    AudioManager::getInstance().loadSound("menu-click", "assets/sounds/menu-click.mp3");
}

void Game::run()
{
    Uint32 frameStartTime, frameElapsedTime;
    isRunning = true;

    while (isRunning)
    {
        frameStartTime = SDL_GetTicks();

        update();
        render();

        frameElapsedTime = SDL_GetTicks() - frameStartTime;

        // Check if a delay is needed
        if (frameElapsedTime < DELAY_TIME) {
            SDL_Delay((int) (DELAY_TIME - frameElapsedTime));
        }
    }
    
    clean();
}

void Game::update()
{
    InputHandler::getInstance().update(this);

    // if (InputHandler::getInstance().getMouseButtonState(MouseButton::MOUSE_BUTTON_LEFT))
    // {
    //     AudioManager::getInstance().pauseMusic();
    //     AudioManager::getInstance().playSound("menu-click", "channel_ui", LoopMode::PLAY_ONCE);
    // }

    // if (InputHandler::getInstance().getMouseButtonState(MouseButton::MOUSE_BUTTON_RIGHT))
    // {
    //     AudioManager::getInstance().playSound("menu-click", "channel_ui", LoopMode::PLAY_ONCE);
    //     AudioManager::getInstance().resumeMusic();
    // }
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0x6F, 0xB9, 0x42, 0xFF);
    SDL_RenderClear(renderer);

    TextRenderer::getInstance().renderAll(menuItems, {32, 32}, {80, 0});

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

void Game::quit()
{
    isRunning = false;
}