#include "Grafo.hpp"
#include "Algoritmos.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

Grafo gerarGrafoCiclo(int numVertices)
{
    Grafo grafo = Grafo(numVertices);

    for (int i = 0; i < numVertices - 1; i++)
    {
        grafo.addEdge(i, i + 1);
    }

    grafo.addEdge(numVertices - 1, 0);

    return grafo;
}

int main()
{
    Grafo grafo = gerarGrafoCiclo(100000);

    // grafo.print();
    // cout << "----------" << endl;

    Algoritmos algoritmos;

    if (!grafo.isEuleriano())
    {
        cout << "Grafo Não Euleriano" << endl;
        return 0;
    }

    cout << "Grafo Euleriano" << endl;

    vector<int> euleriano = algoritmos.fleury(grafo);

    for (int v : euleriano)
    {
        cout << v << " ";
    }

    return 0;
}