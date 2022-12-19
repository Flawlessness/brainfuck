#include "game.h"
#include "cooperate_always_strategy.h"
#include "deflect_always_strategy.h"
#include "random_strategy.h"
#include "tit_for_tat_strategy.h"
#include "tit_for_tat_forgiveness_strategy.h"
#include "simpleton_strategy.h"
#include "majority_strategy.h"
#include "scoundrel_strategy.h"
namespace
{
    const int players_counts = 3;
}

void game ::detailed_game()
{
    std::vector<std::shared_ptr<IStrategy>> strategies(players_counts, nullptr);
    std::vector<int> results(players_counts, 0);
    std::vector<std::vector<bool>> history;
    std::vector<bool> tmp(players_counts, 0);
    std::vector<bool> player_choice(players_counts, 0);
    char key = 0;

    for(int i = 0; i < players_counts; i++)
    {
        strategies[i] = factory.create(input_strategies[i]);
    }

    for (int w = 0; w < 10000; w++)
    {
        unsigned int index = 0;
        for (int j = 0; j < players_counts; j++)
        {
            player_choice[j] = static_cast<int>(strategies[j]->run(history, w, j));
            tmp[j] = player_choice[j];
            index |= player_choice[j] << (players_counts - 1 - j);
        }
        history.push_back(tmp);
        for (int j = 0; j < players_counts; j++)
        {
            results[j] += game_matrix[index][j];
        }

        std :: cout << "input strategies: |";
        for (int j = 0; j < players_counts; j++)
        {
            std :: cout << input_strategies[j] << "|";
        }
        std :: cout << std :: endl;

        std :: cout << "player choice: ";
        for (int j = 0; j < players_counts; j++)
        {
            std :: cout << player_choice[j] << " ";
        }
        std :: cout << std :: endl;

        std :: cout << "players points per round: ";
        for (int j = 0; j < players_counts; j++)
        {
            std :: cout << game_matrix[index][j] << " ";
        }
        std :: cout << std :: endl;

        std :: cout << "final score: ";
        for (int j = 0; j < players_counts; j++)
        {
            std :: cout << results[j] << " ";
        }
        std :: cout << std :: endl;

        key = static_cast<char>(getchar());
        if (key == 'q')
        {
            int best_strategy_index = 0;
            int max_score = -1;
            for (int i = 0; i < input_strategies.size(); i++)
            {
                if (results[i] > max_score)
                {
                    max_score = results[i];
                    best_strategy_index = i;
                }
            }

            std :: cout << std :: endl <<"Best scoring strategy: " << input_strategies[best_strategy_index] << std :: endl;
            std :: cout << "Score: " << max_score << std :: endl;
            break;
        }
    }
}

std :: vector<int> game ::fast_game(const std::vector<std::string> &input_strategies_)
{
    std::vector<std::shared_ptr<IStrategy>> strategies(players_counts);
    std::vector<int> results(players_counts, 0);
    std::vector<std::vector<bool>> history(steps_count, std :: vector<bool>(players_counts, 0));
    std::vector<bool> tmp(players_counts, 0);
    std::vector<bool> player_choice(players_counts, 0);


    for(int i = 0; i < players_counts; i++)
    {
        strategies[i] = factory.create(input_strategies_[i]);
    }

    for (int i = 0; i < steps_count; i++)
    {
        unsigned int index = 0;
        for (int j = 0; j < 3; j++)
        {
            player_choice[j] = static_cast<int>(strategies[j]->run(history, i, j));
            history[i][j] = player_choice[j];
            index |= player_choice[j] << (2 - j);
        }
        for (int j = 0; j < 3; j++)
        {
            results[j] += game_matrix[index][j];
        }
    }
    return results;
}

