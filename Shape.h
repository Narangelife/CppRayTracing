#pragma once
#include "Ray.h"
#include "HitRecorder.h"
namespace rayTracing{
    class Shape{
    public:
        virtual bool hit(const Ray& r, float t0, float t1, HitRecorder& hitRecorder) const = 0;
    };
}