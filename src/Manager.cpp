//
// Created by joaomendes on 03-05-2024.
//

#include <fstream>
#include <iostream>
#include <sstream>
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
