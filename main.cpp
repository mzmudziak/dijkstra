#include <iostream>
#include <vector>
#include "Graph.h"
#include "Utils.h"
#include <random>

using namespace std;


int main() {
    char mode;
    cout << "Choose mode:" << endl;
    cout << "A - single test for random graph" << endl;
    cout << "B - benchmark test for multiple randomly generated graphs" << endl;

    cin >> mode;
    switch (mode) {
        case 'a':
        case 'A': {
            int n, k;
            cout << "[A] - Single test" << endl;
            cout << "How many vertices?" << endl;
            cin >> n;
            int maxEdges = n * (n - 1) / 2;
            auto minEdges = static_cast<int>(ceil(0.25 * n * (n - 1)));
            uniform_int_distribution<int> uni(minEdges, maxEdges);
            cout << "Min. edges for compact graph: " << n - 1 << endl;
            cout << "Min. edges, for dense graph: " << minEdges << endl;
            cout << "Max edges: " << maxEdges << endl;
            cout << "How many edges would you like? ("<< minEdges << ".." << maxEdges << ")" << endl;
            cin >> k;
            while (k < minEdges || k > maxEdges) {
                cin >> k;
            }
            int searched = -1;
            cout << "Type target vertex number if you only want single shortest path, otherwise type \"-1\"";
            cin >> searched;

            cout << "Vertices: " << n << endl;
            cout << "Edges: " << n << endl;
            cout << "Looking for:" << searched << endl;
            auto *g = new Graph(n, k);
            g->print();
            auto start = chrono::steady_clock::now();
            g->dijkstra(0, searched);
            auto end = chrono::steady_clock::now();
            auto diff = end - start;
            cout << "\nExecution:" << chrono::duration<double, nano>(diff).count() << " ns" << endl;
            break;
        }
        case 'b':
        case 'B': {
            int min, max, amountOfExecutions, saturation;
            cout << "[B] - Benchmark!" << endl;
            cout << "How many vertices at minimum?" << endl;
            cin >> min;
            cout << "How many vertices at maximum?: " << endl;
            cin >> max;
            cout << "Graph saturation percentage:: " << endl;
            cin >> saturation;
            cout << "How many executions per iteration? " << endl;
            cin >> amountOfExecutions;
            for (int i = min; i < max; i++) {
                int maxEdges =  i * (i - 1) / 2;
                int amountOfEdges = static_cast<int>(maxEdges * saturation / 100);
                cout << "Saturation: " << saturation << " (" << amountOfEdges << " of " << maxEdges << " edges created)" << endl;
                double execution = 0;
                cout << "[" << i << "] ";
                for (int j = 0; j < amountOfExecutions; j++) {
                    auto *graf = new Graph(i, amountOfEdges);
                    auto start = chrono::steady_clock::now();
                    graf->dijkstra(0, -1);
                    auto end = chrono::steady_clock::now();
                    auto diff = chrono::duration<double, nano>(end - start).count();
                    cout << diff << " ";
                    execution += chrono::duration<double, nano>(diff).count();
                }
                cout << "\nMean execution time: " << execution / amountOfExecutions << " ns" << endl;
            }
            break;
        }
        default:
            cout << "Wrong mode... exiting..." << endl;
    }
    return 0;
}
