/*
** EPITECH PROJECT, 2023
** main.cpp$
** File description:
** main.cpp$
*/

#include <iostream>
#include <vector>
#include "sfml.hpp"

void SFML::initScreen()
{
    // create a window with size 800x600 pixels and title "SFML window"
    _window = new sf::RenderWindow(sf::VideoMode(WINDOW_W, WINDOW_H), "SFML window");

    // set the framerate limit to 60 frames per second
    _window->setFramerateLimit(60);
}

SFML::SFML()
{
    _window = nullptr;
    _font.loadFromFile("./assets/neon_pixel-7.ttf");
}

SFML::~SFML()
{
    SFML::destroyScreen();
}

void SFML::destroyScreen()
{
    // close the window
    if (_window == nullptr)
        return;
    _window->close();
}

void SFML::drawRectangle(int posX, int posY, float width, float height, Arcade::Color color, Arcade::Direction direction, std::string textOrPath)
{
    if (_window == nullptr)
        return;
    sf::RectangleShape rectangle(sf::Vector2f(width * CELL_SIZE, height * CELL_SIZE));
    rectangle.setPosition(sf::Vector2f((WINDOW_W / 2 - 40 * CELL_SIZE) + posX * CELL_SIZE, posY * CELL_SIZE));
    (void) direction;
    (void) textOrPath;

    // set the color of the rectangle based on the specified Arcade::Color enum value
    switch (color) {
        case Arcade::Color::BLACK:
            rectangle.setFillColor(sf::Color::Black);
            break;
        case Arcade::Color::BLUE:
            rectangle.setFillColor(sf::Color::Blue);
            break;
        case Arcade::Color::CYAN:
            rectangle.setFillColor(sf::Color::Cyan);
            break;
        case Arcade::Color::GREEN:
            rectangle.setFillColor(sf::Color::Green);
            break;
        case Arcade::Color::ORANGE:
            rectangle.setFillColor({230, 126, 34});
            break;
        case Arcade::Color::PURPLE:
            rectangle.setFillColor({142, 68, 173});
            break;
        case Arcade::Color::RED:
            rectangle.setFillColor(sf::Color::Red);
            break;
        case Arcade::Color::WHITE:
            rectangle.setFillColor(sf::Color::White);
            break;
        case Arcade::Color::YELLOW:
            rectangle.setFillColor(sf::Color::Yellow);
            break;
        case Arcade::Color::DARK_RED:
            rectangle.setFillColor({192, 57, 43});
            break;
        case Arcade::Color::DARK_BLUE:
            rectangle.setFillColor({41, 128, 185});
            break;
        case Arcade::Color::DARK_GREEN:
            rectangle.setFillColor({39, 174, 96});
            break;
        case Arcade::Color::DARK_YELLOW:
            rectangle.setFillColor({241, 196, 15});
            break;
        case Arcade::Color::DARK_PURPLE:
            rectangle.setFillColor({155, 89, 182});
            break;
        case Arcade::Color::DARK_ORANGE:
            rectangle.setFillColor({120, 65, 15});
            break;
        default:
            break;
    }

    // draw the rectangle to the screen
    _window->draw(rectangle);
}

void SFML::drawCircle(int posX, int posY, float width, float height, Arcade::Color color, Arcade::Direction direction, std::string textOrPath)
{
    if (_window == nullptr)
        return;
    float radius = width;
    sf::CircleShape Circle(radius * 10);
    Circle.setPosition(sf::Vector2f((WINDOW_W / 2 - 40 * CELL_SIZE) + posX * CELL_SIZE - radius * 10 + CELL_SIZE/2, posY * CELL_SIZE - radius * 10 + CELL_SIZE/2));
    (void) height;
    (void) direction;
    (void) textOrPath;

    // set the color of the rectangle based on the specified Arcade::Color enum value
    switch (color) {
        case Arcade::Color::BLACK:
            Circle.setFillColor(sf::Color::Black);
            break;
        case Arcade::Color::BLUE:
            Circle.setFillColor(sf::Color::Blue);
            break;
        case Arcade::Color::CYAN:
            Circle.setFillColor(sf::Color::Cyan);
            break;
        case Arcade::Color::GREEN:
            Circle.setFillColor(sf::Color::Green);
            break;
        case Arcade::Color::RED:
            Circle.setFillColor(sf::Color::Red);
            break;
        case Arcade::Color::WHITE:
            Circle.setFillColor(sf::Color::White);
            break;
        case Arcade::Color::YELLOW:
            Circle.setFillColor(sf::Color::Yellow);
            break;
        case Arcade::Color::ORANGE:
            Circle.setFillColor({230, 126, 34});
            break;
        case Arcade::Color::PURPLE:
            Circle.setFillColor({142, 68, 173});
            break;
        case Arcade::Color::DARK_RED:
            Circle.setFillColor({192, 57, 43});
            break;
        case Arcade::Color::DARK_BLUE:
            Circle.setFillColor({41, 128, 185});
            break;
        case Arcade::Color::DARK_GREEN:
            Circle.setFillColor({39, 174, 96});
            break;
        case Arcade::Color::DARK_YELLOW:
            Circle.setFillColor({241, 196, 15});
            break;
        case Arcade::Color::DARK_PURPLE:
            Circle.setFillColor({155, 89, 182});
            break;
        case Arcade::Color::DARK_ORANGE:
            Circle.setFillColor({120, 65, 15});
            break;
        default:
            break;
    }

    // draw the rectangle to the screen
    _window->draw(Circle);
}

