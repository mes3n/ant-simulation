#include "logic.hpp"

bool LOGIC::nearby (sf::Vector2f p1, sf::Vector2f p2, const unsigned int r) {  // see if p1 and p2 are within a square with side r of each other
    return (p1.x < p2.x + r && p1.x + r > p2.x && p1.y < p2.y + r && p1.y + r > p2.y);
}


float LOGIC::distance (sf::Vector2f p1, sf::Vector2f p2) {  // distance formula to get distance between p1 and p2
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

sf::Vector2f LOGIC::rotate (sf::Vector2f vec, float angle) {  // rotate a vector by angle radians
    return sf::Vector2f(
        vec.x * cos(angle) - vec.y * sin(angle),
        vec.x * sin(angle) + vec.y * cos(angle)
    );
}

sf::Vector2f LOGIC::standardise (sf::Vector2f vec) {  // standardise vector to absolute value of 1
    float abs = distance(sf::Vector2f(0, 0), vec);
    return sf::Vector2f(
        vec.x/abs, vec.y/abs
    );
}
