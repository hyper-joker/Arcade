/*
** EPITECH PROJECT, 2023
** main.cpp$
** File description:
** main.cpp$
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include "../../src/ADisplayModule.hpp"

#define CELL_SIZE 16
#define WINDOW_H 1012
#define WINDOW_W 1800

class SFML : public Arcade::ADisplayModule {
public:
    SFML();
    ~SFML();
    void initScreen() override;
    void destroyScreen() override;
    void drawRectangle(int posX, int posY, float width, float height, Arcade::Color color, Arcade::Direction direction, std::string textOrPath) override;
    void drawCircle(int posX, int posY, float width, float height, Arcade::Color color, Arcade::Direction direction, std::string textOrPath) override;
    void drawText(int posX, int posY, float width, float height, Arcade::Color color, Arcade::Direction direction, std::string textOrPath) override;
    void cleanScreen() override;
    void drawScreen() override;
    std::vector<int> getInputPressed() override;
    std::vector<Arcade::MouseInput> getMousePressed() override;
private:
    std::vector<int> _inputPressed;
    std::vector<Arcade::MouseInput> _mousePressed;
    std::array<std::string, 60> _board;
    sf::RenderWindow* _window;
    sf::Font _font;
    int _fontSize;
};
