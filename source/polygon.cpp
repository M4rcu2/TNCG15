#include "polygon.h"
#include "ray.h"

#include <glm/gtx/string_cast.hpp>  //to string for vec

// Polygon subclass------------------------------------------------------------------------

glm::vec3 Polygon::getNormal() const {
    return glm::vec3(0, 0, 0); // Should NOT be used
}

bool Polygon::collision(const Ray& ray, glm::vec3& pointAtIntersection) {
    return false; // Should NOT be used
}

// Rectangle subclass----------------------------------------------------------------------

bool Rectangle::IntersectPlane(const Ray& ray) const{
    //Calculate if the normal of the infinitally large plane is opposoite direction of the ray to know if the ray goes away from the plane or not
    //Dot product calculation
    float dotProd = glm::dot(recNormal, ray.direction);
    //Is dot product positive, negative or zero?
    if(dotProd < 0){
        return true;//The ray and normal are opposite direction
    }
    else{
        return false;//Not opposite direction
    } 
}

bool Rectangle::collision(const Ray& ray, glm::vec3& pointAtIntersection)  {

    bool isOnPlane = IntersectPlane(ray);

    if (isOnPlane) {

        double t = glm::dot((vertices[0] - ray.startVertex), recNormal) / glm::dot(ray.direction, recNormal);
        glm::vec3 C_1 = vertices[1] - vertices[0];
        glm::vec3 C_2 = vertices[3] - vertices[0];
        glm::vec3 intersection;

        intersection.x = ray.startVertex.x + t * ray.direction.x;
        intersection.y = ray.startVertex.y + t * ray.direction.y;
        intersection.z = ray.startVertex.z + t * ray.direction.z;


        // if the intersecting surface is very close to the last intersection point
        if (t <= 0.01) {
            return false;
        }

        double a = glm::dot((intersection - vertices[0]), C_1) / glm::dot(C_1, C_1);
        double b = glm::dot((intersection - vertices[0]), C_2) / glm::dot(C_2, C_2);


        if ((0.0 <= a && a <= 1.0 && 0.0 <= b && b <= 1.0) || (abs(a) <= EPSILON && 0.0 <= b && b <= 1.0) || (abs(b) <= EPSILON && 0.0 <= a && a <= 1.0)) {
            pointAtIntersection.x = intersection.x + recNormal.x*EPSILON;
            pointAtIntersection.y = intersection.y + recNormal.y*EPSILON;
            pointAtIntersection.z = intersection.z + recNormal.z*EPSILON;
            return true;
        }
    }
    return false;
}

glm::vec3 Rectangle::getNormal() const{
    glm::vec3 edge1 = vertices[1]-vertices[0];
    glm::vec3 edge2 = vertices[2]-vertices[0];
    glm::vec3 theNormal = glm::cross(edge1, edge2);
    theNormal = glm::normalize(theNormal);
    return theNormal;
}

float Rectangle::getWidth() const {
    // Assuming vertices[1] and vertices[0] are adjacent edges of the rectangle
    return glm::length(vertices[1] - vertices[0]);
}

float Rectangle::getHeight() const {
    // Assuming vertices[2] and vertices[0] are adjacent edges of the rectangle
    return glm::length(vertices[2] - vertices[0]);
}

// Triangle subclass----------------------------------------------------------------------

bool Triangle::IntersectPlane(const Ray &ray) const{

    //Calculate if the normal of the infinitally large plane is opposoite direction of the ray to know if the ray goes away from the plane or not
    //Dot product calculation

    float dotProd = glm::dot(triNormal, ray.direction);
    //Is dot product positive, negative or zero?
    if(dotProd < 0){
        return true;//Opposite direction for normal of the triangle and the ray
    }
    else{
        return false; //Not opposite direction
    }
}

