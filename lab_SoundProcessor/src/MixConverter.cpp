#include "MixConverter.hpp"
#include "Converter.hpp"


void MixConverter::run_converter(int16_t *block, size_t block_size, size_t block_start)
{
    int16_t *mix_block = new int16_t[block_size];
    size_t mix_size = mixing_stream.read(mix_block, block_size);
    if ((block_start >= end_pos && 0 != end_pos) || block_start + block_size < start_pos)
    {
        return;
    }
    size_t i;
    if (start_pos < block_start)
    {
        i = 0;
    }
    else
    {
        i = start_pos - block_start;
    }
    while (i < block_size && (i < end_pos - block_start || end_pos == 0))
    {
        int16_t avg = block[i];
        if (i < mix_size)
        {
            avg /= 2;
            avg += mix_block[i] / 2;
        }
        block[i] = avg;
        i++;
    }

    delete[] mix_block;
}

std::shared_ptr<Converter> MixConverterCreator::create_converter(const std::vector<int> &interval_time, const std::vector<std::string> &files, const std::vector<size_t> &indexes_processed_file) const
{
    if (interval_time.size() > 2 || indexes_processed_file.size() != 1)
    {
        throw std::invalid_argument("Bad number of arguments for mix converter.");
    }
    int start_pos = 0;
    int end_pos = 0;
    if (interval_time.size() >= 1)
    {
        start_pos = interval_time[0];
    }
    if (interval_time.size() == 2)
    {
        end_pos = interval_time[1];
    }

    if (start_pos < 0 || end_pos < 0)
    {
        throw std::invalid_argument("Bad arguments for mix converter.");
    }
    iSampleStream input_stream{files[indexes_processed_file[0]]};
    return std::make_shared<MixConverter>(input_stream, static_cast<size_t>(start_pos) * SAMPLE_RATE, static_cast<size_t>(end_pos) * SAMPLE_RATE);
}

const char *MixConverterCreator::name() const
{
    return "mix";
}

const char *MixConverterCreator::help() const
{
    return "mix converter: "
           "Mixes stream from previous converter and mixes with input stream\n"
           "configuration: mix $<stream number> <start>[=0] <end>[=0]\n";
}
