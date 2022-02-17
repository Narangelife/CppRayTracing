#pragma once
#include <memory>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Library/stb_image.h"
#include "Library/stb_image_write.h"
#include "Library/n_math.h"
#include "Filter.h"
#include "TonemapFilter.h"

#define GAMMA_FACTOR 2.2

namespace rayTracing{
    class Image{
    public:

        struct rgb{
            unsigned char r;
            unsigned char g;
            unsigned char b;
        };

        //Image() : m_pixcels(nullptr){}
        Image(int width, int height){
            m_width = width;
            m_height = height;
            m_pixcels.reset(new rgb[m_width * m_height]);
            m_filters.push_back(std::make_unique<GammaFilter>(GAMMA_FACTOR));
            m_filters.push_back(std::make_unique<TonemapFilter>());
        }

        int width() const {
            return m_width;
        }

        int height() const {
            return m_height;
        }

        void* pixcels() const {
            return m_pixcels.get();
        }

        void write(int x, int y, float r, float g, float b){
            n_math::Vector3 c{r, g, b};
            for (auto& f : m_filters){
                c = f->filter(c);
            }
            int index = m_width * y + x;
            m_pixcels[index].r = static_cast<unsigned char>(c.x * 255.99f);
            m_pixcels[index].g = static_cast<unsigned char>(c.y * 255.99f);
            m_pixcels[index].b = static_cast<unsigned char>(c.z * 255.99f);
        }

    private:
        int m_width;
        int m_height;
        std::unique_ptr<rgb[]> m_pixcels;
        std::vector<std::unique_ptr<ImageFilter>> m_filters;
    };
}