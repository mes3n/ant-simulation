#ifndef ANT_H
#define ANT_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <vector>


const unsigned int ANT_POPULATION = 500;
const unsigned int FAMILIAR_RADIUS = 75;

class Ant {
    // the ants follow a set of simplified rules
    //  - they forage around chaotically looking for food
    //  - they must return to their nest to get energy and store food
    //  - they can rembember their surroundings for navigation

private:
    int id;  // the ants id

    int energy;  // make sure ant has enough energy to surive
    bool hasFood;  // if it is carrying food, head home and place phermones

    // the ant uses familiarPoints to navigate home
    std::vector<sf::Vector2f> familiarPoints;  // points the ant recognizes
    int destinationPointIndex;  // the point the ant is heading to

    // positional values of the ant
    sf::Vector2f coordinates;
    sf::Vector2f velocity;

    void setVelocity (sf::Vector2f, float, bool);  // set the ants velocity
    void addFamiliarPoint ();  // add a new familiar point if conditions are met
    int nearestPoint (int);  // get index of nearest familiar points to ant
    float getPhermoneDirection ();  //  get the direction which has the most phermones

public:
    sf::CircleShape entity;

    void init (sf::Vector2f, int);
    void move (void);  //  - add delta time

};



class AntNest {
    // class for the ants nest, simply a visual start for the ants

private:
    sf::Vector2f coordinates;  // coordinates for the center of the home

public:
    sf::CircleShape entity;  // the viual representation

    void init (sf::Vector2f);

};



extern std::vector<Ant> ants;
extern AntNest antNest;



namespace ANTS {

    void init (sf::Vector2f);
    void moveAnts (void);

};


#endif // ANT_H
