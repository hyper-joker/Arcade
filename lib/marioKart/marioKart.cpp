/*
** EPITECH PROJECT, 2023
** main.cpp$
** File description:
** main.cpp$
*/

#include <iostream>
#include "marioKart.hpp"

void MarioKart::initNetworking()
{
//Networking
    _network.messageIndex = 0;
    for (int i = 0; i < 16; i++)
        _network.message[i] = "";
    _network.timer = 0;
    _network.sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (_network.sock < 0) {
        perror("socket");
        exit(84);
    }
    _network.addrlen = sizeof(_network.addr_recv);
    bzero((char *)&(_network.addr_recv), _network.addrlen);
    _network.addr_recv.sin_family = AF_INET;
    _network.addr_recv.sin_addr.s_addr = htonl(INADDR_ANY);
    _network.addr_recv.sin_port = htons(EXAMPLE_PORT);
    // Stay on LAN
    unsigned char ttl = 1; // stay on LAN => time to live = 1
    if(setsockopt(_network.sock, IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttl, sizeof(ttl)) < 0) {
        perror("setsockopt");
        exit(84);
    }
    // Allow multiple binds on same host
    int on = 1;
    if (setsockopt(_network.sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        perror("setsockopt reuse addr");
    if (setsockopt(_network.sock, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on)) < 0)
        perror("setsockopt reuse port");
    // Bind to socket (start listening)
    if (bind(_network.sock, (struct sockaddr *) &(_network.addr_recv), _network.addrlen) < 0) {
        perror("bind");
        exit(84);
    }
    // Join Multicast group
    _network.mreq.imr_multiaddr.s_addr = inet_addr(EXAMPLE_GROUP);
    _network.mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(_network.sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &(_network.mreq), sizeof(_network.mreq)) < 0) {
        perror("setsockopt mreq");
        exit(84);
    }
    // Prepare for sending UDP to multicast group EXAMPLE_GROUP on EXAMPLE_PORT
    bzero((char *)&(_network.addr_send), _network.addrlen);
    _network.addr_send.sin_family = AF_INET;
    _network.addr_send.sin_addr.s_addr = inet_addr(EXAMPLE_GROUP);
    _network.addr_send.sin_port = htons(EXAMPLE_PORT);

    _network.id = "";
    for (int i = 0; i < 6; i += 1)
        _network.id += (char) (rand() % 26 + 65);
    std::cout << "Your ID is: " << _network.id << std::endl;
}

MarioKart::MarioKart()
{
    srand(time(NULL) + getpid());
    _cameraX = 450;
    _cameraY = 450;
    _cameraZ = 50;
    _player.x = 500 * 6;
    _player.y = 500 * 3;
    _player.speed = 0;
    _player.acceleration = 2;
    _player.turnSpeed = 4;
    _player.turningAngle = 0;
    _player.maxTurnAngle = 4 * PI180;
    _player.stabilisationSpeed = 24;
    _player.angleLooking = 0;
    _player.lookX = cos(_player.angleLooking) * 5;
    _player.lookY = sin(_player.angleLooking) * 5;
    _player.maxSpeed = 20;
    _player.driftSpeed = 8;
    _player.driftAngle = 0;
    _player.movementX = 0;
    _player.movementY = 0;
    _player.initialSpeed = 0;
    _autoMove = false;
    _inputAccelerate = 0;
    _inputTurn = 0;
    _inputDrift = 0;
    _inputLaunchItem = false;
    _maxSpeed = 60;
    _fov = 15 * PI180;
    _distanceCamera = 424; //distance between camera and player
    _isTurning = 0;
    _characterSelected = MARIO;
    _dustTimer = 0;
    _boxTimer = 0;
    _boxColor = 0;
    _currentCheckPoint = 0;
    _currentLap = 0;
    _timeMushroom = 0;
    _timeBroken = 0;
    _brokenDirection = 0;
    _brokenRotationTimer = 0;
    _brokenRotation = 0;
    _inMenu = true;
    _timerMenu = 0;
    _inputMenu = 0;
    _isReady = false;
    _hasFinish = false;
    _endScreen = false;
    _rank = 0;

    for (int i = 0; i < 5; i += 1) {
        _bots[i].active = false;
        _bots[i].x = 0;
        _bots[i].y = 0;
        _bots[i].id = "";
        _bots[i].character = MARIO;
        _bots[i].isTurning = 0;
        _bots[i].rotation = 0;
        _bots[i].isReady = false;
        _bots[i].hasFinish = false;
        _bots[i].lap = 0;
    }

    initNetworking();

    _currentMap = MARIO_CIRCUIT;
    initMap();

    /*Connect to server*/
    networkSendNewConnection("ping");
}

MarioKart::~MarioKart() {

}

