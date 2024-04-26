//
// Created by joaomendes on 26-04-2024.
//

#include "Menu.h"
#include <iostream>

int Menu::main() {
    std::cout << "+---------------------------------------------------------+\n";
    std::cout << "| Before starting, you have to choose a dataset           |\n";
    std::cout << "| to perform the operations.                              |\n";
    std::cout << "|                                                         |\n";
    std::cout << "| 1 - Toy-graphs                                          |\n";
    std::cout << "| 2 - Extra-fully-connected graphs                        |\n";
    std::cout << "| 3 - Real-world graphs                                    |\n";
    std::cout << "| ======================================================= |\n";
    std::cout << "| Please enter your choice:                               |\n";
    std::cout << "+---------------------------------------------------------+\n";
    int n;
    std::cin >> n;
    std::cout << std::endl;

    if (std::cin.fail()) {
        throw std::invalid_argument("Error 001: Your input was not an integer. Please restart the program and try again.");
    }

    while ((n < 1 || n > 2 ) && !(std::cin.fail())) {
        std::cout << "Choose a valid option." << std::endl;
        std::cin >> n;
        std::cout << std::endl;
    }

    switch(n) {
        case 1:
            break;
        case 2:
            break;
    }
    mainMenu();
    return 0;
}

int Menu::mainMenu() {
    std::cout << "+---------------------------------------------------------+\n";
    std::cout << "| Welcome to the TSP program.                             |\n";
    std::cout << "|                                                         |\n";
    std::cout << "| Our menu works based on                                 |\n";
    std::cout << "| number inputs! i.e., for                                |\n";
    std::cout << "| option 1, please input 1 in                             |\n";
    std::cout << "| the terminal.                                           |\n";
    std::cout << "|                                                         |\n";
    std::cout << "| ==================== Main Menu ======================== |\n";
    std::cout << "| 1 - Number of elements                                  |\n";
    std::cout << "| 9 - Exit                                                |\n";
    std::cout << "| ======================================================= |\n";
    std::cout << "| Please enter your choice:                               |\n";
    std::cout << "+---------------------------------------------------------+\n";
    return 0;
}
