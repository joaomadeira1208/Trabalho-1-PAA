#include "Algoritmos.hpp"
#include <vector>
#include <utility>
#include <algorithm>
#include <stack>
#include <unordered_set>

struct par_hash
{
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

using namespace std;

bool Algoritmos::naive(Grafo &grafo, int u, int v)
{
    grafo.removeEdge(u, v);

    if (!grafo.isConexo(u, v))
    {
        grafo.addEdge(u, v);
        return true;
    }
    grafo.addEdge(u, v);
    return false;
}

// void Algoritmos::dfsTarjan(int vertice, int pai, Grafo &grafo, vector<bool> &visitado, vector<int> &tempoDescoberta, vector<int> &menorTempoAcessivel, int &tempoAtual, vector<pair<int, int>> &pontes)
// {
//     visitado[vertice] = true;
//     tempoDescoberta[vertice] = menorTempoAcessivel[vertice] = tempoAtual++;

//     for (int vizinho : grafo.getListaAdjacencia()[vertice])
//     {
//         if (vizinho == pai)
//             continue;

//         if (!visitado[vizinho])
//         {
//             dfsTarjan(vizinho, vertice, grafo, visitado, tempoDescoberta, menorTempoAcessivel, tempoAtual, pontes);
//             menorTempoAcessivel[vertice] = min(menorTempoAcessivel[vertice], menorTempoAcessivel[vizinho]);

//             if (menorTempoAcessivel[vizinho] > tempoDescoberta[vertice])
//             {
//                 pontes.push_back({vertice, vizinho});
//             }
//         }
//         else
//         {
//             menorTempoAcessivel[vertice] = min(menorTempoAcessivel[vertice], tempoDescoberta[vizinho]);
//         }
//     }
// }

void Algoritmos::dfsTarjan(int vertice, int pai, Grafo &grafo, vector<bool> &visitado, vector<int> &tempoDescoberta, vector<int> &menorTempoAcessivel, int &tempoAtual, vector<pair<int, int>> &pontes)
{
    stack<tuple<int, int, int>> pilha;
    pilha.push({vertice, pai, 0});

    while (!pilha.empty())
    {
        auto [v, p, estado] = pilha.top();
        pilha.pop();

        if (estado == 0) // Primeira vez visitando o vértice
        {
            visitado[v] = true;
            tempoDescoberta[v] = menorTempoAcessivel[v] = tempoAtual++;
            pilha.push({v, p, 1}); // Retorna a esse estado após percorrer os vizinhos

            for (int vizinho : grafo.getListaAdjacencia()[v])
            {
                if (vizinho == p)
                    continue;

                if (!visitado[vizinho])
                {
                    pilha.push({vizinho, v, 0});
                }
                else
                {
                    menorTempoAcessivel[v] = min(menorTempoAcessivel[v], tempoDescoberta[vizinho]);
                }
            }
        }
        else // Pós-processamento
        {
            for (int vizinho : grafo.getListaAdjacencia()[v])
            {
                if (vizinho != p && visitado[vizinho])
                {
                    menorTempoAcessivel[v] = min(menorTempoAcessivel[v], menorTempoAcessivel[vizinho]);

                    if (menorTempoAcessivel[vizinho] > tempoDescoberta[v])
                    {
                        pontes.push_back({v, vizinho});
                    }
                }
            }
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

    while (true)
    {
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
    }

    return caminho;
}

vector<int> Algoritmos::fleuryTarjan(Grafo &grafo)
{
    vector<pair<int, int>> pontes = tarjan(grafo);
    unordered_set<pair<int, int>, par_hash> pontesSet(pontes.begin(), pontes.end());

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

    while (true)
    {
        if (grafo.grau(u) == 0)
            break;

        list<int> vizinhos = grafo.getListaAdjacencia()[u];
        bool todasArestasPontes = true;
        for (int v : vizinhos)
        {
            pair<int, int> aresta = {min(u, v), max(u, v)}; // aresta ordenada p/ busca eficiente em pontesSet
            if (grafo.grau(u) != 1)
            {
                vector<pair<int, int>> pontes = tarjan(grafo);
                unordered_set<pair<int, int>, par_hash> pontesSet(pontes.begin(), pontes.end());
                if (pontesSet.find(aresta) == pontesSet.end())
                {
                    todasArestasPontes = false;
                    grafo.removeEdge(u, v);
                    caminho.push_back(v);
                    u = v;
                    break;
                }
            }
        }

        if (todasArestasPontes)
        {
            int v = vizinhos.front();
            grafo.removeEdge(u, v);
            caminho.push_back(v);
            u = v;
        }
    }
    return caminho;
}

vector<int> Algoritmos::fleuryNaive(Grafo &grafo)
{
    int numVertices = grafo.getListaAdjacencia().size();
    int u = 0;

    // Encontrar vértice inicial (se houver vértices ímpares)
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

    while (true)
    {
        if (grafo.grau(u) == 0)
            break;

        list<int> vizinhos = grafo.getListaAdjacencia()[u];
        for (int v : vizinhos)
        {
            if (!naive(grafo, u, v) || grafo.grau(u) == 1)
            { // naive retorna false se a aresta for ponte
                grafo.removeEdge(u, v);
                caminho.push_back(v);
                u = v;
                break;
            }
        }
    }

    return caminho;
}
