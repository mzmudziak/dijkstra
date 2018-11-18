//
// Created by Michal Zmudziak on 05/11/2018.
//

#include "Graph.h"
#include "Utils.h"

Graph::Graph(int vertices, int edges) {
    this->n = vertices;
    // generate 0-filled adjacency matrix
    this->matrix = new int *[vertices];
    for (int i = 0; i < vertices; i++) {
        this->matrix[i] = new int[vertices];
        for (int j = 0; j < vertices; j++) {
            this->matrix[i][j] = 0;
        }
    }
    // create required n-1 edges
    vector<int> randomIndexedVector = fisherYatesShuffle(indexedVector(vertices));
    for (int k = 0; k < vertices - 1; k++) {
        int index = randomIndexedVector[k];
        int nextIndex = randomIndexedVector[k + 1];
        this->matrix[index][nextIndex] = random(0, 100);
        this->matrix[nextIndex][index] = random(0, 100);
    }
    // find all possible edge (i,j) pairs
    vector<std::pair<int, int>> free;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < i; ++j) {
            if (this->matrix[i][j] == 0) {
                free.emplace_back(i, j);
            }
        }
    }
    // shuffle the pairs so they are random
    vector<std::pair<int, int>> shuffledFree = fisherYatesShuffle(free);

    // create (edges - n + 1) edges
    for (int i = 0; i < edges - n + 1; i++) {
        this->matrix[shuffledFree[i].first][shuffledFree[i].second] = random(0, 100);
        this->matrix[shuffledFree[i].second][shuffledFree[i].first] = random(0, 100);
    }
}

int Graph::shortest(const int *dystans, const bool *znalezione, int n) {
    int min = INT_MAX;
    int min_index = -1;
    for (int i = 0; i < n; i++) {
        if (!znalezione[i] && dystans[i] <= min) {
            min = dystans[i];
            min_index = i;
        }
    }
    return min_index;
}

void Graph::print() {
    cout << "Graf o " << n << " wierzcholkach" << endl << '\t';
    for (int i = 0; i < this->n; ++i) {
        cout << i << "\t";
    }
    cout << endl;
    for (int i = 0; i < this->n; i++) {
        cout << i << "\t";
        for (int j = 0; j < this->n; j++) {
            cout << this->matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void Graph::printPath(int parent[], int i) {
    if (parent[i] == -1) {
        return;
    }
    printPath(parent, parent[i]);
    cout << i << " ";
}

void Graph::printSolution(int dist[], int parent[], int destination) {
    int src = 0;
    cout << "\nTrasa\t\tWaga\tSciezka";
    if (destination != -1) {
        cout << "\n" << src << " -> " << destination << "\t\t" << dist[destination] << "\t\t\t" << src << " ";
        printPath(parent, destination);
    } else {
        for (int i = 0; i < n; i++) {
            cout << "\n" << src << " -> " << i << "\t\t" << dist[i] << "\t\t\t" << src << " ";
            printPath(parent, i);
        }
    }
}

void Graph::dijkstra(int source, int destination) {
    int *distance = new int[n];
    bool *visited = new bool[n];
    int *parent = new int[n];
    for (int i = 0; i < n; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
    }
    parent[source] = -1;
    distance[source] = 0;
    for (int j = 0; j < n - 1; j++) {
        int u = shortest(distance, visited, n);
        visited[u] = true;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && this->matrix[u][v] && distance[u] != INT_MAX &&
                distance[u] + this->matrix[u][v] < distance[v]) {
                distance[v] = distance[u] + this->matrix[u][v];
                parent[v] = u;
            }
        }
        if (u == destination) {
            break;
        }
    }
    printSolution(distance, parent, destination);
}


