#include <random>
#include <math.h>

std::default_random_engine generator;
 // the direction of the ant is rotated by $rotation radians
std::uniform_real_distribution<float> rotation(-M_PI/12, M_PI/12);
