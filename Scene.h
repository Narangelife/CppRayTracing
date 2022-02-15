#pragma once
#include "Ray.h"
#include "Camera.h"
#include "Image.h"
#include "ShapeList.h"
#include "Sphere.h"
#include <random>

namespace rayTracing{
    class Scene{
    public:
        Scene(int width, int height, int samples): m_image(std::make_unique<Image>(width, height)), m_backColor{0.2f, 0.2f, 0.2f}, m_samples(samples){
        }

        void build(){
            float nb = (float(m_image->width()) / float(m_image->height()));
            n_math::Vector3 w{-nb * nb / 2.f, -nb / 2, -1.f};
            n_math::Vector3 u{nb * nb, 0.f, 0.f};
            n_math::Vector3 v{0.f, nb, 0.f};
            m_camera = std::make_unique<Camera>(u, v, w);

            ShapeList* world = new ShapeList();
            world->add(std::make_shared<Sphere>(n_math::Vector3{0, 0, -1}, 0.5f));
            world->add(std::make_shared<Sphere>(n_math::Vector3{1, -100.5f, -1}, 100.f));
            m_world.reset(world);
        }

        n_math::Vector3 color(const Ray& r, const Shape* world) const{
            HitRecorder hitRecorder;
            if (world->hit(r, 0.001f, FLT_MAX, hitRecorder)){
                n_math::Vector3 target = hitRecorder.p + hitRecorder.n + Ray::random_in_unit_sphere();
                return 0.8f * color(Ray(hitRecorder.p, target - hitRecorder.p), world);
            }
            return backgroundSky(r.direction());
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
//#pragma omp parallel for schedule(dynamic, 1) num_threads(NUM_THREAD)
            // 計測開始
            clock_t start = clock();
            std::cerr << "Rendering..." << std::endl;

            // 処理開始
            for (int i = 0; i < ny; i++){
                for (int j = 0; j < nx; j++){
                    n_math::Vector3 c{0 ,0 ,0};
                    for (int k = 0; k < m_samples; k++){
                        float u = (float(j) + n_math::drand()) / float(nx);
                        float v = (float(i) + n_math::drand()) / float(ny);
                        Ray r = m_camera->getRay(u, v);
                        c = c + color(r, m_world.get());
                    }
                    c = c / (float)m_samples;
                    m_image->write(j, (ny - i - 1), c.x, c.y, c.z);
                }
            }

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