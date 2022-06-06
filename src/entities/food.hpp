#ifndef FOOD_H
#define FOOD_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <vector>

const int FOOD_PER_BLOB = 100;

typedef struct {
    // food entities the ants will be looking for

    int id;
    int amount;

    sf::Vector2f coordinates;
    sf::CircleShape entity;
    void decrement();

} FoodPiece;

extern std::vector<FoodPiece> food;

namespace FOOD {

    void place (sf::Vector2f);
    FoodPiece * nearest (sf::Vector2f, sf::Vector2f*, float*);

};


#endif  // FOOD_H
