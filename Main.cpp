#include "Grafo.hpp"
#include "Algoritmos.hpp"
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

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

    int qntd_vertices = 1000;
    Grafo grafoOriginal = gerarGrafoCiclo(qntd_vertices); // ciclo com n vertices

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
