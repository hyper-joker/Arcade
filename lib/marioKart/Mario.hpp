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

static const int mario_texture_front[6][6] = {
        0, 1, 1, 1, 1, 0,
        0, 1, 1, 1, 1, 0,
        0, 2, 2, 2, 2, 0,
        0, 3, 1, 1, 3, 0,
        7, 3, 3, 3, 3, 7,
        7, 8, 8, 8, 8, 7
};

static const int mario_texture_side[6][6] = {
        0, 0, 1, 1, 1, 0,
        0, 1, 1, 1, 1, 0,
        2, 2, 2, 2, 2, 0,
        0, 1, 1, 3, 1, 0,
        7, 7, 3, 3, 3, 7,
        7, 7, 8, 8, 8, 8
};
