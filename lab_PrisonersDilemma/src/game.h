#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "Factory.h"


class game {
private:
    Factory factory;
    int steps_count;
    int gamemode;
    std :: vector<std :: string> input_strategies;
    std :: vector<std :: string> available_strategies{"cooperate", "deflect", "random", "tit_for_tat", "tit_for_tat_forgiveness", "simpleton", "majority", "scoundrel"};
    void help();
    void detailed_game();
    std :: vector<int> fast_game(const std::vector<std::string> &input_strategies);
    void tournament_game();
    std :: vector<std :: vector<int>> game_matrix = {{1,1,1},{5,5,0},{5,0,5},{9,3,3},{0,5,5},{3,9,3},{3,3,9},{7,7,7}};
public:
    void run();
    game (int argc, char * argv[]);
};
