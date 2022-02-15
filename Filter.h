#pragma once
#include "Ray.h"
#include "Library/n_math.h"

namespace rayTracing{
    class ImageFilter{
    public:
        virtual n_math::Vector3 filter(const n_math::Vector3& c) const = 0;
    };

    class GammaFilter : public ImageFilter {
    public:
        GammaFilter(float factor) : m_factor(factor){}
        virtual n_math::Vector3 filter(const n_math::Vector3& c) const override{
            return Ray::gamma_to_linear(c, m_factor);
        }
    private:
        float m_factor;
    };

}