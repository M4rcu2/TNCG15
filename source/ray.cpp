#include "../include/ray.h"


Ray::Ray(glm::vec3 start, glm::vec3 direction, ColorDBL color, Ray* prev, Ray* next)
: startVertex(start), direction(direction), previousRay(prev), nextRay(next), color(color)  {
    glm::normalize(direction); // Normalizes the direction vector
}
