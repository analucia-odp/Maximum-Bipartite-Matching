//---------------------------------------------------------------------
// Arquivo	: graph.cpp
// Conteudo	: Implementação do grafo
// Autor	: Ana Lúcia Oliveira de Paula (analop@ufmg.br)
// Historico	: 2023-04-28 - arquivo criado
//---------------------------------------------------------------------
#include "graph.hpp"
#include <iostream>

using namespace std;

Graph::Graph(int num_users, int num_jobs)
{
    numberOfUsers = num_users; //dobro do número de vértices +2, pois começa a contagem da posição 2 do vetor
    numberOfJobs = num_jobs;
    numberOfVertex = num_users + num_jobs;
    graphs = new vector<node>[numberOfVertex];
    amountOfPairs = 0;
}

void Graph::insertEdge(string v1, int pos_v1, string v2, int pos_v2)
{
    graphs[pos_v1].push_back(node{v2,pos_v2});
    graphs[pos_v2].push_back(node{v1,pos_v1});
}

Graph::~Graph()
{
    for (int i = 0; i < numberOfVertex; i++)
    {
        graphs[i].clear();
    }
    delete[] graphs;
}
