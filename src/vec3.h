#pragma once
#include "common.h"

class vec3
{
public:
    double e[3];

    vec3()
    {
        e[0]=0;
        e[1]=0;
        e[2]=0;
    }
    
    vec3(double e0, double e1, double e2)
    {
        e[0]=e0;
        e[1]=e1;
        e[2]=e2;
    }

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[] (int i) const { return e[i]; }
    double& operator[] (int i) { return e[i]; }

    vec3& operator+=(const vec3 v)
    {
        e[0]+=v.e[0];
        e[1]+=v.e[1];
        e[2]+=v.e[2];
        return *this;
    }

    vec3& operator*=(double t)
    {
        e[0]*=t;
        e[1]*=t;
        e[2]*=t;
        return *this;
    }

    vec3& operator/=(double t) {
        return *this *= 1/t;
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    static vec3 random(){return vec3(random_double(), random_double(), random_double());}

    static vec3 random(double min, double max) {
        return vec3(random_double(min, max),random_double(min, max),random_double(min, max));
    }

};

using point3 = vec3; //using point3 as an alias, useful for clarity

inline std::ostream& operator<<(std::ostream& out, const vec3& v){
    return out <<v.e[0]<<' '<<v.e[1]<<' '<<v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v){
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v){
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v){
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(const vec3& u, double t){
    return vec3(u.e[0] * t, u.e[1] * t, u.e[2] * t);
}

inline vec3 operator*(double t, const vec3& u){
    return u*t;
}

inline vec3 operator/(const vec3& u, double t){
    return u*(1/t);
}

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

inline vec3 random_in_unit_sphere()
{
    while (true)
    {
        vec3 p = vec3::random(-1,1);
        if(p.length_squared()<1)
            return p;
    }
}

inline vec3 random_unit_vector()
{
    return unit_vector(random_in_unit_sphere());
}

inline vec3 random_on_hemisphere(const vec3& normal)
{
    vec3 v = random_unit_vector();
    if(dot(normal, v)>0)
        return v;
    else 
        return -v;
}