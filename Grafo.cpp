#include "Grafo.hpp"

using namespace std;

Grafo::Grafo(int n) : n(n), listaAdjacencia(n) {}

void Grafo::addEdge(int u, int v)
{
    listaAdjacencia[u].push_back(v);
    listaAdjacencia[v].push_back(u);
}

void Grafo::removeEdge(int u, int v)
{
    listaAdjacencia[u].remove(v);
    listaAdjacencia[v].remove(u);
}

const vector<list<int>> &Grafo::getListaAdjacencia()
{
    return listaAdjacencia;
}

void Grafo::DFS(int v, vector<bool> &visitado)
{
    visitado[v] = true;
    for (int vizinho : listaAdjacencia[v])
    {
        if (!visitado[vizinho])
        {
            DFS(vizinho, visitado);
        }
    }
}

bool Grafo::isConexo()
{
    vector<bool> visitado(n, false);

    int inicio = 0;

    DFS(inicio, visitado);

    for (int i = 0; i < n; i++)
    {
        if (!visitado[i])
        {
            return false;
        }
    }

    return true;
}

void Grafo::print()
{
    for (int i = 0; i < n; i++)
    {
        cout << "Vértice " << i << ":";
        for (int vizinho : listaAdjacencia[i])
        {
            cout << " " << vizinho;
        }
        cout << endl;
    }
}
