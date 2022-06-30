#include "phermone.hpp"
#include "../logic.hpp"

void Phermone::decrement () {
    strenght *= 0.7;

    if (strenght <= 1) {
        phermones.erase(phermones.begin() + id);
    }
}


void PHERM::place (sf::Vector2f point) {

    for (Phermone &phermone : phermones) {
        if (LOGIC::nearby(phermone.coordinates, point, 12)) {  // clump together phermones that are close to each other
            phermone.strenght += PHERMONE_STRENGHT;
            return;
        }
    }

    Phermone phermone;

    phermone.coordinates = point;
    phermone.strenght = PHERMONE_STRENGHT;
    phermone.id = phermones.size();

    // float radius = 2;
    // phermone.entity.setRadius(radius);
    // phermone.entity.setPosition(point.x - radius, point.y - radius);
    // phermone.entity.setFillColor(sf::Color::Yellow);
    // phermone.entity.setOutlineColor(sf::Color::Black);  // color can change
    // phermone.entity.setOutlineThickness(0.5);

    phermones.push_back(phermone);
}

void PHERM::decrementAll () {
    for (Phermone &phermone : phermones) {
        phermone.decrement();
    }
}
