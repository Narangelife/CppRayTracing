#pragma once

#include "Shape.h"

namespace rayTracing{
    class FlipNormal : public Shape{
    public:
        FlipNormal(const std::shared_ptr<Shape>& shape) : m_shape(shape){};

        virtual bool hit(const Ray& r, float t0, float t1, HitRecorder& hitRecorder) const override{
            if (m_shape->hit(r, t0, t1, hitRecorder)){
                hitRecorder.n = -1.f * hitRecorder.n;
                return true;
            }else{
                return false;
            }
        }

    private:
        std::shared_ptr<Shape> m_shape;
    };
}