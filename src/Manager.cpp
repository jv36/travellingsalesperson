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

        Vertex* vert = new Vertex(idConv, longitude, latitude);
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
            auto vert = new Vertex(originConv);
            graph.addVertex(vert);
        }

        if (!graph.findVertex(destinationConv)) {
            // Toy graph vertex constructor -- different from real world
            auto vert = new Vertex(destinationConv);
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


std::vector<std::pair<std::vector<int>,double>> Manager::backtrackBounding() {
    Graph graph = Manager::graph;
    std::cout << "so";
    for (auto vert: graph.getVertexSet()) {
        vert->setVisited(false);
    }

    double currCost = 0;
    double minCost = 999999999;
    std::vector<int> path;
    path.push_back(0);
    graph.findVertex(0)->setVisited(true);

    std::vector<std::pair<std::vector<int>, double>> paths;
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

std::pair<std::vector<int>,double> Manager::preOrderMST() {
    std::vector<int> preorder;
    double cost=0;
    int lastid;
    std::stack<Vertex*> stack;
    stack.push(graph.findVertex(0));
    Graph debug = graph;
    bool child;
    while (!stack.empty()) {
        Vertex* current = stack.top();
        stack.pop();
        preorder.push_back(current->getID());
        lastid=current->getID();
        child=true;
        for (auto vertexPair : graph.getVertexSet() ) {
            if (vertexPair->getID()!=0 && vertexPair->getID()!=lastid){
                if (vertexPair->getPath()->getOrig()->getID()==current->getID()){
                    cost+=getDist(vertexPair->getID(),current->getID());
                    stack.push(vertexPair);
                    child=false;
                }
            }
        }
        if (child && !stack.empty())  cost+=getDist(current->getID(),stack.top()->getID());;
    }

    preorder.push_back(0);
    for (auto vertexPair :graph.getVertexSet()){
        if (vertexPair->getID()==lastid){
            cost+=getDist(0,vertexPair->getID() );

        }
    }

    return std::make_pair(preorder,cost);
}

std::pair<std::vector<int>,double> Manager::TSPHeuristicAproximation() {

    Prim();
    std::pair<std::vector<int>,double> path = preOrderMST();


    return path;
}

std::set<Edge *> Manager::Prim() {
    if (graph.getVertexSet().empty()) {
        return {};
    }
    std::set<Edge*> mst;
    for(auto vertex : graph.getVertexSet()) {
        vertex->setDist(std::numeric_limits<double>::max());
        vertex->setPath(nullptr);
        vertex->setVisited(false);
    }
    Graph a=graph;
    // start with an arbitrary vertex
    Vertex* root = graph.getVertexSet()[0];
    root->setDist(0);
    MutablePriorityQueue<Vertex> q;
    q.insert(root);
    while( ! q.empty() ) {
        auto v = q.extractMin();
        v->setVisited(true);
        for(auto &e : v->getAdj()) {
            Vertex* w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getDist();
                if(e->getDist() < oldDist) {
                    w->setDist(e->getDist());
                    w->setPath(e);
                    if (oldDist == std::numeric_limits<double>::max()) {
                        q.insert(w);
                    }
                    else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
        if (v->getPath() != nullptr){
            mst.insert(v->getPath());
            v->getPath()->getDest()->incrementmstdegree();
            v->getPath()->getOrig()->incrementmstdegree();
        }


    }

    return mst;
}



double Manager::getDist(int a,int b){
    for (auto edge:graph.findVertex(a)->getAdj()){
        if (edge->getDest()->getID()==b) return edge->getDistance();
    }

    return haversineDistance(std::stod(graph.findVertex(a)->getLatitude()),std::stod(graph.findVertex(a)->getLongitude()),std::stod(graph.findVertex(b)->getLatitude()),std::stod(graph.findVertex(b)->getLongitude()));

}

constexpr double kEarthRadiusKm = 6371.0;

double Manager::degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

double Manager::haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    double dLat = degreesToRadians(lat2 - lat1);
    double dLon = degreesToRadians(lon2 - lon1);

    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(degreesToRadians(lat1)) * std::cos(degreesToRadians(lat2)) *
               std::sin(dLon / 2) * std::sin(dLon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    return kEarthRadiusKm * c;
}