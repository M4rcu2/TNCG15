#include "../include/ray.h"

Ray::Ray(glm::vec3 start, glm::vec3 direction, ColorDBL color, Ray* prev, Ray* next)
    : startVertex(start), direction(direction), color(color), previousRay(prev), nextRay(next)  {}

