/*
** EPITECH PROJECT, 2023
** main.cpp$
** File description:
** main.cpp$
*/

#include <iostream>
#include "../AGameModule.hpp"

class Menu : public Arcade::AGameModule {
public:
    Menu();
    ~Menu();
    void update(float deltaTime) override;
    void onInputPressed(Arcade::InputAction input, bool isPressed) override;
    void setText(int x, int y, std::string text);
    void setDancer(int x, int y, int pattern);
    void setStar(int x, int y, int pattern);
    void drawStar();
    void drawTitle();
    void drawBox(int x, int y, int width, int height);
private:
    int _color;
    float _counterColor;
    int _blip;
    Arcade::Color _colorsPalette[6];
};
