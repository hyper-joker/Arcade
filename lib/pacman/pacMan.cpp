/*
** EPITECH PROJECT, 2023
** main.cpp$
** File description:
** main.cpp$
*/

#include <iostream>
#include <random>
#include <algorithm>
#include "pacMan.hpp"

PacMan::PacMan()
{
    _playerPos = {37, 23};
    _board[_playerPos.x + 10][_playerPos.y + 16].shapeColor = Arcade::YELLOW;
    _board[_playerPos.x + 10][_playerPos.y + 16].shape = Arcade::Shape::CIRCLE;

    _redGhostPos = {24, 25};
    _cooldownRedGhost = 10;
    _board[_redGhostPos.x + 10][_redGhostPos.y + 16].shapeColor = Arcade::RED;
    _board[_redGhostPos.x + 10][_redGhostPos.y + 16].shape = Arcade::Shape::RECTANGLE;

    _pinkGhostPos = {24, 24};
    _cooldownPinkGhost = 20;
    _board[_pinkGhostPos.x + 10][_pinkGhostPos.y + 16].shapeColor = Arcade::RED;
    _board[_pinkGhostPos.x + 10][_pinkGhostPos.y + 16].shape = Arcade::Shape::RECTANGLE;

    _blueGhostPos = {24, 23};
    _cooldownBlueGhost = 30;
    _board[_blueGhostPos.x + 10][_blueGhostPos.y + 16].shapeColor = Arcade::RED;
    _board[_blueGhostPos.x + 10][_blueGhostPos.y + 16].shape = Arcade::Shape::RECTANGLE;

    _orangeGhostPos = {24, 22};
    _cooldownOrangeGhost = 40;
    _board[_orangeGhostPos.x + 10][_orangeGhostPos.y + 16].shapeColor = Arcade::RED;
    _board[_orangeGhostPos.x + 10][_orangeGhostPos.y + 16].shape = Arcade::Shape::RECTANGLE;

    for(int i = 0; i < 48; i++)
        for(int j = 0; j < 48; j++) {
            if (TemplateMap[i][j] == 7)
                map[i][j] = PELLET;
            else if (TemplateMap[i][j] == 8)
                map[i][j] = PELLET_TAKEN;
            else if (TemplateMap[i][j] == 1)
                map[i][j] = WALL;
            else if (TemplateMap[i][j] == 9)
                map[i][j] = GHOST_PATH;
            else if (TemplateMap[i][j] == 0)
                map[i][j] = EMPTY;
            else if (TemplateMap[i][j] == 'o')
                map[i][j] = BIG_PALLET;
            else
                map[i][j] = PELLET_TAKEN;
        }
    resetPathFindingBoard();
    _movement = 0;
    _orangeGhostDelay = 0;
    _orangeRandomDirection = _orangeGhostPos;
    _Alive_blue = true;
    _Alive_red = true;
    _Alive_orange = true;
    _Alive_pink = true;
    _WeakCooldown_blue = 0;
    _WeakCooldown_red = 0;
    _WeakCooldown_orange = 0;
    _WeakCooldown_pink = 0;
    lives = 3;
    _spawnLEFT = {24, 0};
    _spawnRIGHT = {24, 47};
}

PacMan::~PacMan() noexcept
{

}

