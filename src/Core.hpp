/*
** EPITECH PROJECT, 2023
** IGameModule.h$
** File description:
** IGameModule.h$
*/

#pragma once
#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <cstring>
#include <vector>
#include <dirent.h>
#include <chrono>
#include <thread>
#include <dlfcn.h>
#include <memory>
#include "DLLoader.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"

#define NB_VALID_CHAR 36
static const char valid_char[36] = {
        'A', 'B', 'C', 'D', 'E', 'F',
        'G', 'H', 'I', 'J', 'K', 'L',
        'M', 'N', 'O', 'P', 'Q', 'R',
        'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9'
};

namespace Arcade {
    enum stateMenu {
        MENU_GRAPHICAL = 0,
        MENU_GAME,
        MENU_USERNAME1,
        MENU_USERNAME2,
        MENU_USERNAME3
    };

    class Core {
    public:
        Core(std::string graphical);
        ~Core();
        std::vector<std::string> getAllSharedLib(std::string directoryToSearch);
        void refreshLibs();
        void changeLib();
        void changeGame();
        void coreLoop();
        void refreshDeltaTime();
        void printActualGame();
        void printActualGraphical();
        void loadGame(std::string gameName);
        void loadGraphical(std::string graphicalName);
        Arcade::IGameModule *getGameModule();
        Arcade::IDisplayModule *getGraphicalModule();
        void drawToGraphical(std::array<std::array<BoardCell, 80>, 60> &board);
        void launchGame();
        std::array<std::array<BoardCell, 80>, 60> boardMenu(std::array<std::array<BoardCell, 80>, 60> board, std::vector<int> inputs);
        void getHighScores();
        void addHighScore(std::string name, int score);
    private:
        std::vector<std::string> _games;
        std::vector<std::string> _graphics;
        float _deltaTime;
        std::chrono::high_resolution_clock::time_point _previousTime;
        bool _hasStopped;
        bool _hasAGame;
        std::unique_ptr<Arcade::DLLoader<Arcade::IDisplayModule>> _loaderGraphical;
        std::string _actualGraphical;
        int _numberForActualGraphical;
        std::unique_ptr<Arcade::DLLoader<Arcade::IGameModule>> _loaderGame;
        std::string _actualGame;
        int _numberForActualGame;
        char _username[3];
        int _validChar[3];
        int _stateMenu;
        int _selectorMenu;
        float _inputsTimer[9];

        std::string _hsNames[20];
        int _hsScores[20];
        int _currentScore;
    };
}
