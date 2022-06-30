#ifndef PHERMONE_H
#define PHERMONE_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <vector>

const int PHERMONE_STRENGHT = 5;

typedef struct {
    // food entities the ants will be looking for

    int id;
    int strenght;

    sf::Vector2f coordinates;
    // sf::CircleShape entity;  // in case of wanting visuals

    void decrement();

} Phermone;

extern std::vector<Phermone> phermones;

namespace PHERM {

    void place (sf::Vector2f);

    void decrementAll ();

};


#endif  // PHERMONE_H
