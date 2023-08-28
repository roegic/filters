#include "reader.h"

write_and_read::Reader::Reader(const std::string& file) {
    file_ = file;
}

size_t write_and_read::Reader::BytesToNum(unsigned char* chrs) {
    size_t res = *chrs;
    for (size_t i = 0; i < constants::BYTES_TO_NUM_OFFSETS.size(); ++i) {
        res += *(chrs + i + 1) << constants::BYTES_TO_NUM_OFFSETS[i];
    }
    return res;
}

const size_t write_and_read::GetPaddings(size_t width) {
    return (constants::MAX_PADDINGS - (width * constants::CNT_OF_COLORS % constants::MAX_PADDINGS)) %
           constants::MAX_PADDINGS;
}

Image write_and_read::Reader::ReadFile() {
    unsigned char bmp_header[constants::BMP_HEADER_SIZE];
    unsigned char dib_header[constants::DIB_HEADER_SIZE];

    std::ifstream image;
    image.open(file_, std::fstream::in | std::fstream::binary);
    if (!image.is_open()) {
        throw std::ifstream::failure("failed to open file" + file_);
    }
    if (errno == EACCES) {
        throw std::invalid_argument("Permission denied");
    }

    image.read(reinterpret_cast<char*>(bmp_header), constants::BMP_HEADER_SIZE);

    if (bmp_header[0] != constants::BMP_FORMAT[0] || bmp_header[1] != constants::BMP_FORMAT[1]) {
        throw std::invalid_argument(file_ + " is not bmp\n");
    }

    try {
        image.read(reinterpret_cast<char*>(dib_header), constants::DIB_HEADER_SIZE);

        uint32_t width = BytesToNum(dib_header + constants::WIDTH_OFFSET);
        uint32_t height = BytesToNum(dib_header + constants::HEIGHT_OFFSET);
        Image image_data(height, width);

        std::vector<std::vector<Color>> img(height);
        std::vector<Color> tmp(width);
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {
                unsigned char pix[constants::CNT_OF_COLORS];
                image.read(reinterpret_cast<char*>(pix), constants::CNT_OF_COLORS);
                tmp[j].SetColor(static_cast<uint8_t>(pix[0]), static_cast<uint8_t>(pix[1]),
                                static_cast<uint8_t>(pix[2]));
            }
            img[i] = tmp;
            image.ignore(static_cast<std::streamsize>(GetPaddings(width)));
        }
        image_data = Image(img);
        image.close();
        return image_data;

    } catch (std::exception& e) {
        throw "Error in reading: " + static_cast<std::string>(e.what());
    }
}