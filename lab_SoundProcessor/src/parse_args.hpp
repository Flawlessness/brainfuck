#pragma once

#include "Processor.hpp"

void parse_args(std::string &output_file, std::string &config_file, std::vector<std::string> &input_files, int argc, char *argv[]);

int start(int argc, char *argv[]);
