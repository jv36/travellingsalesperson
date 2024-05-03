//
// Created by joaomendes on 26-04-2024.
//

#ifndef TRAVELLINGSALESPERSON_MENU_H
#define TRAVELLINGSALESPERSON_MENU_H

#include "Graph.h"
#include "Manager.h"

class Menu {
public:
    int main();
    int mainMenu();
    int toySelector();
    int realWorldSelector();
    int extraFullyConnectedSelector();
private:
    Manager manager;
    Graph graph;
};
#endif //TRAVELLINGSALESPERSON_MENU_H
