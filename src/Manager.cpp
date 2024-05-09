//
// Created by joaomendes on 03-05-2024.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stack>
#include <set>
#include <cmath>
#include <limits>
#include "Manager.h"
#include <ctime>

void Manager::createNodesRealWorld(const std::string &filename, Graph &graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    getline(file, line);

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string id, longitude, latitude;

        getline(iss, id, ',');
        getline(iss, longitude, ',');
        getline(iss, latitude, ',');

        int idConv = std::stoi(id);

        Vertex* vert = new Vertex(idConv, std::stod(longitude), std::stod(latitude));
        graph.addVertex(vert);
    }
}

void Manager::createEdgesRealWorld(const std::string &filename, Graph &graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    getline(file, line);

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string origin, destination, distance;

        getline(iss, origin, ',');
        getline(iss, destination, ',');
        getline(iss, distance, ',');

        int originConv = std::stoi(origin);
        int destinationConv = std::stoi(destination);
        double doubleDist = std::stod(distance);

        graph.addEdge(originConv, destinationConv, doubleDist);
    }
}

void Manager::createToyGraphs(const std::string &filename, Graph &graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    getline(file, line);

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string origin, destination, distance;

        getline(iss, origin, ',');
        getline(iss, destination, ',');
        getline(iss, distance, ',');

        int originConv = std::stoi(origin);
        int destinationConv = std::stoi(destination);
        double doubleDist = std::stod(distance);

        if (!graph.findVertex(originConv)) {
            // Toy graph vertex constructor -- different from real world
            auto vert = new Vertex(originConv, 0.0, 0.0);
            graph.addVertex(vert);
        }

        if (!graph.findVertex(destinationConv)) {
            // Toy graph vertex constructor -- different from real world
            auto vert = new Vertex(destinationConv, 0.0, 0.0);
            graph.addVertex(vert);
        }

        // not sure?
        // graph.addBidirectionalEdge(originConv, destinationConv, doubleDist);
        graph.addEdge(originConv, destinationConv, doubleDist);
        graph.addEdge(destinationConv, originConv, doubleDist);
    }
}

void Manager::counter(Graph& graph) {
    int number = 0;
    for (auto v : graph.getVertexSet()) {
        for (auto e : v->getAdj()) {
            e->setSelected(false);
        }
    }
    for (auto v : graph.getVertexSet()) {
        for (auto e : v->getAdj()) {
            if (!e->isSelected()) {
                number++;
                e->setSelected(true);
            }
        }
    }

    std::cout << "Number of nodes: " << graph.getVertexSet().size() << "\n";
    std::cout << "Number of edges: " << number << "\n";
}

// Backtracking



void Manager::backtracking(Graph& graph, std::vector<int>& path, std::vector<std::pair<std::vector<int>,double>>& paths, double currCost, double minCost, int currVertex) {

    // número de cidades
    int n = graph.getVertexSet().size();

    if (path.size() == n) {
        // se todas as cidades foram visitadas
        // adicionar o custo do caminho de volta
        for (auto edge : graph.findVertex(currVertex)->getAdj()) {
            if (edge->getDest()->getID() == 0) {
                currCost += edge->getDistance();
                if (currCost < minCost) {
                    minCost = currCost;
                }
                paths.emplace_back(path, currCost);
                return;
            }
        }

    }
    std::cout << paths.size();

    for (auto edge: graph.findVertex(currVertex)->getAdj()) {
        if (!edge->getDest()->isVisited()) {
            // próximo vértice
            path.push_back(edge->getDest()->getID());
            edge->getDest()->setVisited(true);
            backtracking(graph, path, paths, currCost + edge->getDistance(), minCost, edge->getDest()->getID());
            path.pop_back();
            edge->getDest()->setVisited(false);
        }
    }
}


std::vector<Vertex*> Manager::backtrackBounding(Graph& graph) {
    for (auto vert: graph.getVertexSet()) {
        vert->setVisited(false);
    }

    double currCost = 0;
    double minCost = 999999999;
    std::vector<int> path;
    path.push_back(0);
    graph.findVertex(0)->setVisited(true);

    std::vector<Vertex*> path;
    backtracking(graph, path, paths, currCost, minCost, 0);
    std::sort(paths.begin(), paths.end(),
              [](const std::pair<std::vector<int>, double> &a, const std::pair<std::vector<int>, double> &b) {
                  return a.second < b.second;
              });

    double min = paths.at(0).second;
    std::vector<std::pair<std::vector<int>, double>> minCostPaths;

    for (const auto &path: paths) {
        if (path.second == min) {
            minCostPaths.push_back(path);
        }
    }

    return minCostPaths;
}













