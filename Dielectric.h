#pragma once

#include "Material.h"
#include "Metal.h"

namespace rayTracing{

    inline bool refract(const n_math::Vector3& v, const n_math::Vector3& n, float ni_over_nt, n_math::Vector3& refracted){
        n_math::Vector3 uv = n_math::normalize(v);
        float dt = n_math::dot(uv, n);
        float D = 1.f - n_math::pow(ni_over_nt, 2) * (1.f - n_math::pow(dt, 2));
        if (D > 0.f){
            refracted = -1.f * ni_over_nt * (uv - n * dt) - n * sqrtf(D);
            return true;
        }else{
            return false;
        }
    }

    inline float schlick(float cosine, float ri){
        float r0 = n_math::pow((1.f - ri) / (1.f + ri), 2);
        return r0 + (1.f - r0) * n_math::pow(1.f - cosine, 5);
    }

    class Dielectric : public Material{
    public:
        Dielectric(float ri) : m_ri(ri){}

        virtual bool scatter(const Ray& r, const HitRecorder& hitRecorder, ScatterRecorder& scatterRecorder) const override{
            n_math::Vector3 outward_normal;
            n_math::Vector3 reflected = reflect(r.direction(), hitRecorder.n);
            float ni_over_nt;
            float reflect_prob;
            float cosine;
            if (n_math::dot(r.direction(), hitRecorder.n) > 0){
                outward_normal = -1.f * hitRecorder.n;
                ni_over_nt = m_ri;
                cosine = m_ri * n_math::dot(r.direction(), hitRecorder.n) / n_math::length(r.direction());
            }else{
                outward_normal = hitRecorder.n;
                ni_over_nt = 1.f / m_ri;
                cosine = -1.f * n_math::dot(r.direction(), hitRecorder.n) / n_math::length(r.direction());
            }

            scatterRecorder.albedo = n_math::Vector3{1, 1, 1};
            n_math::Vector3 refracted;
            if (refract(-1.f * r.direction(), outward_normal, ni_over_nt, refracted)){
                reflect_prob = schlick(cosine, m_ri);
            }else{
                reflect_prob = 1;
            }

            if (n_math::drand() < reflect_prob){
                scatterRecorder.ray = Ray(hitRecorder.p, reflected);
            }else{
                scatterRecorder.ray = Ray(hitRecorder.p, refracted);
            }

            return true;
        }

    private:
        float m_ri;
    };

}