bool Triangle::collision(const Ray& ray, glm::vec3& pointAtIntersection)  {

    bool isOnPlane = IntersectPlane(ray);

    if (isOnPlane) {

        // M�ller
        glm::vec3 T = ray.startVertex - vertices[0];
        glm::vec3 E1 = vertices[1] - vertices[0];
        glm::vec3 E2 = vertices[2] - vertices[0];
        glm::vec3 D = ray.direction;
        glm::vec3 P = glm::cross(D, E2);
        glm::vec3 Q = glm::cross(T, E1);

        glm::vec3 result = (1.0 / glm::dot(P, E1)) * glm::dvec3(glm::dot(Q, E2), glm::dot(P, T), glm::dot(Q, D));
        double t = result.x;
        double u = result.y;
        double v = result.z;

        if ((0.0 <= u && 0.0 <= v && (u + v) <= 1.0) || (abs(u) <= EPSILON && 0.0 <= v && v <= 1.0) || (abs(v) <= EPSILON && 0.0 <= u && u <= 1.0)) {
            
            pointAtIntersection.x = ray.startVertex.x + t * D.x + triNormal.x*EPSILON;
            pointAtIntersection.y = ray.startVertex.y + t * D.y + triNormal.y*EPSILON;
            pointAtIntersection.z = ray.startVertex.z + t * D.z + triNormal.z*EPSILON;

            // if the intersecting surface is very close to the last intersection point
            if (t <= 0.01) {
                return false;
            }

            return true;
        }

    }
    return false;
}

glm::vec3 Triangle::getNormal() const {
    glm::vec3 edge1 = vertices[1]-vertices[0];
    glm::vec3 edge2 = vertices[2]-vertices[0];
    glm::vec3 theNormal = glm::cross(edge1, edge2);
    theNormal = glm::normalize(theNormal);
    return theNormal;
}


// tetrahedra subclass----------------------------------------------------------------------

glm::vec3 Tetrahedron::getNormal() const {
    return glm::vec3(0, 0, 0); // Is never used (For now)
}

bool Tetrahedron::collision(const Ray& ray, glm::vec3& pointAtIntersection) {
    return false; // Should NOT be used
}

// sphere subclass-------------------------------------------------------------------------

bool Sphere::collision(const Ray& ray, glm::vec3& pointAtIntersection) {
    
    glm::vec3 directionVector = ray.startVertex - this->sphereCenter;

    double C_1 = glm::dot(ray.direction, ray.direction);                            // C_1 = D^2
    double C_2 = glm::dot(glm::vec3(2.0,2.0,2.0) * ray.direction, directionVector); // C_2 = 2D(S-C)
    double C_3 = glm::dot(directionVector, directionVector) - pow(this->radius, 2); // (S - C)^2 - r^2

    double arg = pow(C_2, 2) - 4.0 * C_1 * C_3;

    if (abs(arg) < EPSILON) {
        glm::vec3 intersection = ray.startVertex + ray.direction * glm::vec3(-C_2 / 2.0, -C_2 / 2.0,-C_2 / 2.0);

        spheNormal = glm::normalize((intersection - this->sphereCenter));

        pointAtIntersection = intersection;

        return true;
    }
    else if (arg > 0.0) {

        double t1 = (-C_2 + sqrt(arg)) / (2.0 * C_1);
        double t2 = (-C_2 - sqrt(arg)) / (2.0 * C_1);

        double t = glm::min(t1, t2);

        // If the new intersection point is very close to the starting point of the ray, the ray does not intersect the surface
        if (t <= EPSILON) {

            if ((glm::max(t1, t2)) <= EPSILON) {

                return false;
            }
            t = glm::max(t1, t2);
        }

        glm::vec3 intersection = ray.startVertex + ray.direction * glm::vec3(t, t, t);

        spheNormal = glm::normalize((intersection - this->sphereCenter));

        pointAtIntersection = intersection;

        return true;
    }

    return false;
}

glm::vec3 Sphere::getNormal() const {
    return spheNormal; // Should NOT be used
}
