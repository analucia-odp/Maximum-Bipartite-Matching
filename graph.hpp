//---------------------------------------------------------------------
// Arquivo	: graph.hpp
// Conteudo	: Definição da classe grafo
// Autor	: Ana Lúcia Oliveira de Paula (analop@ufmg.br)
// Historico	: 2023-04-28 - arquivo criado
//---------------------------------------------------------------------
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>

#define INF 0x3f3f3f3f

#define WHITE 0
#define BLACK 1

using namespace std;

struct node{
    string name;
    int ID;
};

class Graph {
    public:
        Graph(int num_users, int num_job);
        virtual ~Graph();

        void insertEdge(string v1, int pos_v1, string v2, int pos_v2);

        virtual void greedy_algorithm(){};
        virtual void exact_algorithm(){};

    protected:
        vector<node> *graphs;
        int numberOfUsers;
        int numberOfJobs;
        int numberOfVertex;
        int amountOfPairs;
};

#endif // GRAPH_HPP