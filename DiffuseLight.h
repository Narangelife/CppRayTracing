#pragma once
#include "Material.h"
#include "Texture.h"
namespace rayTracing{
    class DiffuseLight : public Material{
    public:
        DiffuseLight(const std::shared_ptr<Texture>& emit): m_emit(emit){}

        virtual bool scatter(const Ray& r, const HitRecorder& hitRecorder, ScatterRecorder& scatterRecorder) const override{
            return false;
        }

        virtual n_math::Vector3 emitted(const Ray& r, const HitRecorder& hitRecorder) const override{
            return m_emit->value(hitRecorder.u, hitRecorder.v, hitRecorder.p);
        }

    private:
        std::shared_ptr<Texture> m_emit;
    };
}