void PacMan::LastPressed()
{
    switch (_direction) {
        case 0:
            if (map[_playerPos.x - 1][_playerPos.y] == PELLET || map[_playerPos.x - 1][_playerPos.y] == PELLET_TAKEN || map[_playerPos.x - 1][_playerPos.y] == BIG_PALLET) {
                _board[_playerPos.x + 10][_playerPos.y + 16].shapeColor = Arcade::BLACK;
                _board[_playerPos.x + 10][_playerPos.y + 16].shape = Arcade::Shape::RECTANGLE;
                _playerPos.x -= 1;
            }
            break;
        case 1:
            if (map[_playerPos.x + 1][_playerPos.y] == PELLET || map[_playerPos.x + 1][_playerPos.y] == PELLET_TAKEN || map[_playerPos.x + 1][_playerPos.y] == BIG_PALLET) {
                _board[_playerPos.x + 10][_playerPos.y + 16].shapeColor = Arcade::BLACK;
                _board[_playerPos.x + 10][_playerPos.y + 16].shape = Arcade::Shape::RECTANGLE;
                _playerPos.x += 1;
            }
            break;
        case 3:
            if (map[_playerPos.x][_playerPos.y - 1]== PELLET || map[_playerPos.x][_playerPos.y - 1] == PELLET_TAKEN || map[_playerPos.x][_playerPos.y - 1] == BIG_PALLET) {
                _board[_playerPos.x + 10][_playerPos.y + 16].shapeColor = Arcade::BLACK;
                _board[_playerPos.x + 10][_playerPos.y + 16].shape = Arcade::Shape::RECTANGLE;
                _playerPos.y -= 1;
            }
            break;
        case 2:
            if (map[_playerPos.x][_playerPos.y + 1] == PELLET || map[_playerPos.x][_playerPos.y + 1] == PELLET_TAKEN || map[_playerPos.x][_playerPos.y + 1] == BIG_PALLET) {
                _board[_playerPos.x + 10][_playerPos.y + 16].shapeColor = Arcade::BLACK;
                _board[_playerPos.x + 10][_playerPos.y + 16].shape = Arcade::Shape::RECTANGLE;
                _playerPos.y += 1;
            }
            break;
        default:
            break;
   }
    if (map[_playerPos.x][_playerPos.y] == PELLET)
        _score += 10;
    if (map[_playerPos.x][_playerPos.y] == BIG_PALLET) {
        _score += 50;
        _WeakCooldown_orange = 50;
        _WeakCooldown_blue = 50;
        _WeakCooldown_red = 50;
        _WeakCooldown_pink = 50;
    }
    map[_playerPos.x][_playerPos.y] = PELLET_TAKEN;
}

void PacMan::onInputPressed(Arcade::InputAction input, bool isPressed)
{
    PacMan::movement = 0;

    if (isPressed) {
            switch (input) {
                case Arcade::InputAction::UP:
                    if (map[_playerPos.x - 1][_playerPos.y] == PELLET || map[_playerPos.x - 1][_playerPos.y] == PELLET_TAKEN || map[_playerPos.x - 1][_playerPos.y] == BIG_PALLET)
                        _direction = 0;
                    break;
                case Arcade::InputAction::DOWN:
                    if (map[_playerPos.x + 1][_playerPos.y] == PELLET || map[_playerPos.x + 1][_playerPos.y] == PELLET_TAKEN || map[_playerPos.x + 1][_playerPos.y] == BIG_PALLET)
                        _direction = 1;
                    break;
                case Arcade::InputAction::LEFT:
                    if (map[_playerPos.x][_playerPos.y - 1]== PELLET || map[_playerPos.x][_playerPos.y - 1] == PELLET_TAKEN || map[_playerPos.x][_playerPos.y - 1] == BIG_PALLET)
                        _direction = 3;
                    break;
                case Arcade::InputAction::RIGHT:
                    if (map[_playerPos.x][_playerPos.y + 1] == PELLET || map[_playerPos.x][_playerPos.y + 1] == PELLET_TAKEN || map[_playerPos.x][_playerPos.y + 1] == BIG_PALLET)
                        _direction = 2;
                    break;
                default:
                    break;
            }
    }
}

