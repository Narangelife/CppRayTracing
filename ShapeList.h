#pragma once
#include "Shape.h"

namespace rayTracing{
    class ShapeList : public Shape{
    public:
        ShapeList(){}

        void add(const std::shared_ptr<Shape>& shape){
            m_list.push_back(shape);
        }

        virtual bool hit(const Ray& r, float t0, float t1, HitRecorder& hitRecorder) const override{
            HitRecorder temp_rec;
            bool hit_anything = false;
            float closest_so_far = t1;
            for (auto& p : m_list){
                if (p->hit(r, t0, closest_so_far, temp_rec)){
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    hitRecorder = temp_rec;
                }
            }
            return hit_anything;
        }

    private:
        std::vector<std::shared_ptr<Shape>> m_list;
    };
}