#include "food.hpp"
#include "../logic.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


void Food::decay () {

    auto it = foodPieces.begin();
    for ( ; it != foodPieces.end(); it++) {
        it->amount -= 1;

        if (it->amount <= 0) {
            foodPieces.erase(it--);
        }
    }
}


void Food::place (sf::Vector2f point) {

    for (FoodPiece piece : foodPieces) {
        if (LOGIC::nearby(piece.position, point, 6))
            return;  // can't be placed less than 6 u away from another piece
    } 

    FoodPiece piece;

    piece.position = point;
    piece.amount = FOOD_PER_BLOB;

    float radius = 2;
    piece.entity.setRadius(radius);
    piece.entity.setPosition(point.x - radius, point.y - radius);
    piece.entity.setFillColor(sf::Color::Green);
    // piece.entity.setOutlineColor(sf::Color::Black);  // color can change
    // piece.entity.setOutlineThickness(0.5);

    foodPieces.push_back(piece);

}

void Food::nearest (sf::Vector2f coordinates, sf::Vector2f * point, float * pointDistance) const {
    // find the food piece closest to coordinates
    // store food piece coordinates to point
    // and the distance to point in pointDistance

    if (foodPieces.empty()) {
        *pointDistance = NAN;
        return;
    }

    FoodPiece new_piece;

    *pointDistance = 4096;  // arbitrarily big number

    for (FoodPiece piece: foodPieces) {
        if (LOGIC::nearby(coordinates, piece.position, 75)) {
            if (LOGIC::distance(coordinates, piece.position) <= *pointDistance) {
                *pointDistance = LOGIC::distance(coordinates, piece.position);
                *point = piece.position;
                new_piece = piece;
            }
        }
    }
}

void Food::draw (sf::RenderTarget& target, sf::RenderStates states) const {
    for (FoodPiece piece: foodPieces) {
        target.draw(piece.entity, states);
    }
}
