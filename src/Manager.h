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

    std::vector<std::pair<std::vector<int>, double>> backtrackBounding();
    void backtracking(Graph &graph, std::vector<int> &path, std::vector<std::pair<std::vector<int>, double>> &paths,
                      double currCost, double minCost, int currVertex);

private:
    Graph graph;

    std::pair<std::vector<int>, double> preOrderMST();

    double haversineDistance(double lat1, double lon1, double lat2, double lon2);

    double getDistanceCoordHaversine(int a, int b);

    double degreesToRadians(double degrees);

    std::pair<std::vector<int>, double> TSPHeuristicAproximation();

    std::set<Edge *> Prim();
};


#endif //TRAVELLINGSALESPERSON_MANAGER_H
