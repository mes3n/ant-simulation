#ifndef PHERMONE_H
#define PHERMONE_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <vector>

#define PHERMONE_STRENGHT 5

typedef struct {  // food entities the ants will be looking for
    int strenght;
    sf::Vector2f coordinates;
    // sf::CircleShape entity;  // in case of wanting visuals

} Phermone;


class Phermones {
    public:
        std::vector<Phermone> phermones;

        void place (sf::Vector2f);
        void decay (void);

};


#endif  // PHERMONE_H