void PacMan::MapDraw()
{
    for (int i = 0; i < 48; i++) {
        for (int j = 0; j < 48; j++) {
            if (map[i][j] == WALL) {
                _board[i + 10][j + 16].shape = Arcade::RECTANGLE;
                _board[i + 10][j + 16].shapeSize = {1, 1};
                _board[i + 10][j + 16].shapeColor = Arcade::BLUE;
            } else if (map[i][j] == PELLET) {
                _board[i + 10][j + 16].shape = Arcade::Shape::CIRCLE;
                _board[i + 10][j + 16].shapeSize = {0.5, 0.5};
                _board[i + 10][j + 16].shapeColor = Arcade::YELLOW;
            } else if (map[i][j] == BIG_PALLET) {
                _board[i + 10][j + 16].shape = Arcade::Shape::CIRCLE;
                _board[i + 10][j + 16].shapeSize = {0.75, 0.75};
                _board[i + 10][j + 16].shapeColor = Arcade::WHITE;
            } else {
                _board[i + 10][j + 16].shape = Arcade::RECTANGLE;
                _board[i + 10][j + 16].shapeSize = {1, 1};
                _board[i + 10][j + 16].shapeColor = Arcade::BLACK;
            }
        }
    }
    _board[_redGhostPos.x + 10][_redGhostPos.y + 16].shape = Arcade::Shape::RECTANGLE;
    _board[_redGhostPos.x + 10][_redGhostPos.y + 16].shapeSize = {1, 1};
    if (_WeakCooldown_red > 0)
        _board[_redGhostPos.x + 10][_redGhostPos.y + 16].shapeColor = Arcade::BLUE;
    else
        _board[_redGhostPos.x + 10][_redGhostPos.y + 16].shapeColor = Arcade::RED;
    if (!_Alive_red) {
        _board[_redGhostPos.x + 10][_redGhostPos.y + 16].shape = Arcade::Shape::CIRCLE;
        _board[_redGhostPos.x + 10][_redGhostPos.y + 16].shapeSize = {0.8f, 0.8f};
        _board[_redGhostPos.x + 10][_redGhostPos.y + 16].shapeColor = Arcade::WHITE;
    }

    _board[_pinkGhostPos.x + 10][_pinkGhostPos.y + 16].shape = Arcade::Shape::RECTANGLE;
    _board[_pinkGhostPos.x + 10][_pinkGhostPos.y + 16].shapeSize = {1, 1};
    if (_WeakCooldown_pink > 0)
        _board[_pinkGhostPos.x + 10][_pinkGhostPos.y + 16].shapeColor = Arcade::BLUE;
    else
        _board[_pinkGhostPos.x + 10][_pinkGhostPos.y + 16].shapeColor = Arcade::PURPLE;
    if (!_Alive_pink) {
        _board[_pinkGhostPos.x + 10][_pinkGhostPos.y + 16].shape = Arcade::Shape::CIRCLE;
        _board[_pinkGhostPos.x + 10][_pinkGhostPos.y + 16].shapeSize = {0.8f, 0.8f};
        _board[_pinkGhostPos.x + 10][_pinkGhostPos.y + 16].shapeColor = Arcade::WHITE;
    }

    _board[_blueGhostPos.x + 10][_blueGhostPos.y + 16].shape = Arcade::Shape::RECTANGLE;
    _board[_blueGhostPos.x + 10][_blueGhostPos.y + 16].shapeSize = {1, 1};
    if (_WeakCooldown_blue > 0)
        _board[_blueGhostPos.x + 10][_blueGhostPos.y + 16].shapeColor = Arcade::BLUE;
    else
        _board[_blueGhostPos.x + 10][_blueGhostPos.y + 16].shapeColor = Arcade::CYAN;
    if (!_Alive_blue) {
        _board[_blueGhostPos.x + 10][_blueGhostPos.y + 16].shape = Arcade::Shape::CIRCLE;
        _board[_blueGhostPos.x + 10][_blueGhostPos.y + 16].shapeSize = {0.8f, 0.8f};
        _board[_blueGhostPos.x + 10][_blueGhostPos.y + 16].shapeColor = Arcade::WHITE;
    }

    _board[_orangeGhostPos.x + 10][_orangeGhostPos.y + 16].shape = Arcade::Shape::RECTANGLE;
    _board[_orangeGhostPos.x + 10][_orangeGhostPos.y + 16].shapeSize = {1, 1};
    if (_WeakCooldown_orange > 0)
        _board[_orangeGhostPos.x + 10][_orangeGhostPos.y + 16].shapeColor = Arcade::BLUE;
    else
        _board[_orangeGhostPos.x + 10][_orangeGhostPos.y + 16].shapeColor = Arcade::ORANGE;
    if (!_Alive_orange) {
        _board[_orangeGhostPos.x + 10][_orangeGhostPos.y + 16].shape = Arcade::Shape::CIRCLE;
        _board[_orangeGhostPos.x + 10][_orangeGhostPos.y + 16].shapeSize = {0.8f, 0.8f};
        _board[_orangeGhostPos.x + 10][_orangeGhostPos.y + 16].shapeColor = Arcade::WHITE;
    }

    _board[_playerPos.x + 10][_playerPos.y + 16].shape = Arcade::Shape::CIRCLE;
    _board[_playerPos.x + 10][_playerPos.y + 16].shapeSize = {1, 1};
    _board[_playerPos.x + 10][_playerPos.y + 16].shapeColor = Arcade::YELLOW;

    _board[2][49].shape = Arcade::TEXT;
    _board[2][49].shapeColor = Arcade::WHITE;
    _board[2][49].textOrPath = "HIGH SCORE: " + std::to_string(_score);
    _board[2][49].shapeSize.first = 20;
    _board[2][49].shapeSize.second = 2;

    _board[5][16].shape = Arcade::TEXT;
    _board[5][16].shapeColor = Arcade::WHITE;
    _board[5][16].textOrPath = "LIVES: " + std::to_string(lives);
    _board[5][16].shapeSize.first = 20;
    _board[5][16].shapeSize.second = 2;
}

