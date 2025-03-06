#include "Ponte.hpp"
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

vector<pair<int, int>> Ponte::naive(Grafo &grafo)
{
    vector<pair<int, int>> pontes;
    auto listaAdj = grafo.getListaAdjacencia();

    for (int u = 0; u < listaAdj.size(); u++)
    {
        for (int v : listaAdj[u])
        {
            if (u < v)
            {
                grafo.removeEdge(u, v);

                if (!grafo.isConexo())
                {
                    pontes.push_back({u, v});
                }
                grafo.addEdge(u, v);
            }
        }
    }
    return pontes;
}

void Ponte::dfs(int vertice, int pai, Grafo &grafo, vector<bool> &visitado, vector<int> &tempoDescoberta, vector<int> &menorTempoAcessivel, int &tempoAtual, vector<pair<int, int>> &pontes)
{
    visitado[vertice] = true;
    tempoDescoberta[vertice] = menorTempoAcessivel[vertice] = tempoAtual++;

    for (int vizinho : grafo.getListaAdjacencia()[vertice])
    {
        if (vizinho == pai)
            continue;

        if (!visitado[vizinho])
        {
            dfs(vizinho, vertice, grafo, visitado, tempoDescoberta, menorTempoAcessivel, tempoAtual, pontes);
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

vector<pair<int, int>> Ponte::tarjan(Grafo &grafo)
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
            dfs(vertice, -1, grafo, visitado, tempoDescoberta, menorTempoAcessivel, tempoAtual, pontes);
        }
    }

    return pontes;
}
