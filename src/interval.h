#pragma once
#include "common.h"

class interval
{
public:
    double min, max;

    interval()
        : min(+infinity), max(-infinity)
    {}

    interval(double min, double max)
        : min(min), max(max)
    {}

    double size() const
    {
        return max - min;
    }

    double clamp(double x) const 
    {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    bool contains(double x) const
    {
        return x>=min && x<=max;
    }

    bool surrounds(double x) const
    {
        return x>min && x<max;
    }

    static const interval empty, universe;

};

const interval interval::empty = interval(infinity,-infinity);
const interval interval::universe = interval(-infinity, infinity);