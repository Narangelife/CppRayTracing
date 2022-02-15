#pragma once
#include "Shape.h"

namespace rayTracing{
    class Sphere : public Shape{
    public:
        Sphere() {}
        Sphere(const n_math::Vector3& c, float r) : m_center(c), m_radius(r){}

        virtual bool hit(const Ray& r, float t0, float t1, HitRecorder& hitRecorder) const override{
            n_math::Vector3 oc = r.origin() - m_center;
            float a = n_math::dot(r.direction(), r.direction());
            float b = 2.f * n_math::dot(r.direction(), oc);
            float c = n_math::dot(oc, oc) - n_math::pow(m_radius, 2);
            float D = b * b - 4 * a * c;
            if (D > 0){
                float root = sqrtf(D);
                float temp = (-b - root) / (2.f * a);
                if (temp < t1 && temp > t0){
                    hitRecorder.t = temp;
                    hitRecorder.p = r.at(hitRecorder.t);
                    hitRecorder.n = (hitRecorder.p - m_center) / m_radius;
                    return true;
                }
                temp = (-b + root) / (2.f * a);
                if (temp < t1 && temp > t0){
                    hitRecorder.t = temp;
                    hitRecorder.p = r.at(hitRecorder.t);
                    hitRecorder.n = (hitRecorder.p - m_center) / m_radius;
                    return true;
                }
            }
            return false;
        }

    private:
        n_math::Vector3 m_center;
        float m_radius;
    };
}