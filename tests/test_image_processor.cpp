#include <catch.hpp>
#include "../Image/image.h"
#include <string>
#include "../Read_and_write/reader.h"
#include "../Read_and_write/parser.h"

const int64_t NUM = 700;

TEST_CASE("CrystalFilter") {
    write_and_read::Reader img_reader2 = write_and_read::Reader("tasks/image_processor/tests/lenna_out.bmp");
    write_and_read::Reader img_reader = write_and_read::Reader("tasks/image_processor/tests/lenna.bmp");
    Image img = img_reader.ReadFile();
    Image res = img_reader2.ReadFile();
    filters::Crystallize crystal(NUM);
    img = crystal.Apply(img);
    REQUIRE(img.GetImg() == res.GetImg());
}

TEST_CASE("CropFilter not enough arguments") {
    write_and_read::Reader img_reader = write_and_read::Reader("tasks/image_processor/tests/lenna.bmp");
    Image img = img_reader.ReadFile();
    FilterConfig filter;
    filter.name = "crop";
    filter.arguments.emplace_back("567");
    std::vector<FilterConfig> filters_l;
    filters_l.emplace_back(filter);
    ParserResult parsed_info("input.bmp", "output.bmp", filters_l);
    REQUIRE_THROWS_AS(parsed_info.ApplyFilter(img), std::invalid_argument);
}

TEST_CASE("EdgeFilter wrong Arguments") {
    write_and_read::Reader img_reader = write_and_read::Reader("tasks/image_processor/tests/lenna.bmp");
    Image img = img_reader.ReadFile();
    FilterConfig filter;
    filter.name = "edge";
    filter.arguments.emplace_back("hello");
    std::vector<FilterConfig> filters_l;
    filters_l.emplace_back(filter);
    ParserResult parsed_info("input.bmp", "output.bmp", filters_l);
    REQUIRE_THROWS_AS(parsed_info.ApplyFilter(img), std::invalid_argument);
}

TEST_CASE("EdgeFilter not enough Arguments") {
    write_and_read::Reader img_reader = write_and_read::Reader("tasks/image_processor/tests/lenna.bmp");
    Image img = img_reader.ReadFile();
    FilterConfig filter;
    filter.name = "edge";
    filter.arguments = {};
    std::vector<FilterConfig> filters_l;
    filters_l.emplace_back(filter);
    ParserResult parsed_info("input.bmp", "output.bmp", filters_l);
    REQUIRE_THROWS_AS(parsed_info.ApplyFilter(img), std::invalid_argument);
}

TEST_CASE("Sharpening too many arguments") {
    write_and_read::Reader img_reader = write_and_read::Reader("tasks/image_processor/tests/lenna.bmp");
    Image img = img_reader.ReadFile();
    FilterConfig filter;
    filter.name = "sharp";
    filter.arguments.emplace_back("993");
    std::vector<FilterConfig> filters_l;
    filters_l.emplace_back(filter);
    ParserResult parsed_info("input.bmp", "output.bmp", filters_l);
    REQUIRE_THROWS_AS(parsed_info.ApplyFilter(img), std::invalid_argument);
}

TEST_CASE("Negative too many arguments") {
    write_and_read::Reader img_reader = write_and_read::Reader("tasks/image_processor/tests/lenna.bmp");
    Image img = img_reader.ReadFile();
    FilterConfig filter;
    filter.name = "neg";
    filter.arguments.emplace_back("1000");
    filter.arguments.emplace_back("7");
    std::vector<FilterConfig> filters_l;
    filters_l.emplace_back(filter);
    ParserResult parsed_info("input.bmp", "output.bmp", filters_l);
    REQUIRE_THROWS_AS(parsed_info.ApplyFilter(img), std::invalid_argument);
}

TEST_CASE("Grayscale too many arguments") {
    write_and_read::Reader img_reader = write_and_read::Reader("tasks/image_processor/tests/lenna.bmp");
    Image img = img_reader.ReadFile();
    FilterConfig filter;
    filter.name = "neg";
    filter.arguments.emplace_back("1000");
    filter.arguments.emplace_back("7");
    filter.arguments.emplace_back("hullo");
    std::vector<FilterConfig> filters_l;
    filters_l.emplace_back(filter);
    ParserResult parsed_info("input.bmp", "output.bmp", filters_l);
    REQUIRE_THROWS_AS(parsed_info.ApplyFilter(img), std::invalid_argument);
}

TEST_CASE("Filter doesn't exist") {
    write_and_read::Reader img_reader = write_and_read::Reader("tasks/image_processor/tests/lenna.bmp");
    Image img = img_reader.ReadFile();
    FilterConfig filter;
    filter.name = "Boris";
    filter.arguments = {};
    std::vector<FilterConfig> filters_l;
    filters_l.emplace_back(filter);
    ParserResult parsed_info("input.bmp", "output.bmp", filters_l);
    REQUIRE_THROWS_AS(parsed_info.ApplyFilter(img), std::invalid_argument);
}

TEST_CASE("Wrong path") {
    write_and_read::Reader img_reader = write_and_read::Reader("Hell/lenna.bmp");
    REQUIRE_THROWS_AS(img_reader.ReadFile(), std::ifstream::failure);
}

TEST_CASE("Wrong file format") {
    write_and_read::Reader img_reader = write_and_read::Reader("Hell/ydx.txt");
    REQUIRE_THROWS_AS(img_reader.ReadFile(), std::ifstream::failure);
}