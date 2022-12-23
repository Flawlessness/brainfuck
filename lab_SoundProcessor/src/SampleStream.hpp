#pragma once

#include <fstream>
#include <string>

class iSampleStream
{
public:
    explicit iSampleStream(const std::string &);

    iSampleStream(const iSampleStream &o) : iSampleStream(*o.name) {};

    ~iSampleStream()
    {
        file.close();
        delete name;
    }

    size_t read(int16_t *buffer, size_t size);

private:
    std::ifstream file;
    std::streampos data_start_pos;
    std::size_t data_size_bytes;
    const std::string *name;

    void initWAVfile();
};

class oSampleStream
{
public:
    explicit oSampleStream(const std::string &);

    ~oSampleStream()
    {
        file.close();
        delete name;
    }

    void write(const int16_t *buffer, size_t size);


private:
    std::ofstream file;
    std::size_t data_size;
    const std::string *name;


};

