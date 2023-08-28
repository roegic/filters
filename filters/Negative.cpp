#include "filters.h"

Image filters::Negative::Apply(const Image& image) const {
    std::vector<std::vector<Color>> res = image.GetImg();

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            res[i][j].SetColor(constants::MAX_COLOR - res[i][j].blue, constants::MAX_COLOR - res[i][j].green,
                               constants::MAX_COLOR - res[i][j].red);
        }
    }
    return Image(res);
}