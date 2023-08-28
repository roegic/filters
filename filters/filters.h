#pragma once

#include "../Image/image.h"
#include "../Read_and_write/constants.h"

namespace filters {
class Filter {
public:
    Filter() = default;
    virtual ~Filter() = default;
    virtual Image Apply(const Image& img) const = 0;
    std::vector<uint8_t> ApplyMatrix(const std::vector<std::vector<int>>& matrix, const Image& img, int x, int y) const;
};

class Crop : public Filter {
public:
    Crop(size_t width, size_t height);
    Image Apply(const Image& img) const override;

private:
    size_t width_;
    size_t height_;
};

class Negative : public filters::Filter {
public:
    Image Apply(const Image& img) const override;
};

class Grayscale : public Filter {
public:
    Image Apply(const Image& img) const override;
};

class EdgeDetection : public Filter {
public:
    explicit EdgeDetection(double threshold);
    Image Apply(const Image& img) const override;

private:
    int threshold_;
};

class Sharpening : public Filter {
public:
    Image Apply(const Image& img) const override;
};
}  // namespace filters

enum class Filters { crop, gs };