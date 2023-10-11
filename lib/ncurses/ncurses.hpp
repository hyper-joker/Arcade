/*
** EPITECH PROJECT, 2023
** main.cpp$
** File description:
** main.cpp$
*/

#include <iostream>
#include <ncurses.h>
#include "../../src/ADisplayModule.hpp"

class Ncurses : public Arcade::ADisplayModule {
public:
    Ncurses();
    ~Ncurses();
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
};
