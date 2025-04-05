#include <iostream>
#include <cstdlib>
#include <ctime>
#include "project/tasks/choose_who_start_first/choose_who_start_first.h"
#include "project/tasks/print_score_sheet/print_score_sheet.h"


#define DICE_COUNT 5
#define DICE_START_COUNT 2
#define DICE_SIZE 6
#define DICE_THREE_COUNT 3

void print_dices(int *dice, int size) {
    std::string word;
    for (int i = 0; i < size; i++) {
        word += std::to_string(dice[i]);
        if (i != size - 1) {
            word += ", ";
        }
    }
    std::cout << "Current Dices: " << word << std::endl;
}


void rollDice(int dice[DICE_COUNT]) {
    for (int i = 0; i < DICE_COUNT; i++) {
        dice[i] = rand() % DICE_SIZE + 1;
    }
}

bool isAllVeriablesEqual(const int dice[DICE_COUNT]) {
    int first = dice[0];

    for (int i = 1; i < DICE_COUNT; ++i) {
        if (dice[i] != first) {
            return false;
        }
    }
    return true;
}


void calculate_score(int *score, int dice[DICE_COUNT]) {
    if (isAllVeriablesEqual(dice)) {
        *score += 50;
    } else {
        *score += 1;
    }
}

void myDiceRoll(int my_dice[5], int *my_score) {
    rollDice(my_dice);
}


void computerDiceRoll(int computer_dice[5], int *computer_score) {
    rollDice(computer_dice);
}

void askReroll(bool *isYes) {
    char input;
    std::cout << "Shall I roll for you (Y/N)?" << std::endl;
    std::cin >> input;
    *isYes = (input == 'Y' || input == 'y');
}

void whichOneDoYouKeep(int currentDices[5], int keepList[2]) {
    int keepListCopy[2];
    bool validInput = false;

    while (!validInput) {
        print_dices(currentDices, 5);
        std::cout << "Which ones do you want to keep (2 values):" << std::endl;

        for (int i = 0; i < 2; i++) {
            std::cin >> keepListCopy[i];
        }

        if (keepListCopy[0] == keepListCopy[1]) {
            std::cout << "You can't choose the same dice twice. Please try again." << std::endl;
        } else {
            validInput = true;
        }
    }

    keepList[0] = keepListCopy[0] - 1;
    keepList[1] = keepListCopy[1] - 1;
}


void rollThreeDice(int dice[3]) {
    for (int i = 0; i < 3; i++) {
        dice[i] = rand() % DICE_SIZE + 1;
    }
}

void newDiceAfterReroll(int currentDice[DICE_COUNT], int newThreeDice[3], int keepList[2]) {
    int newIndex = 0;


    for (int i = 0; i < DICE_COUNT; i++) {
        bool keep = false;

        for (int j = 0; j < 2; j++) {
            if (i == keepList[j]) {
                keep = true;
                break;
            }
        }

        if (!keep) {
            if (newIndex < 3) {
                currentDice[i] = newThreeDice[newIndex++];
            }
        }
    }

    print_dices(currentDice, DICE_COUNT);
}


void my_round(int *my_score, int my_dice[5]) {
    myDiceRoll(my_dice, my_score);
    std::cout << "I got " << std::endl;
    print_dices(my_dice, DICE_COUNT);
    for (int i = 0; i < 2; i++) {
        bool isReroll;
        askReroll(&isReroll);
        if (isReroll) {
            int keepList[2];
            int newThreeDice[3];
            whichOneDoYouKeep(my_dice, keepList);
            rollThreeDice(newThreeDice);
            newDiceAfterReroll(my_dice, newThreeDice, keepList);
        } else {
            break;
        }
    }
}

void computer_round(int *computer_score, int computer_dice[5]) {
    computerDiceRoll(computer_dice, computer_score);
    std::cout << "You got " << std::endl;
    print_dices(computer_dice, DICE_COUNT);

    for (int i = 0; i < 2; i++) {
        bool isReroll;
        askReroll(&isReroll);
        if (isReroll) {
            int keepList[2];
            int newThreeDice[3];
            whichOneDoYouKeep(computer_dice, keepList);
            rollThreeDice(newThreeDice);
            newDiceAfterReroll(computer_dice, newThreeDice, keepList);
        } else {
            break;
        }
    }
}


int main() {
    srand(time(0));

    std::cout << "Welcome to Generala game." << std::endl;

    std::cout << "Let's get started!" << std::endl;


    int rounds;

    printf("How many rounds would you like to play? ");
    std::cin >> rounds;

    bool isIStartFirst;

    choose_who_start_first(&isIStartFirst);


    int my_total_score = 0, computer_total_score = 0;


    int my_dice[DICE_COUNT];
    int computer_dice[DICE_COUNT];


    int my_score = 0, computer_score = 0;

    int current_round = 1;


    while (current_round <= rounds) {
        std::cout << "Round: " << current_round << "\n\n";
        std::cout << "---------------------" << std::endl;

        my_score = 0;
        computer_score = 0;

        if (isIStartFirst) {
            isIStartFirst = false;
            my_round(&my_total_score, my_dice);
            computer_round(&computer_total_score, computer_dice);
        } else {
            isIStartFirst = true;
            computer_round(&computer_score, computer_dice);
            my_round(&my_total_score, my_dice);
        }

        calculate_score(&my_score, my_dice);
        calculate_score(&computer_score, computer_dice);

        my_total_score += my_score;
        computer_total_score += computer_score;

        print_score_sheet_after_round(current_round, my_total_score, computer_total_score);
        current_round++;
    }


    return 0;
}
