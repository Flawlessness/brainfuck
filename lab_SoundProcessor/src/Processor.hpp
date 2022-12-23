#pragma once

#include <string>
#include <vector>
#include "Converter.hpp"
#include "SampleStream.hpp"

const size_t SAMPLE_RATE = 44100;

class Configuration
{
public:
    Configuration(const std::string &, const std::vector<std::string> &);

    const std::vector<std::shared_ptr<Converter>> &get_converters() const
    {
        return active_creators;
    }

    const static std::vector<ConverterCreator *> &available_creators;
private:
    std::vector<std::shared_ptr<Converter>> active_creators;

    void readConfig(std::ifstream &, const std::vector<std::string> &);

    std::shared_ptr<Converter> converter_parser(const std::string &converter_name, const std::vector<int> &interval_time, const std::vector<std::string> &input_files, const std::vector<size_t> &indexes_processed_file);
};

class Processor
{
public:
    Processor(const Configuration &cfg, const std::string &output_file, const std::string &input_file) : config(cfg), input_stream(input_file), output_stream(output_file) {};

    void run();

private:
    const Configuration &config;
    iSampleStream input_stream;
    oSampleStream output_stream;
};
