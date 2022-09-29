#include "phermone.hpp"
#include "../logic.hpp"

void Phermones::decay () {
    auto it = phermones.begin();
    for ( ; it != phermones.end(); it++) {
        it->strenght *= 0.7f;

        if (it->strenght <= 1) {
            phermones.erase(it--);
        }
    }
}


void Phermones::place (sf::Vector2f point) {

    for (Phermone phermone : phermones) {
        if (LOGIC::nearby(phermone.coordinates, point, 12)) {  // clump together phermones that are close to each other
            phermone.strenght += PHERMONE_STRENGHT;
            return;
        }
    }

    Phermone phermone;

    phermone.coordinates = point;
    phermone.strenght = PHERMONE_STRENGHT;

    // float radius = 2;
    // phermone.entity.setRadius(radius);
    // phermone.entity.setPosition(point.x - radius, point.y - radius);
    // phermone.entity.setFillColor(sf::Color::Yellow);
    // phermone.entity.setOutlineColor(sf::Color::Black);  // color can change
    // phermone.entity.setOutlineThickness(0.5);

    phermones.push_back(phermone);
}
