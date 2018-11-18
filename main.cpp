#include <iostream>
#include <vector>
#include "Graph.h"
#include "Utils.h"
#include <random>

using namespace std;


int main() {
    char mode;
    cout << "Wybierz tryb:" << endl;
    cout << "A - pojedynczy test dla losowego grafu" << endl;
    cout << "B - strumieniowy test dla losowych grafów" << endl;

    cin >> mode;
    switch (mode) {
        case 'a':
        case 'A': {
            int n, k;
            cout << "Wybrano tryb A." << endl;
            cout << "Podaj liczbę wierzchołków grafu:" << endl;
            cin >> n;
            int maxEdges = n * (n - 1) / 2;
            auto minEdges = static_cast<int>(ceil(0.25 * n * (n - 1)));
            uniform_int_distribution<int> uni(minEdges, maxEdges);
            cout << "Min. ilość krawędzi, aby graf był spójny: " << n - 1 << endl;
            cout << "Min. ilość krawędzi, aby graf był gęsty: " << minEdges << endl;
            cout << "Maksymalna ilość krawędzi: " << maxEdges << endl;
            cout << "Podaj liczbę krawędzi grafu grafu: ()" << endl;
            cin >> k;
            while (k < minEdges || k > maxEdges) {
                cin >> k;
            }
            int searched = -1;
            cout << "Jesli chcesz wyszukac najkrótszą ścieżkę do konkretnego wierzchołka, podaj jego numer lub -1:";
            cin >> searched;

            cout << "N:" << n << endl;
            cout << "K:" << n << endl;
            cout << "S:" << searched << endl;
            auto *g = new Graph(n, k);
            g->print();
            auto start = chrono::steady_clock::now();
            g->dijkstra(0, searched);
            auto end = chrono::steady_clock::now();
            auto diff = end - start;
            cout << "\nCzas wykonania:" << chrono::duration<double, nano>(diff).count() << " ns" << endl;
            break;
        }
        case 'b':
        case 'B': {
            int min, max, executions, completion;
            cout << "Wybrano tryb B." << endl;
            cout << "Podaj minimalną liczbę wierzchołków: " << endl;
            cin >> min;
            cout << "Podaj maksymalna liczbę wierzchołków: " << endl;
            cin >> max;
            cout << "Podaj procent nasycenia: " << endl;
            cin >> completion;
            cout << "Podaj liczbe wykonan: " << endl;
            cin >> executions;
            for (int i = min; i < max; i++) {
                int maxEdges =  i * (i - 1) / 2;
                int vertices = static_cast<int>(maxEdges * completion / 100);
                cout << "Graf o nasyceniu " << completion << " (" << vertices << " z " << maxEdges << " krawędzi)" << endl;
                double czasy = 0;
                for (int j = 0; j < executions; j++) {
                    auto *graf = new Graph(i, vertices);
                    auto start = chrono::steady_clock::now();
                    graf->dijkstra(0, -1);
                    auto end = chrono::steady_clock::now();
                    auto diff = end - start;
                    czasy += chrono::duration<double, nano>(diff).count();
                }
                cout << "Czas wykonania: " << czasy / executions << " ns" << endl;
            }
            break;
        }
        default:
            cout << "Wybrano zły tryb..." << endl;
    }
    return 0;
}
