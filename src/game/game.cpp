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


    /////////// Init: TESTING /////////////////////////

    mainGrid = new Grid(15, 20, Size{32, 32});

    GridCell* gridCell = mainGrid->getCell(Vector2D{7, 7});

    if (gridCell)
    {
    bee = new GameObject(gridCell);
    }

    

    bee->buildSprite([](Sprite** sprite) {

        *sprite = SpriteBuilder(TextureManager::getInstance().getTexture("bee"), GridSize{3, 4})
            .withScale(Scale{1, 1})
            .enableBoundingBox(false)
            .setUniformFrameSize(Size{32, 32})
            .setUniformFrameDuration(90)
            .addAnimation("flying_up", {0, 1, 2})
            .addAnimation("flying_left", {3, 4, 5})
            .addAnimation("flying_down", {6, 7, 8})
            .addAnimation("flying_right", {9, 10, 11})
            .build();

        (*sprite)->playAnimation("flying_down");

    });

    /////////// TESTING /////////////////////////


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
    TextureManager::getInstance().load("bee", "assets/images/bee.png");

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

    ///////////////// TESTING /////////////////
    bee->update();

    switch (InputHandler::getInstance().getLastKeyPressed())
    {
        case SDL_SCANCODE_UP:
            bee->move(Direction::DIRECTION_UP);
            break;

        case SDL_SCANCODE_DOWN:
            bee->move(Direction::DIRECTION_DOWN);
            break;

        case SDL_SCANCODE_LEFT:
            bee->move(Direction::DIRECTION_LEFT);
            break;

        case SDL_SCANCODE_RIGHT:
            bee->move(Direction::DIRECTION_RIGHT);
            break;

        default:
            // No movement key pressed or irrelevant key
            break;
    }
    ////////////// TESTING ///////////////////////
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0x18, 0x21, 0x28, 0xFF);
    SDL_RenderClear(renderer);

    /////////// TESTING //////////////////////////

    mainGrid->drawLines(renderer);

    TextRenderer::getInstance().render(
        TextObject{
            "Press UP, DOWN, LEFT or RIGHT arrows", 
            TextStyle{
                12, 
                SDL_Color{0xFF, 0xFF, 0xFF, 0xFF}, SDL_Color{0x00, 0x00, 0x00, 0xFF}
            }
        }, 
        Vector2D{32, 32}
    );
    TextRenderer::getInstance().render(
        TextObject{
            "to control the direction of the bee", 
            TextStyle{
                9, 
                SDL_Color{0xFF, 0xFF, 0xFF, 0xFF}, SDL_Color{0x00, 0x00, 0x00, 0xFF}
            }
        }, 
        Vector2D{32, 54}
    );

    bee->render(renderer);


    //////////////// TESTING ///////////////////////////

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