void SFML::drawText(int posX, int posY, float width, float height, Arcade::Color color, Arcade::Direction direction, std::string textOrPath)
{
    if (_window == nullptr)
        return;
    sf::Text text(textOrPath, _font, 20 * height);
    text.setPosition(sf::Vector2f((WINDOW_W / 2 - 40 * CELL_SIZE) + posX * CELL_SIZE, posY * CELL_SIZE));
    (void) width;
    (void) direction;

    // set the color of the text based on the specified Arcade::Color enum value
    switch (color) {
        case Arcade::Color::BLACK:
            text.setFillColor(sf::Color::Black);
            break;
        case Arcade::Color::BLUE:
            text.setFillColor(sf::Color::Blue);
            break;
        case Arcade::Color::CYAN:
            text.setFillColor(sf::Color::Cyan);
            break;
        case Arcade::Color::GREEN:
            text.setFillColor(sf::Color::Green);
            break;
        case Arcade::Color::RED:
            text.setFillColor(sf::Color::Red);
            break;
        case Arcade::Color::WHITE:
            text.setFillColor(sf::Color::White);
            break;
        case Arcade::Color::YELLOW:
            text.setFillColor(sf::Color::Yellow);
            break;
        case Arcade::Color::ORANGE:
            text.setFillColor({230, 126, 34});
            break;
        case Arcade::Color::PURPLE:
            text.setFillColor({142, 68, 173});
            break;
        case Arcade::Color::DARK_RED:
            text.setFillColor({192, 57, 43});
            break;
        case Arcade::Color::DARK_BLUE:
            text.setFillColor({41, 128, 185});
            break;
        case Arcade::Color::DARK_GREEN:
            text.setFillColor({39, 174, 96});
            break;
        case Arcade::Color::DARK_YELLOW:
            text.setFillColor({241, 196, 15});
            break;
        case Arcade::Color::DARK_PURPLE:
            text.setFillColor({155, 89, 182});
            break;
        case Arcade::Color::DARK_ORANGE:
            text.setFillColor({120, 65, 15});
            break;
        default:
            break;
    }

    // draw the text to the screen
    _window->draw(text);
}

void SFML::cleanScreen()
{
    if (_window == nullptr)
        return;
    _window->clear(sf::Color::Black);
}

void SFML::drawScreen()
{
    if (_window == nullptr)
        return;
    _window->display();
}

std::vector<int> SFML::getInputPressed()
{
    std::vector<int> inputs;

    inputs.clear();
    if (_window == nullptr)
        return inputs;
    if (!_window->hasFocus())
        return inputs;

    for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
    {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
        {
            inputs.push_back(static_cast<char>(i + 'a')); // Convert the key code to a character
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            inputs.push_back(27);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            inputs.push_back(32);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            inputs.push_back(10);
        }
    }
    return inputs;
}

std::vector<Arcade::MouseInput> SFML::getMousePressed()
{
    std::vector<Arcade::MouseInput> mouseInputs;

    mouseInputs.clear();
    // poll the events in the event queue
    //if (_window == nullptr)
    sf::Event event;
    while (_window->pollEvent(event)) {
        // if the event is a mouse press, add the mouse position and event type to the vector of mouse inputs
        if (event.type == sf::Event::MouseButtonPressed) {
            Arcade::MouseInput mouseInput;
            mouseInput.mousePos = std::make_pair(event.mouseButton.x, event.mouseButton.y);
            switch (event.mouseButton.button) {
                case sf::Mouse::Right:
                    mouseInput.event = Arcade::MouseEvent::rmbPressed;
                    break;
                case sf::Mouse::Left:
                    mouseInput.event = Arcade::MouseEvent::lmbPressed;
                    break;
                default:
                    break;
            }
        }
            // if the event is a mouse release, add the mouse position and event type to the vector of mouse inputs
        else if (event.type == sf::Event::MouseButtonReleased) {
            Arcade::MouseInput mouseInput;
            mouseInput.mousePos = std::make_pair(event.mouseButton.x, event.mouseButton.y);
            switch (event.mouseButton.button) {
                case sf::Mouse::Right:
                    mouseInput.event = Arcade::MouseEvent::rmbReleased;
                    break;
                case sf::Mouse::Left:
                    mouseInput.event = Arcade::MouseEvent::lmbReleased;
                    break;
                default:
                    break;
            }
            mouseInputs.push_back(mouseInput);
        }
    }

    return mouseInputs;
}

void __attribute__((constructor)) my_constructor()
{

}

void __attribute__((destructor)) my_destructor()
{

}

extern "C" Arcade::IDisplayModule* entryDisplay()
{
    return new SFML;
}
