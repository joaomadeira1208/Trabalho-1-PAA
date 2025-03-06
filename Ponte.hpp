#ifndef PONTE_HPP
#define PONTE_HPP

#include <iostream>
#include "Grafo.hpp"
#include <vector>
#include <utility>

using namespace std;

class Ponte
{
public:
    Ponte() {};

    vector<pair<int, int>> naive(Grafo &grafo);
    vector<pair<int, int>> tarjan(Grafo &grafo);
    void dfs(int u, int pai, Grafo &grafo, vector<bool> &visitado, vector<int> &tin, vector<int> &low, int &tempo, vector<pair<int, int>> &pontes);
};

#endif
