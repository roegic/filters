#include "parser.h"

ParserResult::ParserResult(std::string input, std::string output, std::vector<FilterConfig> filters) {
    input_path_ = input;
    output_path_ = output;
    filters_list_ = filters;
}

ParserResult ParserResult::Parse(int argc, char* argv[]) {
    ParserResult parser_results;
    if (argc < 2) {
        std::cerr << "{имя программы} {путь к входному файлу} {путь к выходному файлу} [-{имя фильтра 1} [параметр "
                     "фильтра 1] [параметр фильтра 2] ...]"
                  << "\n";
    }
    parser_results.input_path_ = argv[1];
    parser_results.output_path_ = argv[2];
    FilterConfig config;
    for (int index = 3; index < argc; ++index) {
        if (argv[index][0] == '-') {
            if (!config.name.empty()) {
                parser_results.filters_list_.emplace_back(config);
            }
            config.name = std::string(argv[index]).substr(1);
            config.arguments.resize(0);
        } else {
            config.arguments.emplace_back(argv[index]);
        }
    }
    if (!config.name.empty()) {
        parser_results.filters_list_.emplace_back(config);
    }
    return parser_results;
}

Image ParserResult::ApplyFilter(Image& img) const {

    for (const FilterConfig& filter : filters_list_) {
        if (filter.name == "crop") {
            if (filter.arguments.size() != 2) {
                std::cerr << "two arguments needed"
                          << "\n";
                throw std::invalid_argument("invalid number of arguments");
            }
            try {
                filters::Crop c(std::stoi(filter.arguments[0]), std::stoi(filter.arguments[1]));
                img = c.Apply(img);
            } catch (std::exception& e) {
                throw std::invalid_argument("width and height parameteres should be a number");
            }
        } else if (filter.name == "gs") {
            if (!filter.arguments.empty()) {
                std::cerr << "filter gs doesn't take any arguments"
                          << "\n";
                throw std::invalid_argument("too many arguments");
            }
            filters::Grayscale g;
            img = g.Apply(img);
        } else if (filter.name == "neg") {
            if (!filter.arguments.empty()) {
                std::cerr << "filter neg doesn't take any arguments"
                          << "\n";
                throw std::invalid_argument("too many arguments");
            }
            filters::Negative neg;
            img = neg.Apply(img);
        } else if (filter.name == "edge") {
            if (filter.arguments.size() != 1) {
                std::cerr << "one arguments needed in edge filter"
                          << "\n";
                throw std::invalid_argument("invalid number of arguments");
            }
            try {
                filters::EdgeDetection edge(std::stod(filter.arguments.at(0)) * constants::MAX_COLOR);
                img = edge.Apply(img);
            } catch (std::exception& e) {
                std::cerr << "threshold should be a number"
                          << "\n";
                throw std::invalid_argument("threshold should be a number");
            }
        } else if (filter.name == "sharp") {
            if (!filter.arguments.empty()) {
                std::cerr << "filter sharp doesn't take any arguments"
                          << "\n";
                throw std::invalid_argument("too many arguments");
            }
            filters::Sharpening sharp;
            img = sharp.Apply(img);
        } else if (filter.name == "crystal") {
            if (filter.arguments.size() != 1) {
                std::cerr << "one arguments needed in crystal filter"
                          << "\n";
                throw std::invalid_argument("invalid number of arguments");
            }
            filters::Crystallize crystal(std::stoi(filter.arguments.at(0)));
            img = crystal.Apply(img);
        } else if (!filter.name.empty()) {
            std::cerr << "this filter doesn't exist"
                      << "\n";
            throw std::invalid_argument("no matching filter");
        }
    }
    return img;
}