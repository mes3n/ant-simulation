#include "food.hpp"
#include "../logic.hpp"

void FoodPiece::decrement () {
    amount -= 1;

    if (amount <= 0) {
        food.erase(food.begin() + id);
    }
}


void FOOD::place (sf::Vector2f point) {

    for (unsigned int i = 0; i < food.size(); i++) {
        if (LOGIC::distance(food[i].coordinates, point) < 3) return;  // can't be placed less than 3 u away from another piece
    }

    FoodPiece foodPiece;

    foodPiece.coordinates = point;
    foodPiece.amount = FOOD_PER_BLOB;
    foodPiece.id = food.size();

    float radius = 2;
    foodPiece.entity.setRadius(radius);
    foodPiece.entity.setPosition(point.x - radius, point.y - radius);
    foodPiece.entity.setFillColor(sf::Color::Green);
    foodPiece.entity.setOutlineColor(sf::Color::Black);  // color can change
    foodPiece.entity.setOutlineThickness(0.5);

    food.push_back(foodPiece);
}

FoodPiece * FOOD::nearest (sf::Vector2f coordinates, sf::Vector2f * point, float * pointDistance) {
    // find the food piece closest to point

    if (!food.size()) {
        *pointDistance = NAN;
        return nullptr;
    }

    *pointDistance = 4096;  // arbitrarily big number
    int index = 0;

    for (unsigned int i = 0; i < food.size(); i++) {
        if (LOGIC::distance(coordinates, food[i].coordinates) <= *pointDistance) {
            *pointDistance = LOGIC::distance(coordinates, food[i].coordinates);
            *point = food[i].coordinates;
            index = i;
        }
    }
    return &food[index];
}
