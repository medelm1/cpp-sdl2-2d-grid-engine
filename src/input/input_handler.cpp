#include "input/input_handler.hpp"

InputHandler* InputHandler::instance = nullptr;

InputHandler::InputHandler()
    : mouseButtonsStates(3, false),
      mousePosition(0, 0),
      keyStates(nullptr),
      lastKeyPressed(SDL_SCANCODE_UNKNOWN),
      keyStack()
{

}

InputHandler::~InputHandler()
{
    delete instance;
    instance = nullptr;
}

InputHandler& InputHandler::getInstance()
{
    if (instance == nullptr) {
        instance = new InputHandler();
    }

    return *instance;
}

void InputHandler::onKeyDown(SDL_Event& e)
{
    SDL_Scancode scancode = e.key.keysym.scancode;

    // Add key to stack if not already present
    if (std::find(keyStack.begin(), keyStack.end(), scancode) == keyStack.end()) {
        keyStack.push_back(scancode);
    }
}

void InputHandler::onKeyUp(SDL_Event& e)
{
    SDL_Scancode scancode = e.key.keysym.scancode;

    // Remove key from stack
    auto it =  std::find(keyStack.begin(), keyStack.end(), scancode);
    if (it != keyStack.end()) {
        keyStack.erase(it);
    }
}

// handle mouse events
void InputHandler::onMouseMove(SDL_Event& e)
{
    mousePosition.setX((float) e.motion.x);
    mousePosition.setY((float) e.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event& e)
{
    if (e.button.button == SDL_BUTTON_LEFT) {
        mouseButtonsStates[MouseButton::MOUSE_BUTTON_LEFT] = true;
    }

    if (e.button.button == SDL_BUTTON_MIDDLE) {
        mouseButtonsStates[MouseButton::MOUSE_BUTTON_MIDDLE] = true;
    }

    if (e.button.button == SDL_BUTTON_RIGHT) {
        mouseButtonsStates[MouseButton::MOUSE_BUTTON_RIGHT] = true;
    }
}

void InputHandler::onMouseButtonUp(SDL_Event& e)
{
    if (e.button.button == SDL_BUTTON_LEFT) {
        mouseButtonsStates[MouseButton::MOUSE_BUTTON_LEFT] = false;
    }

    if (e.button.button == SDL_BUTTON_MIDDLE) {
        mouseButtonsStates[MouseButton::MOUSE_BUTTON_MIDDLE] = false;
    }

    if (e.button.button == SDL_BUTTON_RIGHT) {
        mouseButtonsStates[MouseButton::MOUSE_BUTTON_RIGHT] = false;
    }
}

void InputHandler::update(IGame* gameCtx)
{
    SDL_Event event;
    keyStates = SDL_GetKeyboardState(nullptr);

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                gameCtx->quit();
                break;

            case SDL_MOUSEMOTION:
                onMouseMove(event);
                break;
            
            case SDL_MOUSEBUTTONDOWN:
                onMouseButtonDown(event);
                break;

            case SDL_MOUSEBUTTONUP:
                onMouseButtonUp(event);
                break;

            case SDL_KEYDOWN:
                onKeyDown(event);
                break;

            case SDL_KEYUP:
                onKeyUp(event);
                break;
            
            default:
                break;
        }
    }
}

bool InputHandler::getMouseButtonState(MouseButton mouseButton)
{
    return mouseButtonsStates[mouseButton];
}

Vector2D InputHandler::getMousePosition()
{
    return mousePosition;
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
    return keyStates != nullptr && keyStates[key] == 1;
}


SDL_Scancode InputHandler::getLastKeyPressed()
{
    if (!keyStack.empty()) {
        return keyStack.back();
    }

    return SDL_SCANCODE_UNKNOWN;
}