#include "filters.h"

filters::EdgeDetection::EdgeDetection(double threshold) {
    threshold_ = static_cast<int>(threshold);
}

Image filters::EdgeDetection::Apply(const Image& img) const {
    Image gray_img = filters::Grayscale().Apply(img);
    std::vector<std::vector<int>> matrix = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    std::vector<std::vector<Color>> res;
    for (int i = 0; i < gray_img.GetHeight(); ++i) {
        std::vector<Color> tmp(gray_img.GetWidth());
        for (int j = 0; j < gray_img.GetWidth(); ++j) {
            std::vector<uint8_t> colors_of_pix = ApplyMatrix(matrix, gray_img, j, i);
            if (colors_of_pix.front() > threshold_) {
                tmp[j] = {constants::MAX_COLOR, constants::MAX_COLOR, constants::MAX_COLOR};
            } else {
                tmp[j] = {constants::MIN_COLOR, constants::MIN_COLOR, constants::MIN_COLOR};
            }
        }
        res.push_back(tmp);
    }
    return Image(res);
}