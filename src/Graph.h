//
// Created by joaomendes on 03-05-2024.
//

#ifndef TRAVELLINGSALESPERSON_GRAPH_H
#define TRAVELLINGSALESPERSON_GRAPH_H


#include <vector>
#include <string>


class Edge;


class Vertex {
public:
    Vertex(int id, std::string longitude, std::string latitude); // Realworld vertex
    Vertex(int id); // Toy graph vertex

    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    std::vector<Edge*> getAdj() const;
    bool isVisited() const;
    Edge* getPath() const;
    std::vector<Edge*> getIncoming() const;

    void setVisited(bool visited);
    void setPath(Edge *path);
    Edge* addEdge(Vertex *dest, double w);
    bool removeEdge(int in);
    void removeOutgoingEdges();

    int getID() const;
    std::string getLongitude() const;
    std::string getLatitude() const;

protected:
    int id;
    std::string longitude;
    std::string latitude;
    std::vector<Edge*> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge *path = nullptr;

    std::vector<Edge*> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge *edge);
};


class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double distance);

    Vertex* getDest() const;
    double getDistance() const;
    bool isSelected() const;
    Vertex* getOrig() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
protected:
    Vertex* dest; // destination vertex
    double distance; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems
};

class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    Vertex *findVertex(const int &in) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(Vertex* v);
    bool removeVertex(const int &in);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const int &sourc, const int &dest, double w);
    bool removeEdge(const int &source, const int &dest);
    bool addBidirectionalEdge(const int &sourc, const int &dest, double w);
    std::vector<Vertex*> getVertexSet() const;
protected:
    std::vector<Vertex*> vertexSet;    // vertex set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall
};


#endif //TRAVELLINGSALESPERSON_GRAPH_H
