#include <vector>
#include <iostream>
#include "Read_and_write/reader.h"
#include "Read_and_write/writer.h"
#include "Read_and_write/parser.h"

int main(int argc, char** argv) {
    ParserResult parser;
    ParserResult parsed_info = parser.Parse(argc, argv);
    write_and_read::Reader img_reader = write_and_read::Reader(parsed_info.input_path_);
    Image img = img_reader.ReadFile();

    img = parsed_info.ApplyFilter(img);

    write_and_read::Writer wr = write_and_read::Writer(parsed_info.output_path_);
    wr.WriteImage(img);
    return 0;
}