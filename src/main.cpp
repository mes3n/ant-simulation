#include "graphics.hpp"
#include "entities/ant.hpp"
#include "entities/food.hpp"
#include "entities/phermone.hpp"


sf::RenderWindow window;

std::vector<Ant> ants(ANT_POPULATION);
AntNest antNest;

std::vector<Phermone> phermones;
std::vector<FoodPiece> food;


int main (int argc, char** argv) {

    GUI::init();
    ANTS::init(sf::Vector2f(WIDTH/2, HEIGTH/2));

    while (window.isOpen()) {

        GUI::events();

        ANTS::moveAnts();

        GUI::update();

    }

    return 0;
}
