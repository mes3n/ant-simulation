#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include "graphics.hpp"
#include "entities/ant.hpp"


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

    // if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    //     place_food(sf::Mouse::getPosition(window));

}


// void place_food (sf::Vector2i position) {
//     for (unsigned int i = 0; i < FOOD_COUNT; i++) {
//         if (!food[i].entity.getPosition().x && !food[i].entity.getPosition().y || !food[i].exists) {
//             food[i].entity.setPosition(sf::Vector2f(position));
//
//             food[i].entity.setFillColor(sf::Color(128, 128, 0));
//             food[i].entity.setRadius(4);
//
//             food[i].coordinates = sf::Vector2f(position);
//             food[i].exists = true;
//
//             return;
//         }
//     }
// }

void GUI::update (void) {
    window.clear(sf::Color::White);

    // window.draw(antHome);
    //
    // for (unsigned int i = 0; i < POPULATION; i++) {
    //     window.draw(ants[i].entity);
    // }
    //
    // for (unsigned int i = 0; i < FOOD_COUNT; i++) {
    //     if (food[i].exists) window.draw(food[i].entity);
    // }
    for (unsigned int i = 0; i < ANT_POPULATION; i++) {
        window.draw(ants[i].entity);
    }

    window.display();
}
