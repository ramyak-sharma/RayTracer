#pragma once
#include "common.h"

class hit_record;

class material
{
public:
    virtual ~material() = default;
    virtual bool scatter(const ray& in, const hit_record& rec, color& attenuation, ray& scattered) const 
    {
        return false;
    }
};

class lambertian : public material
{
public:
    lambertian(const color& albedo)
        : albedo(albedo)
    {}

    bool scatter(const ray& in, const hit_record& rec, color& attenuation, ray& scattered) const override
    {
        vec3 scatter_direction = rec.normal + random_unit_vector();
        if(scatter_direction.near_zero()){
            scatter_direction=rec.normal;
        }
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;

};

class metal : public material
{
public:
    metal(const color& albedo)
        :albedo(albedo)
    {}

    bool scatter(const ray& in, const hit_record& rec, color& attenuation, ray& scattered) const override
    {
        vec3 reflected = reflect(in.direction(), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return true;
    }
private:
    color albedo;
};