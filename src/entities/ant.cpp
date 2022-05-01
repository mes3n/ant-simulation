#include "ant.hpp"
#include "random.hpp"
#include "../logic.hpp"

#include <iostream>

void Ant::init (sf::Vector2f center) {

    coordinates = center;
    float theta = rotation(generator) * 12;  // convert pi/12 to pi radians
    velocity = sf::Vector2f(cos(theta), sin(theta));

    energy = 60 * 20;
    hasFood = 0;

    familiarPoints[0] = center;
    for (unsigned int i = 1; i < N_FAMILIAR_POINTS; i++) {
        familiarPoints[i] = sf::Vector2f(-1, -1);
    }
    destinationPointIndex = N_FAMILIAR_POINTS - 1;
    familiarRadius = 75;

    entity.setRadius(3);
    entity.setPosition(coordinates);
    entity.setFillColor(sf::Color::Black);

}

void Ant::move (void) {

    if (energy) {

        setVelocity();

        coordinates += velocity;
        energy -= 1;

        addFamiliarPoint();

        entity.setPosition(coordinates);

    }
}

void Ant::setVelocity () {
    float theta = rotation(generator);  // roatation between +-pi/12 radians
    int energyLowLimit = 60*10;

    if (energy > energyLowLimit) {  // move around chaotically
        velocity = rotate(velocity, theta);  // rotate movement by theta radians
    }
    else if (energy == energyLowLimit) {  // start moving home
        destinationPointIndex = nearestPoint(destinationPointIndex);  // find the nearest point of the ones the ant recognizes
        velocity = rotate(velocity, theta);  // ant does a 180 turn
    }
    else if (energy < energyLowLimit || hasFood) {
        sf::Vector2f point = familiarPoints[destinationPointIndex];  // the point used for navigation
        float deltaDistance = distance(coordinates, point);  // distance to said point

        if (deltaDistance <= familiarRadius) {  // if close enough to be familiar
            velocity = rotate(standardise(sf::Vector2f(
                point.x - coordinates.x, point.y - coordinates.y
            )), theta);  // set velocity towards the point
            if (deltaDistance <= familiarRadius / 10) {
                // if close enough to point select next one, unless ant is already home
                if (destinationPointIndex > 0) destinationPointIndex -= 1;
            }
        }
        else {
            // destinationPointIndex = nearestPoint(N_FAMILIAR_POINTS - 1);  // search through all points
            velocity = rotate(velocity, theta);  // rotate movement by theta radians
        }
    }
}

void Ant::addFamiliarPoint () {
    for (unsigned int i = 0; i < N_FAMILIAR_POINTS; i++) {
        if (distance(coordinates, familiarPoints[i]) <= familiarRadius*0.75) {
            // add points at a smallar radius than they can be found from
            return;
        }
    }
    for (unsigned int i = 0; i < N_FAMILIAR_POINTS; i++) {
        if (familiarPoints[i].x == -1 && familiarPoints[i].y == -1) {
            familiarPoints[i] = coordinates;
            return;
        }
    }
}

int Ant::nearestPoint (int index) {
    // find the closest familiar point the ant knows, which is closer to the
    // nest than the currently selected point

    float minDistance = 1000;
    int minPoint = index;

    for (int i = 0; i < index; i++) {
        if (familiarPoints[i].x != -1 && familiarPoints[i].y != -1) {
            if (distance(coordinates, familiarPoints[i]) < minDistance) {
                float minDistance = distance(coordinates, familiarPoints[i]);
                minPoint = i;
            }
        }
    }
    return minPoint;
}

void AntNest::init (sf::Vector2f center) {
    coordinates = center;

    radius = 10;  // the radius size of the nest itself

    entity.setRadius(radius);
    entity.setPosition(coordinates);
    entity.setFillColor(sf::Color::Cyan);  // color can change
}


void ANT::init (sf::Vector2f center) {  // initialize the antNest and the ants
    antNest.init(center);

    for (unsigned int i = 0; i < ANT_POPULATION; i++) {
        ants[i].init(center);
    }
}


void ANT::moveAnts (void) {  // move all ants

    for (unsigned int i = 0; i < ANT_POPULATION; i++) {
        ants[i].move();
    }
}
