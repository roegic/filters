#include "image.h"

Image::Image(const Image& img) : img_(img.img_), height_(img.height_), width_(img.width_) {
}

Image::Image(size_t height, size_t width) : height_(height), width_(width) {
    std::vector<std::vector<Color>> img(height);
    std::vector<Color> tmp(width);
    for (int i = 0; i < height; ++i) {
        img_.emplace_back(tmp);
    }
}

Image::Image(const std::vector<std::vector<Color>>& data) : img_(data), height_(data.size()) {
    if (!data.empty()) {
        width_ = data[0].size();
    } else {
        width_ = 0;
        throw std::invalid_argument("image shouldn't be empty");
    }
}

size_t Image::GetHeight() const {
    return this->height_;
}

size_t Image::GetWidth() const {
    return this->width_;
}

const std::vector<std::vector<Color>>& Image::GetImg() const {
    return this->img_;
}

const Color& Image::GetColor(size_t x, size_t y) const {
    if (x < this->width_ && y < this->height_) {
        return this->img_[y][x];
    }
    throw std::invalid_argument("coordinates are out of range");
}

void Image::SetColor(size_t x, size_t y, Color color) {
    if (x < this->width_ && y < this->height_) {
        this->img_[y][x] = color;
    }
}
