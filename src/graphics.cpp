#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include <SFML/System/Vector2.hpp>

#include "graphics.hpp"
#include "entities/ant.hpp"
#include "entities/food.hpp"
#include "entities/phermone.hpp"


void GUI::init (void) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window.create(sf::VideoMode(WIDTH, HEIGTH), "ant simulation", sf::Style::Close, settings);
    window.setFramerateLimit(60);

}


void GUI::events () {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        FOOD::place(sf::Vector2f(mousePos.x, mousePos.y));
    }
}

void GUI::update (void) {
    window.clear(sf::Color::White);

    for (Ant &ant : ants) {
        window.draw(ant.entity);
    }
    window.draw(antNest.entity);

    for (FoodPiece &foodPiece : food) {
        window.draw(foodPiece.entity);
    }

    // for (Phermone &phermone : phermones) {
    //     window.draw(phermone.entity);
    // }

    window.display();
}
