#pragma once
#include "Shape.h"
#include "Material.h"

namespace rayTracing{
    class Rect : public Shape{
    public:
        enum AxisType{
            kXY = 0,
            kXZ,
            kYZ
        };

        Rect(float x0, float x1, float y0, float y1, float k, AxisType axis, const std::shared_ptr<Material>& m)
            :m_x0(x0), m_x1(x1), m_y0(y0), m_y1(y1), m_k(k), m_axis(axis), m_material(m){};

        virtual bool hit(const Ray& r, float t0, float t1, HitRecorder& hitRecorder) const override{
            n_math::Vector3 axis;
            float x, y, t;
            switch(m_axis){
                case kXY:
                    axis = n_math::Vector3{0, 0, 1};
                    t = (m_k - r.origin().z) / r.direction().z;
                    if (t < t0 || t > t1){
                        return false;
                    }
                    x = r.origin().x + t * r.direction().x;
                    y = r.origin().y + t * r.direction().y;
                    break;
                case kXZ:
                    axis = n_math::Vector3{0, 1, 0};
                    t = (m_k - r.origin().y) / r.direction().y;
                    if (t < t0 || t > t1){
                        return false;
                    }
                    x = r.origin().x + t * r.direction().x;
                    y = r.origin().z+ t * r.direction().z;
                    break;
                case kYZ:
                    axis = n_math::Vector3{1, 0, 0};
                    t = (m_k - r.origin().x) / r.direction().x;
                    if (t < t0 || t > t1){
                        return false;
                    }
                    x = r.origin().y + t * r.direction().y;
                    y = r.origin().z + t * r.direction().z;
                    break;
            }

            if (x < m_x0 || x > m_x1 || y < m_y0 || y > m_y1){
                return false;
            }

            hitRecorder.u = (x - m_x0) / (m_x1 - m_x0);
            hitRecorder.v = (y - m_y0) / (m_y1 - m_y0);
            hitRecorder.t = t;
            hitRecorder.mat = m_material;
            hitRecorder.p = r.at(t);
            hitRecorder.n = axis;
            return true;
        }

    private:
        float m_x0, m_x1, m_y0, m_y1, m_k;
        AxisType m_axis;
        std::shared_ptr<Material> m_material;
    };
}