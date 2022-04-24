#ifndef ANT_H
#define ANT_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>


const int ANT_POPULATION = 4;


class ant {
    // the ants follow a set of simplified rules
    // they forage around chaotically looking for food
    // they must return to their nest to preserve energy
    //
    private:
        int energy;  // make sure ant has enough energy to surive
        int food;  // if it is carrying food, head home and place phermones

    public:
        // positional values of the ant
        sf::Vector2f coordinates;
        sf::Vector2f velocity;

        // the ants visual representation
        sf::CircleShape entity;

        void init (void);

        void move (void);

        void setVelocity ();

};

extern ant ants[ANT_POPULATION];

namespace ANT {

    void initAnts (void);

    void moveAnts (void);
};


#endif // ANT_H
