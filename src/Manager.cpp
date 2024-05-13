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
#include <unordered_set>

/**
 * @brief Faz parse aos vértices dos grafos do tipo Real World.
 * @brief Cria os vértices e adiciona-os ao grafo.
 * @details Complexidade: O(n)
 * @param filename: nome do ficheiro com os nodes, em formato CSV
 * @param graph: grafo onde os vértices serão adicionados
 */
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

/**
 * @brief Faz parse às arestas dos grafos do tipo Real World.
 * @brief Cria as arestas e adiciona-as ao grafo.
 * @details Complexidade: O(n)
 * @param filename: nome do ficheiro com as arestas, em formato CSV
 * @param graph: grafo onde as arestas serão adicionadas
 */
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

/**
 * @brief Faz parse aos vértices dos grafos do tipo Toy Graph.
 * @brief Cria os vértices e adiciona-os ao grafo.
 * @details Complexidade: O(n)
 * @param filename: nome do ficheiro com os nodes, em formato CSV
 * @param graph: grafo onde os vértices serão adicionados
 */
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

/**
 * @brief Imprime o número de vértices e arestas de um grafo.
 * @details Complexidade: O(n)
 * @param graph: grafo a ser analisado
 */
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




/**
 * @brief Função que implementa o backtracking para encontrar o caminho mais curto num grafo.
 * @brief Utiliza recursão para explorar todos os caminhos possíveis, e guarda o caminho mais curto. (bruteforce)
 * @details Complexidade: O(n!)
 * @param graph: grafo a ser analisado
 * @param path: caminho atual
 * @param min_path: caminho mais curto
 * @param minDistance: distância do caminho mais curto
 * @param totalDistance: distância total do caminho atual
 * @param currVertex: vértice atual
 * @param startVertex: vértice de início
 */
void Manager::backtracking(Graph& graph, std::vector<int>& path, std::vector<int>& min_path, double& minDistance, double &totalDistance, Vertex* currVertex, int startVertex) {
    if (path.size() == graph.getVertexSet().size() && currVertex->getID() == startVertex) {
        if (totalDistance < minDistance) {
            min_path = path;
            minDistance = totalDistance;
        }
        return;
    }

    for (auto edge : currVertex->getAdj()) {
        if (!edge->getDest()->isVisited()) {
            if (totalDistance + edge->getDistance() >= minDistance) {
                continue;
            }
            path.push_back(edge->getDest()->getID());
            edge->getDest()->setVisited(true);
            totalDistance += edge->getDistance();
            backtracking(graph, path, min_path, minDistance, totalDistance, edge->getDest(), startVertex);
            path.pop_back();
            edge->getDest()->setVisited(false);
            totalDistance -= edge->getDistance();
        }
    }
}

/**
 * @brief Função que chama a função de backtracking para encontrar o caminho mais curto num grafo.
 * @brief Começa no vértice de ID 0 - backtracking com bounding - e depois imprime o caminho e a distância, bem como o tempo de execução.
 * @brief Este algoritmo é demorado e não é eficiente para grafos grandes. Por isso, apenas deve ser utilizado em Toy Graphs.
 * @details Complexidade: O(n!)
 * @param graph: grafo a ser analisado
 */
