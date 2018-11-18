


#ifndef DJIKSTRA_GRAPH_H
#define DJIKSTRA_GRAPH_H

#include <iostream>
#include <queue>
#include <list>

using namespace std;

class Graph {
private:
    int n;
    int **matrix;
public:
    explicit Graph(int n, int k);

    void print();

    int shortest(const int *distance, const bool *visited);

    void printShortestPath(int *parent, int i);

    void print(int *dist, int *parent, int destination);

    void dijkstra(int source, int destination);
};
#endif
