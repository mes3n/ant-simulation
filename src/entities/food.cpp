#include "food.hpp"
#include "../logic.hpp"

void FoodPiece::decrement () {
    amount -= 1;

    if (amount <= 0) {
        food.erase(food.begin() + id);
    }
}


void FOOD::place (sf::Vector2f point) {

    for (FoodPiece foodPiece : food) {
        if (LOGIC::nearby(foodPiece.coordinates, point, 6))
            return;  // can't be placed less than 6 u away from another piece
    }

    FoodPiece piece;

    piece.coordinates = point;
    piece.amount = FOOD_PER_BLOB;
    piece.id = food.size();

    float radius = 2;
    piece.entity.setRadius(radius);
    piece.entity.setPosition(point.x - radius, point.y - radius);
    piece.entity.setFillColor(sf::Color::Green);
    piece.entity.setOutlineColor(sf::Color::Black);  // color can change
    piece.entity.setOutlineThickness(0.5);

    food.push_back(piece);

}

void FOOD::nearest (sf::Vector2f coordinates, sf::Vector2f * point, float * pointDistance) {
    // find the food piece closest to coordinates
    // store food piece coordinates to point
    // and the distance to point in pointDistance

    if (!food.size()) {
        *pointDistance = NAN;
        return;
    }

    FoodPiece piece;

    *pointDistance = 4096;  // arbitrarily big number

    for (FoodPiece &foodPiece : food) {
        if (LOGIC::nearby(coordinates, foodPiece.coordinates, 75)) {
            if (LOGIC::distance(coordinates, foodPiece.coordinates) <= *pointDistance) {
                *pointDistance = LOGIC::distance(coordinates, foodPiece.coordinates);
                *point = foodPiece.coordinates;
                piece = foodPiece;
            }
        }
    }
    piece.decrement();
}
