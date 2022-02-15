#pragma once
#include "Ray.h"
#include "Library/n_math.h"

namespace rayTracing{
    // カメラから光線を飛ばします
    class Camera{
    public:
        Camera(){}
        Camera(const n_math::Vector3& u, const n_math::Vector3& v, const n_math::Vector3& w){
            m_origin = n_math::Vector3{0, 0, 0};
            m_uvw[0] = u;
            m_uvw[1] = v;
            m_uvw[2] = w;
        }
        Camera(const n_math::Vector3& lookFrom, const n_math::Vector3& lookAt, const n_math::Vector3& vUp, float vFov, float aspect){
            n_math::Vector3 u{}, v{}, w{};
            float halfH = tanf(n_math::to_Radian(vFov) / 2.f); //スクリーン中央からの高さ (カメラからスクリーンまでの距離: 1)
            float halfW = aspect * halfH; //スクリーン中央からの幅 (aspect = sx / sh)
            m_origin = lookFrom; // カメラの位置
            w = n_math::normalize(lookFrom - lookAt);
            u = n_math::normalize(n_math::cross(vUp, w)); // u = vup × Z
            v = n_math::cross(w, u); // v = w × u
            // スクリーン上の位置p = vec_u u + vec_v v + vec_w
            m_uvw[0] = 2.f * halfW * u;
            m_uvw[1] = 2.f * halfH * v;
            m_uvw[2] = m_origin - halfW * u - halfH * v - w;
        }

        Ray getRay(float u, float v) const{
            return Ray(m_origin, m_uvw[2] + m_uvw[0] * u + m_uvw[1] * v - m_origin);
        }

    private:
        // 位置ベクトル
        n_math::Vector3 m_origin;

        // 直交基底ベクトル (カメラ相対の直交座標)
        n_math::Vector3 m_uvw[3];
    };
}