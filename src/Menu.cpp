//
// Created by joaomendes on 26-04-2024.
//

#include "Menu.h"
#include "Manager.h"
#include <iostream>

int Menu::main() {

    Manager manager;

    std::cout << "+---------------------------------------------------------+\n";
    std::cout << "| Before starting, you have to choose a type of dataset   |\n";
    std::cout << "| to perform the operations.                              |\n";
    std::cout << "|                                                         |\n";
    std::cout << "| 1 - Toy-graphs                                          |\n";
    std::cout << "| 2 - Extra-fully-connected graphs                        |\n";
    std::cout << "| 3 - Real-world graphs                                   |\n";
    std::cout << "| ======================================================= |\n";
    std::cout << "| Please enter your choice:                               |\n";
    std::cout << "+---------------------------------------------------------+\n";
    int n;
    std::cin >> n;
    std::cout << std::endl;

    if (std::cin.fail()) {
        throw std::invalid_argument("Error 001: Your input was not an integer. Please restart the program and try again.");
    }

    while ((n < 1 || n > 3 ) && !(std::cin.fail())) {
        std::cout << "Choose a valid option." << std::endl;
        std::cin >> n;
        std::cout << std::endl;
    }

    switch(n) {
        case 1:
            toySelector();
            break;
        case 2:
            extraFullyConnectedSelector();
            break;
        case 3:
            realWorldSelector();
            break;
    }
    return 0;
}

int Menu::toySelector() {
    std::cout << "+---------------------------------------------------------+\n";
    std::cout << "| TOY-GRAPHS - Select the desired type:                   |\n";
    std::cout << "|                                                         |\n";
    std::cout << "| 1 - Shipping                                            |\n";
    std::cout << "| 2 - Stadiums                                            |\n";
    std::cout << "| 3 - Tourism                                             |\n";
    std::cout << "| ======================================================= |\n";
    std::cout << "| Please enter your choice:                               |\n";
    std::cout << "+---------------------------------------------------------+\n";
    int n;
    std::cin >> n;
    std::cout << std::endl;

    if (std::cin.fail()) {
        throw std::invalid_argument("Error 001: Your input was not an integer. Please restart the program and try again.");
    }

    while ((n < 1 || n > 3 ) && !(std::cin.fail())) {
        std::cout << "Choose a valid option." << std::endl;
        std::cin >> n;
        std::cout << std::endl;
    }

    switch(n) {
        case 1:
            manager.createToyGraphs("../datasets/toy_graphs/shipping.csv", graph);
            break;
        case 2:
            manager.createToyGraphs("../datasets/toy_graphs/stadiums.csv", graph);
            break;
        case 3:
            manager.createToyGraphs("../datasets/toy_graphs/tourism.csv", graph);
            break;
    }
    mainMenu();
    return 0;
}

int Menu::realWorldSelector() {
    std::cout << "+---------------------------------------------------------+\n";
    std::cout << "| REAL-WORLD - Select the desired type:                   |\n";
    std::cout << "|                                                         |\n";
    std::cout << "| 1 - Graph 1                                             |\n";
    std::cout << "| 2 - Graph 2                                             |\n";
    std::cout << "| 3 - Graph 3                                             |\n";
    std::cout << "| ======================================================= |\n";
    std::cout << "| Please enter your choice:                               |\n";
    std::cout << "+---------------------------------------------------------+\n";
    int n;
    std::cin >> n;
    std::cout << std::endl;

    if (std::cin.fail()) {
        throw std::invalid_argument("Error 001: Your input was not an integer. Please restart the program and try again.");
    }

    while ((n < 1 || n > 3 ) && !(std::cin.fail())) {
        std::cout << "Choose a valid option." << std::endl;
        std::cin >> n;
        std::cout << std::endl;
    }

    switch(n) {
        case 1:
            manager.createNodesRealWorld("../datasets/realworld_graphs/graph1/nodes.csv", graph);
            manager.createEdgesRealWorld("../datasets/realworld_graphs/graph1/edges.csv", graph);
            break;
        case 2:
            manager.createNodesRealWorld("../datasets/realworld_graphs/graph2/nodes.csv", graph);
            manager.createEdgesRealWorld("../datasets/realworld_graphs/graph2/edges.csv", graph);
            break;
        case 3:
            manager.createNodesRealWorld("../datasets/realworld_graphs/graph3/nodes.csv", graph);
            manager.createEdgesRealWorld("../datasets/realworld_graphs/graph3/edges.csv", graph);
            break;
    }
    mainMenu();
    return 0;
}

