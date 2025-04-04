#include <iostream>
#include <cstdlib>
#include <ctime>
#include "project/tasks/choose_who_start_first/choose_who_start_first.h"


#define DICE_COUNT 5
#define DICE_START_COUNT 2
#define DICE_SIZE 6


int main() {
    srand(time(0));

    bool isIStartFirst;

    choose_who_start_first(&isIStartFirst);

    if(isIStartFirst) {

    }else {

    }


    return 0;
}
