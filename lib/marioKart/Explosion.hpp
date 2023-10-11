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

static const int explosion_small[12][6] = {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 0, 0,
        0, 1, 2, 6, 1, 0,
        1, 2, 6, 2, 6, 1,
        1, 6, 2, 6, 2, 1,
        0, 1, 6, 2, 1, 0
};

static const int explosion_big[12][6] = {
        0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 0, 0,
        0, 1, 2, 6, 1, 0,
        1, 2, 6, 2, 6, 1,
        1, 1, 2, 6, 1, 1,
        0, 1, 6, 2, 1, 0,
        0, 1, 2, 6, 1, 0,
        6, 1, 6, 2, 1, 6,
        0, 6, 6, 6, 6, 0,
        0, 1, 6, 2, 1, 0,
        0, 1, 2, 6, 1, 0,
        1, 1, 6, 2, 1, 1
};
