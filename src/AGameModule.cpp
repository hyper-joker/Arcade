/*
** EPITECH PROJECT, 2023
** AGameModule.cpp$
** File description:
** AGameModule.cpp$
*/

#include "AGameModule.hpp"

Arcade::AGameModule::AGameModule()
{
    _board = std::array<std::array<Arcade::BoardCell, 80>, 60>();
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 80; j++) {
            _board[i][j].shape = RECTANGLE;
            _board[i][j].shapeSize = {1, 1};
            _board[i][j].shapeColor = BLACK;
        }
    }
    _score = 0;
}

std::array<std::array<Arcade::BoardCell, 80>, 60> Arcade::AGameModule::getBoard()
{
    return _board;
}

int Arcade::AGameModule::getActualScore()
{
    return _score;
}

void Arcade::AGameModule::onMousePressed(Arcade::MouseInput input)
{
    (void)input;
}
