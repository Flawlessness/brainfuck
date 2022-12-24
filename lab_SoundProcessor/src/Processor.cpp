#include <fstream>
#include <sstream>
#include "Processor.hpp"
#include "MuteConverter.hpp"
#include "MixConverter.hpp"
#include "VolumeConverter.hpp"

namespace
{

    MuteConverterCreator mute_conv;
    MixConverterCreator mix_conv;
    VolumeConverterCreator vol_conv;

    const std::vector<ConverterCreator *> AVAILABLE_CONVERTERS = {&mute_conv, &mix_conv, &vol_conv};

}


std::shared_ptr<Converter> Configuration::converter_parser(const std::string &converter_name, const std::vector<int> &interval_time, const std::vector<std::string> &input_files, const std::vector<size_t> &indexes_processed_file)
{
    for (auto creator: available_creators)
    {
        if (!converter_name.compare(creator->name()))
        {
            return creator->create_converter(interval_time, input_files, indexes_processed_file);
        }
    }
    throw std::invalid_argument("Bad converter name.");
}

const std::vector<ConverterCreator *> &Configuration::available_creators = AVAILABLE_CONVERTERS;

Configuration::Configuration(const std::string &condig_file, const std::vector<std::string> &input_files)
{
    std::ifstream f_config;
    f_config.exceptions(std::fstream::badbit | std::fstream::failbit);
    try
    {
        f_config.open(condig_file, std::ios::in);
    }
    catch (const std::fstream::failure &e)
    {
        throw std::fstream::failure("Cannot open configuration file.");
    }
    try
    {
        readConfig(f_config, input_files);
    }
    catch (const std::fstream::failure &e)
    {
        throw std::fstream::failure("Unexpected failure during reading configuration file.");
    }
}

void Configuration::readConfig(std::ifstream &f_config, const std::vector<std::string> &input_files)
{
    while (!f_config.eof() && EOF != f_config.peek())
    {
        std::stringstream buffer_stream;
        std::string buffer_string;
        getline(f_config, buffer_string);
        buffer_stream << buffer_string;
        buffer_stream >> buffer_string;
        if ('#' == buffer_string[0])
        {
            continue;
        }
        std::vector<int> interval_time;
        std::vector<size_t> indexes_processed_file;
        std::string buf;
        while (!buffer_stream.eof())
        {
            buffer_stream >> buf;
            if (buf[0] == '$')
            {
                buf.erase(0, 1);
                size_t id;
                try
                {
                    id = stoul(buf);
                }
                catch (const std::exception &)
                {
                    throw std::invalid_argument("Bad stream number after $");
                }
                if (id >= input_files.size() + 1 || 0 == id)
                {
                    throw std::invalid_argument("Bad stream number after $");
                }
                indexes_processed_file.push_back(id - 1);
            }
            else if (!buf.empty())
            {
                try
                {
                    interval_time.push_back(stoi(buf));
                }
                catch (const std::exception &)
                {
                    throw std::invalid_argument("Not integer argument for converter.");
                }
            }
        }
        if (!isspace(buffer_string[0]))
        {
            active_creators.push_back(converter_parser(buffer_string, interval_time, input_files, indexes_processed_file));
        }
    }
}

void Processor::run()
{
    size_t size;
    size_t i = 0;
    int16_t second[SAMPLE_RATE];
    const std::vector<std::shared_ptr<Converter>> &active_creators = config.get_converters();
    size = input_stream.read(second, SAMPLE_RATE);
    while (size != 0)
    {
        for (auto &converter: active_creators)
        {
            converter->run_converter(second, size, i);
        }
        output_stream.write(second, size);
        i += size;
        size = input_stream.read(second, SAMPLE_RATE);
    }
}
