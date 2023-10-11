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

static const int wario_texture_front[6][6] = {
        0, 2, 2, 2, 2, 0,
        0, 2, 2, 2, 2, 0,
        0, 6, 6, 6, 6, 0,
        0, 5, 2, 2, 5, 0,
        7, 5, 5, 5, 5, 7,
        7, 8, 8, 8, 8, 7
};

static const int wario_texture_side[6][6] = {
        0, 0, 2, 2, 2, 0,
        0, 2, 2, 2, 2, 0,
        6, 6, 6, 6, 6, 0,
        0, 2, 2, 5, 2, 0,
        7, 7, 5, 5, 5, 7,
        7, 7, 8, 8, 8, 8
};
