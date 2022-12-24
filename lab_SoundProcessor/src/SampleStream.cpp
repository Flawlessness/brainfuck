#include <cstring>
#include "SampleStream.hpp"

namespace
{

    const char *WAVHeader = "RIFF\0\0\0\0WAVE"
                            "fmt\x20\x10\0\0\0"     // fmt chunk header
                            "\x01\0\x01\0"          // PCM mono
                            "\x44\xAC\0\0"          // 44100
                            "\x88\x58\x01\0"        // 88200
                            "\2\0\x10\0"            // align & bits per sample
                            "data\0\0\0\0";         // data chunk header


    uint32_t bytes_to_int32(const char bytes[4])
    {
        return (bytes[0] & 0xff) | ((bytes[1] & 0xff) << 8) | ((bytes[2] & 0xff) << 16) | ((bytes[3] & 0xff) << 24);
    }


    uint16_t bytes_to_int16(const char bytes[2])
    {
        return (bytes[0] & 0xff) | ((bytes[1] & 0xff) << 8);
    }

    void int16_to_bytes(char bytes[2], uint16_t i)
    {
        bytes[0] = i & 0xff;
        bytes[1] = (i >> 8) & 0xff;
    }

}


iSampleStream::iSampleStream(const std::string &file_name) : name(new std::string(file_name))
{
    file.exceptions(std::ios::badbit | std::ios::failbit | std::ios::eofbit);
    try
    {
        file.open(file_name, std::ios::in | std::ios::binary);
    }
    catch (const std::fstream::failure &e)
    {
        throw std::fstream::failure("Cannot open input file");
    }
    try
    {
        initWAVfile();
    }
    catch (const std::fstream::failure &e)
    {
        throw std::invalid_argument("Bad input WAV file");
    }
}

size_t iSampleStream::read(int16_t *second, size_t size)
{
    size *= 2;
    std::streampos curpos = file.tellg();
    if (size + curpos - data_start_pos > data_size_bytes)
    {
        size = data_size_bytes - (curpos - data_start_pos);
    }
    char *cbuf = reinterpret_cast<char *>(second);
    try
    {
        file.read(cbuf, size);
    }
    catch (const std::ifstream::failure &e)
    {
        throw std::invalid_argument("File read error.");
    }
    for (size_t i = 0; i < size / 2; i++)
    {
        int16_t tmp = bytes_to_int16(cbuf + i * 2);
        second[i] = tmp;
    }

    return size / 2;
}

void iSampleStream::initWAVfile()
{
    char buff[4];
    bool flag = false;
    while (!flag)
    {
        file.read(buff, 4);
        if (0 != strncmp(buff, "data", 4))
        {
            file.seekg(-3, file.cur);
        }
        else
        {
            file.read(buff, 4);
            data_start_pos = file.tellg();
            data_size_bytes = bytes_to_int32(buff);
            flag = true;
        }
    }
}

oSampleStream::oSampleStream(const std::string &file_name) : name(new std::string(file_name)), data_size(0)
{
    file.exceptions(std::ios::badbit | std::ios::failbit | std::ios::eofbit);
    try
    {
        file.open(file_name, std::ios::out | std::ios::binary);
    }
    catch (const std::fstream::failure &e)
    {
        throw std::fstream::failure("Cannot open input file.");
    }
    try
    {
        file.write(WAVHeader, 44);
    }
    catch (const std::fstream::failure &e)
    {
        throw std::fstream::failure("Unexpected exception while writing output file.");
    }
}

void oSampleStream::write(const int16_t *buffer, size_t size)
{
    size *= 2;
    data_size += size;
    char *cbuf = new char[size];
    for (size_t i = 0; i < size / 2; i++)
    {
        int16_to_bytes(cbuf + i * 2, buffer[i]);
    }
    file.write(cbuf, size);
}

