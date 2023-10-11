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
#include "../../src/AGameModule.hpp"

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
 */

static const int shell_texture[4][4] = {
        0, 4, 4, 0,
        4, 4, 4, 4,
        8, 7, 7, 8,
        0, 8, 8, 0
};

static const int red_shell_texture[4][4] = {
        0, 1, 1, 0,
        1, 1, 1, 1,
        8, 7, 7, 8,
        0, 8, 8, 0
};

static const int banana_texture[4][4] = {
        0, 0, 7, 0,
        0, 7, 2, 7,
        7, 6, 2, 0,
        6, 2, 7, 6
};

static const int mushroom_texture[4][4] = {
        0, 6, 1, 0,
        1, 6, 6, 6,
        6, 8, 8, 1,
        0, 8, 8, 0
};

static const int bomb_texture[4][4] = {
        0, 7, 7, 2,
        7, 8, 7, 7,
        7, 7, 7, 7,
        0, 7, 7, 6
};

static const int dust_texture[4][4] = {
        0, 8, 8, 0,
        8, 8, 8, 8,
        8, 8, 8, 8,
        0, 8, 8, 0
};
