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

    window = SDL_CreateWindow(
        "CppPlayground - SDL2",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
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



    // Fire Sprite + frame & animation configuration + start animation

    fireSprite = SpriteBuilder(TextureManager::getInstance().getTexture("fire"), GridSize{4, 1})
        .withScale(Scale{1, 1})
        .enableBoundingBox(false)
        .setFrameSizes({
            {0, Size{32, 32}}, 
            {1, Size{32, 32}}, 
            {2, Size{32, 32}}, 
            {3, Size{32, 32}}
        })
        .setFrameDurations({
            {0, 100}, 
            {1, 100}, 
            {2, 100}, 
            {3, 100}
        })
        .addAnimation("burning", {0, 1, 2, 3})
        .build();

    fireSprite->playAnimation("burning");

    // Coin Sprite + frame & animation configuration + start animation

    coinSprite = SpriteBuilder(TextureManager::getInstance().getTexture("coin"), GridSize{5, 1})
        .withScale(Scale{1, 1})
        .enableBoundingBox(false)
        .setUniformFrameSize(Size{32, 32})
        .setUniformFrameDuration(120)
        .addAnimation("right-spinning", {0, 1, 2, 3, 4})
        .addAnimation("left-spinning", {4, 3, 2, 1, 0})
        .build();

    coinSprite->playAnimation("left-spinning");

    return true;
}

void Game::initSystems()
{
    // Init audio system
    AudioManager::getInstance().init(this);
    AudioManager::getInstance().addChannel("channel_1");
    AudioManager::getInstance().addChannel("channel_2");

    // Init text rendering system
    TextRenderer::getInstance().init(renderer, "assets/fonts/prstartk.ttf");

    // Init Texture management system
    TextureManager::getInstance().init(renderer);

    // Init grid
    mainGrid = Grid(15, 20, 32);
}

void Game::loadAssets()
{
    // Load sounds & music
    AudioManager::getInstance().loadMusic("clouds", "assets/sounds/clouds.mp3");
    AudioManager::getInstance().loadSound("fairy-magic-wand", "assets/sounds/fairy-magic-wand.wav");
    AudioManager::getInstance().loadSound("magic-church-bell", "assets/sounds/magic-church-bell.mp3");
    AudioManager::getInstance().loadSound("menu-click", "assets/sounds/menu-click.mp3");

    // Load images
    TextureManager::getInstance().load("green-gem", "assets/images/green-gem.png");
    TextureManager::getInstance().load("fire", "assets/images/fire.png");
    TextureManager::getInstance().load("coin", "assets/images/coin.png");

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

    fireSprite->update();
    coinSprite->update();

    if (InputHandler::getInstance().getLastKeyPressed() == SDL_SCANCODE_P)
    {
        coinSprite->pauseAnimation();
    }

    if (InputHandler::getInstance().getLastKeyPressed() == SDL_SCANCODE_N)
    {
        coinSprite->resumeAnimation();
    }

}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0x18, 0x21, 0x28, 0xFF);
    SDL_RenderClear(renderer);

    mainGrid.drawLines(renderer);


    fireSprite->render(renderer, Vector2D{6, 4});

    coinSprite->render(renderer, Vector2D{10, 10});

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