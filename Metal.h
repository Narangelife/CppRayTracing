#pragma once
#include "Material.h"

namespace rayTracing{
    inline n_math::Vector3 reflect(const n_math::Vector3& v, const n_math::Vector3& n){
        return v - 2.f * n_math::dot(v, n) * n;
    }

    class Metal : public Material{
    public:
        Metal(const n_math::Vector3& c, float fuzz) : m_albedo(c), m_fuzz(fuzz){}

        virtual bool scatter(const Ray& r, const HitRecorder& hitRecorder, ScatterRecorder& scatterRecorder) const override{
            n_math::Vector3 reflected = reflect(n_math::normalize(r.direction()), hitRecorder.n);
            reflected = reflected + m_fuzz * Ray::random_in_unit_sphere();
            scatterRecorder.ray = Ray(hitRecorder.p, reflected);
            scatterRecorder.albedo = m_albedo;
            return n_math::dot(scatterRecorder.ray.direction(), hitRecorder.n) > 0;
        }

    private:
        n_math::Vector3 m_albedo;
        float m_fuzz;
    };
}