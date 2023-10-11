/*
** EPITECH PROJECT, 2023
** main.cpp$
** File description:
** main.cpp$
*/

#include <iostream>
#include "../../src/AGameModule.hpp"

static const int TemplateMap[48][48] = {                                 //x = 48 / y = 48
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 1, 1, 1, 1, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 1},
        {1, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 1},
        {1, 0,'o', 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0,'o', 0, 1},
        {1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1},
        {1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1},
        {1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1},
        {1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1},
        {1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1},
        {1, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 1},
        {1, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 1},
        {1, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 1},
        {1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1},
        {1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1},
        {1, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 1, 1, 1, 1, 0, 7, 7, 7, 7, 0, 1, 1, 1, 1, 1, 1, 0, 7, 7, 7, 7, 0, 1, 1, 1, 1, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 1},
        {1, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 1, 1, 1, 1, 0, 0, 0, 0, 8, 0, 1, 1, 1, 1, 1, 1, 0, 8, 0, 0, 0, 0, 1, 1, 1, 1, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 0, 8, 0, 1, 1, 1, 1, 1, 1, 0, 8, 0, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 0, 8, 0, 1, 1, 1, 1, 1, 1, 0, 8, 0, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 7, 0, 1, 1, 1, 1, 1, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1, 1, 1, 1, 1, 0, 7, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 7, 0, 1, 1, 1, 1, 1, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 1, 1, 1, 1, 1, 0, 7, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 7, 0, 1, 1, 1, 1, 1, 0, 8, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 8, 0, 1, 1, 1, 1, 1, 0, 7, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 0, 8, 0, 1, 1, 1, 9, 9, 9, 9, 1, 1, 1, 0, 8, 0, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 8, 0, 1, 0, 0, 9, 9, 9, 9, 0, 0, 1, 0, 8, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 0, 1, 0, 0, 4, 5, 6, 3, 0, 0, 1, 0, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 8, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 8, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 8, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 8, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 7, 0, 1, 1, 1, 1, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 1, 1, 1, 1, 0, 7, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 7, 0, 1, 1, 1, 1, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 1, 1, 1, 1, 0, 7, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 7, 0, 1, 1, 1, 1, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 1, 1, 1, 1, 0, 7, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 8, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 8, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 1, 1, 1, 1, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 1},
        {1, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 1},
        {1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1},
        {1, 0, 7, 0, 0, 0, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 0, 0, 0, 7, 0, 1},
        {1, 0,'o', 7, 7, 0, 1, 1, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 1, 1, 0, 7, 7,'o', 0, 1},
        {1, 0, 0, 0, 7, 0, 1, 1, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 1, 1, 0, 7, 0, 0, 0, 1},
        {1, 1, 1, 0, 7, 0, 1, 1, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 1, 1, 0, 7, 0, 1, 1, 1},
        {1, 1, 1, 0, 7, 0, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 0, 7, 0, 1, 1, 1},
        {1, 0, 0, 0, 7, 0, 0, 0, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 0, 0, 0, 7, 0, 0, 0, 1},
        {1, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 1, 1, 1, 1, 0, 7, 7, 7, 7, 7, 0, 1, 1, 1, 1, 0, 7, 7, 7, 7, 7, 0, 1, 1, 1, 1, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 1},
        {1, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 1},
        {1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 0, 7, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1},
        {1, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 1},
        {1, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

enum CellType {
    EMPTY = 0,
    WALL,
    PELLET,
    BIG_PALLET,
    PELLET_TAKEN,
    POWER_PELLET,
    PACMAN,
    RED_GHOST,
    PINK_GHOST,
    BLUE_GHOST,
    ORANGE_GHOST,
    GHOST_PATH
};

struct Pos {
    int x;
    int y;
};

class PacMan : public Arcade::AGameModule {
public:
    PacMan();
    ~PacMan();
    void update(float deltaTime) override;
    void onInputPressed(Arcade::InputAction input, bool isPressed) override;
    void MapDraw();
    int ScoreSystem();
    void LastPressed();
    void RedGhost(float deltaTime);
    void PinkGhost(float deltaTime);
    void BlueGhost(float deltaTime);
    void OrangeGhost(float deltaTime);
    void GhostsEaten();
    void resetPathFindingBoard();
    Pos getDirectionPathFinding(Pos start, Pos end);
    void restartLevel();
    void newLevel();
    void gameOver();
    void respawnOtherSide();
    bool checkIfStillPellets();
    void redrawPellets();

protected:
    int movement;
    Pos _playerPos;
    Pos _redGhostPos;
    int _cooldownRedGhost;
    Pos _pinkGhostPos;
    int _cooldownPinkGhost;
    Pos _blueGhostPos;
    int _cooldownBlueGhost;
    Pos _orangeGhostPos;
    int _cooldownOrangeGhost;
    int map[48][48];
    int _pathFindingBoard[48][48];
    int _direction;
    int _directionRed;
    float _movement;
    int _distanceGhostPlayer;
    int _orangeGhostDelay;
    Pos _orangeRandomDirection;
    bool _Alive_red;
    bool _Alive_blue;
    bool _Alive_pink;
    bool _Alive_orange;
    int _WeakCooldown_red;
    int _WeakCooldown_blue;
    int _WeakCooldown_pink;
    int _WeakCooldown_orange;
    int lives;
    Pos _spawnLEFT;
    Pos _spawnRIGHT;
};

//red goes to pacman, pink goes to pacman + 4 tiles in front of him, blue goes to pacman + 2 tiles in front of him, orange goes to pacman randomly on the map