/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** IGameModule
*/

#pragma once
#include <array>
#include <string>
#include "ArcadeDefs.hpp"

namespace Arcade {

    class IGameModule {
    public:
        virtual ~IGameModule() = 0;

        virtual void update(float deltaTime) = 0;
        virtual std::array<std::array<BoardCell, 80>, 60> getBoard() = 0;
        virtual void onInputPressed(InputAction input, bool isPressed) = 0;
        virtual int getActualScore() = 0;
        virtual void onMousePressed(Arcade::MouseInput input) = 0;
    };
}
