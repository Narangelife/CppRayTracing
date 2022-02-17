#pragma once

#include "Ray.h"
#include "Texture.h"
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
        float u;
        float v;
        n_math::Vector3 p;
        n_math::Vector3 n;
        std::shared_ptr<Material> mat;
    };

    class Material{
    public:
        virtual bool scatter(const Ray& r, const HitRecorder& hitRecorder, ScatterRecorder& scatterRecorder) const = 0;
        virtual n_math::Vector3 emitted(const Ray& r, const HitRecorder& hitRecorder) const {return n_math::Vector3{0, 0, 0};};
    };

    class Lambertian : public Material{
    public:
        Lambertian(const std::shared_ptr<Texture> c) : m_albedo(c){}

        virtual bool scatter(const Ray& r, const HitRecorder& hitRecorder, ScatterRecorder& scatterRecorder) const override{
            n_math::Vector3 target = hitRecorder.p + hitRecorder.n + Ray::random_in_unit_sphere();
            scatterRecorder.ray = Ray(hitRecorder.p, target - hitRecorder.p);
            scatterRecorder.albedo = m_albedo->value(hitRecorder.u, hitRecorder.v, hitRecorder.p);
            return true;
        };

    private:
        std::shared_ptr<Texture> m_albedo;
    };


}