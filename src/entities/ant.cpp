#include "ant.hpp"
#include "random.hpp"
#include "../logic.hpp"

#include "food.hpp"
#include "phermone.hpp"


void Ant::init (sf::Vector2f center, int index) {
    id = index;

    coordinates = center;
    float theta = rotation(generator) * 12;  // convert +-pi/12 to +-pi radians
    velocity = sf::Vector2f(cos(theta), sin(theta));

    energy = 60 * 20;  // 60 fps * 20 seconds
    hasFood = 0;

    familiarPoints.push_back(center);

    float radius = 1;
    entity.setRadius(radius);
    entity.setPosition(center.x - radius, center.y - radius);
    entity.setFillColor(sf::Color::Black);

}

void Ant::move (void) {

    int energyLowLimit = 60 * 12;  // energy left when heading home (60 fps * seconds)
    // float phermoneDirection = getPhermoneDirection();

    if (true) {
        sf::Vector2f point;
        float pointDistance;
        bool foraging;

        if (energy < energyLowLimit || hasFood) {
            point = familiarPoints[destinationPointIndex];  // the point used for navigation
            pointDistance = LOGIC::distance(coordinates, point);  // distance to said point
            foraging = false;

            if (hasFood) {
                PHERM::place(coordinates);
            }
        }

        else if (energy >= energyLowLimit) {
            FOOD::nearest(coordinates, &point, &pointDistance);
            foraging = true;

            if (pointDistance < 1 && !hasFood) {  // looking for food and within 1 u of it (ant has found food)
                hasFood = true;
            }
        }


        setVelocity(point, pointDistance, foraging);

        coordinates += velocity;
        entity.move(velocity);

        energy -= 1;

        if (LOGIC::nearby(coordinates, familiarPoints[0], 5)) {  // distance to home <= 5
            familiarPoints.erase(familiarPoints.begin() + 1, familiarPoints.end());

            float theta = rotation(generator) * 12;  // convert pi/12 to pi radians
            velocity = sf::Vector2f(cos(theta), sin(theta));

            hasFood = false;
            energy = 60 * 20;
        }

        addFamiliarPoint();
    }
}

void Ant::setVelocity (sf::Vector2f point, float pointDistance, bool foraging) {
    float theta = rotation(generator);  // roatation between +-pi/12 radians

    // SET DIRECTION OF PHERMONE PATH NOW...
    // getPhermoneDirection();

    if (pointDistance <= FAMILIAR_RADIUS) {  // if close enough to be familiar to specific point
        velocity = LOGIC::rotate(LOGIC::standardise(sf::Vector2f(
            point.x - coordinates.x, point.y - coordinates.y
        )), theta);  // set velocity towards the point
    }
    else {

        velocity = LOGIC::rotate(velocity, theta);  // rotate movement by theta radians

    }


    if (!foraging) {  // navigating home

        if (pointDistance <= FAMILIAR_RADIUS * 0.1) {  // if close enough to point select next one, unless ant is already home
            if (destinationPointIndex > 0)
                destinationPointIndex -= 1;
        }

        else if (pointDistance > FAMILIAR_RADIUS) {
            destinationPointIndex = nearestPoint(destinationPointIndex);  // search through all points closer then currently selected
        }
    }
}

void Ant::addFamiliarPoint () {
    for (sf::Vector2f &familiarPoint : familiarPoints) {
        if (LOGIC::distance(coordinates, familiarPoint) <= FAMILIAR_RADIUS * 0.75) {  // add points at a smallar radius than they can be found from
            return;
        }
    }
    destinationPointIndex = familiarPoints.size();  // find the nearest point of the ones the ant recognizes
    familiarPoints.push_back(coordinates);
}

int Ant::nearestPoint (int index) {
    // find the closest familiar point the ant knows, which is closer to the
    // nest than the currently selected point

    float minDistance = 4096;  // arbitrarily big number
    int minIndex = 0;

    for (int i = 0; i < index; i++) {
        if (LOGIC::distance(coordinates, familiarPoints[i]) <= minDistance) {
            minDistance = LOGIC::distance(coordinates, familiarPoints[i]);
            minIndex = i;
        }
    }
    return minIndex;
}

float Ant::getPhermoneDirection () {  // draw straight lines and count phermones close to the line

    int maxPhermoneCount = 0;
    float maxPhermoneAngle = 0;

    for (float theta = -M_PI; theta < M_PI; theta += M_PI * 0.125) {
        int phermoneCount = 0;
        for (float r = FAMILIAR_RADIUS * 0.1; r < FAMILIAR_RADIUS; r += FAMILIAR_RADIUS * 0.1) {
            sf::Vector2f point(coordinates.x + r*cos(theta), coordinates.y + r*sin(theta));

            for (Phermone &phermone : phermones) {
                if (LOGIC::distance(point, phermone.coordinates) < 10) {
                    phermoneCount += phermone.strenght;
                }
            }
        }
        if (phermoneCount > maxPhermoneCount) {
            maxPhermoneCount = phermoneCount;
            maxPhermoneAngle = theta;
        }
    }

    return maxPhermoneCount ? maxPhermoneAngle : NAN;

}


void AntNest::init (sf::Vector2f center) {
    coordinates = center;

    float radius = 10;  // the radius size of the nest itself

    entity.setRadius(radius);
    entity.setPosition(center.x - radius, center.y - radius);
    entity.setFillColor(sf::Color::Cyan);
    entity.setOutlineColor(sf::Color::Black);  // color can change
    entity.setOutlineThickness(0.5);
}


void ANTS::init (sf::Vector2f center) {  // initialize the antNest and the ants
    antNest.init(center);

    for (unsigned int i = 0; i < ANT_POPULATION; i++) {
        ants[i].init(center, i);
    }
}


void ANTS::moveAnts (void) {  // move all ants

    for (Ant &ant : ants) {
        ant.move();
    }
    PHERM::decrementAll();

}
