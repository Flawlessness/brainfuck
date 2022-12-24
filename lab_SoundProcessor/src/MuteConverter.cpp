#include "MuteConverter.hpp"
#include "Converter.hpp"


void MuteConverter::run_converter(int16_t *block, size_t block_size, size_t block_start)
{
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
        block[i] = 0;
        i++;
    }
}

std::shared_ptr<Converter> MuteConverterCreator::create_converter(const std::vector<int> &interval_time, const std::vector<std::string> &files, const std::vector<size_t> &indexes_processed_file) const
{
    if (interval_time.size() > 2 || indexes_processed_file.size() != 0)
    {
        throw std::invalid_argument("Bad number of arguments for mute converter.");
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
        throw std::invalid_argument("Bad arguments for mute converter.");
    }
    return std::make_shared<MuteConverter>(static_cast<size_t>(start_pos) * SAMPLE_RATE, static_cast<size_t>(end_pos) * SAMPLE_RATE);
}

const char *MuteConverterCreator::help() const
{
    return "mute converter: "
           "Mutes stream from previous converter at interval\n"
           "configuration: mute <start>[=0] <end>[=0]\n";
}

const char *MuteConverterCreator::name() const
{
    return "mute";
}
