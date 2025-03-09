#include "Grafo.hpp"
#include "Algoritmos.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <set>
#include <queue>
#include <random>

using namespace std;
using namespace chrono;

// Grafo gerarGrafoEulerianoAleatorio(int nVertices)
// {
//     Grafo grafo(nVertices);

//     if (nVertices <= 0)
//         return grafo;

//     static std::mt19937 rng(static_cast<unsigned long>(
//         std::chrono::high_resolution_clock::now().time_since_epoch().count()));

//     for (int i = 1; i < nVertices; i++)
//     {
//         std::uniform_int_distribution<int> dist(0, i - 1);
//         int parent = dist(rng);
//         grafo.addEdge(parent, i);
//     }

//     std::vector<int> oddVertices;
//     for (int v = 0; v < nVertices; v++)
//     {
//         if (grafo.grau(v) % 2 != 0)
//         {
//             oddVertices.push_back(v);
//         }
//     }

//     std::shuffle(oddVertices.begin(), oddVertices.end(), rng);

//     for (size_t i = 0; i < oddVertices.size(); i += 2)
//     {
//         if (i + 1 >= oddVertices.size())
//             break;
//         int u = oddVertices[i];
//         int v = oddVertices[i + 1];
//         grafo.addEdge(u, v);
//     }

//     return grafo;
// }

Grafo gerarGrafoEulerianoAleatorio(int nVertices)
{
    Grafo grafo(nVertices);

    if (nVertices <= 0)
        return grafo;

    static std::mt19937 rng(static_cast<unsigned long>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()));

    // 1. Generate spanning tree (no duplicates)
    for (int i = 1; i < nVertices; i++)
    {
        std::uniform_int_distribution<int> dist(0, i - 1);
        int parent = dist(rng);
        grafo.addEdge(parent, i);
    }

    // 2. Identify odd-degree vertices
    std::vector<int> oddVertices;
    for (int v = 0; v < nVertices; v++)
    {
        if (grafo.grau(v) % 2 != 0)
        {
            oddVertices.push_back(v);
        }
    }

    // 3. Pair odd-degree vertices without duplicates
    std::shuffle(oddVertices.begin(), oddVertices.end(), rng);

    size_t i = 0;
    while (i < oddVertices.size())
    {
        if (i + 1 >= oddVertices.size())
            break;

        int u = oddVertices[i];
        bool found_non_adjacent = false;

        // Search for a non-adjacent vertex starting from i+2
        for (size_t j = i + 1; j < oddVertices.size(); ++j)
        {
            int candidate = oddVertices[j];
            if (!grafo.hasEdge(u, candidate))
            {
                std::swap(oddVertices[i + 1], oddVertices[j]);
                found_non_adjacent = true;
                break;
            }
        }

        int v = oddVertices[i + 1];
        if (!grafo.hasEdge(u, v))
        {
            grafo.addEdge(u, v);
        }
        else
        {
            // Fallback: Allow duplicate edge only if no other option
            grafo.removeEdge(u, v);
        }

        i += 2;
    }

    return grafo;
}

Grafo gerarGrafoCiclo(int numVertices)
{

    Grafo grafo(numVertices);
    for (int i = 0; i < numVertices - 1; i++)
    {
        grafo.addEdge(i, i + 1);
    }

    grafo.addEdge(numVertices - 1, 0);
    return grafo;
}

int main()
{

    int qntd_vertices = 100000;
    Grafo grafoOriginal = gerarGrafoEulerianoAleatorio(qntd_vertices);
    cout << endl;

    cout << "Grafo com " << qntd_vertices << " vertices" << endl;
    Algoritmos algoritmos;

    if (!grafoOriginal.isEuleriano())
    {
        cout << "Grafo Não Euleriano" << endl;
        return 0;
    }

    cout << "Grafo Euleriano" << endl;

    Grafo grafoTarjan = grafoOriginal;

    auto inicioTarjan = high_resolution_clock::now();
    vector<int> caminhoTarjan = algoritmos.fleuryTarjan(grafoTarjan);
    // cout << "Caminho Euleriano (Fleury-Tarjan): ";
    // for (int v : caminhoTarjan)
    //     cout << v << " ";
    // cout << endl;
    auto fimTarjan = high_resolution_clock::now();
    auto duracaoTarjan = duration_cast<microseconds>(fimTarjan - inicioTarjan);
    cout << "Tempo de execucao Fleury-Tarjan: " << duracaoTarjan.count() << " microsegundos" << endl;
    cout << endl;

    Grafo grafoNaive = grafoOriginal;

    auto inicioNaive = high_resolution_clock::now();
    vector<int> caminhoNaive = algoritmos.fleury(grafoNaive);
    // cout << "Caminho Euleriano (Fleury-Naive): ";
    // for (int v : caminhoNaive)
    //     cout << v << " ";
    // cout << endl;
    auto fimNaive = high_resolution_clock::now();
    auto duracaoNaive = duration_cast<microseconds>(fimNaive - inicioNaive);
    cout << "Tempo de execucao Fleury-Naive: " << duracaoNaive.count() << " microsegundos" << endl;
    cout << endl;

    return 0;
}
