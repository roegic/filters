#pragma once

#include <stdint.h>
#include <vector>

namespace constants {
const int BMP_HEADER_SIZE = 14;
const int DIB_HEADER_SIZE = 40;
const int WIDTH_OFFSET = 4;
const int HEIGHT_OFFSET = 8;
const int MAX_PADDINGS = 4;
const int CNT_OF_COLORS = 3;
const int BMP_FORMAT_OFFSET_FIRST = 0;
const int BMP_FORMAT_OFFSET_SECOND = 1;
const int BMP_SIZE_OFFSET = 2;
const int BMP_POSITION_OFFSET = 10;
const int DIB_SIZE_OFFSET = 0;
const int CNT_OF_BITS_PER_PIX = 24;
const int BITS_PER_PIX_OFFSET = 14;
const int NOT_EMPTY = 1;
const int NOT_EMPTY_POSITION = 12;
const uint8_t MAX_COLOR = 255;
const uint8_t MIN_COLOR = 0;
const double GRAYSCALE_BLUE = 0.114;
const double GRAYSCALE_RED = 0.299;
const double GRAYSCALE_GREEN = 0.587;
const int FIVE = 5;

const std::vector<char> BMP_FORMAT = {'B', 'M'};
const std::vector<int> BYTES_TO_NUM_OFFSETS = {8, 16, 24};
}  // namespace constants