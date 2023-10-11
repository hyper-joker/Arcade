/*
** EPITECH PROJECT, 2023
** arcade
** File description:
**
*/

#pragma once
#include <vector>
#include <string>
#include <array>

namespace Arcade {
    enum MouseEvent {
        rmbPressed = 0,
        rmbReleased,
        lmbPressed,
        lmbReleased
    };

    enum Color {
        BLACK = 0,
        WHITE,
        RED,
        BLUE,
        YELLOW,
        PURPLE,
        ORANGE,
        GREEN,
        CYAN,
        DARK_RED,
        DARK_BLUE,
        DARK_YELLOW,
        DARK_PURPLE,
        DARK_ORANGE,
        DARK_GREEN
    };
    enum Shape {
        RECTANGLE = 0,
        CIRCLE,
        TEXT,
        USERNAME,
        NONE
    };
    enum InputAction {
        UP = 0,
        DOWN,
        RIGHT,
        LEFT,
        BUTTON1,
        BUTTON2,
        BUTTON3,
        ENTER,
        PAUSE,
        QUIT
    };
    enum Direction {
        NORTH,
        SOUTH,
        WEST,
        EAST
    };

    struct MouseInput {
        std::pair<int, int> mousePos;
        MouseEvent event;
    };

    struct BoardCell {
        Color shapeColor;
        Shape shape;
        std::pair<float, float> shapeSize;
        std::string textOrPath;
        Direction spriteDirection;
    };
}
