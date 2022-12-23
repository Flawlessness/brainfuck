#pragma once

#include "Processor.hpp"


class MuteConverter : public Converter
{
public:
    MuteConverter(size_t s = 0, size_t e = 0) : start_pos(s), end_pos(e) {};

    virtual void run_converter(int16_t *, size_t, size_t);

private:
    size_t start_pos;
    size_t end_pos;
};

class MuteConverterCreator : public ConverterCreator
{
public:
    virtual std::shared_ptr<Converter> create_converter(const std::vector<int> &interval_time, const std::vector<std::string> &input_files, const std::vector<size_t> &indexes_processed_file) const;

    virtual const char *name() const;

    virtual const char *help() const;
};