void PacMan::GhostsEaten()
{
    if (_redGhostPos.x == _playerPos.x && _redGhostPos.y == _playerPos.y) {
        if (_WeakCooldown_red > 0) {
            _score += 200;
            _WeakCooldown_red = 0;
            _Alive_red = false;
        } else if (_Alive_red) {
           restartLevel();
        }
    }
    if (_pinkGhostPos.x == _playerPos.x && _pinkGhostPos.y == _playerPos.y) {
        if (_WeakCooldown_pink > 0) {
            _score += 200;
            _WeakCooldown_pink = 0;
            _Alive_pink = false;
        } else if (_Alive_pink) {
            restartLevel();
        }
    }
    if (_blueGhostPos.x == _playerPos.x && _blueGhostPos.y == _playerPos.y) {
        if (_WeakCooldown_blue > 0) {
            _score += 200;
            _WeakCooldown_blue = 0;
            _Alive_blue = false;
        } else if (_Alive_blue) {
            restartLevel();
        }
    }
    if (_orangeGhostPos.x == _playerPos.x && _orangeGhostPos.y == _playerPos.y) {
        if (_WeakCooldown_orange > 0) {
            _score += 200;
            _WeakCooldown_orange = 0;
            _Alive_orange = false;
        } else if (_Alive_orange) {
            restartLevel();
        }
    }
}

void PacMan::newLevel()
{
    for(int i = 0; i < 48; i++)
        for(int j = 0; j < 48; j++) {
            if (TemplateMap[i][j] == 7)
                map[i][j] = PELLET;
            else if (TemplateMap[i][j] == 8)
                map[i][j] = PELLET_TAKEN;
            else if (TemplateMap[i][j] == 1)
                map[i][j] = WALL;
            else if (TemplateMap[i][j] == 9)
                map[i][j] = GHOST_PATH;
            else if (TemplateMap[i][j] == 0)
                map[i][j] = EMPTY;
            else if (TemplateMap[i][j] == 'o')
                map[i][j] = BIG_PALLET;
            else
                map[i][j] = PELLET_TAKEN;
        }

    _playerPos = {37, 23};
    _redGhostPos = {24, 25};
    _pinkGhostPos = {24, 24};
    _blueGhostPos = {24, 23};
    _orangeGhostPos = {24, 22};
    _WeakCooldown_red = 0;
    _WeakCooldown_pink = 0;
    _WeakCooldown_blue = 0;
    _WeakCooldown_orange = 0;
    _cooldownOrangeGhost = 40;
    _cooldownBlueGhost = 30;
    _cooldownPinkGhost = 20;
    _cooldownRedGhost = 10;
}

void PacMan::restartLevel()
{
    _playerPos = {37, 23};
    _redGhostPos = {24, 25};
    _pinkGhostPos = {24, 24};
    _blueGhostPos = {24, 23};
    _orangeGhostPos = {24, 22};
    _WeakCooldown_red = 0;
    _WeakCooldown_pink = 0;
    _WeakCooldown_blue = 0;
    _WeakCooldown_orange = 0;
    _Alive_red = true;
    _Alive_pink = true;
    _Alive_blue = true;
    _Alive_orange = true;
    lives -= 1;
    _cooldownOrangeGhost = 40;
    _cooldownBlueGhost = 30;
    _cooldownPinkGhost = 20;
    _cooldownRedGhost = 10;
}

