/*
** EPITECH PROJECT, 2023
** main.cpp$
** File description:
** main.cpp$
*/

#include <iostream>
#include <stdlib.h>
#include "Menu.hpp"

Menu::Menu()
{
    _counterColor = 0;
    _color = 0;
    _blip = 0;
    _colorsPalette[0] = Arcade::Color::YELLOW;
    _colorsPalette[1] = Arcade::Color::GREEN;
    _colorsPalette[2] = Arcade::Color::CYAN;
    _colorsPalette[3] = Arcade::Color::BLUE;
    _colorsPalette[4] = Arcade::Color::PURPLE;
    _colorsPalette[5] = Arcade::Color::RED;
}

Menu::~Menu()
{

}

void Menu::onInputPressed(Arcade::InputAction input, bool isPressed)
{
    (void)input;
    (void)isPressed;
}

void Menu::setText(int x, int y, std::string text)
{
    _board[y][x].shape = Arcade::TEXT;
    _board[y][x].shapeColor = Arcade::WHITE;
    _board[y][x].textOrPath = text;
}

void Menu::setDancer(int x, int y, int pattern)
{
    _board[y][x].shape = Arcade::TEXT;
    _board[y][x].shapeColor = Arcade::WHITE;
    if ((_blip + pattern) % 2 == 0)
        _board[y][x].textOrPath = "  o/ ";
    else
        _board[y][x].textOrPath = " \\o  ";
    _board[y + 1][x].shape = Arcade::TEXT;
    _board[y + 1][x].shapeColor = Arcade::WHITE;
    if ((_blip + pattern) % 2 == 1)
        _board[y + 1][x].textOrPath = "  |\\ ";
    else
        _board[y + 1][x].textOrPath = " /|  ";
    _board[y + 2][x].shape = Arcade::TEXT;
    _board[y + 2][x].shapeColor = Arcade::WHITE;
    if ((_blip + pattern) % 2 == 1)
        _board[y + 2][x].textOrPath = " (\\ ";
    else
        _board[y + 2][x].textOrPath = "  /)  ";
}

void Menu::setStar(int x, int y, int pattern)
{
    _board[y][x].shape = Arcade::TEXT;
    _board[y][x].shapeColor = _colorsPalette[(_color + y + x) % 6];
    if ((_blip + pattern) % 2 == 0)
        _board[y][x].textOrPath = ".";
    else
        _board[y][x].textOrPath = "*";
}

void Menu::drawStar()
{
    setStar(20, 11, 0);
    setStar(21, 14, 1);
    setStar(24, 15, 1);
    setStar(17, 4, 0);
    setStar(22, 3, 1);
    setStar(19, 1, 1);
    setStar(33, 1, 0);
    setStar(37, 2, 1);
    setStar(34, 4, 1);
    setStar(38, 5, 0);
    setStar(25, 7, 0);
    setStar(26, 4, 1);
    setStar(29, 3, 1);
    setStar(49, 5, 0);
    setStar(54, 7, 1);
    setStar(51, 9, 1);
    setStar(55, 9, 0);
    setStar(52, 8, 0);
    setStar(41, 13, 1);
    setStar(44, 12, 1);
    setStar(48, 11, 0);
    setStar(28, 11, 0);
    setStar(32, 12, 1);
    setStar(29, 14, 1);
    setStar(33, 15, 0);
    setStar(54, 2, 1);
    setStar(38, 3, 0);
    setStar(42, 4, 1);
    setStar(39, 6, 1);
    setStar(43, 7, 0);
    setStar(44, 2, 0);
    setStar(48, 3, 1);
    setStar(45, 5, 1);
}

void Menu::drawTitle()
{
    _board[6][25].shape = Arcade::TEXT;
    _board[6][25].shapeColor = _colorsPalette[(_color + 0) % 6];
    _board[6][25].textOrPath = "   @@@@     @@@@    @@@@@    @@@@    @@@@@    @@@@@";
    _board[7][25].shape = Arcade::TEXT;
    _board[7][25].shapeColor = _colorsPalette[(_color + 1) % 6];
    _board[7][25].textOrPath = "  @@  @@   @@  @@  @@   @@  @@  @@   @@  @@  @@    ";
    _board[8][25].shape = Arcade::TEXT;
    _board[8][25].shapeColor = _colorsPalette[(_color + 2) % 6];
    _board[8][25].textOrPath = "  @@@@@@   @@@@@   @@       @@@@@@   @@  @@  @@@@@@";
    _board[9][25].shape = Arcade::TEXT;
    _board[9][25].shapeColor = _colorsPalette[(_color + 3) % 6];
    _board[9][25].textOrPath = "  @@  @@   @@  @@  @@   @@  @@  @@   @@  @@  @@     ";
    _board[10][25].shape = Arcade::TEXT;
    _board[10][25].shapeColor = _colorsPalette[(_color + 4) % 6];
    _board[10][25].textOrPath = "  @@  @@   @@   @@  @@@@@   @@  @@   @@@@@    @@@@@";
}

