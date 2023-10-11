/*
** EPITECH PROJECT, 2023
** ADisplayModule.cpp$
** File description:
** ADisplayModule.cpp$
*/

#include "Core.hpp"
#include "Menu/Menu.hpp"

Arcade::Core::Core(std::string graphical)
{
    _games = getAllSharedLib("games");
    _graphics = getAllSharedLib("graphical");
    _hasStopped = false;
    _previousTime = std::chrono::high_resolution_clock::now();
    _deltaTime = 0;
    _hasAGame = false;
    _loaderGame = nullptr;
    _loaderGraphical = nullptr;
    _loaderGame = std::make_unique<Arcade::DLLoader<Arcade::IGameModule>>("./src/Menu/arcade_menu.so", GAME);
    _actualGame = "Menu";
    _loaderGraphical = std::make_unique<Arcade::DLLoader<Arcade::IDisplayModule>>(graphical, GRAPHICAL);
    _actualGraphical = graphical;
    for (int i = 0; i < 3; i += 1) {
        _username[i] = 'A';
        _validChar[i] = 0;
    }
    _stateMenu = Arcade::MENU_GRAPHICAL;
    _selectorMenu = 0;
    _numberForActualGame = 0;
    _numberForActualGraphical = 0;
    for (int i = 0; i < 9; i += 1)
        _inputsTimer[i] = 0.f;
    for (int i = 0; i < 20; i += 1) {
        _hsNames[i] = "";
        _hsScores[i] = 0;
    }
    _currentScore = 0;
    getHighScores();
}

Arcade::Core::~Core()
{
    _games.clear();
    _graphics.clear();
    _loaderGame = nullptr;
    _loaderGraphical = nullptr;
}

void Arcade::Core::printActualGame()
{
    std::cout << "Actual game: " << _actualGame << std::endl;
}

void Arcade::Core::printActualGraphical()
{
    std::cout << "Actual graphical: " << _actualGraphical << std::endl;
}

std::vector<std::string> Arcade::Core::getAllSharedLib(std::string directoryToSearch)
{
    std::vector<std::string> shared_libraries = {};
    DIR* dir = opendir("./lib");
    struct dirent* entry;

    if (dir == NULL) {
        std::cerr << "Erreur lors de l'ouverture du répertoire" << std::endl;
        return shared_libraries;
    }
    while ((entry = readdir(dir)) != NULL)
        if (std::strstr(entry->d_name, ".so") != NULL) {
            void * createFunc = nullptr;
            std::string path = "./lib/" + std::string(entry->d_name);
            void *handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!handle)
                throw std::runtime_error(dlerror());
            if (directoryToSearch == "graphical")
                createFunc = reinterpret_cast<void *>(dlsym(handle, "entryDisplay"));
            else if (directoryToSearch == "games")
                createFunc = reinterpret_cast<void *>(dlsym(handle, "entryGame"));
            if (!createFunc) {
                continue;
            }
            shared_libraries.push_back(entry->d_name);
        }
    closedir(dir);
    return shared_libraries;
}

void Arcade::Core::refreshLibs()
{
    _games.clear();
    _graphics.clear();
    _games = getAllSharedLib("games");
    _graphics = getAllSharedLib("graphical");
}

void Arcade::Core::refreshDeltaTime()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = currentTime - _previousTime;
    _deltaTime = duration.count();
    _previousTime = currentTime;
}

void Arcade::Core::loadGame(std::string gameName)
{
    std::string path = "./lib/" + gameName;
    _loaderGame = std::make_unique<Arcade::DLLoader<Arcade::IGameModule>>(path, GAME);
    _actualGame = gameName;
}

void Arcade::Core::loadGraphical(std::string graphicalName)
{
    std::string path = "./lib/" + graphicalName;
    _loaderGraphical = std::make_unique<Arcade::DLLoader<Arcade::IDisplayModule>>(path, GRAPHICAL);
    _actualGraphical = graphicalName;
}

Arcade::IGameModule *Arcade::Core::getGameModule()
{
    auto game = _loaderGame->getInstance();
    return game;
}

Arcade::IDisplayModule *Arcade::Core::getGraphicalModule()
{
    auto graphical = _loaderGraphical->getInstance();
    return graphical;
}

