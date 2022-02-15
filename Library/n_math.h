/*
 * Narange Math Library for Ray Tracing
 */

#pragma once
#include <random>

namespace n_math{

    // 3次元ベクトル
    struct Vector3{
        //Vector3(float _x, float _y, float _z): x{_x}, y{_y}, z{_z} {} //コンストラクタ
        float x;
        float y;
        float z;
    };

    // Vector3の加算実装
    Vector3 operator+(const Vector3& left, const Vector3& right){
        const Vector3 value = {
                left.x + right.x,
                left.y + right.y,
                left.z + right.z
        };
        return value;
    }

    //Vector3の減算実装
    Vector3 operator-(const Vector3& left, const Vector3& right){
        const Vector3 value = {
                left.x - right.x,
                left.y - right.y,
                left.z - right.z
        };
        return value;
    }

    //Vector3の乗算実装
    Vector3 operator*(const float& left, const Vector3& right){
        const Vector3 value = {
                left * right.x,
                left * right.y,
                left * right.z
        };
        return value;
    }

    //Vector3の乗算実装
    Vector3 operator*(const Vector3& left, const float& right){
        const Vector3 value = {
                left.x * right,
                left.y * right,
                left.z * right
        };
        return value;
    }

    //Vector3の除算実装
    Vector3 operator/(const Vector3& left, const float& right){
        const Vector3 value = {
                left.x / right,
                left.y / right,
                left.z / right
        };
        return value;
    }

    // 円周率
    static float PI = 3.14159265359f;

    // 内積を返します
    float dot(Vector3 u, Vector3 v){
        float value = u.x * v.x + u.y * v.y + u.z * v.z;
        return value;
    }

    // 外積を返します
    Vector3 cross(Vector3 u, Vector3 v){
        Vector3 value{
            .x = u.y * v.z - v.y * u.z,
            .y = u.z * v.x - v.z * u.x,
            .z = u.x * v.y - v.x * u.y
        };
        return value;
    }

    // ベクトルの大きさを返します
    float length(Vector3 u){
        float value = sqrtf(u.x * u.x + u.y * u.y + u.z * u.z);
        return value;
    }

    // ベクトルの大きさの2乗を返します
    float lengthSqr(Vector3 u){
        float value = u.x * u.x + u.y * u.y + u.z * u.z;
        return value;
    }

    // 正規化ベクトルを返します
    Vector3 normalize(Vector3 u){
        float abs = length(u);
        Vector3 value{
            .x = u.x / abs,
            .y = u.y / abs,
            .z = u.z / abs
        };
        return value;
    }

    //アダマール積を返します
    Vector3 hadamard(Vector3 u, Vector3 v){
        Vector3 value{
            .x = u.x * v.x,
            .y = u.y * v.y,
            .z = u.z * v.z
        };
        return value;
    }

    // ベクトルを線形補間します
    Vector3 lerp(Vector3 u, Vector3 v, float t){
        Vector3 value{
            .x = u.x + t * (v.x - u.x),
            .y = u.y + t * (v.y - u.y),
            .z = u.z + t * (v.z - u.z)
        };
        return value;
    }

    // n乗を返します
    inline float pow(float x, unsigned n){
        float value = 1.f;
        for (int i = 0; i < n; i++){
            value *= x;
        }
        return value;
    }

    // nを[low, high]に収めます
    inline float clamp(float n, float low, float high){
        return n < low ? low: n > high ? high: n;
    }

    // nを[0, 1]に収めます
    inline float saturate(float n){
        return n < 0.f ? 0.f: n > 1.f ? 1.f: n;
    }

    // スカラーを線形補間します
    inline float mix(float x, float y, float t){
        return x + t * (y - x);
    }

    // edgeに対してtの大小で0か1を返します
    inline float step(float edge, float t){
        return t < edge ? 0.f : 1.f;
    }

    // xとyをtでエルミート補間した値を返します
    inline float smoothStep(float x, float y, float t){
        if (x >= y) return 0.f;
        float v = saturate((t - x) / (y - x));
        return v * v * (3.f - (2.f * v));
    }

    // degをラジアンに変換します
    inline float to_Radian(float deg){
        return (deg / 180.f) * PI;
    }

    // radを度数に変換します
    inline float to_Degrees(float rad){
        return (rad / PI) * 180.f;
    }

    // [0, 1]の乱数を返します
    inline float drand(){
        return float((double)rand() / RAND_MAX);
    }

}