#pragma once
#include "Ray.h"
#include "Camera.h"
#include "Image.h"
#include "ShapeList.h"
#include "Sphere.h"
#include "Material.h"
#include "Metal.h"
#include "Dielectric.h"
#include "DiffuseLight.h"
#include "Rect.h"
#include "FlipNormal.h"
#include <random>
#include <omp.h>
#include <iostream>

#define MAX_DEPTH 50

namespace rayTracing{
    class Scene{
    public:
        Scene(int width, int height, int samples): m_image(std::make_unique<Image>(width, height)), m_backColor{0.1f, 0.1f, 0.1f}, m_samples(samples){
        }

        void build(){
            float nb = (float(m_image->width()) / float(m_image->height()));
            n_math::Vector3 w{-nb * nb / 2.f, -nb / 2, -1.f};
            n_math::Vector3 u{nb * nb, 0.f, 0.f};
            n_math::Vector3 v{0.f, nb, 0.f};
            n_math::Vector3 lookFrom{278, 278, -800};
            n_math::Vector3 lookAt{278, 278, 0};
            n_math::Vector3 vUp{0, 1, 0};
            float aspect = float(m_image->width()) / float(m_image->height());
            //m_camera = std::make_unique<Camera>(u, v, w);
            m_camera = std::make_unique<Camera>(lookFrom, lookAt, vUp, 40, aspect);

            std::shared_ptr<Material> red = std::make_shared<Lambertian>(std::make_shared<Colortexture>(n_math::Vector3{0.65f, 0.05f, 0.05f}));
            std::shared_ptr<Material> white = std::make_shared<Lambertian>(std::make_shared<Colortexture>(n_math::Vector3{0.73f, 0.73f, 0.73f}));
            std::shared_ptr<Material> green = std::make_shared<Lambertian>(std::make_shared<Colortexture>(n_math::Vector3{0.12f, 0.45f, 0.15f}));
            std::shared_ptr<Material> light = std::make_shared<DiffuseLight>(std::make_shared<Colortexture>(n_math::Vector3{15.f, 15.f, 15.f}));

            ShapeList* world = new ShapeList();

            world->add(std::make_shared<FlipNormal>(std::make_shared<Rect>(0, 555, 0, 555, 555, Rect::kYZ, green)));
            world->add(std::make_shared<Rect>(0, 555, 0, 555, 0, Rect::kYZ, red));
            world->add(std::make_shared<Rect>(213, 343, 227, 332, 554, Rect::kXZ, light));
            world->add(std::make_shared<FlipNormal>(std::make_shared<Rect>(0, 555, 0, 555, 555, Rect::kXZ, white)));
            world->add(std::make_shared<Rect>(0, 555, 0, 555, 0, Rect::kXZ, white));
            world->add(std::make_shared<FlipNormal>(std::make_shared<Rect>(0, 555, 0, 555, 555, Rect::kXY, white)));

            m_world.reset(world);
        }

        n_math::Vector3 color(const Ray& r, const Shape* world, int depth) const{
            HitRecorder hitRecorder;
            if (world->hit(r, 0.001f, FLT_MAX, hitRecorder)){
                n_math::Vector3 emitted = hitRecorder.mat->emitted(r, hitRecorder);
                ScatterRecorder scatterRecorder;
                if (depth < MAX_DEPTH && hitRecorder.mat->scatter(r, hitRecorder, scatterRecorder)){
                    return emitted + n_math::hadamard(scatterRecorder.albedo, color(scatterRecorder.ray, world, depth++));
                }else{
                    return emitted;
                }
//                n_math::Vector3 target = hitRecorder.p + hitRecorder.n + Ray::random_in_unit_sphere();
//                return 0.8f * color(Ray(hitRecorder.p, target - hitRecorder.p), world);
            }
            return background(r.direction());
            //return backgroundSky(r.direction());
        }

        n_math::Vector3 background(const n_math::Vector3& d) const {
            return m_backColor;
        }

        n_math::Vector3 backgroundSky(const n_math::Vector3& d) const {
            n_math::Vector3 v = n_math::normalize(d);
            float t = 0.5f * (v.y + 1.f);
            return n_math::lerp(n_math::Vector3{1, 1, 1}, n_math::Vector3{0.5f, 0.7f, 1.f}, t);
        }

        void render(){
            build();
            int nx = m_image->width();
            int ny = m_image->height();
            // 計測開始
            clock_t start = clock();
            std::cerr << "Rendering..." << std::endl;
//#pragma omp parallel for schedule(dynamic, 1) num_threads(NUM_THREAD)
            // 処理開始
            int l = 0;
            for (int i = 0; i < ny; i++){
                if (100.0 * i / (ny - 1) >= l){
                    std::string mae = "";
                    std::string ushiro = "";
                    for (int m = 0; m < l; m++){
                       mae += "|";
                    }
                    for (int m = 0; m < 100 - l; m++){
                        ushiro += " ";
                    }
                    std::cerr << "[ " << 100.0 * i / (ny - 1) << "% ] [" << mae << ushiro << "]" << std::endl;
                    l++;
                }
                for (int j = 0; j < nx; j++){
                    n_math::Vector3 c{0 ,0 ,0};
                    for (int k = 0; k < m_samples; k++){
                        float u = (float(j) + n_math::drand()) / float(nx);
                        float v = (float(i) + n_math::drand()) / float(ny);
                        Ray r = m_camera->getRay(u, v);
                        c = c + color(r, m_world.get(), 0);
                    }
                    c = c / (float)m_samples;
                    m_image->write(j, (ny - i - 1), c.x, c.y, c.z);
                }
            }
            std::cerr << std::endl;

            // 処理・計測終了
            clock_t end = clock();
            double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
            std::cerr << "Complete! (Time: " << time << " ms)" << std::endl;

            stbi_write_bmp("render.bmp", nx, ny, sizeof(rayTracing::Image::rgb), m_image->pixcels());
        }

    private:
        std::unique_ptr<Camera> m_camera;
        std::unique_ptr<Image> m_image;
        std::unique_ptr<Shape> m_world;
        n_math::Vector3 m_backColor;
        int m_samples;
    };
}