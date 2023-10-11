/*
** EPITECH PROJECT, 2023
** main.cpp$
** File description:
** main.cpp$
*/

#include <iostream>
#include <vector>
#include "ncurses.hpp"

void Ncurses::setColors()
{
    start_color();
    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    init_pair(3, COLOR_BLUE, COLOR_BLUE);
    init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(6, COLOR_CYAN, COLOR_CYAN);
    init_pair(7, COLOR_WHITE, COLOR_WHITE);
    init_pair(8, COLOR_BLACK, COLOR_BLACK);
    init_pair(11, COLOR_RED, COLOR_BLACK);
    init_pair(12, COLOR_GREEN, COLOR_BLACK);
    init_pair(13, COLOR_BLUE, COLOR_BLACK);
    init_pair(14, COLOR_YELLOW, COLOR_BLACK);
    init_pair(15, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(16, COLOR_CYAN, COLOR_BLACK);
    init_pair(17, COLOR_WHITE, COLOR_BLACK);
}

Ncurses::Ncurses()
{
    setColors();
}

Ncurses::~Ncurses()
{
    reset_shell_mode();
    endwin();
}

void Ncurses::initScreen()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    clear();
    refresh();
}

void Ncurses::destroyScreen()
{
    reset_shell_mode();
    endwin();
}

void Ncurses::drawRectangle(int posX, int posY, float width, float height, Arcade::Color color, Arcade::Direction direction, std::string textOrPath)
{
    setColors();
    (void)width;
    (void)height;
    (void)direction;
    (void)textOrPath;
    if (color == Arcade::Color::RED || color == Arcade::Color::DARK_RED)
        attrset(COLOR_PAIR(1));
    else if (color == Arcade::Color::GREEN || color == Arcade::Color::DARK_GREEN)
        attrset(COLOR_PAIR(2));
    else if (color == Arcade::Color::BLUE || color == Arcade::Color::DARK_BLUE)
        attrset(COLOR_PAIR(3));
    else if (color == Arcade::Color::YELLOW || color == Arcade::Color::DARK_YELLOW)
        attrset(COLOR_PAIR(4));
    else if (color == Arcade::Color::PURPLE || color == Arcade::Color::DARK_PURPLE)
        attrset(COLOR_PAIR(5));
    else if (color == Arcade::Color::CYAN)
        attrset(COLOR_PAIR(6));
    else if (color == Arcade::Color::WHITE)
        attrset(COLOR_PAIR(7));
    else if (color == Arcade::Color::BLACK)
        attrset(COLOR_PAIR(8));
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    (void)rows;
    int center_col = cols / 2;
    mvprintw(posY, posX * 2 + 1 + (center_col - 80), "  ");
}

void Ncurses::drawCircle(int posX, int posY, float width, float height, Arcade::Color color, Arcade::Direction direction, std::string textOrPath)
{
    setColors();
    (void)textOrPath;
    (void)width;
    (void)height;
    (void)direction;
    if (color == Arcade::Color::RED || color == Arcade::Color::DARK_RED)
        attrset(COLOR_PAIR(11));
    else if (color == Arcade::Color::GREEN || color == Arcade::Color::DARK_GREEN)
        attrset(COLOR_PAIR(12));
    else if (color == Arcade::Color::BLUE || color == Arcade::Color::DARK_BLUE)
        attrset(COLOR_PAIR(13));
    else if (color == Arcade::Color::YELLOW || color == Arcade::Color::DARK_YELLOW)
        attrset(COLOR_PAIR(14));
    else if (color == Arcade::Color::PURPLE || color == Arcade::Color::DARK_PURPLE)
        attrset(COLOR_PAIR(15));
    else if (color == Arcade::Color::CYAN)
        attrset(COLOR_PAIR(16));
    else if (color == Arcade::Color::WHITE)
        attrset(COLOR_PAIR(17));
    else if (color == Arcade::Color::BLACK)
        attrset(COLOR_PAIR(8));
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    (void)rows;
    int center_col = cols / 2;
    mvprintw(posY, posX * 2 + 1 + (center_col - 80), "()");
}

void Ncurses::drawText(int posX, int posY, float width, float height, Arcade::Color color, Arcade::Direction direction, std::string textOrPath)
{
    setColors();
    (void)width;
    (void)height;
    (void)direction;
    if (color == Arcade::Color::RED || color == Arcade::Color::DARK_RED)
        attrset(COLOR_PAIR(11));
    else if (color == Arcade::Color::GREEN || color == Arcade::Color::DARK_GREEN)
        attrset(COLOR_PAIR(12));
    else if (color == Arcade::Color::BLUE || color == Arcade::Color::DARK_BLUE)
        attrset(COLOR_PAIR(13));
    else if (color == Arcade::Color::YELLOW || color == Arcade::Color::DARK_YELLOW)
        attrset(COLOR_PAIR(14));
    else if (color == Arcade::Color::PURPLE || color == Arcade::Color::DARK_PURPLE)
        attrset(COLOR_PAIR(15));
    else if (color == Arcade::Color::CYAN)
        attrset(COLOR_PAIR(16));
    else if (color == Arcade::Color::WHITE)
        attrset(COLOR_PAIR(17));
    else if (color == Arcade::Color::BLACK)
        attrset(COLOR_PAIR(8));
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    (void)rows;
    int center_col = cols / 2;
    mvprintw(posY, posX * 2 + 1 + (center_col - 80), "%s", textOrPath.c_str());
}

void Ncurses::cleanScreen()
{
    clear();
}

void Ncurses::drawScreen()
{
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    (void)rows;
    int center_col = cols / 2;
    attrset(COLOR_PAIR(17));
    for (int i = 0; i < 61; i += 1) {
        mvprintw(i, 0 + (center_col - 80), "|");
        mvprintw(i, 159 + (center_col - 80), "|");
    }
    refresh();
}

std::vector<int> Ncurses::getInputPressed()
{
    std::vector<int> vec;

    vec.clear();
    nodelay(stdscr, true);

    int ch;
    for (int i = 0; i < 5; i += 1) {
        ch = getch();
        if (ch != ERR)
            vec.push_back(ch);
        else
            break;
    }
    return vec;
}

std::vector<Arcade::MouseInput> Ncurses::getMousePressed()
{
    std::vector<Arcade::MouseInput> vec;

    vec.clear();
    return vec;
}

void __attribute__((constructor)) my_constructor()
{

}

void __attribute__((destructor)) my_destructor()
{

}

extern "C" Arcade::IDisplayModule* entryDisplay()
{
    return new Ncurses;
}
