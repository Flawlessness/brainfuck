#pragma once

#include <memory>
#include "SampleStream.hpp"

class Converter
{
public:
    virtual void run_converter(int16_t *, size_t, size_t) = 0;

    virtual ~Converter() = default;
};

class ConverterCreator
{
public:
    virtual std::shared_ptr<Converter> create_converter(const std::vector<int> &interval_time, const std::vector<std::string> &input_files, const std::vector<size_t> &indexes_processed_file) const = 0;

    virtual const char *name() const = 0;

    virtual const char *help() const = 0;
};