void Arcade::Core::drawToGraphical(std::array<std::array<BoardCell, 80>, 60> &board)
{
    getGraphicalModule()->cleanScreen();
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 80; j++) {
            if (board[i][j].shape == Arcade::RECTANGLE)
                getGraphicalModule()->drawRectangle(j, i, board[i][j].shapeSize.first,
                                                    board[i][j].shapeSize.second,
                                                    board[i][j].shapeColor, NORTH, board[i][j].textOrPath);
        }
    }
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 80; j++) {
            if (board[i][j].shape == Arcade::CIRCLE)
                getGraphicalModule()->drawCircle(j, i, board[i][j].shapeSize.first,
                                                 board[i][j].shapeSize.second,
                                                 board[i][j].shapeColor, NORTH, board[i][j].textOrPath);
        }
    }
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 80; j++) {
            if (board[i][j].shape == Arcade::TEXT)
                getGraphicalModule()->drawText(j, i, board[i][j].shapeSize.first,
                                               board[i][j].shapeSize.second,
                                               board[i][j].shapeColor, NORTH, board[i][j].textOrPath);
        }
    }
    getGraphicalModule()->drawScreen();
}

void Arcade::Core::launchGame()
{
    loadGame(_games[_numberForActualGame]);
    _hasAGame = true;
    getGraphicalModule()->destroyScreen();
    loadGraphical(_graphics[_numberForActualGraphical]);
    getGraphicalModule()->initScreen();
}

