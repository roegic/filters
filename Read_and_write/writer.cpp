#include "writer.h"

write_and_read::Writer::Writer(std::string file) : file_(file) {
}

void write_and_read::Writer::NumToBytes(size_t numb, unsigned char* chrs) {
    *chrs = numb;
    for (size_t i = 0; i < constants::BYTES_TO_NUM_OFFSETS.size(); ++i) {
        *(chrs + i + 1) = numb >> constants::BYTES_TO_NUM_OFFSETS[i];
    }
}

void write_and_read::Writer::BMPWrite(unsigned char* bmp_header, size_t size_of_img) {
    bmp_header[constants::BMP_FORMAT_OFFSET_FIRST] = constants::BMP_FORMAT[constants::BMP_FORMAT_OFFSET_FIRST];
    bmp_header[constants::BMP_FORMAT_OFFSET_SECOND] = constants::BMP_FORMAT[constants::BMP_FORMAT_OFFSET_SECOND];
    NumToBytes(size_of_img, bmp_header + constants::BMP_SIZE_OFFSET);
    bmp_header[constants::BMP_POSITION_OFFSET] = constants::BMP_HEADER_SIZE + constants::DIB_HEADER_SIZE;
}

void write_and_read::Writer::DIBWrite(unsigned char* dib_header, size_t width, size_t height) {
    dib_header[constants::DIB_SIZE_OFFSET] = constants::DIB_HEADER_SIZE;
    NumToBytes(width, dib_header + constants::WIDTH_OFFSET);
    NumToBytes(height, dib_header + constants::HEIGHT_OFFSET);
    dib_header[constants::BITS_PER_PIX_OFFSET] = constants::CNT_OF_BITS_PER_PIX;
    dib_header[constants::NOT_EMPTY_POSITION] = constants::NOT_EMPTY;
}

void write_and_read::Writer::WriteImage(const Image& img) {
    std::ofstream out_file;
    out_file.open(file_, std::ios::out | std::ios::binary);
    if (!out_file.is_open()) {
        throw std::ifstream::failure("file is not opened" + file_);
    }

    const size_t size_of_file = constants::BMP_HEADER_SIZE + constants::DIB_HEADER_SIZE +
                                img.GetHeight() * img.GetWidth() * constants::CNT_OF_COLORS +
                                GetPaddings(img.GetWidth()) * img.GetHeight();

    unsigned char bmp_header[constants::BMP_HEADER_SIZE] = {};
    std::fill(bmp_header, bmp_header + constants::BMP_HEADER_SIZE, 0);
    BMPWrite(bmp_header, size_of_file);

    unsigned char dib_header[constants::DIB_HEADER_SIZE] = {};
    std::fill(dib_header, dib_header + constants::DIB_HEADER_SIZE, 0);
    DIBWrite(dib_header, img.GetWidth(), img.GetHeight());

    out_file.write(reinterpret_cast<char*>(bmp_header), constants::BMP_HEADER_SIZE);
    out_file.write(reinterpret_cast<char*>(dib_header), constants::DIB_HEADER_SIZE);

    unsigned char bmp_padd[constants::MAX_PADDINGS] = {0, 0, 0};
    for (size_t i = 0; i < img.GetHeight(); ++i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            unsigned char blue = static_cast<unsigned char>(img.GetColor(j, i).blue);
            unsigned char green = static_cast<unsigned char>(img.GetColor(j, i).green);
            unsigned char red = static_cast<unsigned char>(img.GetColor(j, i).red);
            unsigned char pix[] = {blue, green, red};
            out_file.write(reinterpret_cast<char*>(pix), constants::CNT_OF_COLORS);
        }
        out_file.write(reinterpret_cast<char*>(bmp_padd), static_cast<std::streamsize>(GetPaddings(img.GetWidth())));
    }
    out_file.close();
}