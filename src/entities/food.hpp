#ifndef FOOD_H
#define FOOD_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <vector>

#define FOOD_PER_BLOB 400

typedef struct {
    int amount;
    sf::Vector2f position;

    sf::CircleShape entity;

} FoodPiece;

class Food : public sf::Drawable {
    private: 
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        std::vector<FoodPiece> foodPieces;

    public:
        void place (sf::Vector2f coordinates);
        void nearest (sf::Vector2f coordinates, sf::Vector2f* n_coordinates, float* n_distance) const;
        void decay (void);

};


#endif  // FOOD_H
