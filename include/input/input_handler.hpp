#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <vector>
#include <algorithm>
#include <SDL.h>

#include "game_interface.hpp"
#include "math/vector_2d.hpp"
#include "types/mouse_button.hpp"

class InputHandler
{

private:
    static InputHandler* instance;
    std::vector<bool> mouseButtonsStates;
    Vector2D mousePosition;
    const Uint8* keyStates;
    SDL_Scancode lastKeyPressed;
    std::vector<SDL_Scancode> keyStack;

private:
    InputHandler();
    ~InputHandler();

    // handle keyboard events
    void onKeyDown(SDL_Event& e);
    void onKeyUp(SDL_Event& e);

    // handle mouse events
    void onMouseMove(SDL_Event& e);
    void onMouseButtonDown(SDL_Event& e);
    void onMouseButtonUp(SDL_Event& e);

public:
    InputHandler(const InputHandler&) = delete;
    InputHandler& operator=(const InputHandler&) = delete;

    static InputHandler& getInstance();

    void update(IGame* gameCtx);
    bool getMouseButtonState(MouseButton mouseButton);
    Vector2D getMousePosition();
    bool isKeyDown(SDL_Scancode key);
    SDL_Scancode getLastKeyPressed();

};

#endif