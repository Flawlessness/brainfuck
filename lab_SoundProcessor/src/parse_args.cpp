#include "parse_args.hpp"
#include <iostream>
#include <cstring>

void parse_args(std::string &output_file, std::string &config_file, std::vector<std::string> &input_files, int argc, char *argv[])
{
    unsigned int argi = 1;
    enum
    {
        FIRST, CONF, OUT, IN
    } state = FIRST;
    while (argi < argc)
    {
        if (state == FIRST)
        {
            if (0 == strcmp("-c", argv[argi]))
            {
                config_file = argv[++argi];
                state = OUT;
            }
            else
            {
                output_file = argv[argi];
                state = CONF;
            }
        }
        else if (state == CONF)
        {
            if (0 == strcmp("-c", argv[argi]))
            {
                config_file = argv[++argi];
                state = IN;
            }
            else
            {
                input_files.push_back(argv[argi]);
                state = CONF;
            }
        }
        else if (state == OUT)
        {
            output_file = argv[argi];
            state = IN;
        }
        else if (state == IN)
        {
            input_files.push_back(argv[argi]);
            state = IN;
        }
        argi++;
    }
}


int start(int argc, char *argv[])
{
    if (argc > 1 && 0 == strcmp(argv[1], "-h"))
    {
        std::cout << "sound_processor [-h] "
                     "[-c <config file>] "
                     "<output> <input1> [<input2> …]\n" << std::endl;
        std::cout << "Valid input files are WAV files; mono PCM s16le 44100Hz format." << std::endl;
        std::cout << "Configuration file includes comment-lines after #,"
                     " and converters with arguments." << std::endl;
        std::cout << "Valid Converters:\n" << std::endl;
        for (auto creator: Configuration::available_creators)
        {
            std::cout << creator->help() << std::endl;
        }
        return 0;
    }
    std::string output_file;
    std::string config_file;
    std::vector<std::string> input_files;
    parse_args(output_file, config_file, input_files, argc, argv);
    if (output_file.compare("") == 0)
    {
        std::cerr << "No output file!" << std::endl;
        return 1;
    }
    if (config_file.compare("") == 0)
    {
        std::cerr << "Configuration file is required!" << std::endl;
        return 1;
    }
    if (0 == input_files.size())
    {
        std::cerr << "No input files!" << std::endl;
        return 1;
    }

    try
    {
        Configuration configuration{config_file, input_files};
        Processor conversion{configuration, output_file, input_files[0]};
        conversion.run();
    }
    catch (const std::invalid_argument &ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    catch (const std::fstream::failure &ex)
    {
        std::cerr << ex.what() << std::endl;
        return 2;
    }
    catch (const std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
        return 3;
    }

    return 0;
}
