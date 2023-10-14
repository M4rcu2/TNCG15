#include "polygon.h"
#include "ray.h"

#include <glm/gtx/string_cast.hpp>  //to string for vec

// Rectangle subclass----------------------------------------------------------------------
glm::vec3 Rectangle::PointInPolygon(const Ray& ray) const{

    bool isOnPlane = IntersectPlane(ray);

    if(isOnPlane){
        glm::vec3 s = ray.startVertex;
        glm::vec3 d = ray.direction;
        glm::vec3 v = vertices[0];
        glm::vec3 c1 = vertices[1]-v;
        glm::vec3 c2 = vertices[2]-v;
        float t = glm::dot((v-s),recNormal)/glm::dot(d,recNormal);
        glm::vec3 intersectionPoint = s + t * d;

        //a and b criterion
        float a = glm::dot((intersectionPoint-v),c1)/glm::dot(c1,c1);
        float b = glm::dot((intersectionPoint-v),c2)/glm::dot(c2,c2);
        if(a>=0 && a<=1 && b>=0 && b<=1){
            return intersectionPoint + recNormal*errorMargin;
        }
    }
    glm::vec3 notOnPlane(-100,-100,-100);//Vector for when we do not intersect with the rectangle
    return notOnPlane;
}
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
//Calculate the normal and normalizes it before returning
glm::vec3 Rectangle::getNormal() const{
    glm::vec3 edge1 = vertices[1]-vertices[0];
    glm::vec3 edge2 = vertices[2]-vertices[0];
    glm::vec3 theNormal = glm::cross(edge1, edge2);
    theNormal = glm::normalize(theNormal);
    return theNormal;
}

// Implementations for new Rectangle methods
float Rectangle::getWidth() const {
    // Assuming vertices[1] and vertices[0] are adjacent edges of the rectangle
    return glm::length(vertices[1] - vertices[0]);
}

float Rectangle::getHeight() const {
    // Assuming vertices[2] and vertices[0] are adjacent edges of the rectangle
    return glm::length(vertices[2] - vertices[0]);
}

bool Rectangle::collision(const Ray& ray, glm::vec3& refIntersection) const {

    bool isOnPlane = IntersectPlane(ray);

    if (isOnPlane) {
        double t = glm::dot((vertices[0] - ray.startVertex), recNormal) / glm::dot(ray.direction, recNormal);
        //std::cout << recNormal.x << " + " << recNormal.y << " + " << recNormal.z << std::endl;
        glm::vec3 c1 = vertices[1] - vertices[0];
        glm::vec3 c2 = vertices[3] - vertices[0];
        glm::vec3 x;

        x.x= ray.startVertex.x + t * ray.direction.x;
        x.y = ray.startVertex.y + t * ray.direction.y;
        x.z = ray.startVertex.z + t * ray.direction.z;


        // Extra check to see if the intersecting surface is very close to the last intersection point
        if (t <= 0.01) {
            return false;
        }

        double a = glm::dot((x - vertices[0]), c1) / glm::dot(c1, c1);
        double b = glm::dot((x - vertices[0]), c2) / glm::dot(c2, c2);


        if ((0.0 <= a && a <= 1.0 && 0.0 <= b && b <= 1.0) || (abs(a) <= errorMargin && 0.0 <= b && b <= 1.0) || (abs(b) <= errorMargin && 0.0 <= a && a <= 1.0)) {
            refIntersection = x;
            //std::cout << refIntersection.x << " + " << refIntersection.y << " + " << refIntersection.z << std::endl;
            return true;
        }
    }
    return false;
}

