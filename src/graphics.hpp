#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "entities/ant.hpp"
#include "entities/food.hpp"

class Window : public sf::RenderWindow {
    public:
        Window (const int width, const int height, const std::string &title);

        void events (Food& food);
        void render (const AntNest& antNest, const AntColony& antColony, const Food& food);

};


#endif // GRAPHICS_H