void PacMan::gameOver()
{
    if (lives <= 0) {
        _board[2][16].shape = Arcade::TEXT;
        _board[2][16].shapeColor = Arcade::WHITE;
        _board[2][16].textOrPath = "GAME OVER";
        _board[2][16].shapeSize.first = 20;
        _board[2][16].shapeSize.second = 2;
        _score = 0;
        _playerPos = {37, 23};
        _redGhostPos = {24, 25};
        _pinkGhostPos = {24, 24};
        _blueGhostPos = {24, 23};
        _orangeGhostPos = {24, 22};
        for (int i = 0; i < 48; i++) {
            for (int j = 0; j < 48; j++) {
                if (map[i][j] == WALL) {
                    _board[i + 10][j + 16].shape = Arcade::RECTANGLE;
                    _board[i + 10][j + 16].shapeSize = {1, 1};
                    _board[i + 10][j + 16].shapeColor = Arcade::BLUE;
                } else if (map[i][j] == PELLET) {
                    _board[i + 10][j + 16].shape = Arcade::Shape::CIRCLE;
                    _board[i + 10][j + 16].shapeSize = {0.5, 0.5};
                    _board[i + 10][j + 16].shapeColor = Arcade::YELLOW;
                } else if (map[i][j] == BIG_PALLET) {
                    _board[i + 10][j + 16].shape = Arcade::Shape::CIRCLE;
                    _board[i + 10][j + 16].shapeSize = {0.75, 0.75};
                    _board[i + 10][j + 16].shapeColor = Arcade::WHITE;
                } else {
                    _board[i + 10][j + 16].shape = Arcade::RECTANGLE;
                    _board[i + 10][j + 16].shapeSize = {1, 1};
                    _board[i + 10][j + 16].shapeColor = Arcade::BLACK;
                }
            }
        }
    }
}

bool PacMan::checkIfStillPellets()
{
    for (int i = 0; i < 48; i++) {
        for (int j = 0; j < 48; j++) {
            if (map[i][j] == PELLET) {
                return true;
            }
        }
    }
    return false;
}

void PacMan::redrawPellets()
{
        for (int i = 0; i < 48; i++) {
            for (int j = 0; j < 48; j++) {
                if (map[i][j] == PELLET) {
                    _board[i + 10][j + 16].shape = Arcade::Shape::CIRCLE;
                    _board[i + 10][j + 16].shapeSize = {0.5, 0.5};
                    _board[i + 10][j + 16].shapeColor = Arcade::YELLOW;
                } else if (map[i][j] == BIG_PALLET) {
                    _board[i + 10][j + 16].shape = Arcade::Shape::CIRCLE;
                    _board[i + 10][j + 16].shapeSize = {0.75, 0.75};
                    _board[i + 10][j + 16].shapeColor = Arcade::WHITE;
                }
            }
        }
}

void PacMan::resetPathFindingBoard()
{
    for (int i = 0; i < 48; i++) {
        for (int j = 0; j < 48; j++) {
            if (map[i][j] == PELLET || map[i][j] == PELLET_TAKEN || map[i][j] == POWER_PELLET || map[i][j] == GHOST_PATH || map[i][j] == BIG_PALLET)
                _pathFindingBoard[i][j] = -1;
            else
                _pathFindingBoard[i][j] = -2;
        }
    }
}

void PacMan::respawnOtherSide()
{
    if (_playerPos.x == _spawnLEFT.x && _playerPos.y == _spawnLEFT.y) {
        _playerPos.x = _spawnRIGHT.x;
        _playerPos.y = _spawnRIGHT.y;
    } else if (_playerPos.x == _spawnRIGHT.x && _playerPos.y == _spawnRIGHT.y) {
        _playerPos.x = _spawnLEFT.x;
        _playerPos.y = _spawnLEFT.y;
    }
}

