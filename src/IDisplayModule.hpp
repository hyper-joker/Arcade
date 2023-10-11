/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** IDisplayModule
*/

#pragma once
#include <array>
#include <string>
#include <vector>
#include "ArcadeDefs.hpp"

namespace Arcade {

    class IDisplayModule {
    public:
        virtual ~IDisplayModule() = 0;
        virtual void initScreen() = 0;
        virtual void destroyScreen() = 0;
        virtual void drawRectangle(int posX, int posY, float width, float height, Color color, Direction direction, std::string textOrPath) = 0;
        virtual void drawCircle(int posX, int posY, float width, float height, Color color, Direction direction, std::string textOrPath) = 0;
        virtual void drawText(int posX, int posY, float width, float height, Color color, Direction direction, std::string textOrPath) = 0;
        virtual void cleanScreen() = 0;
        virtual void drawScreen() = 0;
        virtual std::vector<int> getInputPressed() = 0;
        virtual std::vector<MouseInput> getMousePressed() = 0;
    };
}
