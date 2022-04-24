#include "graphics.hpp"
#include "entities/ant.hpp"


sf::RenderWindow window;
ant ants[ANT_POPULATION];


int main () {

    GUI::init();
    ANT::initAnts();

    while (window.isOpen()) {

        GUI::events();

        ANT::moveAnts();

        GUI::update();
    }

    return 0;
}