// Triangle subclass----------------------------------------------------------------------
glm::vec3 Triangle::PointInPolygon(const Ray& ray) const{

    bool isOnPlane = IntersectPlane(ray);

    if(isOnPlane){
        glm::vec3 E1 = vertices[1]-vertices[0];
        glm::vec3 E2 = vertices[2]-vertices[0];
        glm::vec3 T = ray.startVertex-vertices[0];
        glm::vec3 D = ray.direction;
        glm::vec3 P = glm::cross(D, E2);
        glm::vec3 Q = glm::cross(T, E1);
        //float t = dot(Q,E2)/dot(P,E1);
        float u = dot(P,T)/dot(P,E1);
        float v = dot(Q,D)/dot(P,E1);
        //implement intersectionPoint
        glm::vec3 intersectionPoint = (1-u-v)*vertices[0] + u*vertices[1] + v*vertices[2];
        if(u>=0 && v>=0 && u+v<=1){
            return intersectionPoint + triNormal*errorMargin;
        }
    }
    glm::vec3 notOnPlane(-100,-100,-100); //Vector for when we do not intersect with the triangle
    return notOnPlane;
}
//Function to know if the ray intersects the triangle (or more like "does it come from the right direction")
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
//Calculate the normal and normalizes it before returning
glm::vec3 Triangle::getNormal() const{
    glm::vec3 edge1 = vertices[1]-vertices[0];
    glm::vec3 edge2 = vertices[2]-vertices[0];
    glm::vec3 theNormal = glm::cross(edge1, edge2);
    theNormal = glm::normalize(theNormal);
    return theNormal;
}

bool Triangle::collision(const Ray& ray, glm::vec3& refIntersection) const {

    // Check if the normal is facing the ray
    bool isOnPlane = IntersectPlane(ray);

    if (isOnPlane) {

        // Möller-Trumbore algoritm
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

        if ((0.0 <= u && 0.0 <= v && (u + v) <= 1.0) || (abs(u) <= errorMargin && 0.0 <= v && v <= 1.0) || (abs(v) <= errorMargin && 0.0 <= u && u <= 1.0)) {
            
            refIntersection.x = ray.startVertex.x + t * D.x;
            refIntersection.y = ray.startVertex.y + t * D.y;
            refIntersection.z = ray.startVertex.z + t * D.z;

            // Extra check to see if the intersecting surface is very close to the last intersection point
            if (t <= 0.01) {
                return false;
            }

            return true;
        }

    }
    return false;
}

// tetrahedra subclass----------------------------------------------------------------------
glm::vec3 Tetrahedron::pointOnTetra(const Ray& ray) {
    
    glm::vec3 a = faces[1]->PointInPolygon(ray);
    std::cout<<"normal face1 "<<glm::to_string(faces[1]->triNormal);
    if(a != glm::vec3(-100, -100, -100)){
        return a;
    }
    return glm::vec3(-100, -100, -100);
}

// sphere subclass-------------------------------------------------------------------------
bool Sphere::collision(const Ray& ray, glm::vec3& refIntersection) {
    
    glm::vec3 directionVector = ray.startVertex - this->sphereCenter;

    double C_1 = glm::dot(ray.direction, ray.direction);                            // C_1 = D^2
    double C_2 = glm::dot(glm::vec3(2.0,2.0,2.0) * ray.direction, directionVector); // C_2 = 2D(S-C)
    double C_3 = glm::dot(directionVector, directionVector) - pow(this->radius, 2); // (S - C)^2 - r^2

    double arg = pow(C_2, 2) - 4.0 * C_1 * C_3;
    float errorMargin = 10e-2f;

    if (abs(arg) < errorMargin) {
        glm::vec3 xr = ray.startVertex + ray.direction * glm::vec3(-C_2 / 2.0, -C_2 / 2.0,-C_2 / 2.0);

        spheNormal = glm::normalize((xr - this->sphereCenter));

        refIntersection = xr;

        return true;
    }
    else if (arg > 0.0) {

        double t1 = (-C_2 + sqrt(arg)) / (2.0 * C_1);
        double t2 = (-C_2 - sqrt(arg)) / (2.0 * C_1);

        double t = glm::min(t1, t2);

        // If the new intersection point is very close to the starting point of the ray, the ray does not intersect the surface
        if (t <= errorMargin) {

            if ((glm::max(t1, t2)) <= errorMargin) {

                return false;
            }
            t = glm::max(t1, t2);
        }

        glm::vec3 xr = ray.startVertex + ray.direction * glm::vec3(t,t,t);

        spheNormal = glm::normalize((xr - this->sphereCenter));

        refIntersection = xr;

        return true;
    }

    return false;
}

