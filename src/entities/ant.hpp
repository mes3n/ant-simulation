#ifndef ANT_H
#define ANT_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>


const int ANT_POPULATION = 5000;
const int N_FAMILIAR_POINTS = 30;

class Ant {
    // the ants follow a set of simplified rules
    //  - they forage around chaotically looking for food
    //  - they must return to their nest to get energy and store food
    //  - they can rembember their surroundings for navigation
    private:
        int index;  // the ants "name"

        int energy;  // make sure ant has enough energy to surive
        int hasFood;  // if it is carrying food, head home and place phermones

        // the ant uses familiarPoints to navigate home
        sf::Vector2f familiarPoints[N_FAMILIAR_POINTS];  // points the ant recognizes
        int destinationPointIndex;  // the point the ant is heading to
        int familiarRadius;

        // positional values of the ant
        sf::Vector2f coordinates;
        sf::Vector2f velocity;

        void setVelocity ();  // set the ants velocity

        void addFamiliarPoint ();  // add a new familiar point if conditions are met

        int nearestPoint (int);  // get index of nearest familiar points to ant

    public:
        sf::CircleShape entity;  // the ants visual representation

        void init (sf::Vector2f, int);

        void move (void);  //  - add delta time


};


class AntNest {
    private:
        int radius;  // size of the actual ant home

    public:
        sf::Vector2f coordinates;  // coordinates for the center of the home
        sf::CircleShape entity;  // the viua representation

        void init (sf::Vector2f);
};


extern Ant ants[ANT_POPULATION];

extern AntNest antNest;


namespace ANT {

    void init (sf::Vector2f);

    void moveAnts (void);
};




#endif // ANT_H
