#include "print_score_sheet.h"

#include <iostream>
#include <ostream>


void print_score_sheet(const int round, const int my_total_score, const int computer_total_score) {
    std::cout << "Our scoresheet after round " << round << ":" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "My score\n" << my_total_score << std::endl;
    std::cout << "Computer score\n" << computer_total_score << std::endl;
}
