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

    void backtrackBounding(Graph& graph);
    void backtracking(Graph& graph, std::vector<int>& path, std::vector<int>& min_path, double& minDistance, double &totalDistance, Vertex* currVertex, int startVertex);

    std::vector<Vertex*> prim(Graph graph);
    void triangular(Graph& graph);
    double getDistanceCoordHaversine(Graph& graph, Vertex* a, Vertex* b);

private:
    Graph graph;

    double haversine(double lat1, double lon1, double lat2, double lon2);



    double convert_to_radians(double coord);



    // std::set<Edge *> prim();

};


#endif //TRAVELLINGSALESPERSON_MANAGER_H
