#include "graphics.hpp"
#include "entities/ant.hpp"
#include "entities/food.hpp"
#include "entities/phermone.hpp"


int main (int argc, char** argv) {

    const int width = 1000, height = 1000; 
    Window window(width, height, "Ant Simulation");

    AntNest antNest(width / 2, height / 2);
    AntColony antColony(antNest, ANT_POPULATION);

    Phermones phermones;
    Food food;

    while (window.isOpen()) {

        window.events(food);

        antColony.update(phermones, food);

        window.render(antNest, antColony, food);

    }

    return 0;
}
