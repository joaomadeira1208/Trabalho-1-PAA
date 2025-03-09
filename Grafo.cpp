#include "Grafo.hpp"
#include <stack>
#include <algorithm>

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

bool Grafo::hasEdge(int u, int v)
{
    return std::find(listaAdjacencia[u].begin(), listaAdjacencia[u].end(), v) != listaAdjacencia[u].end();
}

const int Grafo::grau(int v) const
{
    return listaAdjacencia[v].size();
}

const vector<list<int>> &Grafo::getListaAdjacencia() const
{
    return listaAdjacencia;
}

// void Grafo::DFS(int v, vector<bool> &visitado)
// {
//     visitado[v] = true;
//     for (int vizinho : listaAdjacencia[v])
//     {
//         if (!visitado[vizinho])
//         {
//             DFS(vizinho, visitado);
//         }
//     }
// }

// bool Grafo::isConexo()
// {
//     vector<bool> visitado(n, false);

//     int inicio = 0;

//     DFS(inicio, visitado);

//     for (int i = 0; i < n; i++)
//     {
//         if (!visitado[i])
//         {
//             return false;
//         }
//     }

//     return true;
// }

bool Grafo::DFS(int v, int destino, vector<bool> &visitado)
{
    stack<int> pilha;
    pilha.push(v);

    while (!pilha.empty())
    {
        int vertice = pilha.top();
        pilha.pop();

        if (!visitado[vertice])
        {
            visitado[vertice] = true;

            if (vertice == destino)
                return true;

            for (int vizinho : listaAdjacencia[vertice])
            {
                if (!visitado[vizinho])
                {
                    pilha.push(vizinho);
                }
            }
        }
    }
    return false;
}

bool Grafo::isConexo(int origem, int destino)
{
    vector<bool> visitado(n, false);
    return DFS(origem, destino, visitado);
}

bool Grafo::isEuleriano()
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (grau(i) % 2 != 0)
        {
            count++;
            if (count > 2)
            {
                return false;
            }
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
