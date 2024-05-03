//
// Created by joaomendes on 03-05-2024.
//

#ifndef TRAVELLINGSALESPERSON_MANAGER_H
#define TRAVELLINGSALESPERSON_MANAGER_H


#include <string>
#include "Graph.h"

class Manager {
public:
    void createNodesRealWorld(const std::string &filename, Graph& graph);
    void createEdgesRealWorld(const std::string &filename, Graph& graph);
    void createToyGraphs(const std::string &filename, Graph& graph);

    void counter(Graph& graph);

private:
    Graph graph;
};


#endif //TRAVELLINGSALESPERSON_MANAGER_H
