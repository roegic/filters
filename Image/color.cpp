#include "color.h"

Color::Color(uint8_t blue, uint8_t green, uint8_t red) : blue(blue), green(green), red(red) {
}

void Color::SetColor(uint8_t b, uint8_t g, uint8_t r) {
    this->blue = b;
    this->green = g;
    this->red = r;
}

bool Color::operator==(const Color& c) const {
    return (red == c.red && green == c.green && blue == c.blue);
}