void Manager::backtrackBounding(Graph& graph) {
    clock_t start = clock();

    std::vector<int> path;
    std::vector<int> min_path;
    double minDistance = std::numeric_limits<double>::infinity();
    double totalDistance = 0;
    Vertex* currVertex = graph.findVertex(0);

    backtracking(graph, path, min_path, minDistance, totalDistance, currVertex, 0);


    // add zero, to return to the starting point
    min_path.insert(min_path.begin(), 0);
    std::cout << "Path: ";
    for (auto it = min_path.rbegin(); it != min_path.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Minimum distance: " << minDistance << std::endl;
    std::cout << "Execution time (milliseconds): " << (clock() - start) << "ms" << std::endl;
    std::cout << "Execution time (seconds): " << (double)(clock() - start) / CLOCKS_PER_SEC << "s" << std::endl;
}



// Triangular approximation

/**
 * @brief Função que implementa o algoritmo Prim para encontrar uma MST de um grafo.
 * @brief Utiliza uma mutable priority queue para escolher o vértice mais próximo, e guarda o caminho mais curto.
 * @details Complexidade: O(V+E)log(V))
 * @param graph: grafo a ser analisado
 * @return vetor com os vértices da MST
 */
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

/**
 * @brief Função que implementa o algoritmo Prim para encontrar uma MST de um grafo.
 * @brief Utiliza uma mutable priority queue para escolher o vértice mais próximo, e guarda o caminho mais curto.
 * @brief Função apenas utilizada em Christofides, tendo como diferença a possibilidade da escolha do vértice inicial.
 * @brief No algoritmo de Prim da outra função, subentende-se que se começa no primeiro vértice do grafo.
 * @details Complexidade: O(V+E)log(V))
 * @param graph: grafo a ser analisado
 * @param startingVert: vértice de início (ID)
 * @return vetor com os vértices da MST
 */
std::vector<Vertex*> Manager::christofidesPrim(Graph graph, int startingVert) {
    // This version of the algorithm allows for inputting a vertex to start from
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
    auto first = graph.findVertex(startingVert);
    if (first == nullptr) {
        return mst; // Returning an empty vector
    }
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

/**
 * @brief Função que implementa o algoritmo triangular approximation para encontrar um caminho aproximado num grafo.
 * @brief Utiliza o algoritmo de Prim para encontrar a MST, e depois percorre a MST para encontrar o caminho.
 * @brief O caminho é encontrado através da verificação de ligações entre vértices.
 * @brief Imprime o caminho e a distância, bem como o tempo de execução.
 * @details Complexidade: O(V+E)log(V))
 * @param graph: grafo a ser analisado
 */
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

// Other heuristics - Christofides algorithm

// a more complex algorithm for TSP
// find MST
// find set of vertices with odd degree
// find minimum weight perfect matching (MWM) on that set
// combine MST and MWM to form a connected graph
// find eulerian circuit on the graph
// convert the eulerian into a hamiltonian circuit*
// (a tour that visits each vertex exactly once by skipping repeated vertices)

/**
 * @brief Função que implementa o algoritmo de Christofides para encontrar um caminho aproximado num grafo.
 * @brief Utiliza o algoritmo de Prim para encontrar a MST
 * @brief Encontra os vértices com grau ímpar
 * @brief Encontra o MWM
 * @brief Combina a MST e o MWM
 * @brief Encontra o circuito euleriano
 * @brief Converte o circuito euleriano num circuito hamiltoniano
 * @brief Imprime o caminho e a distância, bem como o tempo de execução.
 * @brief É possível escolher o vértice de início bem como ver uma lista completa de vértices.
 * @details Complexidade:
 * @param graph: grafo a ser analisado
 */
void Manager::christofides(Graph& graph) {
    clock_t start = clock();
    std::vector<int> min_path;
    double totalDistance = 0.0;

    std::cout << "You have to choose a vertex to start the algorithm." << std::endl;
    std::cout << "Do you wish to see the full list of vertices? (y/n)" << std::endl;
    char choice;
    std::cin >> choice;
    if (choice == 'y') {
        for (auto vert : graph.getVertexSet()) {
            std::cout << vert->getID() << std::endl;
        }
    }
    std::cout << "Choose the first vertex: " << std::endl;
    int vertx;
    std::cin >> vertx;
    // step 1 - find mst
    Graph mst = MST(graph, vertx);

    std::cout << "Finding MST..." << std::endl;

    // step 2 - find set of vertices with odd degree
    std::vector<Vertex*> oddDegree = findOddDegree(mst);

    std::cout << "Finding vertices with odd degree..." << std::endl;

    // step 3 - find MWM
    Graph mwm = findMWM(graph, oddDegree);

    std::cout << "Finding MWM..." << std::endl;

    // step 4 - combine MST/MWM
    Graph combinedGraph = combineMSTMWM(mst, mwm);

    std::cout << "Combining MST and MWM..." << std::endl;

    // step 5 - find eulerian
    std::vector<int> eulerian = findEulerCircuit(combinedGraph);

    std::cout << "Finding eulerian circuit..." << std::endl;

    // step 6 - eulerian -> hamiltonian circuit
    std::vector<int> hamiltonian = findHamiltonCircuit(eulerian);

    std::cout << "Finding hamiltonian circuit..." << std::endl;


    std:: cout << "Getting total distance..." << std::endl;
    for (int i = 0; i < hamiltonian.size() - 1; i++) {
        int src = hamiltonian[i];
        int dest = hamiltonian[i + 1];
        auto srcVertex = graph.findVertex(src);

        if (!srcVertex) {
            // if src is null
            continue;
        }

        Edge* edge = nullptr;
        for (auto ed : srcVertex->getAdj()) {
            if (ed->getDest()->getID() == dest) {
                edge = ed;
                break;
            }
        }

        if (!edge) {
            // if edge not found
            continue;
        }

        totalDistance += edge->getDistance();
    }

    std::cout << "-----------------------" << std::endl;
    std::cout << "Path: ";
    for (auto v : hamiltonian) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    std::cout << "Total distance: " << totalDistance << std::endl;
    std::cout << "Execution time (milliseconds): " << (clock() - start) << "ms" << std::endl;
    std::cout << "Execution time (seconds): " << (double)(clock() - start) / CLOCKS_PER_SEC << "s" << std::endl;
}

/**
 * @brief Função que implementa Prim para encontrar a MST de um grafo.
 * @brief E converte a MST num grafo.
 * @brief É utilizada no algoritmo de Christofides.
 * @details Complexidade: O(V+E)log(V))
 * @param graph: grafo a ser analisado
 * @param startingVert: vértice de início (ID)
 * @return grafo com a MST
 */
Graph Manager::MST(Graph& graph, int startingVert) {
    Graph newGraph;
    std::vector<Vertex*> mst = christofidesPrim(graph, startingVert);

    std::unordered_set<Vertex*> visited;

    for (auto vert : mst) {
        newGraph.addVertex(new Vertex(vert->getID(), 0.0, 0.0));
        visited.insert(vert);
    }

    for (auto vert : graph.getVertexSet()) {
        vert->setVisited(false);
    }

    for (auto vert : graph.getVertexSet()) {
        if (vert->getPath() != nullptr) {
            auto edge = vert->getPath();
            auto origin = edge->getOrig();
            auto dest = edge->getDest();

            if (!origin->isVisited() && !dest->isVisited()) {
                newGraph.addBidirectionalEdge(origin->getID(), dest->getID(), edge->getDistance());
                visited.insert(origin);
                visited.insert(dest);
            }
        }
    }

    return newGraph;
}

/**
 * @brief Função que encontra os vértices com grau ímpar num grafo.
 * @brief Utilizada no algoritmo de Christofides.
 * @details Complexidade: O(n^2)
 * @param mst: grafo a ser analisado (no caso, uma MST)
 * @return vetor com os vértices de graus ímpares
 */
std::vector<Vertex*> Manager::findOddDegree(Graph& mst) {

    std::vector<Vertex*> oddDegree;

    for (auto vert : graph.getVertexSet()) {
        vert->setIndegree(0);
    }

    for (auto vert : graph.getVertexSet()) {
        int deg = vert->getIndegree();
        for (auto edge : vert->getIncoming()) {
            auto src = edge->getOrig();
            deg++;
            deg += src->getIndegree();
        }

        // if odd
        if (deg % 2 != 0) {
            oddDegree.push_back(vert);
        }
    }

    return oddDegree;
}

/**
 * @brief Função que encontra o MWM (Minimum Weight Matching) num grafo.
 * @brief É necessário, obviamente, ter como argumento o conjunto de vértices de grau ímpar do próprio grafo.
 * @brief Utilizada no algoritmo de Christofides.
 * @details Complexidade: O(n^2)
 * @param graph: grafo a ser analisado
 * @param oddDegree: vértices com grau ímpar desse grafo
 * @return grafo com o MWM
 */
Graph Manager::findMWM(Graph& graph, std::vector<Vertex*>& oddDegree) {
    Graph mwm;

    for (auto vert : oddDegree) {
        mwm.addVertex(new Vertex(vert->getID(), 0.0, 0.0));
    }

    std::vector<bool> isVisited(oddDegree.size(), false);
    for (int i = 0; i < oddDegree.size(); i++) {
        if (!isVisited[i]) {
            double minDist = std::numeric_limits<double>::max();
            Vertex* minVert = nullptr;

            for (int j = i + 1; j < oddDegree.size(); j++) {
                if (!isVisited[j]) {
                    double dist = graph.getDistBetween(oddDegree[i]->getID(), oddDegree[j]->getID());
                    if (dist < minDist) {
                        minDist = dist;
                        minVert = oddDegree[j];
                    }
                }
            }

            isVisited[i] = true;
            if (minVert) {
                isVisited[std::distance(oddDegree.begin(), std::find(oddDegree.begin(), oddDegree.end(), minVert))] = true;
                mwm.addEdge(oddDegree[i]->getID(), minVert->getID(), minDist);
            }
        }
    }

    return mwm;
}

/**
 * @brief Função que combina a MST e o MWM num grafo.
 * @brief Utilizada no algoritmo de Christofides.
 * @details Complexidade: O(Vmst + Vmwm + Emst + Emwm)
 * @param mst: minimum spanning tree
 * @param mwm: minimum weight matching
 * @return grafo combinado
 */
Graph Manager::combineMSTMWM(Graph& mst, Graph& mwm) {
    Graph newGraph = mst;

    for (auto vert : mwm.getVertexSet()) {
        for (auto edge : vert->getAdj()) {
            newGraph.addBidirectionalEdge(edge->getOrig()->getID(), edge->getDest()->getID(), edge->getDistance());
        }
    }

    return newGraph;
}

/**
 * @brief Função que encontra o circuito euleriano num grafo.
 * @brief Utilizada no algoritmo de Christofides.
 * @details Complexidade: O(V+E)
 * @param graph: grafo a ser analisado
 * @return vetor com o circuito euleriano (com os IDs dos vértices)
 */
std::vector<int> Manager::findEulerCircuit(Graph& graph) {
    std::vector<int> euler;

    auto vertexSet = graph.getVertexSet();
    if (vertexSet.empty()) {
        // Handle the case where the vertex set is empty
        return euler; // Returning an empty vector
    }

    auto first = vertexSet.front();

    std::stack<Vertex*> st;
    st.push(first);
    while (!st.empty()) {
        auto curVert = st.top();
        if (curVert->getAdj().empty()) {
            euler.push_back(curVert->getID());
            st.pop();
        } else {
            auto edges = curVert->getAdj();
            auto edge = edges.front();
            if (!edge) {
                // Handle the case where the edge is null
                st.pop();
                continue;
            }
            auto dest = edge->getDest();
            if (!dest) {
                // Handle the case where the destination vertex is null
                st.pop();
                continue;
            }
            curVert->removeEdge(dest->getID());
            st.push(dest);
        }
    }

    std::reverse(euler.begin(), euler.end());

    return euler;
}

/**
 * @brief Função que encontra o circuito hamiltoniano num grafo.
 * @brief Converte o circuito euleriano num circuito hamiltoniano.
 * @brief Saltando os vértices repetidos.
 * @brief Utilizada no algoritmo de Christofides.
 * @param eulerCircuit: circuito euleriano
 * @return vetor com o circuito hamiltoniano (com os IDs dos vértices)
 */
std::vector<int> Manager::findHamiltonCircuit(std::vector<int>& eulerCircuit) {
    std::vector<int> hamilton;
    std::unordered_set<int> isVisited;

    for (auto vert : eulerCircuit) {
        if (isVisited.count(vert) == 0 || hamilton.empty()) {
            hamilton.push_back(vert);
            isVisited.insert(vert);
        }
    }

    if (!hamilton.empty()) {
        hamilton.push_back(hamilton[0]);
    }

    return hamilton;
}



/**
 * @brief Função que calcula a distância entre dois vértices, utilizando a fórmula de Haversine.
 * @brief Utilizada para calcular a distância entre dois vértices num grafo do tipo Real World.
 * @details Complexidade: O(1)
 * @param graph: grafo a ser analisado
 * @param a: vértice de origem
 * @param b: vértice de destino
 * @return distância entre os dois vértices
 */
double Manager::getDistanceCoordHaversine(Graph& graph, Vertex* a, Vertex* b){

    if (a->getLatitude() == 0 && a->getLongitude() == 0 && b->getLatitude() == 0 && b->getLongitude() == 0) {
        std::cout << ">> Executing on a Toy graph <<" << std::endl;
        return 0.0;
    }

    return haversine(a->getLatitude(),a->getLongitude(),b->getLatitude(),b->getLongitude());

}


/**
 * @brief Converte coordenadas de graus para radianos.
 * @param coord: coordenada em graus
 * @return coordenada em radianos
 */
double Manager::convert_to_radians(double coord) {
    return coord * M_PI / 180.0;
}

/**
 * @brief Calcula a distância entre dois pontos na Terra, utilizando a fórmula de Haversine.
 * @brief Utilizada para calcular a distância entre dois vértices num grafo do tipo Real World.
 * @details Complexidade: O(1)
 * @param lat1: latitude do ponto 1
 * @param lon1: longitude do ponto 1
 * @param lat2: latitude do ponto 2
 * @param lon2: longitude do ponto 2
 * @return distância entre os dois pontos
 */
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
