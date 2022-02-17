cmake_minimum_required(VERSION 3.21)
project(CppRayTracing)

set(CMAKE_CXX_STANDARD 20)
# ファイルがUTF-8だからSHIFT-JISとして実行
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /execution-charset:SHIFT_JIS /source-charset:UTF-8")

add_executable(CppRayTracing main.cpp Image.h Ray.h Camera.h Library/n_math.h Scene.h HitRecorder.h Shape.h Sphere.h ShapeList.h Filter.h Material.h Metal.h Dielectric.h DiffuseLight.h Texture.h Rect.h TonemapFilter.h FlipNormal.h)
