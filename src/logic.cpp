#include "logic.hpp"

float distance (sf::Vector2f p1, sf::Vector2f p2) {  // distance formula to get distance between p1 and p2
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

sf::Vector2f rotate (sf::Vector2f vec, float angle) {  // rotate a vector by angle radians
    return sf::Vector2f(
        vec.x * cos(angle) - vec.y * sin(angle),
        vec.x * sin(angle) + vec.y * cos(angle)
    );
}

sf::Vector2f standardise (sf::Vector2f vec) {  // standardise vector to absolute value of 1
    float abs = distance(sf::Vector2f(0, 0), vec);
    return sf::Vector2f(
        vec.x/abs, vec.y/abs
    );
}