void Menu::drawBox(int x, int y, int width, int height)
{
    for (int i = 1; i < width; i += 1) {
        _board[y][x + i].shape = Arcade::TEXT;
        _board[y][x + i].shapeColor = Arcade::WHITE;
        _board[y][x + i].textOrPath = "--";
        _board[y + height][x + i].shape = Arcade::TEXT;
        _board[y + height][x + i].shapeColor = Arcade::WHITE;
        _board[y + height][x + i].textOrPath = "--";
    }
    for (int i = 1; i < height; i += 1) {
        _board[y + i][x].shape = Arcade::TEXT;
        _board[y + i][x].shapeColor = Arcade::WHITE;
        _board[y + i][x].textOrPath = "|";
        _board[y + i][x + width].shape = Arcade::TEXT;
        _board[y + i][x + width].shapeColor = Arcade::WHITE;
        _board[y + i][x + width].textOrPath = "|";
    }
    _board[y][x].shape = Arcade::TEXT;
    _board[y][x].shapeColor = Arcade::WHITE;
    _board[y][x].textOrPath = "+-";
    _board[y][x + width].shape = Arcade::TEXT;
    _board[y][x + width].shapeColor = Arcade::WHITE;
    _board[y][x + width].textOrPath = "+";
    _board[y + height][x].shape = Arcade::TEXT;
    _board[y + height][x].shapeColor = Arcade::WHITE;
    _board[y + height][x].textOrPath = "+-";
    _board[y + height][x + width].shape = Arcade::TEXT;
    _board[y + height][x + width].shapeColor = Arcade::WHITE;
    _board[y + height][x + width].textOrPath = "+";
}

void Menu::update(float deltaTime) {
    _counterColor += deltaTime;
    if (_counterColor >= 1.f) {
        _counterColor = 0.f;
        _color = (_color + 1) % 6;
        _blip = (_blip + 1) % 2;
    }

    _board[21][10].shape = Arcade::TEXT;
    _board[21][10].shapeColor = Arcade::YELLOW;
    _board[21][10].textOrPath = "Graphical Displays:";
    drawBox(9, 22, 17, 9);
    for (int i = 0; i < 8; i += 1) {
        std::string text = "GRAPHICAL_TEXT_";
        text += '1' + i;
        setText(10, 23 + i, text);
    }
    _board[21][30].shape = Arcade::TEXT;
    _board[21][30].shapeColor = Arcade::YELLOW;
    _board[21][30].textOrPath = "Games:";
    drawBox(29, 22, 17, 9);
    for (int i = 0; i < 8; i += 1) {
        std::string text = "GAME_TEXT_";
        text += '1' + i;
        setText(30, 23 + i, text);
    }
    _board[18][55].shape = Arcade::TEXT;
    _board[18][55].shapeColor = Arcade::YELLOW;
    _board[18][55].textOrPath = "LeaderBoard:";
    drawBox(54, 19, 15, 21);
    for (int i = 0; i < 20; i += 1) {
        std::string text = "LEADERBOARD_";
        text += '1' + i;
        setText(55, 20 + i, text);
    }
    for (int i = 0; i < 20; i += 1) {
        std::string text = "SCORE_";
        text += '1' + i;
        setText(61, 20 + i, text);
    }
    _board[21][48].shape = Arcade::TEXT;
    _board[21][48].shapeColor = Arcade::YELLOW;
    _board[21][48].textOrPath = "Username:";
    drawBox(48, 22, 4, 2);
    drawStar();
    drawTitle();
    setDancer(20, 7, 0);
    setDancer(23, 11, 1);
    setDancer(49, 12, 0);
    setDancer(56, 4, 1);
}

void __attribute__((constructor)) my_constructor() {

}

void __attribute__((destructor)) my_destructor() {

}

extern "C" Arcade::IGameModule *entryGame() {
    return new Menu;
}