void game ::tournament_game()
{
    std :: vector<int> results(players_counts, 0);
    std :: vector<int> final_results(input_strategies.size(), 0);
    std :: vector<int> final_results_wins(input_strategies.size(), 0);
    std :: vector<std :: string> strategies(players_counts, "");
    for (int i = 0; i < (input_strategies.size() - 2); i++)
    {
        strategies[0] = input_strategies[i];
        for (int j = i + 1; j < (input_strategies.size() - 1); j++)
        {
            strategies[1] = input_strategies[j];
            for (int k = j + 1; k < input_strategies.size(); k++)
            {
                strategies[2] = input_strategies[k];
                results = fast_game(strategies);
                final_results[i] += results[0];
                final_results[j] += results[1];
                final_results[k] += results[2];
                int max = -1;
                for (int z = 0; z < 3; z++)
                {
                    if (results[z] > max)
                    {
                        max = results[z];
                    }
                }
                for (int z = 0; z < 3; z++)
                {
                    if (results[z] == max)
                    {
                        if (z == 0)
                        {
                            final_results_wins[i]++;
                        }
                        else if (z == 1)
                        {
                            final_results_wins[j]++;
                        }
                        else
                        {
                            final_results_wins[k]++;
                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i < input_strategies.size(); i ++)
    {
        for(int j = 0; j < (input_strategies.size() - 1); j ++)
        {
            if (final_results_wins[j] < final_results_wins[j + 1])
            {
                int tmp = final_results_wins[j];
                final_results_wins[j] = final_results_wins[j + 1];
                final_results_wins[j + 1] = tmp;
                tmp = final_results[j];
                final_results[j] = final_results[j + 1];
                final_results[j + 1] = tmp;
                std :: string tmp_string = input_strategies[j];
                input_strategies[j] = input_strategies[j + 1];
                input_strategies[j + 1] = tmp_string;
            }
        }
    }

    std :: cout << std :: endl << "The best winning strategy: " << input_strategies[0] << " ";
    for (int i = 1; i < input_strategies.size(); i ++)
    {
        if (final_results_wins[i - 1] == final_results_wins[i])
        {
            std::cout << input_strategies[i] << " ";
        }
        else
        {
            break;
        }
    }
    std :: cout << std :: endl << "Wins: " << final_results_wins[0] << std :: endl;

    for(int i = 0; i < input_strategies.size(); i ++)
    {
        for(int j = 0; j < (input_strategies.size() - 1); j ++)
        {
            if (final_results[j] < final_results[j + 1])
            {
                int tmp = final_results[j];
                final_results[j] = final_results[j + 1];
                final_results[j + 1] = tmp;
                tmp = final_results_wins[j];
                final_results_wins[j] = final_results_wins[j + 1];
                final_results_wins[j + 1] = tmp;
                std :: string tmp_string = input_strategies[j];
                input_strategies[j] = input_strategies[j + 1];
                input_strategies[j + 1] = tmp_string;
            }
        }
    }

    std :: cout << std :: endl << "Best scoring strategy: " << input_strategies[0] << " ";
    for (int i = 1; i < input_strategies.size(); i ++)
    {
        if (final_results[i - 1] == final_results[i])
        {
            std::cout << input_strategies[i] << " ";
        }
        else
        {
            break;
        }
    }
    std :: cout << std :: endl << "Score: " << final_results[0] << std :: endl;

    std::cout << std :: endl << "Score top:" << std :: endl;
    for(int i = 0; i < input_strategies.size(); i ++)
    {
        std :: cout << i + 1 << ") " << input_strategies[i] << ": " << final_results[i] << std :: endl;
    }

}

game :: game(int argc, char * argv[])
{
    steps_count = 10;
    factory.register_creator("cooperate", std::make_shared<Creator<cooperate_always_strategy>>());
    factory.register_creator("deflect", std::make_shared<Creator<deflect_always_strategy>>());
    factory.register_creator("random", std::make_shared<Creator<random_strategy>>());
    factory.register_creator("tit_for_tat", std::make_shared<Creator<tit_for_tat_strategy>>());
    factory.register_creator("tit_for_tat_forgiveness", std::make_shared<Creator<tit_for_tat_forgiveness_strategy>>());
    factory.register_creator("simpleton", std::make_shared<Creator<simpleton_strategy>>());
    factory.register_creator("majority", std::make_shared<Creator<majority_strategy>>());
    factory.register_creator("scoundrel", std::make_shared<Creator<scoundrel_strategy>>());

    for(int i = 1; i < argc; i++)
    {
        int flag = 0;
        std :: string arg_vi_string(argv[i]);

        if ((arg_vi_string == "help") || (arg_vi_string == "-h") || (arg_vi_string == "--help"))
        {
            help();
            throw std::invalid_argument("Help.");
        }

        if (arg_vi_string.size() < 5)
        {
            help();
            throw std::invalid_argument("Invalid input.");
        }
        else if (arg_vi_string == "--mode=detailed")
        {
            gamemode = 0;
            flag = 1;
            continue;
        }
        else if (arg_vi_string == "--mode=fast")
        {
            gamemode = 1;
            flag = 1;
            continue;
        }
        else if (arg_vi_string == "--mode=tournament")
        {
            gamemode = 2;
            flag = 1;
            continue;
        }

        for(int j = 0; j < available_strategies.size(); j++)
        {

            if (arg_vi_string == available_strategies[j])
            {
                input_strategies.push_back(available_strategies[j]);
                flag = 1;
                break;
            }
        }
        if ((arg_vi_string.size() > 8) && (flag == 0))
        {
            std::string arg_vi_string_copy = arg_vi_string;
            arg_vi_string_copy.erase(7);
            if (arg_vi_string_copy == "--steps") {
                flag = 1;
                int flag_2 = 0;
                steps_count = 0;
                for (int k = 8; k < arg_vi_string.size(); k++)
                {
                    if ((arg_vi_string[k] <= 57) && (arg_vi_string[k] >= 48))
                    {
                        steps_count = steps_count * 10 + (arg_vi_string[k] - 48);
                        flag_2 = 1;
                    } else
                    {
                        help();
                        std :: cerr << "Invalid input." << std:: endl;
                        exit(0);
                    }
                }
                if (flag_2 == 0)
                {
                    help();
                    std :: cerr << "Invalid input." << std:: endl;
                    exit(0);
                }
            }
        }
        if (flag == 0)
        {
            help();
            std :: cerr << "Invalid input." << std:: endl;
            exit(0);
        }
    }

    if (input_strategies.size() < 3)
    {
        help();
        std :: cerr << "Invalid input." << std:: endl;
        exit(0);
    }

    if ((input_strategies.size() != 3) && (gamemode != 2))
    {
        help();
        std :: cerr << "Invalid input." << std:: endl;
        exit(0);
    }

}

void game :: run()
{
    if (gamemode == 0)
    {
        detailed_game();
    }
    else if (gamemode == 1)
    {
        std :: vector<int> results_tmp(input_strategies.size(), 0);
        results_tmp = fast_game(input_strategies);

        std :: cout << "input strategies: |";
        for (int j = 0; j < players_counts; j++)
        {
            std :: cout << input_strategies[j] << "|";
        }
        std :: cout << std :: endl;

        std :: cout << "final score: ";
        for (int i = 0; i < input_strategies.size(); i++)
        {
            std :: cout << results_tmp[i] << " ";
        }
        std :: cout << std :: endl;
        int best_strategy_index = 0;
        int max_score = -1;
        for (int i = 0; i < input_strategies.size(); i++)
        {
            if (results_tmp[i] > max_score)
            {
                max_score = results_tmp[i];
                best_strategy_index = i;
            }
        }
        std :: cout << "Best scoring strategy: " << input_strategies[best_strategy_index] << std :: endl;
        std :: cout << "Score: " << max_score << std :: endl;
    }
    else
    {
        tournament_game();
    }
}

void game :: help()
{
    std :: cout << "На старте программе подаются следующие аргументы командной строки:\n"
                   "    1)Три (или более - для турнирного режима) имени соревнующихся стратегий.\n"
                   "    2)Название режима --mode=[detailed|fast|tournament] (опциональный, по умолчанию - detailed для трех стратегий, tournament для >3 стратегий)\n"
                   "    3)Число шагов симуляции --steps=<n> (опциональный)\n"
                   "Возможные стратегии:\n"
                   "    1)cooperate (всегда сотрудничает)\n"
                   "    2)deflect (всегда предает)\n"
                   "    3)random (рандом)\n"
                   "    4)tit_for_tat (первым ходом сотрудничает, далее повторяет ходы соперников)\n"
                   "    5)tit_for_tat_forgiveness (аналогична стратегии tit_for_tat, но если соперник предаст 1 раз, она все равно будет сотрудничать следующим ходом)\n"
                   "    6)simpleton (сотрудничает до тех пор, пока соперник не предаст, далее всегда предает)\n"
                   "    7)majority (первым ходом сотрудничает, далее выберает тот ход, который встречался чаще всего в истории ходов соперников)\n"
                   "    8)scoundrel (первым ходом предает, далее, если предыдущий ход сопеника предать, то стратегия предает\n"
                   "                 если предыдущий ход соперник сотрудничать и предыдущий ход стратегии сотдрудничать, то она предает\n"
                   "                 если предыдущий ход соперник сотрудничать и предыдущий ход стратегии предать, то она сотрудничает )\n"
                   "Так как игроков 3, то предательством считаем ход, при котором хотя бы один игрок предал, в противном случае считаем ход сотрудничеством.\n"
                   "Пример передачи аргументов: cooperate deflect random --mode=detailed --steps=100\n"
                   "При выборе режима detailed следующий ход выводиться после нажатии кнопки {enter}, прекращаеться после команды \"quit\"\n";
}