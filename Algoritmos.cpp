#include "Algoritmos.hpp"
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

bool Algoritmos::naive(Grafo &grafo, int u, int v)
{
    grafo.removeEdge(u, v);

    if (!grafo.isConexo())
    {
        return true;
    }
    grafo.addEdge(u, v);
    return false;
}

void Algoritmos::dfsTarjan(int vertice, int pai, Grafo &grafo, vector<bool> &visitado, vector<int> &tempoDescoberta, vector<int> &menorTempoAcessivel, int &tempoAtual, vector<pair<int, int>> &pontes)
{
    visitado[vertice] = true;
    tempoDescoberta[vertice] = menorTempoAcessivel[vertice] = tempoAtual++;

    for (int vizinho : grafo.getListaAdjacencia()[vertice])
    {
        if (vizinho == pai)
            continue;

        if (!visitado[vizinho])
        {
            dfsTarjan(vizinho, vertice, grafo, visitado, tempoDescoberta, menorTempoAcessivel, tempoAtual, pontes);
            menorTempoAcessivel[vertice] = min(menorTempoAcessivel[vertice], menorTempoAcessivel[vizinho]);

            if (menorTempoAcessivel[vizinho] > tempoDescoberta[vertice])
            {
                pontes.push_back({vertice, vizinho});
            }
        }
        else
        {
            menorTempoAcessivel[vertice] = min(menorTempoAcessivel[vertice], tempoDescoberta[vizinho]);
        }
    }
}

vector<pair<int, int>> Algoritmos::tarjan(Grafo &grafo)
{
    int numVertices = grafo.getListaAdjacencia().size();
    vector<bool> visitado(numVertices, false);
    vector<int> tempoDescoberta(numVertices, -1), menorTempoAcessivel(numVertices, -1);
    vector<pair<int, int>> pontes;
    int tempoAtual = 0;

    for (int vertice = 0; vertice < numVertices; vertice++)
    {
        if (!visitado[vertice])
        {
            dfsTarjan(vertice, -1, grafo, visitado, tempoDescoberta, menorTempoAcessivel, tempoAtual, pontes);
        }
    }

    return pontes;
}

vector<int> Algoritmos::fleury(Grafo &grafo)
{
    int numVertices = grafo.getListaAdjacencia().size();
    int u = 0;

    for (int i = 0; i < numVertices; i++)
    {
        if (grafo.grau(i) % 2 == 1)
        {
            u = i;
            break;
        }
    }

    vector<int> caminho;
    caminho.push_back(u);
    // int count = 0;

    while (true)
    {
        cout << "u: " << u << endl;
        if (grafo.grau(u) == 0)
        {
            caminho.pop_back();
            break;
        }

        list<int> vizinhos = grafo.getListaAdjacencia()[u];
        if (grafo.grau(u) == 1)
        {
            caminho.push_back(vizinhos.front());
            grafo.removeEdge(u, vizinhos.front());
            u = vizinhos.front();
            continue;
        }

        for (int v : vizinhos)
        {
            if (grafo.grau(u) == 1 || !naive(grafo, u, v))
            {
                grafo.removeEdge(u, v);
                caminho.push_back(v);
                u = v;
                break;
            }

            grafo.addEdge(u, v);
        }
        // count++;
        // if (count == 10)
        // {
        //     break;
        // }
    }

    return caminho;
}
