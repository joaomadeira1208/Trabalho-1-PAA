#include "Grafo.hpp"
#include "Ponte.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

Grafo gerarGrafoComPontes(int numVertices, int arestasExtras)
{
    srand(time(0));

    Grafo grafo(numVertices);
    set<pair<int, int>> arestasExistentes;

    for (int i = 1; i < numVertices; i++)
    {
        int pai = rand() % i;
        grafo.addEdge(i, pai);
        arestasExistentes.insert({min(i, pai), max(i, pai)});
    }

    for (int i = 0; i < arestasExtras; i++)
    {
        int u, v;
        do
        {
            u = rand() % numVertices;
            v = rand() % numVertices;
        } while (u == v || arestasExistentes.count({min(u, v), max(u, v)}) > 0);

        grafo.addEdge(u, v);
        arestasExistentes.insert({min(u, v), max(u, v)});
    }

    return grafo;
}

int main()
{
    Grafo grafo = gerarGrafoComPontes(4, 1);

    grafo.print();

    cout << "----------" << endl;

    Ponte ponte;

    vector<pair<int, int>> pontes = ponte.naive(grafo);

    cout << "Pontes encontradas pelo método Naïve:" << endl;
    for (auto bridge : pontes)
    {
        cout << "(" << bridge.first << ", " << bridge.second << ") é uma ponte." << endl;
    }

    return 0;
}