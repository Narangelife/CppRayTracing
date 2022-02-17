#pragma once
#include "Library/n_math.h"

namespace rayTracing{
    class Texture{
    public:
        virtual n_math::Vector3 value(float u, float v, const n_math::Vector3& p) const = 0;
    };

    class Colortexture : public Texture{
    public:
        Colortexture(const n_math::Vector3& c) : m_color(c){}

        virtual n_math::Vector3 value(float u, float v, const n_math::Vector3& p) const override{
            return m_color;
        }

    private:
        n_math::Vector3 m_color;
    };
}