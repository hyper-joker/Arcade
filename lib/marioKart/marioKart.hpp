/*
** EPITECH PROJECT, 2023
** main.cpp$
** File description:
** main.cpp$
*/

#pragma once
#include <iostream>
#include <math.h>
#include <tuple>
#include <algorithm>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include "../../src/AGameModule.hpp"
#include "Mario.hpp"
#include "Wario.hpp"
#include "Luigi.hpp"
#include "Waluigi.hpp"
#include "Toad.hpp"
#include "Bowser.hpp"
#include "Items.hpp"
#include "BackGround.hpp"
#include "Explosion.hpp"
#include "maps.hpp"

#define MAP_WIDTH 32
#define MAP_HEIGHT 32
#define PI 3.14159265
#define PI2 6.28318530
#define PI1_2 1.57079632
#define PI3_2 4.71238898
#define PI180 0.01745329

#define EXAMPLE_PORT 18000
#define EXAMPLE_GROUP "224.64.1.1"

const Arcade::Color texture_color[] = {
        Arcade::Color::RED,
        Arcade::Color::YELLOW,
        Arcade::Color::BLUE,
        Arcade::Color::GREEN,
        Arcade::Color::PURPLE,
        Arcade::Color::ORANGE,
        Arcade::Color::BLACK,
        Arcade::Color::WHITE,
        Arcade::Color::DARK_RED,
        Arcade::Color::DARK_YELLOW,
        Arcade::Color::DARK_BLUE,
        Arcade::Color::DARK_GREEN,
        Arcade::Color::DARK_PURPLE,
        Arcade::Color::DARK_ORANGE,
        Arcade::Color::CYAN
};

enum characters {
    MARIO = 0,
    LUIGI,
    TOAD,
    WARIO,
    WALUIGI,
    BOWSER
};

struct Player {
    float x;
    float y;

    float speed;
    float acceleration;
    float maxSpeed;

    float movementX;
    float movementY;

    float turnSpeed;
    float turningAngle;
    float maxTurnAngle;
    float stabilisationSpeed;

    float driftSpeed;
    float driftAngle;
    float initialSpeed;

    float angleLooking;
    float lookX;
    float lookY;
};

enum ItemsType {
    NONE = 0,
    DUST,
    SHELL,
    BANANA,
    BOMB,
    RED_SHELL,
    MUSHROOM,
    EXPLOSION,
    BIG_EXPLOSION,
    TREE,
    PIPE,
    RED_PIPE
};

enum mapType {
    MARIO_CIRCUIT = 0,
    FROZEN_KINGDOM,
    MAPLE_TREEWAY,
    RAINBOW_ROAD
};

struct Items {
    float x;
    float y;
    float deltaX;
    float deltaY;
    ItemsType type;
    bool active;
    float lifeTime;
    float speed;
    float noCollision;
    bool isBig;
    bool isPhysic;
    bool isIndestructible;
    float hitBox;
};

struct Box {
    float x;
    float y;
    bool active;
    float timer;
};

struct Bot {
    float x;
    float y;
    int character;
    std::string id;
    bool active;
    int isTurning;
    int rotation;
    bool isReady;
    bool hasFinish;
    int lap;
    int point;
};

struct Network {
    struct sockaddr_in addr_recv;
    struct sockaddr_in addr_send;
    int addrlen;
    int sock;
    struct ip_mreq mreq;
    std::string id;
    float timer;
    std::string message[16];
    int messageIndex;
};

class MarioKart : public Arcade::AGameModule {
public:
    MarioKart();
    ~MarioKart();
    void initNetworking();
    void update(float deltaTime) override;
    void updateMenu(float deltaTime);
    void onInputPressed(Arcade::InputAction input, bool isPressed) override;
    std::tuple<float, float, float> getPositionOfCollisionX(float angle, float ndeltaZ, int i, int j);
    std::tuple<float, float, float> getPositionOfCollisionY(float angle, float ndeltaZ, int i, int j);
    void playerAccelerate(float deltaTime);
    void playerTurn(float deltaTime);
    void playerDrift(float deltaTime);
    std::pair<float, float> getPointFromVector(float angle, float angleZ);
    int getColorFromPoint(std::pair<float, float> position);
    int isPointOnWall(std::pair<float, float> position);
    int isOnCheckPoint(std::pair<float, float> position);
    void getCameraPosition();
    void drawMainPlayer();
    void playerLaunchItem();
    void drawSkyBox();
    void drawMap();
    void drawHud();
    std::string getCharacterName(int character);
    void updateItems(float deltaTime);
    void updateBox(float deltaTime);
    void drawItems();
    void drawBots();
    void drawBox();
    void bombExplosion(int i);
    int getAvailableItem();
    int createItemBox(float x, float y);
    int getRightTextureCharacter(int x, int y, bool isFront, int character, float distance, int brokenRotation);
    int getRightTextureItems(int x, int y, int items, float distance);
    int getRightBigTexture(int x, int y, int texture, float distance);
    int getRightTextureBox(int x, int y, float distance);
    std::pair<float, float> adjustVector(std::pair<float, float> vector);
    std::pair<int, int> getBoardPosFromWorldPos(std::pair<float, float> position);
    void initMap();
    void createTree(int x, int y);
    void createPipe(int x, int y);
    void createRedPipe(int x, int y);

    void networkUpdate(float deltaTime);
    void networkParse(std::string data);
    void networkSend();
    void networkSendNewConnection(std::string data);
    void networkSendPlayerPosition(std::string data);
    void networkSendPlayerItem(std::string data);
    void networkSendPlayerBox(std::string data);
    void networkSendCharacter(std::string data);
    void networkSendIsReady(std::string data);
    void networkSendHasFinish(std::string data);


private:
    float _cameraX;
    float _cameraY;
    float _cameraZ;

    Player _player;

    bool _autoMove;
    float _inputAccelerate;
    float _inputTurn;
    bool _inputDrift;
    bool _inputLaunchItem;
    float _maxSpeed;
    float _fov;
    float _distanceCamera;
    int _isTurning;
    char _map[MAP_HEIGHT + 1][MAP_WIDTH + 1];
    char _highResMap[(MAP_HEIGHT + 1) * 5][(MAP_WIDTH + 1) * 5];
    int _background[30][360];
    int _currentMap;
    int _characterSelected;
    ItemsType _itemsStored;
    float _timeMushroom;

    float _timeBroken;
    int _brokenDirection;
    float _brokenRotationTimer;
    int _brokenRotation;

    Items _items[2048];
    Box _boxs[256];
    Bot _bots[5];

    float _dustTimer;
    float _boxTimer;
    int _boxColor;
    int _currentLap;
    int _currentCheckPoint;
    int _rank;
    int _point;
    bool _hasFinish;

    bool _inMenu;
    bool _endScreen;
    float _timerMenu;
    int _inputMenu;
    bool _isReady;

    Network _network;
};
