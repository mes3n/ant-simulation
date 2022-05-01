#ifndef LOGIC_H
#define LOGIC_H

#include <SFML/System/Vector2.hpp>
#include <math.h>

float distance (sf::Vector2f, sf::Vector2f);
sf::Vector2f rotate (sf::Vector2f, float);
sf::Vector2f standardise (sf::Vector2f);

#endif  // LOGIC_H
