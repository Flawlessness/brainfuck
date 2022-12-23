add_executable(SoundProcessor main.cpp)

add_library(Lib Converter.hpp Processor.hpp Processor.cpp SampleStream.hpp SampleStream.cpp MuteConverter.hpp MuteConverter.cpp MixConverter.hpp MixConverter.cpp VolumeConverter.hpp VolumeConverter.cpp parse_args.hpp parse_args.cpp)

target_link_libraries(SoundProcessor PRIVATE Lib)