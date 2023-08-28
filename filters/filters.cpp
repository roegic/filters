#include "filters.h"

std::vector<uint8_t> filters::Filter::ApplyMatrix(const std::vector<std::vector<int>>& matrix, const Image& img, int x,
                                                  int y) const {
    int64_t red = 0;
    int64_t green = 0;
    int64_t blue = 0;
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix.front().size(); ++j) {
            int n_x = std::clamp(x - 1 + j, 0, static_cast<int>(img.GetWidth()) - 1);
            int n_y = std::clamp(y - 1 + i, 0, static_cast<int>(img.GetHeight()) - 1);
            red += img.GetColor(n_x, n_y).red * matrix[i][j];
            green += img.GetColor(n_x, n_y).green * matrix[i][j];
            blue += img.GetColor(n_x, n_y).blue * matrix[i][j];
        }
    }
    red = std::clamp(red, static_cast<int64_t>(constants::MIN_COLOR), static_cast<int64_t>(constants::MAX_COLOR));
    green = std::clamp(green, static_cast<int64_t>(constants::MIN_COLOR), static_cast<int64_t>(constants::MAX_COLOR));
    blue = std::clamp(blue, static_cast<int64_t>(constants::MIN_COLOR), static_cast<int64_t>(constants::MAX_COLOR));
    return {static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue)};
}