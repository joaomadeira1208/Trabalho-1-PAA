#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class Grafo
{
private:
    int n;
    vector<list<int>> listaAdjacencia;

public:
    Grafo(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    int grau(int v);
    const vector<list<int>> &getListaAdjacencia();
    bool DFS(int v, int destino, vector<bool> &visitado);
    bool isConexo(int origem, int destino);
    bool isEuleriano();
    void print();
};

#endif