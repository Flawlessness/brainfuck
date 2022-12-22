add_executable(Dilemma main.cpp)

add_library(Lib cooperate_always_strategy.cpp cooperate_always_strategy.h Factory.cpp Factory.h deflect_always_strategy.cpp deflect_always_strategy.h random_strategy.cpp random_strategy.h tit_for_tat_strategy.cpp tit_for_tat_strategy.h tit_for_tat_forgiveness_strategy.cpp tit_for_tat_forgiveness_strategy.h game.cpp game.h simpleton_strategy.cpp simpleton_strategy.h majority_strategy.cpp majority_strategy.h scoundrel_strategy.cpp scoundrel_strategy.h)

target_link_libraries(Dilemma PRIVATE Lib)