Pos PacMan::getDirectionPathFinding(Pos start, Pos end)
{
    bool notBlocked = false;
    int step = 0;

    resetPathFindingBoard();
    _pathFindingBoard[start.x][start.y] = step;

    if (end.x < 0)
        end.x = 0;
    if (end.x > 47)
        end.x = 47;
    if (end.y < 0)
        end.y = 0;
    if (end.y > 47)
        end.y = 47;
    int distance = 1;
    while (_pathFindingBoard[end.x][end.y] == -2) {
        if (end.y + distance < 48 && _pathFindingBoard[end.x][end.y + distance] == -1) {
            end.y += distance;
            break;
        }
        if (end.y - distance >= 0 && _pathFindingBoard[end.x][end.y - distance] == -1) {
            end.y -= distance;
            break;
        }
        if (end.x + distance < 48 && _pathFindingBoard[end.x + distance][end.y] == -1) {
            end.x += distance;
            break;
        }
        if (end.x - distance >= 0 && _pathFindingBoard[end.x - distance][end.y] == -1) {
            end.x -= distance;
            break;
        }
        if (end.y + distance < 48 && end.x + distance < 48 && _pathFindingBoard[end.x + distance][end.y + distance] == -1) {
            end.y += distance;
            end.x += distance;
            break;
        }
        if (end.y - distance >= 0 && end.x - distance >= 0 && _pathFindingBoard[end.x - distance][end.y - distance] == -1) {
            end.y -= distance;
            end.x -= distance;
            break;
        }
        if (end.y + distance < 48 && end.x - distance >= 0 && _pathFindingBoard[end.x - distance][end.y + distance] == -1) {
            end.y += distance;
            end.x -= distance;
            break;
        }
        if (end.y - distance >= 0 && end.x + distance < 48 && _pathFindingBoard[end.x + distance][end.y - distance] == -1) {
            end.y -= distance;
            end.x += distance;
            break;
        }
        distance += 1;
    }

    while (_pathFindingBoard[end.x][end.y] == -1) {
        notBlocked = false;
        for (int i = 0; i < 48; i += 1) {
            for (int j = 0; j < 48; j += 1) {
                if (_pathFindingBoard[i][j] == step) {
                    notBlocked = true;
                    int tmp_i_minus = i - 1;
                    int tmp_j_minus = j - 1;
                    int tmp_i_maxus = i + 1;
                    int tmp_j_maxus = j + 1;

                    if (tmp_i_minus < 0)
                        tmp_i_minus = 47;
                    if (tmp_j_minus < 0)
                        tmp_j_minus = 47;
                    if (tmp_i_maxus > 47)
                        tmp_i_maxus = 0;
                    if (tmp_j_maxus > 47)
                        tmp_j_maxus = 0;

                    if (_pathFindingBoard[tmp_i_minus][j] == -1)
                        _pathFindingBoard[tmp_i_minus][j] = step + 1;
                    if (_pathFindingBoard[tmp_i_maxus][j] == -1)
                        _pathFindingBoard[tmp_i_maxus][j] = step + 1;
                    if (_pathFindingBoard[i][tmp_j_minus] == -1)
                        _pathFindingBoard[i][tmp_j_minus] = step + 1;
                    if (_pathFindingBoard[i][tmp_j_maxus] == -1)
                        _pathFindingBoard[i][tmp_j_maxus] = step + 1;
                }
            }
        }
        if (!notBlocked)
            break;
        step += 1;
    }
    if (step == 0)
        return start;
    while (_pathFindingBoard[end.x][end.y] > 1) {
        int x_minus = end.x - 1;
        int y_minus = end.y - 1;
        int x_maxus = end.x + 1;
        int y_maxus = end.y + 1;

        if (x_minus < 0)
            x_minus = 47;
        if (y_minus < 0)
            y_minus = 47;
        if (x_maxus > 47)
            x_maxus = 0;
        if (y_maxus > 47)
            y_maxus = 0;
        if (_pathFindingBoard[x_minus][end.y] == step - 1) {
            step -= 1;
            end.x = x_minus;
        } else if (_pathFindingBoard[x_maxus][end.y] == step - 1) {
            step -= 1;
            end.x = x_maxus;
        } else if (_pathFindingBoard[end.x][y_minus] == step - 1) {
            step -= 1;
            end.y = y_minus;
        } else if (_pathFindingBoard[end.x][y_maxus] == step - 1) {
            step -= 1;
            end.y = y_maxus;
        }
    }
    return end;
}

void PacMan::RedGhost(float deltaTime)
{
    if (_cooldownRedGhost > 0) {
        _cooldownRedGhost -= 1;
        return;
    }
    (void)deltaTime;
    if (!_Alive_red) {
        _redGhostPos = getDirectionPathFinding(_redGhostPos, {24, 25});
        if (_redGhostPos.x == 24 && _redGhostPos.y == 25)
            _Alive_red = true;
        return;
    }
    if (_WeakCooldown_red > 0) {
        _WeakCooldown_red -= 1;
        _redGhostPos = getDirectionPathFinding(_redGhostPos, {
            47 - _orangeRandomDirection.x,
            _orangeRandomDirection.y});
        return;
    }

    _redGhostPos = getDirectionPathFinding(_redGhostPos, _playerPos);
}

