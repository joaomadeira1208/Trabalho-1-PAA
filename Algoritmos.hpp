#ifndef ALGORITMOS_HPP
#define ALGORITMOS_HPP

#include <iostream>
#include "Grafo.hpp"
#include <vector>
#include <utility>

using namespace std;

class Algoritmos
{
public:
    Algoritmos() {};

    bool naive(Grafo &grafo, int u, int v);
    vector<pair<int, int>> tarjan(Grafo &grafo);
    void dfsTarjan(int u, int pai, Grafo &grafo, vector<bool> &visitado, vector<int> &tin, vector<int> &low, int &tempo, vector<pair<int, int>> &pontes);
    vector<int> fleury(Grafo &grafo);
};

#endif
