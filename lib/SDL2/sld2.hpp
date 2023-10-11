/*
** EPITECH PROJECT, 2023
** main.cpp$
** File description:
** main.cpp$
*/

#include <iostream>
#include <vector>
#include <array>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../../src/ADisplayModule.hpp"

#define SCREEN_HEIGHT 1080
#define SCREEN_WIDTH 1920
#define CELL_SIZE 16

class SLD2 : public Arcade::ADisplayModule {
public:
    SLD2();
    ~SLD2();
    void initScreen() override;
    void destroyScreen() override;
    void drawRectangle(int posX, int posY, float width, float height, Arcade::Color color, Arcade::Direction direction, std::string textOrPath) override;
    void drawCircle(int posX, int posY, float width, float height, Arcade::Color color, Arcade::Direction direction, std::string textOrPath) override;
    void drawText(int posX, int posY, float width, float height, Arcade::Color color, Arcade::Direction direction, std::string textOrPath) override;
    void cleanScreen() override;
    void drawScreen() override;
    std::vector<int> getInputPressed() override;
    std::vector<Arcade::MouseInput> getMousePressed() override;
    void setColors();
private:
    std::vector<int> _inputPressed;
    std::vector<Arcade::MouseInput> _mousePressed;
    std::array<std::string, 60> _board;
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    TTF_Font *_font;
    int _fontsize;
};
