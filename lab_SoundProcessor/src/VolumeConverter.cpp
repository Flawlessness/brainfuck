#include "VolumeConverter.hpp"
#include "Converter.hpp"


void VolumeConverter::run_converter(int16_t *block, size_t block_size, size_t block_start)
{
    if ((block_start >= end_pos && 0 != end_pos) || block_start + block_size < start_pos)
    {
        return;
    }
    double vol = volume;
    vol /= 100;
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
        double new_value = block[i];
        new_value *= vol;
        if (block[i] < 0)
        {
            if (new_value >= INT16_MIN)
            {
                block[i] = static_cast<int16_t>(new_value);
            }
            else
            {
                block[i] = INT16_MIN;
            }
        }
        else
        {
            if (new_value <= INT16_MAX)
            {
                block[i] = static_cast<int16_t>(new_value);
            }
            else
            {
                block[i] = INT16_MAX;
            }
        }
        i++;
    }
}

std::shared_ptr<Converter> VolumeConverterCreator::create_converter(const std::vector<int> &interval_time, const std::vector<std::string> &files, const std::vector<size_t> &indexes_processed_file) const
{
    if (interval_time.size() < 1 || interval_time.size() > 3 || indexes_processed_file.size() != 0)
    {
        throw std::invalid_argument("Bad number of arguments for volume converter.");
    }
    int vol = interval_time[0];
    int start_pos = 0;
    int end_pos = 0;
    if (interval_time.size() >= 2)
    {
        start_pos = interval_time[1];
    }
    if (interval_time.size() == 3)
    {
        end_pos = interval_time[2];
    }
    if (start_pos < 0 || end_pos < 0)
    {
        throw std::invalid_argument("Bad arguments for volume converter.");
    }
    return std::make_shared<VolumeConverter>(static_cast<size_t>(vol), static_cast<size_t>(start_pos) * SAMPLE_RATE, static_cast<size_t>(end_pos) * SAMPLE_RATE);
}

const char *VolumeConverterCreator::help() const
{
    return "volume converter: "
           "Multiplying samples in interval by a <volume>/100. <volume> also can be more then 100.\n"
           "configuration: vol <volume> <start>[=0] <end>[=0]\n";
}

const char *VolumeConverterCreator::name() const
{
    return "vol";
}
