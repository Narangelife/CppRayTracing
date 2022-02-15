#pragma once
#include <iostream>
#include "Library/n_math.h"
#define NUM_THREAD 8
namespace rayTracing{
    // 光線ベクトルを計算します
    class Ray{
    public:
        Ray(const n_math::Vector3& o, const n_math::Vector3& dir): m_origin(o), m_direction(dir){}

        // 始線ベクトルを返します
        [[nodiscard]] const n_math::Vector3& origin() const{
            return m_origin;
        }

        // 方向ベクトルを返します
        [[nodiscard]] const n_math::Vector3& direction() const{
            return m_direction;
        }

        // m_origin + t * m_direction を返します
        [[nodiscard]] n_math::Vector3 at(float t) const{
            return m_origin + t * m_direction;
        }

        // ランダムなベクトルを生成
        inline static n_math::Vector3 random_vector(){
            return n_math::Vector3{n_math::drand(), n_math::drand(), n_math::drand()};
        }

        // 単位球内に任意の点を生成
        inline static n_math::Vector3 random_in_unit_sphere(){
            n_math::Vector3 p{};
            do {
                p = 2.f * random_vector() - n_math::Vector3{1.f, 1.f, 1.f};
            }while (n_math::lengthSqr(p) >= 1.f);
            return p;
        }

        //リニア -> sRGB
        inline n_math::Vector3 linear_to_gamma(const n_math::Vector3& v, float gammaFactor){
            float recipGammaFactor = 1.f / gammaFactor;
            return n_math::Vector3{
                    powf(v.x, gammaFactor),
                    powf(v.y, gammaFactor),
                    powf(v.z, gammaFactor)
            };
        }

        //sRGB -> リニア
        inline static n_math::Vector3 gamma_to_linear(const n_math::Vector3& v, float gammaFactor){
            return n_math::Vector3{
                    powf(v.x, gammaFactor),
                    powf(v.y, gammaFactor),
                    powf(v.z, gammaFactor)
            };
        }

    private:
        // 始線ベクトル
        n_math::Vector3 m_origin;

        //方向ベクトル(非正規化)
        n_math::Vector3 m_direction;
    };

}