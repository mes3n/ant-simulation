#include "ant.hpp"
#include "../graphics.hpp"
#include "random.hpp"


void ant::init (void) {

    coordinates = sf::Vector2f(WIDTH/2, HEIGTH/2);
    float theta = rotation(generator) * 12;  // * 12 since primary velocity can go any direction
    velocity = sf::Vector2f(cos(theta), sin(theta));

    energy = 60 * 10;
    food = 0;

    entity.setRadius(3);
    entity.setPosition(coordinates);
    entity.setFillColor(sf::Color::Black);

}

void ant::move (void) {

    if (energy) {
        coordinates += velocity;
        energy -= 1;

        if (coordinates.x < 0) {}
        if (coordinates.y < 0) {}
        if (coordinates.x > WIDTH) {}
        if (coordinates.y > HEIGTH) {}

        entity.setPosition(coordinates);

    }
}

void ant::setVelocity () {
    float theta = rotation(generator);
    velocity = sf::Vector2f(velocity.x * cos(theta) - velocity.y * sin(theta),
                            velocity.x * sin(theta) + velocity.y * cos(theta));
}


void ANT::initAnts (void) {
    for (unsigned int i = 0; i < ANT_POPULATION; i++) {
        ants[i].init();
    }
}


void ANT::moveAnts (void) {

    for (unsigned int i = 0; i < ANT_POPULATION; i++) {
        ants[i].setVelocity();
        ants[i].move();
    }
}
