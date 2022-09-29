#ifndef ANT_H
#define ANT_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "phermone.hpp"
#include "food.hpp"

#include <vector>


#define ANT_POPULATION 500
#define FAMILIAR_RADIUS 75


class AntNest : public sf::Drawable {
    // class for the ants nest, simply a visual start for the ants
    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    public:
        sf::Vector2f position;  // coordinates for the center of the home
        sf::CircleShape entity;  // the viual representation

        AntNest (int x, int y);

};

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
        sf::Vector2f position;
        sf::Vector2f velocity;

        void setVelocity (sf::Vector2f, float, bool);  // set the ants velocity
        void addFamiliarPoint ();  // add a new familiar point if conditions are met
        int nearestPoint (int);  // get index of nearest familiar points to ant
        float getPhermoneDirection (Phermones phermones);  //  get the direction which has the most phermones

    public:
        sf::CircleShape entity;

        Ant(sf::Vector2f, int index);

        void move (Phermones phermones, Food food);  //  - add delta time

};

class AntColony : public sf::Drawable {
    private:
        std::vector<Ant> ants;
        sf::Vector2f home;
        
        virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const;

    public:
        AntColony(AntNest nest, int population_size);
        void update (Phermones phermones, Food food);
};


#endif // ANT_H