void MarioKart::initMap()
{
    /*Reset*/
    for (int i = 0; i < 2048; i += 1) {
        _items[i].active = false;
        _items[i].type = NONE;
        _items[i].x = 0;
        _items[i].y = 0;
        _items[i].deltaX = 0;
        _items[i].deltaY = 0;
        _items[i].noCollision = 0.f;
        _items[i].isBig = false;
        _items[i].isPhysic = false;
    }

    for (int i = 0; i < 256; i += 1) {
        _boxs[i].active = false;
        _boxs[i].x = 0;
        _boxs[i].y = 0;
        _boxs[i].timer = 0;
    }

    for (int i = 0; i < 16; i += 1)
        for (int j = 0; j < 360; j += 1)
            _background[i][j] = 7;

    /*Create Map*/
    if (_currentMap == MARIO_CIRCUIT) {
        for (int i = 0; i < MAP_HEIGHT + 1; i += 1)
            for (int j = 0; j < MAP_WIDTH + 1; j += 1)
                _map[i][j] = map_plain[i][j];

        for (int i = 0; i < 30; i += 1)
            for (int j = 0; j < 360; j += 1)
                _background[i][j] = 15;
        /*BackGround MarioCircuit*/
        for (int i = 0; i < 16; i += 1)
            for (int j = 0; j < 16; j += 1) {
                if (bg_01_plain[i][j] != 0) {
                    _background[i][j + 2] = bg_01_plain[i][j];
                    _background[i + 1][j + 120] = bg_01_plain[i][j];
                    _background[i][j + 264] = bg_01_plain[i][j];
                }

                if (bg_02_plain[i][j] != 0) {
                    _background[i][j + 48] = bg_02_plain[i][j];
                    _background[i + 2][j + 96] = bg_02_plain[i][j];
                    _background[i + 3][j + 176] = bg_02_plain[i][j];
                    if (bg_02_plain[i][j] == 2) {
                        _background[i + 3][j + 176] = 1;
                        _background[i + 2][j + 96] = 3;
                    }
                }

                if (bg_03_plain[i][j] != 0) {
                    _background[i][j + 10] = bg_03_plain[i][j];
                    _background[i + 2][j + 180] = bg_03_plain[i][j];
                    _background[i + 1][j + 240] = bg_03_plain[i][j];
                }

                if (bg_04_plain[i][j] != 0) {
                    _background[i][j + 320] = bg_04_plain[i][j];
                }
            }

    } else if (_currentMap == FROZEN_KINGDOM) {
        for (int i = 0; i < MAP_HEIGHT + 1; i += 1)
            for (int j = 0; j < MAP_WIDTH + 1; j += 1)
                _map[i][j] = map_ice[i][j];
        for (int i = 0; i < 30; i += 1)
            for (int j = 0; j < 360; j += 1)
                _background[i][j] = 13;
        /*BackGround Frozen Kingdom*/
        for (int i = 0; i < 16; i += 1)
            for (int j = 0; j < 16; j += 1) {
                if (bg_01_plain[i][j] != 0) {
                    _background[i][j + 2] = bg_01_plain[i][j];
                    _background[i + 1][j + 120] = bg_01_plain[i][j];
                    _background[i][j + 264] = bg_01_plain[i][j];
                    _background[i + 1][j + 320] = bg_01_plain[i][j];
                    _background[i + 2][j + 74] = bg_01_plain[i][j];
                    _background[i + 4][j + 196] = bg_01_plain[i][j];
                }

                if (bg_03_plain[i][j] != 0) {
                    _background[i][j + 10] = bg_03_plain[i][j];
                    _background[i + 2][j + 180] = bg_03_plain[i][j];
                    _background[i + 1][j + 240] = bg_03_plain[i][j];
                }
            }

    } else if (_currentMap == MAPLE_TREEWAY) {
        for (int i = 0; i < MAP_HEIGHT + 1; i += 1)
            for (int j = 0; j < MAP_WIDTH + 1; j += 1)
                _map[i][j] = map_maple[i][j];
        for (int i = 0; i < 30; i += 1)
            for (int j = 0; j < 360; j += 1)
                _background[i][j] = 15;
        /*BackGround MAPLE Kingdom*/
        for (int i = 0; i < 16; i += 1)
            for (int j = 0; j < 16; j += 1) {
                if (bg_01_plain[i][j] != 0) {
                    _background[i][j + 2] = bg_01_plain[i][j];
                    _background[i + 1][j + 120] = bg_01_plain[i][j];
                    _background[i][j + 264] = bg_01_plain[i][j];
                    _background[i + 1][j + 320] = bg_01_plain[i][j];
                    _background[i + 2][j + 74] = bg_01_plain[i][j];
                    _background[i + 4][j + 196] = bg_01_plain[i][j];
                }

                if (bg_maple[i][j] != 0) {
                    _background[i][j + 90] = bg_maple[i][j];
                    _background[i][j + 152] = bg_maple[i][j];
                    _background[i][j + 250] = bg_maple[i][j];
                    _background[i][j + 20] = bg_maple[i][j];
                }

                if (bg_03_plain[i][j] != 0) {
                    _background[i][j + 10] = bg_03_plain[i][j];
                    _background[i + 2][j + 180] = bg_03_plain[i][j];
                    _background[i + 1][j + 240] = bg_03_plain[i][j];
                }
            }

    } else if (_currentMap == RAINBOW_ROAD) {
        for (int i = 0; i < MAP_HEIGHT + 1; i += 1)
            for (int j = 0; j < MAP_WIDTH + 1; j += 1)
                _map[i][j] = map_rainbow[i][j];

    }

    /*Place Item Box*/
    for (int i = 0; i < MAP_HEIGHT + 1; i += 1) {
        for (int j = 0; j < MAP_WIDTH + 1; j += 1) {
            if (_map[i][j] == 'o') {
                if (_map[i - 1][j] == 'o' || _map[i + 1][j] == 'o') {
                    createItemBox(j * 500 + 250, i * 500 + 167);
                    createItemBox(j * 500 + 250, i * 500 + 333);
                    if (_map[i + 1][j] == 'o')
                        createItemBox(j * 500 + 250, i * 500 + 500);
                }
                if (_map[i][j - 1] == 'o' || _map[i][j + 1] == 'o') {
                    createItemBox(j * 500 + 167, i * 500 + 250);
                    createItemBox(j * 500 + 333, i * 500 + 250);
                    if (_map[i][j + 1] == 'o')
                        createItemBox(j * 500 + 500, i * 500 + 250);
                }
            } else if (_map[i][j] == '0') { //Place Player
                if (_map[i + 1][j] == '0') {
                    _player.x = j * 500 + 250;
                    _player.y = i * 500 + 500;
                }
            }
        }
    }
    for (int i = 1; i < MAP_HEIGHT; i += 1)
        for (int j = 1; j < MAP_WIDTH; j += 1)
            if (_map[i][j] == 'o')
                _map[i][j] = '*';

    /*Place Tree*/
    for (int i = 0; i < MAP_HEIGHT + 1; i += 1) {
        for (int j = 0; j < MAP_WIDTH + 1; j += 1) {
            if (_map[i][j] == 't') {
                if (_map[i - 1][j] == 't' || _map[i + 1][j] == 'o') {
                    createTree(j * 500 + 250, i * 500 + 167);
                    createTree(j * 500 + 250, i * 500 + 333);
                    if (_map[i + 1][j] == 't')
                        createTree(j * 500 + 250, i * 500 + 500);
                }
                if (_map[i][j - 1] == 't' || _map[i][j + 1] == 't') {
                    createTree(j * 500 + 167, i * 500 + 250);
                    createTree(j * 500 + 333, i * 500 + 250);
                    if (_map[i][j + 1] == 't')
                        createTree(j * 500 + 500, i * 500 + 250);
                }
            }

            if (_map[i][j] == 'p') {
                if (_map[i - 1][j] == 'p' || _map[i + 1][j] == 'p') {
                    createPipe(j * 500 + 250, i * 500 + 167);
                    createPipe(j * 500 + 250, i * 500 + 333);
                    if (_map[i + 1][j] == 'p')
                        createPipe(j * 500 + 250, i * 500 + 500);
                }
                if (_map[i][j - 1] == 'p' || _map[i][j + 1] == 'p') {
                    createPipe(j * 500 + 167, i * 500 + 250);
                    createPipe(j * 500 + 333, i * 500 + 250);
                    if (_map[i][j + 1] == 'p')
                        createPipe(j * 500 + 500, i * 500 + 250);
                }
            }

            if (_map[i][j] == 'P') {
                if (_map[i - 1][j] == 'P' || _map[i + 1][j] == 'P') {
                    createRedPipe(j * 500 + 250, i * 500 + 167);
                    createRedPipe(j * 500 + 250, i * 500 + 333);
                    if (_map[i + 1][j] == 'P')
                        createRedPipe(j * 500 + 250, i * 500 + 500);
                }
                if (_map[i][j - 1] == 'P' || _map[i][j + 1] == 'P') {
                    createRedPipe(j * 500 + 167, i * 500 + 250);
                    createRedPipe(j * 500 + 333, i * 500 + 250);
                    if (_map[i][j + 1] == 'P')
                        createRedPipe(j * 500 + 500, i * 500 + 250);
                }
            }
        }
    }

    for (int i = 1; i < MAP_HEIGHT; i += 1)
        for (int j = 1; j < MAP_WIDTH; j += 1) {
            if (_map[i][j] == 't')
                _map[i][j] = ' ';
            if (_map[i][j] == 'p')
                _map[i][j] = '*';
            if (_map[i][j] == 'P')
                _map[i][j] = '*';
        }

    /*Place Wall*/
    for (int i = 1; i < MAP_HEIGHT; i += 1) {
        for (int j = 1; j < MAP_WIDTH; j += 1) {
            if (_map[i][j] == ' ') {
                if (_map[i - 1][j] == '*' || (_map[i - 1][j] >= '0' && _map[i - 1][j] <= '4'))
                    _map[i][j] = 'x';
                if (_map[i + 1][j] == '*' || (_map[i + 1][j] >= '0' && _map[i + 1][j] <= '4'))
                    _map[i][j] = 'x';
                if (_map[i][j - 1] == '*' || (_map[i][j - 1] >= '0' && _map[i][j - 1] <= '4'))
                    _map[i][j] = 'x';
                if (_map[i][j + 1] == '*' || (_map[i][j + 1] >= '0' && _map[i][j + 1] <= '4'))
                    _map[i][j] = 'x';
            }
        }
    }
    for (int i = 1; i < MAP_HEIGHT; i += 1) {
        for (int j = 1; j < MAP_WIDTH; j += 1) {
            if (_map[i][j] == ' ') {
                if (_map[i - 1][j] == 'x')
                    _map[i][j] = 'p';
                if (_map[i + 1][j] == 'x')
                    _map[i][j] = 'p';
                if (_map[i][j - 1] == 'x')
                    _map[i][j] = 'p';
                if (_map[i][j + 1] == 'x')
                    _map[i][j] = 'p';
            }
        }
    }
    for (int i = 1; i < MAP_HEIGHT; i += 1) {
        for (int j = 1; j < MAP_WIDTH; j += 1) {
            if (_map[i][j] == 'p') {
               _map[i][j] = 'x';
            }
        }
    }

    for (int i = 0; i < (MAP_HEIGHT + 1); i += 1) {
        for (int j = 0; j < (MAP_WIDTH + 1); j += 1) {
            for (int y = 0; y < 5; y += 1) {
                for (int x = 0; x < 5; x += 1) {
                    _highResMap[i*5 + y][j*5 + x] = _map[i][j];
                    if (_map[i][j] == 'x') {
                        if (_map[i + 1][j] != 'x' && _map[i][j + 1] != 'x' && _map[i + 1][j] == _map[i][j + 1] && _map[i + 1][j] != ' ') {
                            if (y + x > 4)
                                _highResMap[i * 5 + y][j * 5 + x] = _map[i + 1][j];
                        }
                        if (_map[i - 1][j] != 'x' && _map[i][j - 1] != 'x' && _map[i - 1][j] == _map[i][j - 1] && _map[i - 1][j] != ' ') {
                            if (y + x < 4)
                                _highResMap[i * 5 + y][j * 5 + x] = _map[i - 1][j];
                        }
                        if (_map[i - 1][j] != 'x' && _map[i][j + 1] != 'x' && _map[i - 1][j] == _map[i][j + 1] && _map[i - 1][j] != ' ') {
                            if (x > y)
                                _highResMap[i * 5 + y][j * 5 + x] = _map[i - 1][j];
                        }
                        if (_map[i + 1][j] != 'x' && _map[i][j - 1] != 'x' && _map[i + 1][j] == _map[i][j - 1] && _map[i + 1][j] != ' ') {
                            if (y > x)
                                _highResMap[i * 5 + y][j * 5 + x] = _map[i + 1][j];
                        }
                    }
                    if (_map[i][j] == ' ') {
                        if (_map[i + 1][j] != ' ' && _map[i][j + 1] != ' ' && _map[i + 1][j] == _map[i][j + 1] && _map[i + 1][j] == 'x') {
                            if (y + x > 4)
                                _highResMap[i * 5 + y][j * 5 + x] = _map[i + 1][j];
                        }
                        if (_map[i - 1][j] != ' ' && _map[i][j - 1] != ' ' && _map[i - 1][j] == _map[i][j - 1] && _map[i - 1][j] == 'x') {
                            if (y + x < 4)
                                _highResMap[i * 5 + y][j * 5 + x] = _map[i - 1][j];
                        }
                        if (_map[i - 1][j] != ' ' && _map[i][j + 1] != ' ' && _map[i - 1][j] == _map[i][j + 1] && _map[i - 1][j] == 'x') {
                            if (x > y)
                                _highResMap[i * 5 + y][j * 5 + x] = _map[i - 1][j];
                        }
                        if (_map[i + 1][j] != ' ' && _map[i][j - 1] != ' ' && _map[i + 1][j] == _map[i][j - 1] && _map[i + 1][j] == 'x') {
                            if (y > x)
                                _highResMap[i * 5 + y][j * 5 + x] = _map[i + 1][j];
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < (MAP_HEIGHT + 1) * 5; i += 1) {
        for (int j = 0; j < (MAP_WIDTH + 1) * 5; j += 1) {
            std::cout << _highResMap[i][j];
        }
        std::cout << std::endl;
    }
}

void MarioKart::createTree(int x, int y)
{
    int tree = getAvailableItem();

    if (tree != -1) {
        _items[tree].x = x;
        _items[tree].y = y;
        _items[tree].type = TREE;
        _items[tree].lifeTime = 5000.f;
        _items[tree].isBig = true;
        _items[tree].isPhysic = false;
        _items[tree].isIndestructible = true;
    }
}

void MarioKart::createPipe(int x, int y)
{
    int pipe = getAvailableItem();

    if (pipe != -1) {
        _items[pipe].x = x;
        _items[pipe].y = y;
        _items[pipe].type = PIPE;
        _items[pipe].lifeTime = 5000.f;
        _items[pipe].isBig = true;
        _items[pipe].isPhysic = true;
        _items[pipe].isIndestructible = true;
        _items[pipe].hitBox = 40.f;
    }
}

void MarioKart::createRedPipe(int x, int y)
{
    int pipe = getAvailableItem();

    if (pipe != -1) {
        _items[pipe].x = x;
        _items[pipe].y = y;
        _items[pipe].type = RED_PIPE;
        _items[pipe].lifeTime = 5000.f;
        _items[pipe].isBig = true;
        _items[pipe].isPhysic = true;
        _items[pipe].isIndestructible = true;
        _items[pipe].hitBox = 40.f;
    }
}

int MarioKart::getAvailableItem()
{
    for (int i = 0; i < 2048; i += 1) {
        if (!_items[i].active) {
            _items[i].active = true;
            _items[i].isPhysic = false;
            _items[i].isBig = false;
            _items[i].isIndestructible = false;
            _items[i].hitBox = 80.f;
            return i;
        }
    }
    return -1;
}

int MarioKart::createItemBox(float x, float y)
{
    for (int i = 0; i < 256; i += 1) {
        if (!_boxs[i].active) {
            _boxs[i].active = true;
            _boxs[i].x = x;
            _boxs[i].y = y;
            return 1;
        }
    }
    return 0;
}

void MarioKart::playerAccelerate(float deltaTime)
{
    float lastX = _player.x / 100.f;
    float lastY = _player.y / 100.f;

    /*Speed Gestion*/
    if (_timeBroken > 0) {
        _inputDrift = true;
        _inputAccelerate = 0;
    }

    _player.speed += _inputAccelerate * deltaTime * _player.acceleration;
    if (_player.speed > 0)
        _player.speed -= 5.f * deltaTime;
    if (_player.speed < 0)
        _player.speed += 5.f * deltaTime;

    if (_player.speed > _player.maxSpeed)
        _player.speed = _player.maxSpeed;
    else if (_player.speed < -_player.maxSpeed/2)
        _player.speed = -_player.maxSpeed/2;

    if (_timeMushroom > 0) {
        _timeMushroom -= deltaTime;
        _player.speed = _player.maxSpeed * 2;
    }
    if (_timeBroken > 1) //Bomb
        _player.speed = _player.maxSpeed * 2;

    /*Angle Accelerate*/
    if (_inputDrift) {
        _player.movementX += (_player.lookX - _player.movementX) / 5;
        _player.movementY += (_player.lookY - _player.movementY) / 5;

        _player.x += _player.movementX * deltaTime * _player.driftSpeed * _player.speed * abs(sin(_player.driftAngle - _player.angleLooking)) * 5;
        _player.y += _player.movementY * deltaTime * _player.driftSpeed * _player.speed * abs(sin(_player.driftAngle - _player.angleLooking)) * 5;

        _player.movementX += (cos(_player.driftAngle) * 5 - _player.movementX) / 5;
        _player.movementY += (sin(_player.driftAngle) * 5 - _player.movementY) / 5;

        _player.x += _player.movementX * deltaTime * _player.initialSpeed * 10; //_inputAccelerate
        _player.y += _player.movementY * deltaTime * _player.initialSpeed * 10;
    } else {
        _player.movementX += (_player.lookX - _player.movementX) / 5;
        _player.movementY += (_player.lookY - _player.movementY) / 5;

        _player.x += _player.movementX * deltaTime * _player.speed * 10;
        _player.y += _player.movementY * deltaTime * _player.speed * 10;
    }

    float newX = _player.x / 100.f;
    float newY = _player.y / 100.f;

    if (isPointOnWall({_player.x, _player.y})) {
        _player.x = lastX * 100;
        _player.y = lastY * 100;
        if ((int)newX != (int)lastX)
            _player.movementX *= -1;
        if ((int)newY != (int)lastY)
            _player.movementY *= -1;
    }
}

void MarioKart::playerTurn(float deltaTime)
{
    float maxAngle = _player.maxTurnAngle;
    float driftStabilisation = 1;

    if (_timeBroken > 0) {
        _inputDrift = true;
        _inputTurn = _brokenDirection * 20;
    }
    if (_inputDrift) {
        maxAngle = _player.maxTurnAngle * 1.4f;
        driftStabilisation = 0.25f;
        _player.turningAngle += PI180 * deltaTime * _inputTurn * _player.turnSpeed * 0.4f;
    } else
        _player.turningAngle += PI180 * deltaTime * _inputTurn * _player.turnSpeed;

    if (_player.turningAngle > maxAngle)
        _player.turningAngle = maxAngle;
    else if (_player.turningAngle < -maxAngle)
        _player.turningAngle = -maxAngle;

    /*No Turning*/
    if (_inputTurn == 0) {
        if (_player.turningAngle < 0) {
            _player.turningAngle += PI180 * deltaTime * _player.stabilisationSpeed * driftStabilisation;
            if (_player.turningAngle > 0)
                _player.turningAngle = 0;
        } else {
            _player.turningAngle -= PI180 * deltaTime * _player.stabilisationSpeed * driftStabilisation;
            if (_player.turningAngle < 0)
                _player.turningAngle = 0;
        }
    }

    _player.angleLooking += _player.turningAngle;
    _player.angleLooking = fmod(_player.angleLooking, 2 * PI);
    _player.lookX = cos(_player.angleLooking) * 5;
    _player.lookY = sin(_player.angleLooking) * 5;

    if (_inputTurn < 0)
        _isTurning = -1;
    else if (_inputTurn > 0)
        _isTurning = 1;
    else
        _isTurning = 0;
}

void MarioKart::playerDrift(float deltaTime)
{
    if (_dustTimer > 0.f)
        _dustTimer -= deltaTime;
    if (_timeBroken > 0)
        _inputDrift = true;
    if (!_inputDrift) {
        _player.driftAngle = _player.angleLooking;
        _player.initialSpeed = _player.speed;
    } else {
        _player.driftAngle += (_player.angleLooking - _player.driftAngle) / 5;

        if (_dustTimer <= 0.f) {
            _dustTimer = 0.1f;
            int items = getAvailableItem();

            if (items == -1)
                return;
            float angle = _player.driftAngle;
            float deltaX = cos(angle) * 5;
            float deltaY = sin(angle) * 5;

            _items[items].y = _player.y;
            _items[items].x = _player.x;
            _items[items].deltaX = deltaX;
            _items[items].deltaY = deltaY;
            _items[items].speed = _player.initialSpeed * 4;
            _items[items].lifeTime = 1.2f;
            _items[items].type = DUST;
        }
    }
}

void MarioKart::playerLaunchItem()
{
    if (_inputLaunchItem) {
        if (_itemsStored == NONE)
            return;
        int items = getAvailableItem();

        if (items == -1)
            return;
        float angle = _player.angleLooking;
        float deltaX = cos(angle) * 5;
        float deltaY = sin(angle) * 5;

        _items[items].noCollision = 0.2f;

        if (_itemsStored == SHELL || _itemsStored == RED_SHELL) {
            _items[items].y = _player.y;
            _items[items].x = _player.x;
            _items[items].deltaX = deltaX;
            _items[items].deltaY = deltaY;
            _items[items].speed = 400;
            _items[items].lifeTime = 20;
            _items[items].type = _itemsStored;
            _items[items].isPhysic = true;

        } else if (_itemsStored == MUSHROOM) {
            _items[items].active = false;
            _timeMushroom = 2.f;
        } else {
            _items[items].y = _player.y - deltaY * 10;
            _items[items].x = _player.x - deltaX * 10;
            _items[items].deltaX = 0;
            _items[items].deltaY = 0;
            _items[items].speed = 0;
            _items[items].lifeTime = 120;
            _items[items].type = _itemsStored;
            _items[items].isPhysic = true;
            if (_items[items].type == BOMB)
                _items[items].lifeTime = 3;
        }
        _itemsStored = NONE;
        if (_items[items].active) {
            std::string data = std::to_string(_items[items].type);

            data += "," + std::to_string(_items[items].x);
            data += "," + std::to_string(_items[items].y);
            data += "," + std::to_string(_items[items].deltaX);
            data += "," + std::to_string(_items[items].deltaY);
            data += "," + std::to_string(_items[items].speed);
            data += "," + std::to_string(_items[items].lifeTime);
            data += "," + std::to_string(_items[items].isPhysic);
            data += "," + std::to_string(_items[items].noCollision);
            networkSendPlayerItem(data);
        }
    }
}

std::pair<float, float> MarioKart::getPointFromVector(float angle, float angleZ)
{
    float ndeltaX = cos(angle) * 5;
    float ndeltaY = sin(angle) * 5;
    float ndeltaZ = sin(angleZ) * 5;
    float rayX = _cameraX;
    float rayY = _cameraY;
    float m = 0;

    if (angleZ >= 0)
        return std::make_pair(-1, -1);
    m = _cameraZ / -ndeltaZ;
    rayX += ndeltaX * m;
    rayY += ndeltaY * m;
    return std::make_pair(rayX, rayY);
}

/*
 * 1: RED
 * 2: YELLOW
 * 3: BLUE
 * 4: GREEN
 * 5: PURPLE
 * 6: ORANGE
 * 7: BLACK
 * 8: WHITE
 * 9: DARK RED
 * 10: DARK YELLOW
 * 11: DARK BLUE
 * 12: DARK GREEN
 * 13: DARK PURPLE
 * 14: DARK ORANGE
 * 15: CYAN
 */

int MarioKart::getColorFromPoint(std::pair<float, float> position)
{
    int x = position.first / 100.f;
    int y = position.second / 100.f;
    int result = 0;
    int mario_circuit_colors[5] = {4, 10, 11, 9, 5}; //GRASS, ROAD, WALL1, WALL2, WALL3
    int frozen_kingdom_colors[5] = {8, 15, 13, 11, 5}; //GRASS, ROAD, WALL1, WALL2, WALL3
    int maple_treeway_colors[5] = {6, 14, 9, 10, 5}; //GRASS, ROAD, WALL1, WALL2, WALL3
    int rainbow_road_colors[5] = {7, 5, 7, 7, 7}; //GRASS, ROAD, WALL1, WALL2, WALL3

    if (x < 0 || y < 0 || x >= (MAP_WIDTH + 1) * 5 || y >= (MAP_HEIGHT + 1) * 5) {
        if (_currentMap == MARIO_CIRCUIT)
            return mario_circuit_colors[0];
        if (_currentMap == FROZEN_KINGDOM)
            return frozen_kingdom_colors[0];
        if (_currentMap == MAPLE_TREEWAY)
            return maple_treeway_colors[0];
        if (_currentMap == RAINBOW_ROAD)
            return rainbow_road_colors[0];
    }
    if (_highResMap[y][x] == ' ')
        result = 0;
    if (_highResMap[y][x] == '*' || (_highResMap[y][x] >= '1' && _highResMap[y][x] <= '4'))
        result = 1;
    if (_highResMap[y][x] == 'x') {
        if ((x + y) % 2 == 0)
            result = 2;
        else
            result = 3;
    }
    if (_highResMap[y][x] == '0') {
        if ((x + y) % 2 == 0)
            result = 7;
        else
            result = 8;
        return result;
    }
    if (result >= 0 && result <= 4) {
        if (_currentMap == MARIO_CIRCUIT)
            return mario_circuit_colors[result];
        if (_currentMap == FROZEN_KINGDOM)
            return frozen_kingdom_colors[result];
        if (_currentMap == MAPLE_TREEWAY)
            return maple_treeway_colors[result];
        if (_currentMap == RAINBOW_ROAD) {
            if (result == 1) {
                int color = ((x + y) / 4) % 6;
                color += 9;
                return color;
            }
            return rainbow_road_colors[result];
        }
    }
    return 0;
}

int MarioKart::isPointOnWall(std::pair<float, float> position)
{
    int x = position.first / 100.f;
    int y = position.second / 100.f;

    if (x < 0 || y < 0 || x >= (MAP_WIDTH + 1) * 5 || y >= (MAP_HEIGHT + 1) * 5)
        return -1;
    if (_highResMap[y][x] == ' ')
        return 1;
    if (_highResMap[y][x] == '*' || (_highResMap[y][x] >= '0' && _highResMap[y][x] <= '4'))
        return 0;
    if (_highResMap[y][x] == 'x') {
       return 1;
    }
    return -1;
}

int MarioKart::isOnCheckPoint(std::pair<float, float> position)
{
    int x = position.first / 100.f;
    int y = position.second / 100.f;

    if (x < 0 || y < 0 || x >= (MAP_WIDTH + 1) * 5 || y >= (MAP_WIDTH + 1) * 5)
        return -1;
    if (_highResMap[y][x] >= '0' && _highResMap[y][x] <= '4')
        return _highResMap[y][x] - '0';
    return -1;
}

void noSegFault(int &collisionX, int &collisionY)
{
    if (collisionX < 0)
        collisionX = 0;
    if (collisionX > 80)
        collisionX = 80;
    if (collisionY < 0)
        collisionY = 0;
    if (collisionY > 60)
        collisionY = 60;
}

void MarioKart::getCameraPosition()
{
    _cameraX = _player.x;
    _cameraY = _player.y;

    _cameraX -= cos(_player.angleLooking) * _distanceCamera;
    _cameraY -= sin(_player.angleLooking) * _distanceCamera;
}

int MarioKart::getRightTextureCharacter(int x, int y, bool isFront, int character, float distance, int brokenRotation)
{
    (void)distance;
    if (brokenRotation == 1) {
        int tmp = x;
        x = 5 - y;
        y = tmp;
    } else if (brokenRotation == 2) {
        x = 5 - x;
        y = 5 - y;
    } else if (brokenRotation == 3) {
        int tmp = x;
        x = y;
        y = 5 - tmp;
    }

    if (x < 0 || y < 0 || x >= 6 || y >= 6)
        return 0;
    if (isFront) {
        if (character == MARIO)
            return mario_texture_front[x][y];
        else if (character == LUIGI)
            return luigi_texture_front[x][y];
        else if (character == TOAD)
            return toad_texture_front[x][y];
        else if (character == WARIO)
            return wario_texture_front[x][y];
        else if (character == WALUIGI)
            return waluigi_texture_front[x][y];
        else if (character == BOWSER)
            return bowser_texture_front[x][y];
    } else {
        if (character == MARIO)
            return mario_texture_side[x][y];
        else if (character == LUIGI)
            return luigi_texture_side[x][y];
        else if (character == TOAD)
            return toad_texture_side[x][y];
        else if (character == WARIO)
            return wario_texture_side[x][y];
        else if (character == WALUIGI)
            return waluigi_texture_side[x][y];
        else if (character == BOWSER)
            return bowser_texture_side[x][y];
    }
    return 0;
}

int MarioKart::getRightTextureItems(int x, int y, int items, float distance)
{
    if (distance >= 3600) {
       if (x != 2)
           x = -1;
       if (y != 2)
           y = -1;
    } else  if (distance >= 2400) {
        if (x < 2)
            x -= 1;
        if (y < 2)
            y -= 1;
        if (x > 2)
            x += 1;
        if (y > 2)
            x += 1;
    } else if (distance >= 1200) {
        if (x < 2)
            x -= 1;
        if (y < 2)
            y -= 1;
    }

    if (x < 0 || y < 0 || x >= 4 || y >= 4)
        return 0;

    if (items == DUST)
        return dust_texture[x][y];
    else if (items == SHELL)
        return shell_texture[x][y];
    else if (items == BANANA)
        return banana_texture[x][y];
    else if (items == BOMB)
        return bomb_texture[x][y];
    else if (items == RED_SHELL)
        return red_shell_texture[x][y];
    else if (items == MUSHROOM)
        return mushroom_texture[x][y];
    return 0;
}

int MarioKart::getRightBigTexture(int x, int y, int texture, float distance)
{
    if (distance >= 4800) {
        if (x < 7)
            x -= 5;
        if (x > 7)
            x += 5;
        if (y != 2)
            y = -1;
    } else if (distance >= 3600) {
        if (x < 4)
            x -= 4;
        if (y < 2)
            y -= 3;
        if (x > 7)
            x += 4;
        if (y > 2)
            y += 2;
    } else if (distance >= 2400) {
        if (x < 4)
            x -= 2;
        if (y < 2)
            y -= 1;
        if (x > 7)
            x += 2;
        if (y > 2)
            y += 1;
    } else if (distance >= 1200) {
        if (x < 3)
            x -= 1;
        if (x > 9)
            x += 1;
        if (y < 2)
            y -= 1;
        if (y > 5)
            y += 1;
    }
    if (x < 0 || y < 0 || x >= 12 || y >= 6)
        return 0;

    if (texture == BIG_EXPLOSION)
        return explosion_big[x][y];
    else if (texture == EXPLOSION)
        return explosion_small[x][y];
    else if (texture == TREE)
        return tree_texture[x][y];
    else if (texture == PIPE) {
        if (_currentMap == FROZEN_KINGDOM)
            return snow_man[x][y];
        if (_currentMap == MAPLE_TREEWAY)
            return souche[x][y];
        return pipes[x][y];
    }
    else if (texture == RED_PIPE)
        return red_pipes[x][y];
    return 0;
}

int MarioKart::getRightTextureBox(int x, int y, float distance)
{
    if (distance >= 3600) {
        if (x != 2)
            x = -1;
        if (y != 2)
            y = -1;
    } else  if (distance >= 2400) {
        if (x < 2)
            x -= 1;
        if (y < 2)
            y -= 1;
        if (x > 2)
            x += 1;
        if (y > 2)
            x += 1;
    } else if (distance >= 1200) {
        if (x < 2)
            x -= 1;
        if (y < 2)
            y -= 1;
    }

    if (x < 0 || y < 0 || x >= 4 || y >= 4)
        return 0;

    return ((_boxColor + x + y) % 6) + 1;
}

void MarioKart::drawSkyBox()
{
    int x = _player.angleLooking / (2 * PI) * 360;

    x %= 360;
    if (x < 0)
        x += 360;
    for (int i = 0; i < 60; i += 1) {
        for (int j = 0; j < 80; j += 1) {
            _board[i][j].shapeColor = Arcade::BLACK;
            _board[i][j].shape = Arcade::RECTANGLE;
        }
    }
    for (int i = 0; i < 30; i += 1) {
        for (int j = 0; j < 80; j += 1) {
            _board[i][j].shapeColor = texture_color[_background[i][(x + j) % 360] - 1];
            if (_board[i][j].shapeColor == Arcade::DARK_GREEN && _currentMap == FROZEN_KINGDOM)
                _board[i][j].shapeColor = Arcade::WHITE;
            if (_board[i][j].shapeColor == Arcade::DARK_GREEN && _currentMap == MAPLE_TREEWAY)
                _board[i][j].shapeColor = Arcade::ORANGE;
            _board[i][j].shape = Arcade::RECTANGLE;
        }
    }
}

std::pair<float, float> MarioKart::adjustVector(std::pair<float, float> vector)
{
    std::pair<float, float> result = {vector.first, vector.second};

    float cos_angle = cos(-_player.angleLooking);
    float sin_angle = sin(-_player.angleLooking);

    result.first = vector.first * cos_angle - vector.second * sin_angle;
    result.second = vector.first * sin_angle + vector.second * cos_angle;
    return result;
}

std::pair<int, int> MarioKart::getBoardPosFromWorldPos(std::pair<float, float> position)
{
    int far = 300;
    int near = 50;

    std::pair<float, float> rayUL = {_cameraX + cosf(_player.angleLooking - _fov) * far, _cameraY + sinf(_player.angleLooking - _fov) * far};
    std::pair<float, float> rayUR = {_cameraX + cosf(_player.angleLooking + _fov) * far, _cameraY + sinf(_player.angleLooking + _fov) * far};
    std::pair<float, float> rayDL = {_cameraX + cosf(_player.angleLooking - _fov) * near, _cameraY + sinf(_player.angleLooking - _fov) * near};
    std::pair<float, float> rayDR = {_cameraX + cosf(_player.angleLooking + _fov) * near, _cameraY + sinf(_player.angleLooking + _fov) * near};

    std::pair<float, float> UR = adjustVector({rayUR.first - _cameraX, rayUR.second - _cameraY});
    std::pair<float, float> DR = adjustVector({rayDR.first - _cameraX, rayDR.second - _cameraY});
    std::pair<float, float> UL = adjustVector({rayUL.first - _cameraX, rayUL.second - _cameraY});
    std::pair<float, float> DL = adjustVector({rayDL.first - _cameraX, rayDL.second - _cameraY});
    std::pair<float, float> P = adjustVector({position.first - _cameraX, position.second - _cameraY});

    float py = (P.first - DR.first);
    float uy = (UR.first - DR.first);
    float y = uy / py;

    float swx = (UL.second - DL.second) / y + DL.second;
    float ewx = (UR.second - DR.second) / y + DR.second;

    float x = (P.second - swx) / (ewx - swx);

    int i = (y * 45);
    int j = (x * 80);

    return {i, j};
}

void MarioKart::bombExplosion(int i)
{
    float distance = sqrt(pow(_items[i].x - _player.x, 2) + pow(_items[i].y - _player.y, 2));

    if (distance < 300.f) {
        _items[i].active = false;
        _timeBroken = 1.f;
        _brokenDirection = rand() % 2;
        if (_brokenDirection == 0)
            _brokenDirection = -1;

        _timeBroken = 1.5f;
    }

    for (int k = 0; k < 8; k += 1) {
        int items = getAvailableItem();
        if (items == -1)
            return;

        _items[items].y = _items[i].y + rand() % 50 - 25;
        _items[items].x = _items[i].x + rand() % 50 - 25;
        _items[items].deltaX = _items[items].x - _items[i].x;
        _items[items].deltaY = _items[items].y - _items[i].y;
        _items[items].speed = 2;
        _items[items].lifeTime = 1.2f;
        _items[items].type = EXPLOSION;
        _items[items].isBig = true;
    }
    int items = getAvailableItem();
    if (items == -1)
        return;

    _items[items].y = _items[i].y;
    _items[items].x = _items[i].x;
    _items[items].deltaX = 0;
    _items[items].deltaY = 0;
    _items[items].speed = 0;
    _items[items].lifeTime = 1.2f;
    _items[items].type = BIG_EXPLOSION;
    _items[items].isBig = true;
}

void MarioKart::updateItems(float deltaTime)
{
    for (int i = 0; i < 2048; i += 1) {
        if (!_items[i].active)
            continue;

        float lastX = _items[i].x / 100.f;
        float lastY = _items[i].y / 100.f;

        _items[i].x += _items[i].deltaX * deltaTime * _items[i].speed;
        _items[i].y += _items[i].deltaY * deltaTime * _items[i].speed;;
        _items[i].lifeTime -= deltaTime;
        if (_items[i].lifeTime <= 0) {
            if (_items[i].type == BOMB)
                bombExplosion(i);
            _items[i].active = false;
        }
        if (_items[i].noCollision > 0) {
            _items[i].noCollision -= deltaTime;
        }

        float newX = _items[i].x / 100.f;
        float newY = _items[i].y / 100.f;

        if (isPointOnWall({_items[i].x, _items[i].y})) {
            _items[i].x = lastX * 100;
            _items[i].y = lastY * 100;
            if ((int)newX != (int)lastX)
                _items[i].deltaX *= -1;
            if ((int)newY != (int)lastY)
                _items[i].deltaY *= -1;
        }

        float distance = sqrt(pow(_items[i].x - _player.x, 2) + pow(_items[i].y - _player.y, 2));

        if (distance < _items[i].hitBox && _items[i].noCollision <= 0 && _items[i].isPhysic) {
            if (!_items[i].isIndestructible)
                _items[i].active = false;
            _timeBroken = 1.f;
            _brokenDirection = rand() % 2;
            if (_brokenDirection == 0)
                _brokenDirection = -1;
            if (_items[i].type == BOMB) {
                bombExplosion(i);
            }
        }
    }
}

void MarioKart::updateBox(float deltaTime)
{
    for (int i = 0; i < 256; i += 1) {
        if (!_boxs[i].active)
            continue;
        if (_boxs[i].timer > 0) {
            _boxs[i].timer -= deltaTime;
            continue;
        }

        float distance = sqrt(pow(_boxs[i].x - _player.x, 2) + pow(_boxs[i].y - _player.y, 2));

        if (distance < 100.f) {
            _boxs[i].timer = 10.f;
            if (_itemsStored == NONE)
                _itemsStored = (ItemsType)((rand() % 5) + 2);
            networkSendPlayerBox(std::to_string(i));
        }
    }
}

void MarioKart::drawItems()
{
    for (int i = 0; i < 2048; i += 1) {
        if (!_items[i].active)
            continue;
        std::pair<int, int> worldPosition = getBoardPosFromWorldPos({_items[i].x, _items[i].y});
        float distance = sqrt(pow(_items[i].x - _cameraX, 2) + pow(_items[i].y - _cameraY, 2));
        if (distance >= 5000 || worldPosition.first < 0 || worldPosition.first >= 45 || worldPosition.second < 0 || worldPosition.second >= 80)
            continue;

        for (int y = 0; y < 16; y += 1) {
            for (int x = 0; x < 6; x += 1) {
                int di = worldPosition.first - 4 + y;
                int dj = worldPosition.second - 2 + x;

                if (_items[i].isBig) {
                    di = worldPosition.first - 12 + y;
                    dj = worldPosition.second - 3 + x;
                } else {
                    if (y >= 4)
                        continue;
                    if (x >= 4)
                        continue;
                }

                if (di < -15 || di >= 45 || dj < 0 || dj >= 80)
                    continue;

                int color = 0;
                if (_items[i].isBig)
                    color = getRightBigTexture(y, x, _items[i].type, distance);
                else
                    color = getRightTextureItems(y, x, _items[i].type, distance);
                int offset = 0;

                if (distance >= 3600)
                    offset = 2;
                else if (distance >= 2400)
                   offset = 1;

                if (_items[i].isBig) {
                    if (distance >= 3600)
                        offset = 5;
                    else if (distance >= 2400)
                        offset = 3;
                    else if (distance >= 1200)
                        offset = 1;
                }

                if (color != 0) {
                    _board[di + 15 + offset][dj].shapeColor = texture_color[color - 1];
                    if (_currentMap == MAPLE_TREEWAY) {
                        if (_board[di + 15 + offset][dj].shapeColor == Arcade::Color::DARK_GREEN)
                            _board[di + 15 + offset][dj].shapeColor = Arcade::Color::YELLOW;
                    }
                }
            }
        }
    }
}

void MarioKart::drawBox()
{
    for (int i = 0; i < 256; i += 1) {
        if (!_boxs[i].active || _boxs[i].timer > 0)
            continue;
        std::pair<int, int> worldPosition = getBoardPosFromWorldPos({_boxs[i].x, _boxs[i].y});
        float distance = sqrt(pow(_boxs[i].x - _cameraX, 2) + pow(_boxs[i].y - _cameraY, 2));

        for (int y = 0; y < 4; y += 1) {
            for (int x = 0; x < 4; x += 1) {
                int di = worldPosition.first - 4 + y;
                int dj = worldPosition.second - 2 + x;

                if (di < 0 || di >= 45 || dj < 0 || dj >= 80)
                    continue;
                int color = getRightTextureBox(y, x, distance);
                int offset = 0;

                if (distance >= 3600)
                    offset = 2;
                else if (distance >= 2400)
                    offset = 1;

                if (color != 0)
                    _board[di + 15 + offset][dj].shapeColor = texture_color[color - 1];
            }
        }
    }
}

void MarioKart::drawMainPlayer()
{
    std::pair<int, int> worldPosition = getBoardPosFromWorldPos({_player.x, _player.y});
    float distance = sqrt(pow(_player.x - _cameraX, 2) + pow(_player.y - _cameraY, 2));

    for (int i = 0; i < 6; i += 1) {
        for (int j = 0; j < 6; j += 1) {
            int color = 0;
            int rotation = _brokenRotation;

            if (_timeBroken <= 0)
                rotation = 0;
            if (_isTurning == -1)
                color = getRightTextureCharacter(i, j, false, _characterSelected, distance, rotation);
            else  if (_isTurning == 1)
                color = getRightTextureCharacter(i, 5 - j, false, _characterSelected, distance, rotation);
            else
                color = getRightTextureCharacter(i, j, true, _characterSelected, distance, rotation);

            if (color == 0)
                continue;
            Arcade::Color ma = texture_color[color - 1];

            int di = worldPosition.first - 6 + i;
            int dj = worldPosition.second - 3 + j;

            if (di < 0 || di >= 45 || dj < 0 || dj >= 80)
                continue;
            _board[(di) + 15][dj].shapeColor = ma;
        }
    }
}

void MarioKart::drawBots()
{
    for (int k = 0; k < 5; k += 1) {
        if (!_bots[k].active)
            continue;
        std::pair<int, int> worldPosition = getBoardPosFromWorldPos({_bots[k].x, _bots[k].y});
        float distance = sqrt(pow(_bots[k].x - _cameraX, 2) + pow(_bots[k].y - _cameraY, 2));

        for (int i = 0; i < 6; i += 1) {
            for (int j = 0; j < 6; j += 1) {
                int color = 0;

                if (_bots[k].isTurning == -1)
                    color = getRightTextureCharacter(i, j, false, _bots[k].character, distance, _bots[k].rotation);
                else if (_bots[k].isTurning == 1)
                    color = getRightTextureCharacter(i, 5 - j, false, _bots[k].character, distance, _bots[k].rotation);
                else
                    color = getRightTextureCharacter(i, j, true, _bots[k].character, distance, _bots[k].rotation);
                if (color == 0)
                    continue;
                Arcade::Color ma = texture_color[color - 1];

                int di = worldPosition.first - 6 + i;
                int dj = worldPosition.second - 3 + j;

                if (di < 0 || di >= 45 || dj < 0 || dj >= 80)
                    continue;
                _board[(di) + 15][dj].shapeColor = ma;
            }
        }
    }
}

void MarioKart::drawMap()
{
    int far = 300;
    int near = 50;

    getCameraPosition();

    std::pair<float, float> rayUL = {_cameraX + cosf(_player.angleLooking - _fov) * far, _cameraY + sinf(_player.angleLooking - _fov) * far};
    std::pair<float, float> rayUR = {_cameraX + cosf(_player.angleLooking + _fov) * far, _cameraY + sinf(_player.angleLooking + _fov) * far};
    std::pair<float, float> rayDL = {_cameraX + cosf(_player.angleLooking - _fov) * near, _cameraY + sinf(_player.angleLooking - _fov) * near};
    std::pair<float, float> rayDR = {_cameraX + cosf(_player.angleLooking + _fov) * near, _cameraY + sinf(_player.angleLooking + _fov) * near};

    for (int i = 0; i < 45; i += 1) {
        for (int j = 0; j < 80; j += 1) {
            float y = i / 45.f;
            float x = j / 80.f;

            std::pair<float, float> heightL = {rayUL.first - rayDL.first, rayUL.second - rayDL.second};
            std::pair<float, float> heightR = {rayUR.first - rayDR.first, rayUR.second - rayDR.second};
            std::pair<float, float> startW = {rayDL.first + heightL.first / y, rayDL.second + heightL.second / y};
            std::pair<float, float> endW = {rayDR.first + heightR.first / y, rayDR.second + heightR.second / y};
            std::pair<float, float> width = {endW.first - startW.first, endW.second - startW.second};
            std::pair<float, float> point = {startW.first + width.first * x, startW.second + width.second * x};

            int color = getColorFromPoint(point);
            int screenHeight = i + 15;

            _board[screenHeight][j].shapeColor = texture_color[color - 1];
        }
    }
}

std::string MarioKart::getCharacterName(int character)
{
    if (character == MARIO)
        return "Mr:";
    else if (character == LUIGI)
        return "Lg:";
    else if (character == TOAD)
        return "Td:";
    else if (character == WARIO)
        return "Wr:";
    else if (character == WALUIGI)
        return "Wl:";
    else if (character == BOWSER)
        return "Bw:";
    return "Er:";
}

void MarioKart::drawHud()
{
    /*Draw score and info*/
    for (int i = 0; i < 80; i += 1) {
        _board[0][i].shapeColor = Arcade::BLACK;
        _board[0][i].shape = Arcade::RECTANGLE;
        _board[1][i].shapeColor = Arcade::BLACK;
        _board[1][i].shape = Arcade::RECTANGLE;
    }
    _board[0][2].shape = Arcade::TEXT;
    _board[0][2].shapeColor = Arcade::WHITE;
    _board[0][2].textOrPath =  getCharacterName(_characterSelected) + "Lap " + std::to_string(_currentLap + 1) + "/3";
    if (_hasFinish)
        _board[0][2].textOrPath = getCharacterName(_characterSelected) + "Finish";

    for (int i = 0; i < 5; i += 1) {
        if (!(_bots[i].active))
            continue;
        _board[0][14 + i * 12].shape = Arcade::TEXT;
        _board[0][14 + i * 12].shapeColor = Arcade::WHITE;
        _board[0][14 + i * 12].textOrPath = getCharacterName(_bots[i].character) + "Lap " + std::to_string(_bots[i].lap + 1) + "/3";
        if (_bots[i].hasFinish)
            _board[0][14 + i * 12].textOrPath = getCharacterName(_bots[i].character) + "Finish";
    }

    for (int i = 2; i < 8; i += 1) {
        for (int j = 73; j < 79; j += 1) {
            if ((i == 2 && (j == 73 || j == 78)) || (i == 7 && (j == 73 || j == 78)))
                continue;
            if (i == 2 || i == 7 || j == 73 || j == 78)
                _board[i][j].shapeColor = Arcade::WHITE;
            else
                _board[i][j].shapeColor = Arcade::BLACK;
        }
    }

    if (_itemsStored == NONE)
        return;
    for (int i = 0; i < 4; i += 1) {
        for (int j = 0; j < 4; j += 1) {
            int color = getRightTextureItems(i, j, _itemsStored, 0);

            if (color != 0)
                _board[i + 3][j + 74].shapeColor = texture_color[color - 1];
        }
    }
}

void MarioKart::networkUpdate(float deltaTime)
{
    fd_set recv_fds;
    fd_set send_fds;
    char message[2048];
    struct timeval tv = {0, 10000}; // Do not wait on select for more than 10ms

    _network.timer -= deltaTime;
    FD_ZERO(&recv_fds);
    FD_ZERO(&send_fds);
    FD_SET(_network.sock, &recv_fds);
    FD_SET(_network.sock, &send_fds);
    // Wait for recv or send to be ready
    if ((select(FD_SETSIZE, &recv_fds, &send_fds, NULL, &tv) < 0) && (errno != EINTR)) {
        perror("select");
        exit(84);
    }
    // Receive
    if (FD_ISSET(_network.sock, &recv_fds)) {
        int cnt = recvfrom(_network.sock, message, sizeof(message), 0, (struct sockaddr *) &(_network.addr_recv), (socklen_t *) &(_network.addrlen));
        if (cnt < 0) {
            perror("recvfrom");
            exit(84);
        } else if (cnt == 0)
            return;
        if (strncmp(_network.id.c_str(), message, strlen(_network.id.c_str())))
            networkParse(message);
    }
    // Send
    if (FD_ISSET(_network.sock, &send_fds)) {
        if (_network.timer < 0) {
            _network.timer = 0.12f;
            if (!_inMenu)
                networkSendPlayerPosition("empty");
            networkSend();
            _network.messageIndex = 0;
            for (int i = 0; i < 16; i++)
                _network.message[i] = "";
        }
    }
}

void MarioKart::updateMenu(float deltaTime)
{
    if (_timerMenu > 0)
        _timerMenu -= deltaTime;
    else {
        if (_inputMenu == 1) {
            _characterSelected += 1;
            if (_characterSelected > 5)
                _characterSelected = 0;
            _isReady = false;
            networkSendIsReady("0");
            networkSendCharacter(std::to_string(_characterSelected));
            _timerMenu = 0.2f;
        } else if (_inputMenu == 2) {
            _characterSelected -= 1;
            if (_characterSelected < 0)
                _characterSelected = 5;
            _isReady = false;
            networkSendIsReady("0");
            networkSendCharacter(std::to_string(_characterSelected));
            _timerMenu = 0.2f;
        } else if (_inputMenu == 3) {
            _isReady = true;
            networkSendIsReady("1");
        }
    }
    _inputMenu = 0;

    if (_isReady) {
        bool okay = true;

        for (int i = 0; i < 5; i += 1) {
            if (!_bots[i].active)
                continue;
            if (!_bots[i].isReady)
                okay = false;
        }
        if (okay) {
            _inMenu = false;
        }
    }

    for (int i = 0; i < 60; i += 1) {
       for (int j = 0; j < 80; j += 1) {
           _board[i][j].shapeColor = Arcade::CYAN;
           _board[i][j].shape = Arcade::RECTANGLE;
       }
    }

    for (int i = 0; i < 6; i += 1) {
        for (int j = 0; j < 6; j += 1) {
            int color = getRightTextureCharacter(i, j, true, _characterSelected, 0, 0);
            if (color > 0)
                _board[i + 24][j + 6].shapeColor = texture_color[color - 1];
        }
    }

    for (int i = 0; i < 9; i += 1) {
        _board[31][6 + i].shape = Arcade::RECTANGLE;
        _board[31][6 + i].shapeColor = Arcade::BLACK;
        _board[32][6 + i].shape = Arcade::RECTANGLE;
        _board[32][6 + i].shapeColor = Arcade::BLACK;
    }
    if (_isReady) {
        _board[31][8].shape = Arcade::TEXT;
        _board[31][8].shapeColor = Arcade::GREEN;
        _board[31][8].textOrPath = "Ready";
    } else {
        _board[31][6].shape = Arcade::TEXT;
        _board[31][6].shapeColor = Arcade::RED;
        _board[31][6].textOrPath = "Not Ready";
    }

    for (int k = 0; k < 5; k += 1) {
        if (!_bots[k].active) {
            for (int i = 0; i < 7; i += 1) {
                _board[26][20 + i + k * 10].shape = Arcade::RECTANGLE;
                _board[26][20 + i + k * 10].shapeColor = Arcade::BLACK;
                _board[27][20 + i + k * 10].shape = Arcade::RECTANGLE;
                _board[27][20 + i + k * 10].shapeColor = Arcade::BLACK;
            }

            _board[26][20 + k * 10].shape = Arcade::TEXT;
            _board[26][20 + k * 10].shapeSize = {1, 1};
            _board[26][20 + k * 10].shapeColor = Arcade::WHITE;
            _board[26][20 + k * 10].textOrPath = "No Player";
            continue;
        }
        for (int i = 0; i < 6; i += 1) {
            for (int j = 0; j < 6; j += 1) {
                    int color = getRightTextureCharacter(i, j, true, _bots[k].character, 0, 0);
                    if (color > 0)
                        _board[i + 24][j + 14 + k * 10].shapeColor = texture_color[color - 1];
            }
        }

        /*Ready*/
        for (int i = 0; i < 9; i += 1) {
            _board[31][16 + i + k * 10].shape = Arcade::RECTANGLE;
            _board[31][16 + i + k * 10].shapeColor = Arcade::BLACK;
            _board[32][16 + i + k * 10].shape = Arcade::RECTANGLE;
            _board[32][16 + i + k * 10].shapeColor = Arcade::BLACK;
        }
        if (_bots[k].isReady) {
            _board[31][18 + k * 10].shape = Arcade::TEXT;
            _board[31][18 + k * 10].shapeColor = Arcade::GREEN;
            _board[31][18 + k * 10].textOrPath = "Ready";
        } else {
            _board[31][16 + k * 10].shape = Arcade::TEXT;
            _board[31][16 + k * 10].shapeColor = Arcade::RED;
            _board[31][16 + k * 10].textOrPath = "Not Ready";
        }
    }
}

void updateEndScreen(float deltaTime)
{
    (void)deltaTime;
}

void MarioKart::update(float deltaTime)
{
    networkUpdate(deltaTime);
    if (_inMenu) {
        updateMenu(deltaTime);
        return;
    }
    if (_endScreen) {
        updateEndScreen(deltaTime);
        return;
    }
    updateItems(deltaTime);
    updateBox(deltaTime);
    if (_hasFinish) {
        _inputAccelerate = 0;
        _inputTurn = 0;
        _inputLaunchItem = false;

        bool okay = true;

        for (int i = 0; i < 5; i += 1) {
            if (!_bots[i].active)
                continue;
            if (!_bots[i].hasFinish)
                okay = false;
        }
        if (okay) {
            _currentMap += 1;
            if (_currentMap >= 4) {
                _currentMap = 0;
                _endScreen = true;
            } else {
                _hasFinish = false;
                _currentLap = 0;
                _currentCheckPoint = 0;
                initMap();
            }
        }
    }
    playerTurn(deltaTime);
    _inputTurn = 0;
    playerDrift(deltaTime);
    playerAccelerate(deltaTime);
    _inputAccelerate = 0;
    playerLaunchItem();
    _inputLaunchItem = false;

    int checkpoint = isOnCheckPoint({_player.x, _player.y});
    if (checkpoint == _currentCheckPoint + 1) {
        _currentCheckPoint += 1;
    } else if (checkpoint == 0 && _currentCheckPoint == 3) {
        _currentCheckPoint = 0;
        _currentLap += 1;
        if (_currentLap >= 3)
            _hasFinish = true;
        networkSendHasFinish(std::to_string(_currentLap));
    }

    if (_timeBroken > 0) {
        _timeBroken -= deltaTime;
        _brokenRotationTimer -= deltaTime;
        if (_brokenRotationTimer <= 0) {
            _brokenRotationTimer = 0.1f;
            _brokenRotation += 1;
            _brokenRotation %= 4;
        }
    }

    drawSkyBox();
    drawMap();
    drawBots();
    drawMainPlayer();
    drawItems();
    drawBox();
    drawHud();

    _boxTimer -= deltaTime;
    if (_boxTimer < 0) {
        _boxTimer = 0.1f;
        _boxColor += 1;
        _boxColor %= 6;
    }
    _inputDrift = false;
}

void MarioKart::onInputPressed(Arcade::InputAction input, bool isPressed)
{
    if (!isPressed)
        return;
    if (input == Arcade::InputAction::LEFT)
        _inputTurn = -10;
    if (input == Arcade::InputAction::RIGHT)
        _inputTurn = 10;
    if (input == Arcade::InputAction::UP) {
        _inputAccelerate = 10;
        _inputMenu = 1;
    }
    if (input == Arcade::InputAction::DOWN) {
        _inputAccelerate = -5;
        _inputMenu = 2;
    }
    if (input == Arcade::InputAction::BUTTON1) {
        _inputDrift = true;
        _inputMenu = 3;
    }
    if (input == Arcade::InputAction::BUTTON2) {
        _inputLaunchItem = true;
        _inputMenu = 3;
    }
}

void MarioKart::networkParse(std::string data)
{
    std::string id = data.substr(0, data.find(":"));
    data = data.substr(data.find(":") + 1, data.length());

    while (data.find(":") != std::string::npos) {
        std::string message = data.substr(0, data.find(":"));
        data = data.substr(data.find(":") + 1, data.length());
        std::string info = data.substr(0, data.find(":"));
        data = data.substr(data.find(":") + 1, data.length());
        info = info.substr(0, info.find("!"));

        if (message == "Nc") {
            bool alreadyExist = false;
            for (int i = 0; i < 5; i += 1) {
                if (_bots[i].id == id && _bots[i].active) {
                    alreadyExist = true;
                    break;
                }
            }
            if (!alreadyExist) {
                for (int i = 0; i < 5; i += 1) {
                    if (!_bots[i].active) {
                        _bots[i].active = true;
                        _bots[i].id = id;
                        break;
                    }
                }
            }
            if (info == "ping") {
                networkSendNewConnection("pong");
            }
        } else if (message == "Pos") {
            std::string x = info.substr(0, info.find(","));
            info = info.substr(info.find(",") + 1, info.length());
            std::string y = info.substr(0, info.find(","));
            info = info.substr(info.find(",") + 1, info.length());
            std::string direction = info.substr(0, info.find(","));
            info = info.substr(info.find(",") + 1, info.length());
            std::string rotation = info.substr(0, info.find(","));


            for (int i = 0; i < 5; i += 1) {
                if (_bots[i].id == id && _bots[i].active) {
                    _bots[i].x = std::stof(x);
                    _bots[i].y = std::stof(y);
                    _bots[i].isTurning = std::stof(direction);
                    _bots[i].rotation = std::stof(rotation);
                    break;
                }
            }
        } else if (message == "It") {
            int items = getAvailableItem();

            if (items == -1)
                return;
            _items[items].active = true;
            _items[items].type = (ItemsType)std::stoi(info.substr(0, info.find(",")));
            info = info.substr(info.find(",") + 1, info.length());
            _items[items].x = std::stof(info.substr(0, info.find(",")));
            info = info.substr(info.find(",") + 1, info.length());
            _items[items].y = std::stof(info.substr(0, info.find(",")));
            info = info.substr(info.find(",") + 1, info.length());
            _items[items].deltaX = std::stof(info.substr(0, info.find(",")));
            info = info.substr(info.find(",") + 1, info.length());
            _items[items].deltaY = std::stof(info.substr(0, info.find(",")));
            info = info.substr(info.find(",") + 1, info.length());
            _items[items].speed = std::stof(info.substr(0, info.find(",")));
            info = info.substr(info.find(",") + 1, info.length());
            _items[items].lifeTime = std::stof(info.substr(0, info.find(",")));
            info = info.substr(info.find(",") + 1, info.length());
            _items[items].isPhysic = std::stoi(info.substr(0, info.find(",")));
            info = info.substr(info.find(",") + 1, info.length());
            _items[items].noCollision = std::stoi(info.substr(0, info.find(",")));
        } else if (message == "Bx") {
            _boxs[atoi(info.c_str())].timer = 10.f;
        } else if (message == "Ch") { //change character
            for (int i = 0; i < 5; i += 1) {
                if (_bots[i].id == id && _bots[i].active) {
                    _bots[i].character = (characters)std::stoi(info);
                    break;
                }
            }
        } else if (message == "Rd") { //ready
            for (int i = 0; i < 5; i += 1) {
                if (_bots[i].id == id && _bots[i].active) {
                    _bots[i].isReady = true;
                    if (info == "0")
                        _bots[i].isReady = false;
                    break;
                }
            }
        } else if (message == "Fn") { //finish
            for (int i = 0; i < 5; i += 1) {
                if (_bots[i].id == id && _bots[i].active) {
                    _bots[i].lap = std::stoi(info);
                    if (_bots[i].lap >= 1) { //TODO change 1 to 3
                        _bots[i].hasFinish = true;
                        _rank += 1;
                    }
                    break;
                }
            }
        }
    }
}

void MarioKart::networkSend()
{
    std::string message = _network.id;
    for (int i = 0; i < _network.messageIndex; i += 1)
        message += ":" + _network.message[i] + "!";
    if (_network.messageIndex == 0)
        return;
    int cnt = sendto(_network.sock, message.c_str(), message.length(), 0, (struct sockaddr *) &(_network.addr_send),
                     _network.addrlen);
    if (cnt < 0) {
        perror("sendto");
        exit(84);
    }
}

void MarioKart::networkSendNewConnection(std::string data)
{
    std::string message = "Nc:" + data;

    std::cout << "send: " << message << std::endl;
    if (_network.messageIndex >= 15)
        return;
    _network.message[_network.messageIndex] = message;
    _network.messageIndex += 1;
}

void MarioKart::networkSendPlayerPosition(std::string data)
{
    (void)(data);
    std::string message = "Pos:";

    if (_network.messageIndex >= 15)
        return;
    message += std::to_string(_player.x) + "," + std::to_string(_player.y);
    message += "," + std::to_string(_isTurning);
    int brokenRotation = _brokenRotation;
    if (_timeBroken <= 0)
        brokenRotation = 0;
    message += "," + std::to_string(brokenRotation);
    _network.message[_network.messageIndex] = message;
    _network.messageIndex += 1;
}

void MarioKart::networkSendPlayerItem(std::string data)
{
    std::string message = "It:" + data;

    if (_network.messageIndex >= 15)
        return;
    _network.message[_network.messageIndex] = message;
    _network.messageIndex += 1;
}

void MarioKart::networkSendCharacter(std::string data)
{
    std::string message = "Ch:" + data;

    if (_network.messageIndex >= 15)
        return;
    _network.message[_network.messageIndex] = message;
    _network.messageIndex += 1;
}

void MarioKart::networkSendIsReady(std::string data)
{
    std::string message = "Rd:" + data;

    if (_network.messageIndex >= 15)
        return;
    _network.message[_network.messageIndex] = message;
    _network.messageIndex += 1;
}

void MarioKart::networkSendHasFinish(std::string data)
{
    std::string message = "Fn:" + data;

    if (_network.messageIndex >= 15)
        _network.messageIndex = 2;
    _network.message[_network.messageIndex] = message;
    _network.messageIndex += 1;
}

void MarioKart::networkSendPlayerBox(std::string data)
{
    std::string message = "Bx:" + data;

    if (_network.messageIndex >= 15)
        return;
    _network.message[_network.messageIndex] = message;
    _network.messageIndex += 1;
}

void __attribute__((constructor)) my_constructor() {

}

void __attribute__((destructor)) my_destructor() {

}

extern "C" Arcade::IGameModule* entryGame() {
    return new MarioKart;
}