int Menu::extraFullyConnectedSelector() {
    std::cout << "+---------------------------------------------------------+\n";
    std::cout << "| FULLY-CONNECTED - Select the number of edges:           |\n";
    std::cout << "|                                                         |\n";
    std::cout << "| 1 - 25                                                  |\n";
    std::cout << "| 2 - 50                                                  |\n";
    std::cout << "| 3 - 75                                                  |\n";
    std::cout << "| 4 - 100                                                 |\n";
    std::cout << "| 5 - 200                                                 |\n";
    std::cout << "| 6 - 300                                                 |\n";
    std::cout << "| 7 - 400                                                 |\n";
    std::cout << "| 8 - 500                                                 |\n";
    std::cout << "| 9 - 600                                                 |\n";
    std::cout << "| 10 - 700                                                |\n";
    std::cout << "| 11 - 800                                                |\n";
    std::cout << "| 12 - 900                                                |\n";
    std::cout << "| ======================================================= |\n";
    std::cout << "| Please enter your choice:                               |\n";
    std::cout << "+---------------------------------------------------------+\n";
    int n;
    std::cin >> n;
    std::cout << std::endl;

    if (std::cin.fail()) {
        throw std::invalid_argument("Error 001: Your input was not an integer. Please restart the program and try again.");
    }

    while ((n < 1 || n > 12 ) && !(std::cin.fail())) {
        std::cout << "Choose a valid option." << std::endl;
        std::cin >> n;
        std::cout << std::endl;
    }

    manager.createNodesRealWorld("../datasets/extra_fully_connected_graphs/nodes.csv", graph);

    switch(n) {
        case 1:
            manager.createEdgesRealWorld("../datasets/extra_fully_connected_graphs/edges_25.csv", graph);
            break;
        case 2:
            manager.createEdgesRealWorld("../datasets/extra_fully_connected_graphs/edges_50.csv", graph);
            break;
        case 3:
            manager.createEdgesRealWorld("../datasets/extra_fully_connected_graphs/edges_75.csv", graph);
            break;
        case 4:
            manager.createEdgesRealWorld("../datasets/extra_fully_connected_graphs/edges_100.csv", graph);
            break;
        case 5:
            manager.createEdgesRealWorld("../datasets/extra_fully_connected_graphs/edges_200.csv", graph);
            break;
        case 6:
            manager.createEdgesRealWorld("../datasets/extra_fully_connected_graphs/edges_300.csv", graph);
            break;
        case 7:
            manager.createEdgesRealWorld("../datasets/extra_fully_connected_graphs/edges_400.csv", graph);
            break;
        case 8:
            manager.createEdgesRealWorld("../datasets/extra_fully_connected_graphs/edges_500.csv", graph);
            break;
        case 9:
            manager.createEdgesRealWorld("../datasets/extra_fully_connected_graphs/edges_600.csv", graph);
            break;
        case 10:
            manager.createEdgesRealWorld("../datasets/extra_fully_connected_graphs/edges_700.csv", graph);
            break;
        case 11:
            manager.createEdgesRealWorld("../datasets/extra_fully_connected_graphs/edges_800.csv", graph);
            break;
        case 12:
            manager.createEdgesRealWorld("../datasets/extra_fully_connected_graphs/edges_900.csv", graph);
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
    std::cout << "| 4 - Change dataset                                      |\n";
    std::cout << "| ==================== Main Menu ======================== |\n";
    std::cout << "| 1 - Number of elements                                  |\n";
    std::cout << "| 2 - Backtrack bounding                                  |\n";
    std::cout << "| 3 - Exit                                                |\n";
    std::cout << "| ======================================================= |\n";
    std::cout << "| Please enter your choice:                               |\n";
    std::cout << "+---------------------------------------------------------+\n";
    int n;
    std::cin >> n;
    std::cout << std::endl;

    if (std::cin.fail()) {
        throw std::invalid_argument("Error 001: Your input was not an integer. Please restart the program and try again.");
    }

    while ((n < 1 || n > 4 ) && !(std::cin.fail())) {
        std::cout << "Choose a valid option." << std::endl;
        std::cin >> n;
        std::cout << std::endl;
    }

    std::vector<std::pair<std::vector<int>,double>> paths;
    switch(n) {
        case 1:
            manager.counter(graph);
            break;
        case 2:
            paths = manager.backtrackBounding();
            std::cout << paths.size();
            for (auto path : paths) {
                std::cout << "Path: ";
                for (auto vertex : path.first) {
                    std::cout << vertex << " ";
                }
                std::cout << "Cost: " << path.second << std::endl;
            }
            break;
        case 3:
            manager.triangular(graph);
            break;
        case 4:
            exit(0);
        case 5:
            graph = Graph();
            main();
            break;
    }

    char c;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Do you wish to perform any other action? (y/n)" << std::endl;
    std::cin >> c;
    std::cout << std::endl;
    if (c == 'y' || c == 'Y') {
        mainMenu();
    } else {
        exit(0);
    }
    return 0;
}
