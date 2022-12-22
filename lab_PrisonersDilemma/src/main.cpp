#include "game.h"

int main(int argc, char *argv[])
{
    try
    {
        game Game(argc, argv);
        Game.run();
    }
    catch (const std::invalid_argument & ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}