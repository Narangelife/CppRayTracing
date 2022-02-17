#pragma once

#include "Library/n_math.h"

namespace rayTracing{
    class TonemapFilter : public ImageFilter{
    public:
        TonemapFilter(){}
        virtual n_math::Vector3 filter(const n_math::Vector3& c) const override{
            return n_math::minPerElem(n_math::maxPerElem(c, n_math::Vector3{0.f, 0.f, 0.f}), n_math::Vector3{1.f,1.f,1.f});
        }
    };
}