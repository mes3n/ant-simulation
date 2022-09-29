#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include <SFML/System/Vector2.hpp>

#include <string>

#include "graphics.hpp"
#include "entities/ant.hpp"
#include "entities/food.hpp"
#include "entities/phermone.hpp"


Window::Window (const int width, const int height, const std::string &title) 
: sf::RenderWindow(sf::VideoMode(width, height), title) {

    setFramerateLimit(120);
}

void Window::events (Food& food) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        close();

    sf::Event event;
    while (pollEvent(event)) {
        if (event.type == sf::Event::Closed) close();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*this);
        food.place(sf::Vector2f(mousePos.x, mousePos.y));
    }
}

void Window::render (AntNest antNest, AntColony antColony, Food food) {
    clear(sf::Color::White);

    draw(antColony);
    draw(antNest);
    draw(food);

    // for (Phermone &phermone : phermones) {
    //     window.draw(phermone.entity);
    // }

    display();
}
