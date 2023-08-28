#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "../Image/image.h"
#include "../filters/filters.h"
#include "../filters/Crystallize.h"

struct FilterConfig {
    std::string name;
    std::vector<std::string> arguments;
};

class ParserResult {
    std::vector<FilterConfig> filters_list_;

public:
    ParserResult Parse(int argc, char* argv[]);
    ParserResult() = default;
    ParserResult(std::string input, std::string output, std::vector<FilterConfig> filters);
    Image ApplyFilter(Image& img) const;
    std::string input_path_;
    std::string output_path_;
};