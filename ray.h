#pragma once
#include "vec3.h"

class ray{
private:
    point3 orig;
    vec3 dir;
public:
    
    ray(const point3& origin, const vec3& direction)
        : orig(origin), dir(direction)
    {}

    ray(){}

    const vec3& direction() const {return dir;}
    const point3& origin() const {return orig;} 

    point3 at(double t) const{
        return orig + t*dir;
    }

};