/*
** EPITECH PROJECT, 2023
** main.cpp$
** File description:
** main.cpp$
*/

#include <iostream>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "snake.hpp"

Snake::Snake()
{
    _playerPos = {23, 23};
    _applePos = {37, 26};
    _dead = false;
    _score = 0;

    for (int i = 0; i < 48; i++)
        for (int j = 0; j < 48; j++)
            map[i][j] = TemplateMap[i][j];
    _movement = 0;
    for (int i = (48 * 48) - 1; i > 0; i--) {
        _snakePos[i].x = -1;
        _snakePos[i].y = -1;
    }
    _sizeSnake = 3;
}

Snake::~Snake() noexcept
{

}

void Snake::LastPressed()
{
    against_wall = 0;
    switch (_direction) {
        case 0:
            _playerPos.x -= 1;
            break;
        case 1:
            _playerPos.x += 1;
            break;
        case 3:
                _playerPos.y -= 1;
            break;
        case 2:
                _playerPos.y += 1;
            break;
        default:
            break;
    }

    if (_playerPos.x == _applePos.x && _playerPos.y == _applePos.y) {
        applePos.x = (std::rand() % 46) + 1;
        applePos.y = (std::rand() % 46) + 1;
        _sizeSnake += 1;
        _applePos = {applePos.x, applePos.y};
        _score += 100;
    }
    for (int i = 0; i < _sizeSnake; i++) {
        if (_playerPos.x == _snakePos[i].x &&
            _playerPos.y == _snakePos[i].y) {
            _dead = true;
            _sizeSnake = 0;
        }
    }
    if (map[_playerPos.x][_playerPos.y] == 1) {
        _dead = true;
        _sizeSnake = 0;
    }
}

void Snake::calculatePosSnake()
{
    for (int i = _sizeSnake; i > 0; i--) {
        _snakePos[i].x = _snakePos[i - 1].x;
        _snakePos[i].y = _snakePos[i - 1].y;
    }
    _snakePos[0].x = _playerPos.x;
    _snakePos[0].y = _playerPos.y;
}

void Snake::AddBodyCircle()
{
    for (int i = 0; i < _sizeSnake; i++) {
        if (_snakePos[i].x == -1 && _snakePos[i].y == -1)
            break;
        _board[_snakePos[i].x + 10][_snakePos[i].y + 16].shapeColor =
                Arcade::YELLOW;
        _board[_snakePos[i].x + 10][_snakePos[i].y + 16].shape =
                Arcade::CIRCLE;
        _board[_snakePos[i].x + 10][_snakePos[i].y + 16].shapeSize =
                {0.5, 0.5};
    }
}

void Snake::onInputPressed(Arcade::InputAction input, bool isPressed)
{
    Snake::movement = 0;

    if (isPressed) {
        switch (input) {
            case Arcade::InputAction::UP:
                if (_direction != 1)
                    _direction = 0;
                break;
            case Arcade::InputAction::DOWN:
                if (_direction != 0)
                    _direction = 1;
                break;
            case Arcade::InputAction::LEFT:
                if (_direction != 2)
                    _direction = 3;
                break;
            case Arcade::InputAction::RIGHT:
                if (_direction != 3)
                    _direction = 2;
                break;
            default:
                break;
        }
    }
}

void Snake::MapDraw()
{
    for (int i = 0; i < 48; i++) {
        for (int j = 0; j < 48; j++) {
            if (map[i][j] == 1) {
                _board[i + 10][j + 16].shapeColor = Arcade::BLUE;
            } else
                _board[i + 10][j + 16].shapeColor = Arcade::BLACK;
            _board[i + 10][j + 16].shape = Arcade::RECTANGLE;
        }
    }

    AddBodyCircle();

    _board[_applePos.x + 10][_applePos.y + 16].shapeColor = Arcade::RED;
    _board[_applePos.x + 10][_applePos.y + 16].shape = Arcade::Shape::CIRCLE;
    _board[_applePos.x + 10][_applePos.y + 16].shapeSize = {0.5, 0.5};

    _board[_playerPos.x + 10][_playerPos.y + 16].shapeColor = Arcade::YELLOW;
    _board[_playerPos.x + 10][_playerPos.y + 16].shape = Arcade::Shape::CIRCLE;
    _board[_playerPos.x + 10][_playerPos.y + 16].shapeSize = {1, 1};
}

void Snake::gameOver()
{
    _playerPos = {37, 23};
    _score = 0;
    _movement = 0;
    for (int i = (48 * 48) - 1; i > 0; i--) {
        _snakePos[i].x = -1;
        _snakePos[i].y = -1;
    }
    _sizeSnake = 3;
}

void Snake::update(float deltaTime)
{
    _movement += deltaTime;
    if (_movement >= 0.1) {
        _movement = 0;
        calculatePosSnake();
        LastPressed();
    }

    if (_dead) {
        gameOver();
        _dead = false;
    }
    MapDraw();

    _board[2][30].shape = Arcade::TEXT;
    _board[2][30].shapeColor = Arcade::WHITE;
    _board[2][30].textOrPath = "HIGH SCORE: " + std::to_string(_score);
    _board[2][30].shapeSize.first = 20;
    _board[2][30].shapeSize.second = 2;
}

void __attribute__((constructor)) my_constructor()
{

}

void __attribute__((destructor)) my_destructor()
{

}

extern "C" Arcade::IGameModule *entryGame()
{
    return new Snake;
}