void PacMan::PinkGhost(float deltaTime)
{
    if (_cooldownPinkGhost > 0) {
        _cooldownPinkGhost -= 1;
        return;
    }
    (void)deltaTime;
    if (!_Alive_pink) {
        _pinkGhostPos = getDirectionPathFinding(_pinkGhostPos, {24, 24});
        if (_pinkGhostPos.x == 24 && _pinkGhostPos.y == 24)
            _Alive_pink = true;
        return;
    }
    if (_WeakCooldown_pink > 0) {
        _WeakCooldown_pink -= 1;
        _pinkGhostPos = getDirectionPathFinding(_pinkGhostPos, {
                _orangeRandomDirection.x,
                47 - _orangeRandomDirection.y});
        return;
    }
    Pos destination = _playerPos;

    if (_direction == Arcade::UP)
        destination.x -= 8;
    else if (_direction == Arcade::DOWN)
        destination.x += 8;
    else if (_direction == Arcade::LEFT)
        destination.y -= 8;
    else if (_direction == Arcade::RIGHT)
        destination.y += 8;
    _pinkGhostPos = getDirectionPathFinding(_pinkGhostPos, destination);
}

void PacMan::BlueGhost(float deltaTime)
{
    if (_cooldownBlueGhost > 0) {
        _cooldownBlueGhost -= 1;
        return;
    }
    (void)deltaTime;
    if (!_Alive_blue) {
        _blueGhostPos = getDirectionPathFinding(_blueGhostPos, {24, 23});
        if (_blueGhostPos.x == 24 && _blueGhostPos.y == 23)
            _Alive_blue = true;
        return;
    }
    if (_WeakCooldown_blue > 0) {
        _WeakCooldown_blue -= 1;
        _blueGhostPos = getDirectionPathFinding(_blueGhostPos, {
                47 - _orangeRandomDirection.x,
                47 - _orangeRandomDirection.y});
        return;
    }
    Pos destination = _playerPos;

    if (_direction == Arcade::UP)
        destination.x -= 4;
    else if (_direction == Arcade::DOWN)
        destination.x += 4;
    else if (_direction == Arcade::LEFT)
        destination.y -= 4;
    else if (_direction == Arcade::RIGHT)
        destination.y += 4;
    _blueGhostPos = getDirectionPathFinding(_blueGhostPos, destination);
}

void PacMan::OrangeGhost(float deltaTime)
{
    (void)deltaTime;

    _orangeGhostDelay -= 1;
    if (_orangeGhostDelay <= 0 || (_orangeRandomDirection.x == _orangeGhostPos.x && _orangeRandomDirection.y == _orangeGhostPos.y)) {
        _orangeGhostDelay = rand() % 5 + 10;
        _orangeRandomDirection.x = rand() % 48;
        _orangeRandomDirection.y = rand() % 48;
    }
    if (_cooldownOrangeGhost > 0) {
        _cooldownOrangeGhost -= 1;
        return;
    }
    if (!_Alive_orange) {
        _orangeGhostPos = getDirectionPathFinding(_orangeGhostPos, {24, 22});
        if (_orangeGhostPos.x == 24 && _orangeGhostPos.y == 22)
            _Alive_orange = true;
        return;
    }
    if (_WeakCooldown_orange > 0) {
        _WeakCooldown_orange -= 1;
        _orangeGhostPos = getDirectionPathFinding(_orangeGhostPos, {
                _orangeRandomDirection.x,
                _orangeRandomDirection.y});
        return;
    }
    _orangeGhostPos = getDirectionPathFinding(_orangeGhostPos, _orangeRandomDirection);
}

void PacMan::update(float deltaTime)
{
    if (!checkIfStillPellets())
    {
        newLevel();
    }
    _movement += deltaTime;
    if (_movement >= 0.095) {
        _movement = 0;
        RedGhost(deltaTime);
        PinkGhost(deltaTime);
        BlueGhost(deltaTime);
        OrangeGhost(deltaTime);
        GhostsEaten();
        LastPressed();
        GhostsEaten();
        respawnOtherSide();
    }
    redrawPellets();
    gameOver();
    MapDraw();
}

void __attribute__((constructor)) my_constructor()
{

}

void __attribute__((destructor)) my_destructor()
{

}

extern "C" Arcade::IGameModule* entryGame() {
    return new PacMan;
}
