#include "graphics.hpp"
#include "entities/ant.hpp"


sf::RenderWindow window;
Ant ants[ANT_POPULATION];
AntNest antNest;

int main () {

    GUI::init();
    ANT::init(sf::Vector2f(WIDTH/2, HEIGTH/2));

    while (window.isOpen()) {

        GUI::events();

        ANT::moveAnts();

        GUI::update();
    }

    return 0;
}
