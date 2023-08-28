#pragma once

#include <cstdint>

struct Color {
    uint8_t blue = 0;
    uint8_t green = 0;
    uint8_t red = 0;

    Color() = default;
    Color(uint8_t blue, uint8_t green, uint8_t red);
    void SetColor(uint8_t blue, uint8_t green, uint8_t red);
    bool operator==(const Color& c) const;
};