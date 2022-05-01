#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics/RenderWindow.hpp>


const int WIDTH = 1000;
const int HEIGTH = 1000;

extern sf::RenderWindow window;

namespace GUI {

    void init(void);

    void events(void);

    void update(void);
};


#endif // GRAPHICS_H