std::array<std::array<Arcade::BoardCell, 80>, 60> Arcade::Core::boardMenu(std::array<std::array<BoardCell, 80>, 60> board, std::vector<int> inputs)
{
    for (int i = 0; i < 9; i += 1) {
        if (_inputsTimer[i] > 0)
        _inputsTimer[i] -= _deltaTime;
    }

    for (auto &input : inputs) {
        if (input == '\n') { //Enter
            launchGame();
            return board;
        }

        if (input == 'z' && _inputsTimer[0] <= 0) { //Left
            _inputsTimer[0] = 0.2f;
            _selectorMenu -= 1;
            if (_selectorMenu < 0)
                _selectorMenu = 0;
            if (_stateMenu >= Arcade::MENU_USERNAME1 && _stateMenu <= Arcade::MENU_USERNAME3) {
                _validChar[_stateMenu - Arcade::MENU_USERNAME1] += 1;
                if (_validChar[_stateMenu - Arcade::MENU_USERNAME1] >= NB_VALID_CHAR)
                    _validChar[_stateMenu - Arcade::MENU_USERNAME1] = 0;
                _username[_stateMenu - Arcade::MENU_USERNAME1] = valid_char[_validChar[_stateMenu - Arcade::MENU_USERNAME1]];
            }
        }

        if (input == 's' && _inputsTimer[1] <= 0) { //Down
            _inputsTimer[1] = 0.2f;
            _selectorMenu += 1;
            if (_stateMenu >= Arcade::MENU_USERNAME1 && _stateMenu <= Arcade::MENU_USERNAME3){
                _validChar[_stateMenu - Arcade::MENU_USERNAME1] -= 1;
                if (_validChar[_stateMenu - Arcade::MENU_USERNAME1] < 0)
                    _validChar[_stateMenu - Arcade::MENU_USERNAME1] = NB_VALID_CHAR - 1;
                _username[_stateMenu - Arcade::MENU_USERNAME1] = valid_char[_validChar[_stateMenu - Arcade::MENU_USERNAME1]];
            }
        }

        if (input == 'd' && _inputsTimer[2] <= 0) { //Right
            _inputsTimer[2] = 0.2f;
            _stateMenu += 1;
            if (_stateMenu > Arcade::MENU_USERNAME3)
                _stateMenu = Arcade::MENU_USERNAME3;
            if (_stateMenu == Arcade::MENU_GAME)
                _selectorMenu = _numberForActualGame;
            if (_stateMenu == Arcade::MENU_GRAPHICAL)
                _selectorMenu = _numberForActualGraphical;
        }

        if (input == 'q' && _inputsTimer[3] <= 0) { //Left
            _inputsTimer[3] = 0.2f;
            _stateMenu -= 1;
            if (_stateMenu < Arcade::MENU_GRAPHICAL)
                _stateMenu = Arcade::MENU_GRAPHICAL;
            if (_stateMenu == Arcade::MENU_GAME)
                _selectorMenu = _numberForActualGame;
            if (_stateMenu == Arcade::MENU_GRAPHICAL)
                _selectorMenu = _numberForActualGraphical;
        }
    }

    if (_stateMenu == Arcade::MENU_GRAPHICAL) {
        if (_selectorMenu >= _graphics.size())
            _selectorMenu = _graphics.size() - 1;
    } else  if (_stateMenu == Arcade::MENU_GAME) {
        if (_selectorMenu >= _games.size())
            _selectorMenu = _games.size() - 1;
    } else
        _selectorMenu = 0;

    if (_stateMenu == Arcade::MENU_GAME) {
        _numberForActualGame = _selectorMenu;
        getHighScores();
    } else if (_stateMenu == Arcade::MENU_GRAPHICAL) {
        _numberForActualGraphical = _selectorMenu;
    }

    for (int i = 0; i < 8; i += 1) {
        if (i >= _graphics.size()) {
            board[23 + i][10].textOrPath = "";
            continue;
        }
        std::string text = _graphics[i];
        board[23 + i][10].textOrPath = text;
    }
    for (int i = 0; i < 8; i += 1) {
        if (i >= _games.size()) {
            board[23 + i][30].textOrPath = "";
            continue;
        }
        std::string text = _games[i];
        board[23 + i][30].textOrPath = text;
    }
    for (int i = 0; i < 3; i += 1) {
        board[23][49 + i].textOrPath = {_username[i], '\0'};
        board[23][49 + i].shapeColor = Color::WHITE;
        board[23][49 + i].shape = TEXT;
    }

    board[23 + _numberForActualGraphical][10].shapeColor = Arcade::GREEN;
    board[23 + _numberForActualGame][30].shapeColor = Arcade::GREEN;
    if (_stateMenu == Arcade::MENU_GRAPHICAL) {
        board[23 + _selectorMenu][10].shapeColor = Arcade::RED;
    } else if (_stateMenu == Arcade::MENU_GAME) {
        board[23 + _selectorMenu][30].shapeColor = Arcade::RED;
    } else if (_stateMenu == Arcade::MENU_USERNAME1) {
        board[23][49].shapeColor = Arcade::RED;
    } else if (_stateMenu == Arcade::MENU_USERNAME2) {
        board[23][50].shapeColor = Arcade::RED;
    } else if (_stateMenu == Arcade::MENU_USERNAME3) {
        board[23][51].shapeColor = Arcade::RED;
    }

    for (int i = 0; i < 20; i += 1) {
        board[20 + i][55].textOrPath = _hsNames[i];
        if (_hsNames[i] == "")
            board[20 + i][61].textOrPath = "";
        else
            board[20 + i][61].textOrPath = std::to_string(_hsScores[i]);
    }

    return board;
}

void Arcade::Core::changeLib()
{
    getGraphicalModule()->destroyScreen();
    _numberForActualGraphical += 1;
    if (_numberForActualGraphical >= _graphics.size())
        _numberForActualGraphical = 0;
    loadGraphical(_graphics[_numberForActualGraphical]);
    getGraphicalModule()->initScreen();
}

void Arcade::Core::changeGame()
{
    _numberForActualGame += 1;
    if (_numberForActualGame >= _games.size())
        _numberForActualGame = 0;
    loadGame(_games[_numberForActualGame]);
}

void Arcade::Core::addHighScore(std::string name, int score)
{
    refreshLibs();
    std::string fileName = "./scores/" + _games[_numberForActualGame] + ".txt";
    std::fstream file(fileName, std::ios::in | std::ios::out | std::ios::app);
    std::string line;
    std::string names[20];
    int scores[20];

    for (int i = 0; i < 20; i += 1) {
        names[i] = "";
        scores[i] = 0;
    }
    if (file.is_open()) {
        for (int i = 0; i < 20; i += 1) {
            getline(file, line);
            if (line == "")
                break;
            names[i] = line.substr(0, line.find(" "));
            scores[i] = std::stoi(line.substr(line.find(" ") + 1, line.size()));
        }
        file.close();
    }
    file.open(fileName, std::ios::out | std::ios::trunc);
    if (file.is_open()) {
        int i = 0;

        for (i = 0; i < 19; i += 1) {
            if (scores[i] > score) {
                file << names[i] << " " << scores[i] << std::endl;
            }
            else
                break;
        }
        file << name << " " << score << std::endl;
        for (; i < 19; i += 1) {
            if (scores[i] <= score) {
                file << names[i] << " " << scores[i] << std::endl;
            }
        }
        file.close();
    }
}

