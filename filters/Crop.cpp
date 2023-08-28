#include "filters.h"

filters::Crop::Crop(size_t width, size_t height) : width_(width), height_(height) {
}

Image filters::Crop::Apply(const Image& image) const {
    std::vector<std::vector<Color>> res = image.GetImg();
    std::reverse(res.begin(), res.end());
    if (height_ < image.GetHeight()) {
        for (size_t i = 0; i < image.GetHeight() - height_; ++i) {
            res.pop_back();
        }
    }
    std::reverse(res.begin(), res.end());

    if (width_ < image.GetWidth()) {
        for (size_t i = 0; i < res.size(); ++i) {
            for (size_t j = 0; j < image.GetWidth() - width_; ++j) {
                res[i].pop_back();
            }
        }
    }
    return Image(res);
}