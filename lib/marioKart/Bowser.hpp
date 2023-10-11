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

static const int bowser_texture_front[6][6] = {
        0, 0, 1, 1, 0, 0,
        0, 4, 4, 4, 4, 0,
        0, 2, 8, 8, 2, 0,
        0, 8, 4, 4, 8, 0,
        7, 4, 8, 8, 4, 7,
        7, 8, 8, 8, 8, 7
};

static const int bowser_texture_side[6][6] = {
        0, 4, 1, 1, 0, 0,
        4, 4, 4, 2, 1, 0,
        2, 2, 2, 4, 8, 0,
        0, 2, 4, 8, 4, 0,
        7, 7, 8, 4, 8, 7,
        7, 7, 8, 8, 8, 8
};
