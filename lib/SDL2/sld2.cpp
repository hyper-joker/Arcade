/*
** EPITECH PROJECT, 2023
** main.cpp$
** File description:
** main.cpp$
*/

#include "sld2.hpp"

SLD2::SLD2()
{

}

SLD2::~SLD2()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void SLD2::initScreen()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    _window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    _font = TTF_OpenFont("./assets/neon_pixel-7.ttf", 24);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    SDL_RenderPresent(_renderer);
}

void SLD2::destroyScreen()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void SLD2::drawRectangle(int posX, int posY, float width, float height, Arcade::Color color, Arcade::Direction direction, std::string textOrPath)
{
    SDL_Rect rect = {
            static_cast<int>((SCREEN_WIDTH / 2 - 40 * CELL_SIZE) + posX * CELL_SIZE),
            static_cast<int>(posY * CELL_SIZE),
            static_cast<int>(width * CELL_SIZE),
            static_cast<int>(height * CELL_SIZE)
    };
    (void)direction;
    (void)textOrPath;

    switch (color) {
        case Arcade::Color::BLACK:
            SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::BLUE:
            SDL_SetRenderDrawColor(_renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::CYAN:
            SDL_SetRenderDrawColor(_renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::GREEN:
            SDL_SetRenderDrawColor(_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::ORANGE:
            SDL_SetRenderDrawColor(_renderer, 230, 126, 34, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::PURPLE:
            SDL_SetRenderDrawColor(_renderer, 142, 68, 173, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::RED:
            SDL_SetRenderDrawColor(_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::WHITE:
            SDL_SetRenderDrawColor(_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::YELLOW:
            SDL_SetRenderDrawColor(_renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::DARK_RED:
            SDL_SetRenderDrawColor(_renderer, 128, 0, 0, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::DARK_BLUE:
            SDL_SetRenderDrawColor(_renderer, 0, 0, 128, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::DARK_GREEN:
            SDL_SetRenderDrawColor(_renderer, 0, 128, 0, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::DARK_YELLOW:
            SDL_SetRenderDrawColor(_renderer, 128, 128, 0, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::DARK_ORANGE:
            SDL_SetRenderDrawColor(_renderer, 128, 64, 0, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::DARK_PURPLE:
            SDL_SetRenderDrawColor(_renderer, 128, 0, 128, SDL_ALPHA_OPAQUE);
            break;
        default:
            break;
    }

    SDL_RenderFillRect(_renderer, &rect);
}

void SLD2::drawCircle(int posX, int posY, float width, float height, Arcade::Color color, Arcade::Direction direction, std::string textOrPath)
{
    (void) direction;
    (void) textOrPath;
    (void) height;
    float radius = width;

    switch (color) {
        case Arcade::Color::BLACK:
            SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::BLUE:
            SDL_SetRenderDrawColor(_renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::CYAN:
            SDL_SetRenderDrawColor(_renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::GREEN:
            SDL_SetRenderDrawColor(_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::RED:
            SDL_SetRenderDrawColor(_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::WHITE:
            SDL_SetRenderDrawColor(_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::YELLOW:
            SDL_SetRenderDrawColor(_renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::ORANGE:
            SDL_SetRenderDrawColor(_renderer, 230, 126, 34, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::PURPLE:
            SDL_SetRenderDrawColor(_renderer, 142, 68, 173, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::DARK_RED:
            SDL_SetRenderDrawColor(_renderer, 128, 0, 0, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::DARK_BLUE:
            SDL_SetRenderDrawColor(_renderer, 0, 0, 128, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::DARK_GREEN:
            SDL_SetRenderDrawColor(_renderer, 0, 128, 0, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::DARK_YELLOW:
            SDL_SetRenderDrawColor(_renderer, 128, 128, 0, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::DARK_ORANGE:
            SDL_SetRenderDrawColor(_renderer, 128, 64, 0, SDL_ALPHA_OPAQUE);
            break;
        case Arcade::Color::DARK_PURPLE:
            SDL_SetRenderDrawColor(_renderer, 128, 0, 128, SDL_ALPHA_OPAQUE);
            break;
        default:
            break;
    }

    int centerX = (SCREEN_WIDTH / 2 - 40 * CELL_SIZE) + posX * CELL_SIZE + CELL_SIZE / 2;
    int centerY = posY * CELL_SIZE + CELL_SIZE / 2;
    for (int x = -radius * 10; x <= radius * 10; x++) {
        int theight = (int)sqrt(radius * radius * 100 - x * x);
        for (int y = -theight; y <= theight; y++) {
            SDL_RenderDrawPoint(_renderer, centerX + x, centerY + y);
        }
    }
}

void SLD2::drawText(int posX, int posY, float width, float height, Arcade::Color color, Arcade::Direction direction, std::string textOrPath)
{
    SDL_Color sdlColor;
    if (textOrPath.c_str() == nullptr)
        return;
    (void) width;
    (void) height;
    (void) direction;
    switch (color) {
        case Arcade::Color::BLACK:
            sdlColor = { 0, 0, 0, 255 };
            break;
        case Arcade::Color::WHITE:
            sdlColor = { 255, 255, 255, 255 };
            break;
        case Arcade::Color::RED:
            sdlColor = { 255, 0, 0, 255 };
            break;
        case Arcade::Color::BLUE:
            sdlColor = { 0, 0, 255, 255 };
            break;
        case Arcade::Color::YELLOW:
            sdlColor = { 255, 255, 0, 255 };
            break;
        case Arcade::Color::PURPLE:
            sdlColor = { 128, 0, 128, 255 };
            break;
        case Arcade::Color::GREEN:
            sdlColor = { 0, 128, 0, 255 };
            break;
        case Arcade::Color::CYAN:
            sdlColor = { 0, 255, 255, 255 };
            break;
        case Arcade::Color::ORANGE:
            sdlColor = { 255, 165, 0, 255};
            break;
        case Arcade::Color::DARK_RED:
            sdlColor = { 128, 0, 0, 255};
            break;
        case Arcade::Color::DARK_BLUE:
            sdlColor = { 0, 0, 128, 255};
            break;
        case Arcade::Color::DARK_GREEN:
            sdlColor = { 0, 128, 0, 255};
            break;
        case Arcade::Color::DARK_YELLOW:
            sdlColor = { 128, 128, 0, 255};
            break;
        case Arcade::Color::DARK_ORANGE:
            sdlColor = { 128, 64, 0, 255};
            break;
        case Arcade::Color::DARK_PURPLE:
            sdlColor = { 128, 0, 128, 255};
            break;
    }
    SDL_Surface *surface = TTF_RenderText_Solid(_font, textOrPath.c_str(), sdlColor);
    if (surface == nullptr) {
        return;
    }
    SDL_Texture *message = SDL_CreateTextureFromSurface(_renderer, surface);

    SDL_Rect Message_rect;
    Message_rect.x = (SCREEN_WIDTH / 2 - 40 * CELL_SIZE) + posX * CELL_SIZE;
    Message_rect.y = posY * CELL_SIZE;
    Message_rect.w = 10; // controls the width of the rect
    Message_rect.h = 20; // controls the height of the rect

    for (int i = 1; textOrPath.c_str()[i] != 0; i++) {
        Message_rect.w += 10;
        if (textOrPath.c_str()[i] == '\n')
            Message_rect.h += 20;
    }
    SDL_RenderCopy(_renderer, message, NULL, &Message_rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);
}

void SLD2::cleanScreen()
{
    // Clear the renderer with black color
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_renderer);

    // Handle events until there are none left in the queue
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                destroyScreen();
                break;
            default:
                break;
        }
    }
}

void SLD2::drawScreen()
{
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_UpdateWindowSurface(_window);
    SDL_RenderPresent(_renderer);
}

std::vector<int> SLD2::getInputPressed()
{
    std::vector<int> inputs;
    inputs.clear();

    const Uint8* state = SDL_GetKeyboardState(nullptr);
    if (SDL_GetKeyboardFocus() != _window)
        return inputs;

    for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
        if (state[i]) {
            if (i == SDL_SCANCODE_A) {
                inputs.push_back('q');
            } else if (i == SDL_SCANCODE_B) {
                inputs.push_back('b');
            } else if (i == SDL_SCANCODE_C) {
                inputs.push_back('c');
            } else if (i == SDL_SCANCODE_D) {
                inputs.push_back('d');
            } else if (i == SDL_SCANCODE_E) {
                inputs.push_back('e');
            } else if (i == SDL_SCANCODE_F) {
                inputs.push_back('f');
            } else if (i == SDL_SCANCODE_G) {
                inputs.push_back('g');
            } else if (i == SDL_SCANCODE_H) {
                inputs.push_back('h');
            } else if (i == SDL_SCANCODE_I) {
                inputs.push_back('i');
            } else if (i == SDL_SCANCODE_J) {
                inputs.push_back('j');
            } else if (i == SDL_SCANCODE_K) {
                inputs.push_back('k');
            } else if (i == SDL_SCANCODE_L) {
                inputs.push_back('l');
            } else if (i == SDL_SCANCODE_SEMICOLON) {
                inputs.push_back('m');
            } else if (i == SDL_SCANCODE_N) {
                inputs.push_back('n');
            } else if (i == SDL_SCANCODE_O) {
                inputs.push_back('o');
            } else if (i == SDL_SCANCODE_P) {
                inputs.push_back('p');
            } else if (i == SDL_SCANCODE_Q) {
                inputs.push_back('a');
            } else if (i == SDL_SCANCODE_R) {
                inputs.push_back('r');
            } else if (i == SDL_SCANCODE_S) {
                inputs.push_back('s');
            } else if (i == SDL_SCANCODE_T) {
                inputs.push_back('t');
            } else if (i == SDL_SCANCODE_U) {
                inputs.push_back('u');
            } else if (i == SDL_SCANCODE_V) {
                inputs.push_back('v');
            } else if (i == SDL_SCANCODE_W) {
                inputs.push_back('z');
            } else if (i == SDL_SCANCODE_X) {
                inputs.push_back('x');
            } else if (i == SDL_SCANCODE_Y) {
                inputs.push_back('y');
            } else if (i == SDL_SCANCODE_Z) {
                inputs.push_back('w');
            } else if (i == SDL_SCANCODE_ESCAPE) {
                inputs.push_back(27);
            } else if (i == SDL_SCANCODE_SPACE) {
                inputs.push_back(32);
            } else if (i == SDL_SCANCODE_RETURN) {
                inputs.push_back(10);
            }
        }
    }

    return inputs;
}

std::vector<Arcade::MouseInput> SLD2::getMousePressed()
{
    std::vector<Arcade::MouseInput> mouseInputs;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            Arcade::MouseInput mouseInput;
            mouseInput.mousePos = std::make_pair(event.button.x, event.button.y);
            switch (event.button.button) {
                case SDL_BUTTON_RIGHT:
                    mouseInput.event = Arcade::MouseEvent::rmbPressed;
                break;
                case SDL_BUTTON_LEFT:
                    mouseInput.event = Arcade::MouseEvent::lmbPressed;
                break;
                default:
                    break;
            }
            mouseInputs.push_back(mouseInput);
        } else if (event.type == SDL_MOUSEBUTTONUP) {
            Arcade::MouseInput mouseInput;
            mouseInput.mousePos = std::make_pair(event.button.x, event.button.y);
            switch (event.button.button) {
                case SDL_BUTTON_RIGHT:
                    mouseInput.event = Arcade::MouseEvent::rmbReleased;
                    break;
                case SDL_BUTTON_LEFT:
                    mouseInput.event = Arcade::MouseEvent::lmbReleased;
                    break;
                default:
                    break;
            }
            mouseInputs.push_back(mouseInput);
        }
    }
    return mouseInputs;
}

extern "C" Arcade::IDisplayModule* entryDisplay()
{
    return new SLD2;
}
