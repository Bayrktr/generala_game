#include "choose_who_start_first.h"
#include "../print_score_sheet/print_score_sheet.h"


#include <iostream>
#include <cstdlib>
#define DICE_COUNT 5
#define DICE_START_COUNT 2
#define DICE_SIZE 6


void start_roll_dice(int dice[DICE_START_COUNT]) {
    for (int i = 0; i < DICE_START_COUNT; i++) {
        dice[i] = rand() % DICE_SIZE;
    }
}

void start_total_score(int &score, int dice[DICE_START_COUNT]) {
    for (int i = 0; i < DICE_START_COUNT; i++) {
        score += dice[i];
    }
}

void choose_who_start_first(bool *isIStartFirst) {
    int my_dices[DICE_START_COUNT], computer_dices[DICE_START_COUNT];

    start_roll_dice(my_dices);
    start_roll_dice(computer_dices);

    int my_total_score = 0, computer_total_score = 0;

    start_total_score(my_total_score, my_dices);
    start_total_score(computer_total_score, computer_dices);

    std::cout << "Computer's total score: " << computer_total_score << std::endl;
    std::cout << "My total score: " << my_total_score << std::endl;


    if (my_total_score > computer_total_score) {
        print_score_sheet(0, my_total_score, computer_total_score);

        std::cout << "I start first" << std::endl;
        *isIStartFirst = true;
    } else if (my_total_score == computer_total_score) {
        std::cout << "Recolling" << std::endl;
        choose_who_start_first(isIStartFirst);
    } else {
        print_score_sheet(0, my_total_score, computer_total_score);

        std::cout << "Computer starts first" << std::endl;
        *isIStartFirst = false;
    }
}