// Triangular approximation

std::vector<Vertex*> Manager::prim(Graph graph) {
    std::vector<Vertex*> mst;
    if (graph.getVertexSet().empty()) {
        // return empty set
        return graph.getVertexSet();
    }

    for (auto vert : graph.getVertexSet()) {
        // set all vertices to infinite distance
        vert->setDist(std::numeric_limits<double>::infinity());
        vert->setVisited(false);
        vert->setPath(nullptr);
    }

    // first vert. as starting point
    auto first = graph.getVertexSet().front();
    first->setDist(0);

    // Friend class (using practical class version)
    // We need to decrease keys so this is useful
    MutablePriorityQueue<Vertex> q;
    q.insert(first);

    while (!q.empty()) {
        // pick closest unprocessed node
        auto v = q.extractMin();
        v->setVisited(true);
        mst.push_back(v);

        for (auto &e : v->getAdj()) {
            auto w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getDist();
                if(e->getDistance() < oldDist) {
                    w->setDist(e->getDistance());
                    w->setPath(e);
                    if (oldDist == std::numeric_limits<double>::infinity()) {
                        q.insert(w);
                    }
                    else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }

    return mst;

}

void Manager::triangular(Graph& graph) {
    clock_t start = clock();
    std::vector<Vertex*> mst = prim(graph);

    double totalDistance = 0;

    Vertex* previousVertex = nullptr;
    Vertex* lastVertex = nullptr;
    std::vector<int> path;
    bool isConnected;

    for (auto v : mst) {
        v->setVisited(false);
    }

    for (auto vertex : mst) {
        if (previousVertex != nullptr) {
            isConnected = false;
            for (auto e : previousVertex->getAdj()) {
                if (e->getDest() == vertex) {
                    if (!vertex->isVisited()) {
                        totalDistance += e->getDistance();
                        path.push_back(vertex->getID());
                        vertex->setVisited(true);
                        previousVertex = vertex;
                    }
                    isConnected = true;
                    break;
                }
            }

            if (!isConnected) {
                vertex->setVisited(true);
                totalDistance += getDistanceCoordHaversine(graph, previousVertex, vertex);
                path.push_back(vertex->getID());
                previousVertex = vertex;
            }
        }
        else {
            previousVertex = vertex;
            path.push_back(vertex->getID());
            lastVertex = vertex;
        }
    }

    path.push_back(0);

    for (auto edge: previousVertex->getAdj()) {
        if (edge->getDest() == lastVertex) {
            totalDistance += edge->getDistance();
        }
    }

    if (previousVertex != nullptr) {
        totalDistance += getDistanceCoordHaversine(graph, graph.findVertex(0), lastVertex);
    }

    std::cout << "Path: ";
    for (auto v : path) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    std::cout << "Total distance: " << totalDistance << std::endl;
    std::cout << "Execution time (milliseconds): " << (clock() - start) << "ms" << std::endl;
    std::cout << "Execution time (seconds): " << (double)(clock() - start) / CLOCKS_PER_SEC << "s" << std::endl;
}

double Manager::getDistanceCoordHaversine(Graph& graph, Vertex* a, Vertex* b){

    if (a->getLatitude() == 0 && a->getLongitude() == 0 && b->getLatitude() == 0 && b->getLongitude() == 0) {
        std::cout << ">> Executing on a Toy graph <<" << std::endl;
        return 0.0;
    }

    return haversine(a->getLatitude(),a->getLongitude(),b->getLatitude(),b->getLongitude());

}



double Manager::convert_to_radians(double coord) {
    return coord * M_PI / 180.0;
}

double Manager::haversine(double lat1, double lon1, double lat2, double lon2) {
    double delta_lat = convert_to_radians(lat2 - lat1);
    double delta_lon = convert_to_radians(lon2 - lon1);

    double converted_lat1 = convert_to_radians(lat1);
    double converted_lat2 = convert_to_radians(lat2);

    // sin^2(delta_lat/2) + cos(rad_lat1) * cos(rad_lat2) * sin^2(delta_lon/2)
    double aux = std::pow(std::sin(delta_lat / 2), 2) + std::cos(converted_lat1) * std::cos(converted_lat2) * std::pow(std::sin(delta_lon/ 2), 2);
    double c = 2.0 * std::atan2(std::sqrt(aux), std::sqrt(1 - aux));
    const double earthRadius = 6371.0;
    return earthRadius * c;
}