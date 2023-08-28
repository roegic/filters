#include "filters.h"

Image filters::Sharpening::Apply(const Image& img) const {
    std::vector<std::vector<int>> matrix = {{0, -1, 0}, {-1, constants::FIVE, -1}, {0, -1, 0}};
    std::vector<std::vector<Color>> res;
    for (int i = 0; i < img.GetHeight(); ++i) {
        std::vector<Color> tmp(img.GetWidth());
        for (int j = 0; j < img.GetWidth(); ++j) {
            std::vector<uint8_t> colors_of_pix = ApplyMatrix(matrix, img, j, i);
            tmp[j] = Color(colors_of_pix[2], colors_of_pix[1], colors_of_pix[0]);
        }
        res.push_back(tmp);
    }
    return Image(res);
}