#include "ant.hpp"
#include "random.hpp"
#include "../logic.hpp"

#include "food.hpp"
#include "phermone.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


AntNest::AntNest (int x, int y) {
    position = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));

    float radius = 10.0f;  // the radius size of the nest itself

    entity.setRadius(radius);
    entity.setPosition(position.x - radius, position.y - radius);
    entity.setFillColor(sf::Color::Cyan);
    // entity.setOutlineColor(sf::Color::Black);  // color can change
    // entity.setOutlineThickness(0.5f);
}

void AntNest::draw (sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(entity, states);
}


Ant::Ant (sf::Vector2f coordinates, int index) {
    id = index;

    position = coordinates;
    float theta = rotation(generator) * 12;  // convert +-pi/12 to +-pi radians
    velocity = sf::Vector2f(cos(theta), sin(theta));

    energy = 60 * 20;  // 60 fps * 20 seconds
    hasFood = 0;

    familiarPoints.push_back(position);

    float radius = 1.0f;
    entity.setRadius(radius);
    entity.setPosition(position.x - radius, position.y - radius);
    entity.setFillColor(sf::Color::Black);

}

void Ant::move (Phermones& phermones, const Food& food) {

    int energyLowLimit = 60 * 12;  // energy left when heading home (60 fps * seconds)
    // float phermoneDirection = getPhermoneDirection();

    if (true) {
        sf::Vector2f point;
        float pointDistance;
        bool foraging;

        if (energy < energyLowLimit || hasFood) {
            point = familiarPoints[destinationPointIndex];  // the point used for navigation
            pointDistance = LOGIC::distance(position, point);  // distance to said point
            foraging = false;

            if (hasFood) {
                phermones.place(position);
            }
        }

        else if (energy >= energyLowLimit) {  // ant is looking for food
            food.nearest(position, &point, &pointDistance);
            foraging = true;

            if (pointDistance < 1 && !hasFood) {  // looking for food and within 1 u of it (ant has found food)
                hasFood = true;
            }
        }


        setVelocity(point, pointDistance, foraging);

        position += velocity;
        entity.setPosition(position);

        energy -= 1;

        if (LOGIC::nearby(position, familiarPoints[0], 5)) {  // distance to home <= 5 (ant is home)
            familiarPoints.erase(familiarPoints.begin() + 1, familiarPoints.end());

            float theta = rotation(generator) * 12;  // get random direction to head in
            velocity = sf::Vector2f(cos(theta), sin(theta));

            hasFood = false;
            energy = 60 * 20;
        }

        addFamiliarPoint();  // and checks if it should add a refernce point
        // if (1) printf("%d: %f, %f\n", id, velocity.x, velocity.y);
        // if (1) printf("%d: %f, %f\n", id, position.x, position.y);
        // if (1) printf("%d: %f, %f\n", id, this->entity.getPosition().x, this->entity.getPosition().y);

    }
}

void Ant::setVelocity (sf::Vector2f point, float pointDistance, bool foraging) {
    float theta = rotation(generator);  // roatation between +-pi/12 radians

    // SET DIRECTION OF PHERMONE PATH NOW...
    // getPhermoneDirection();

    if (pointDistance <= FAMILIAR_RADIUS) {  // if close enough to be familiar to specific point
        velocity = LOGIC::rotate(LOGIC::standardise(sf::Vector2f(
            point.x - position.x, point.y - position.y
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
        if (LOGIC::distance(position, familiarPoint) <= FAMILIAR_RADIUS * 0.75) {  // add points at a smallar radius than they can be found from
            return;
        }
    }
    destinationPointIndex = familiarPoints.size();  // find the nearest point of the ones the ant recognizes
    familiarPoints.push_back(position);
}

int Ant::nearestPoint (int index) {
    // find the closest familiar point the ant knows, which is closer to the
    // nest than the currently selected point

    float minDistance = LOGIC::distance(position, familiarPoints[0]);;  // arbitrarily big number
    int minIndex = 0;

    for (int i = 1; i < index; i++) {
        if (LOGIC::distance(position, familiarPoints[i]) <= minDistance) {
            minDistance = LOGIC::distance(position, familiarPoints[i]);
            minIndex = i;
        }
    }
    return minIndex;
}

float Ant::getPhermoneDirection (const Phermones& phermones) {  // draw straight lines and count phermones close to the line

    // int maxPhermoneCount = 0;
    // float maxPhermoneAngle = 0;

    // for (float theta = -M_PI; theta < M_PI; theta += M_PI * 0.125) {
    //     int phermoneCount = 0;
    //     for (float r = FAMILIAR_RADIUS * 0.1; r < FAMILIAR_RADIUS; r += FAMILIAR_RADIUS * 0.1) {
    //         sf::Vector2f point(position.x + r*cos(theta), position.y + r*sin(theta));

    //         for (Phermone phermone: phermones) {
    //             if (LOGIC::distance(point, phermone.coordinates) < 10) {
    //                 phermoneCount += phermone.strenght;
    //             }
    //         }
    //     }
    //     if (phermoneCount > maxPhermoneCount) {
    //         maxPhermoneCount = phermoneCount;
    //         maxPhermoneAngle = theta;
    //     }
    // }

    // return maxPhermoneCount ? maxPhermoneAngle : NAN;

}


AntColony::AntColony (const AntNest& nest, int population_size) {
    home = nest.position;

    for (int i = 0; i < population_size; i++) {
        ants.push_back(Ant(home, i));
    }
}

void AntColony::update (Phermones& phermones, const Food& food) {
    for (Ant& ant: ants) {  // FUCKING C++ REFERENCES
        ant.move(phermones, food);
    }
}

void AntColony::draw (sf::RenderTarget &target, sf::RenderStates states) const {
    for (const Ant& ant: ants) {
        target.draw(ant.entity, states);
    }
}