void Arcade::Core::getHighScores()
{
    std::string fileName = "./scores/" + _games[_numberForActualGame] + ".txt";
    std::fstream file(fileName, std::ios::in | std::ios::out | std::ios::app);
    std::string line;
    std::string name;
    std::string score;
    int i = 0;

    for (i = 0; i < 20; i += 1) {
        _hsNames[i] = "";
        _hsScores[i] = 0;
    }
    i = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            name = line.substr(0, line.find(" "));
            score = line.substr(line.find(" ") + 1, line.size());
            _hsNames[i] = name;
            _hsScores[i] = std::stoi(score);
            i += 1;
            if (i >= 20)
                break;
        }
        file.close();
    }
}

void Arcade::Core::coreLoop()
{
    std::array<std::array<BoardCell, 80>, 60> board;
    std::vector<int> inputs;

    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 80; j++) {
            board[i][j].shape = RECTANGLE;
            board[i][j].shapeSize = {1, 1};
            board[i][j].shapeColor = BLACK;
        }
    }
    getGraphicalModule()->initScreen();
    while (!_hasStopped) {
        refreshDeltaTime();
        refreshLibs();
        if (_hasAGame) {
            int score = getGameModule()->getActualScore();
            if (score < _currentScore)
                addHighScore(_username, _currentScore);
            _currentScore = score;
        }
        getHighScores();
        inputs = getGraphicalModule()->getInputPressed();
        getGraphicalModule()->getMousePressed();
        for (auto &input : inputs) {
            if (input == 27) {
                if (_hasAGame) {
                    addHighScore(_username, _currentScore);
                    _currentScore = 0;
                    _loaderGame = std::make_unique<Arcade::DLLoader<Arcade::IGameModule>>("./src/Menu/arcade_menu.so", GAME);
                    _inputsTimer[4] = 0.2f;
                    _hasAGame = false;
                } else
                    if (_inputsTimer[4] <= 0.f)
                        _hasStopped = true;
            } else {
                if (_hasAGame) {
                    if (input == 'q')
                        getGameModule()->onInputPressed(Arcade::InputAction::LEFT, true);
                    if (input == 'd')
                        getGameModule()->onInputPressed(Arcade::InputAction::RIGHT, true);
                    if (input == 'z')
                        getGameModule()->onInputPressed(Arcade::InputAction::UP, true);
                    if (input == 's')
                        getGameModule()->onInputPressed(Arcade::InputAction::DOWN, true);
                    if (input == 'i')
                        getGameModule()->onInputPressed(Arcade::InputAction::BUTTON1, true);
                    if (input == 'o')
                        getGameModule()->onInputPressed(Arcade::InputAction::BUTTON2, true);
                    if (input == 'p')
                        getGameModule()->onInputPressed(Arcade::InputAction::BUTTON3, true);
                    if (input == 't')
                        getGameModule()->onInputPressed(Arcade::InputAction::PAUSE, true);
                    if (input == 'g')
                        changeGame();
                }
                if (input == 'l') {
                    changeLib();
                    if (!_hasAGame && _stateMenu == Arcade::MENU_GRAPHICAL)
                        _selectorMenu += 1;
                    if (_selectorMenu >= _graphics.size())
                        _selectorMenu = 0;
                }
            }
        }
        getGameModule()->update(_deltaTime);
        board = getGameModule()->getBoard();
        if (!_hasAGame)
            board = boardMenu(board, inputs);
        drawToGraphical(board);
        std::this_thread::sleep_for(std::chrono::milliseconds(64)); //32 pour 30fps
    }
    getGraphicalModule()->destroyScreen();
    std::cout << "Bye bye" << std::endl;
    _loaderGraphical = nullptr;
    _loaderGame = nullptr;
}
