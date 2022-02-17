#pragma once

#include "Ray.h"
//#include "HitRecorder.h"

namespace rayTracing{

    class Material;
    class ScatterRecorder{
    public:
        Ray ray;
        n_math::Vector3 albedo;
    };

    class HitRecorder{
    public:
        float t;
        n_math::Vector3 p;
        n_math::Vector3 n;
        std::shared_ptr<Material> mat;
    };

    class Material{
    public:
        virtual bool scatter(const Ray& r, const HitRecorder& hitRecorder, ScatterRecorder& scatterRecorder) const = 0;
    };

    class Lambertian : public Material{
    public:
        Lambertian(const n_math::Vector3 c) : m_albedo(c){}

        virtual bool scatter(const Ray& r, const HitRecorder& hitRecorder, ScatterRecorder& scatterRecorder) const override{
            n_math::Vector3 target = hitRecorder.p + hitRecorder.n + Ray::random_in_unit_sphere();
            scatterRecorder.ray = Ray(hitRecorder.p, target - hitRecorder.p);
            scatterRecorder.albedo = m_albedo;
            return true;
        };

    private:
        n_math::Vector3 m_albedo;
    };


}