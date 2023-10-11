/*
** EPITECH PROJECT, 2023
** AGameModule.h$
** File description:
** AGameModule.h$
*/

#pragma once
#include "IGameModule.hpp"

namespace Arcade {
    class AGameModule : public Arcade::IGameModule {
    public :
        AGameModule();
        ~AGameModule() {};
        std::array<std::array<BoardCell, 80>, 60> getBoard() override;
        int getActualScore() override;
        void onMousePressed(Arcade::MouseInput input) override;

    protected:
        std::array<std::array<BoardCell, 80>, 60> _board;
        int _score;
    };
}