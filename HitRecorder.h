#pragma once
#include "Library/n_math.h"

namespace rayTracing{
    class HitRecorder{
    public:
        float t;
        n_math::Vector3 p;
        n_math::Vector3 n;
    };
}