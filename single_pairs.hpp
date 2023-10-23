//---------------------------------------------------------------------
// Arquivo	: single_pairs.hpp
// Conteudo	: Definição da classe auxiliar single pairs
// Autor	: Ana Lúcia Oliveira de Paula (analop@ufmg.br)
// Historico	: 2023-04-28 - arquivo criado
//---------------------------------------------------------------------
#ifndef SINGLE_PAIRS_HPP
#define SINGLE_PAIRS_HPP

#include <iostream>
#include <list>
#include <algorithm>
#include <deque>
#include <bits/stdc++.h>
#include "graph.hpp"

using namespace std;

struct list_size {
    unsigned long int size;
    int ID;
};

class Single_Pairs : public Graph {
    public:
        Single_Pairs(int num_users, int num_jobs);
        ~Single_Pairs();
        void greedy_algorithm() override;
        void exact_algorithm() override;

        bool bfs(int v_id);


    private:
        vector<int> colorsOfNodes; //utilizado no guloso para detecção de emparelhamentos
        vector<int> bfs_array; //utilizado no exato, vetor resultante da bfs
        vector<int> married; //utilizado no exato, vetor que registra os emparelhamentos
        deque<int> aux_queue; //utilizado no exato, fila auxiliar
        vector<bool> visited; //utilizado no exato, array para marcar um vertice como ja visitado em uma bfs
};

#endif // SINGLE_PAIRS_HPP