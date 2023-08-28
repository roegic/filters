#include "Crystallize.h"
filters::Crystallize::Crystallize(int64_t n) : num_(n) {
}

Image filters::Crystallize::Apply(const Image& img) const {
    size_t h = img.GetHeight();
    size_t w = img.GetWidth();

    std::vector<std::vector<Color>> res;
    std::vector<Color> temp(img.GetWidth());
    auto im = img.GetImg();
    for (size_t i = 0; i < h; ++i) {
        res.emplace_back(temp);
    }

    std::default_random_engine gen;
    std::uniform_int_distribution<size_t> distr_x(0, w - 1);
    std::uniform_int_distribution<size_t> distr_y(0, h - 1);

    std::vector<size_t> center_x(num_);
    std::vector<size_t> center_y(num_);

    // генерирую рандомные координаты для кристаллов
    for (size_t i = 0; i < num_; ++i) {
        center_x[i] = distr_x(gen);
        center_y[i] = distr_y(gen);
    }

    std::vector<Color> crystal_color(num_);
    for (size_t i = 0; i < num_; ++i) {
        crystal_color[i] = img.GetImg()[center_y[i]][center_x[i]];
    }

    for (size_t y = 0; y < h; ++y) {
        for (size_t x = 0; x < w; ++x) {
            double closest_crystal = std::numeric_limits<double>::max();
            size_t closest_ind = 0;
            // ищу ближайший к данному пикселю кристалл
            for (size_t i = 0; i < num_; ++i) {
                double distance =
                    static_cast<double>((y - center_y[i]) * (y - center_y[i]) + (x - center_x[i]) * (x - center_x[i]));
                if (distance < closest_crystal) {
                    closest_crystal = distance;
                    closest_ind = i;
                }
            }
            res[y][x] = crystal_color[closest_ind];
        }
    }
    return Image(res);
}