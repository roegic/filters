#include "filters.h"

Image filters::Grayscale::Apply(const Image& image) const {

    std::vector<std::vector<Color>> res = image.GetImg();

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            uint8_t col = static_cast<uint8_t>(constants::GRAYSCALE_BLUE * res[i][j].blue +
                                               constants::GRAYSCALE_GREEN * res[i][j].green +
                                               constants::GRAYSCALE_RED * res[i][j].red);
            res[i][j].SetColor(col, col, col);
        }
    }
    return Image(res);
}