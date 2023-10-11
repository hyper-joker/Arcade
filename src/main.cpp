/*
** EPITECH PROJECT, 2023
** main.cpp$
** File description:
** main.cpp$
*/

#include <iostream>
#include <vector>
#include <cstring>
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "DLLoader.hpp"
#include "Core.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: ./arcade [lib.so]" << std::endl;
        return 84;
    }
    try {
        Arcade::Core core(argv[1]);

        core.coreLoop();
        return 0;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}