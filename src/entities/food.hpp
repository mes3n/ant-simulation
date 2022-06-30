#ifndef FOOD_H
#define FOOD_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <vector>

const int FOOD_PER_BLOB = 400;

typedef struct {
    // food entities the ants will be looking for

    int amount;
    int id;

    sf::Vector2f coordinates;
    sf::CircleShape entity;
    void decrement();

} FoodPiece;

extern std::vector<FoodPiece> food;

namespace FOOD {

    void place (sf::Vector2f);
    void nearest (sf::Vector2f, sf::Vector2f *, float *);

};


#endif  // FOOD_H
