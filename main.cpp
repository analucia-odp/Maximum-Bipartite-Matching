#include <iostream>
#include <string>
#include <map>
#include <time.h>

#include "graph.hpp"
#include "single_pairs.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
    
    int numberOfUsers;
    int numberOfJobs;
    int numberOfEdges;

    string user;
    string job;

    map<string, int> vertex; //faz o mapeamento dos vértices

    try{
        cin >> numberOfUsers;
        if (numberOfUsers > 10000 || numberOfUsers < 2)
            throw "Número de usuários inválido!";
        cin >> numberOfJobs;
        if (numberOfJobs > 10000 || numberOfJobs < 1)
            throw "Número de vagas inválido!";
        cin >> numberOfEdges;
        if (numberOfEdges > (numberOfJobs * numberOfUsers) || numberOfEdges < 1)
            throw "Número de qualificações inválido!";
    }catch(char* msg){
        cout << msg << endl;
    }

    int users_position = 0; //a primeira partição [0...numero de usuarios-1] irá conter os vértices usuários
    int jobs_position = numberOfUsers; //a segunda partição [numero de usuarios ... numero de usuarios + numero de vagas - 1] irá contér os vértices vagas

    Graph * graph = new Single_Pairs(numberOfUsers, numberOfJobs);
    // clock_t inicio, fim;
    // double total;
    // inicio = clock();
    
    while (cin >> user){
        
        auto it_users = vertex.find(user);

        if (it_users == vertex.end()){ //nao achou o elemento
            vertex.insert({user, users_position});
            it_users = vertex.find(user);
            users_position++;
        }

        cin >> job;

        auto it_jobs = vertex.find(job);

        if (it_jobs == vertex.end()){
            vertex.insert({job, jobs_position});
            it_jobs = vertex.find(job);
            jobs_position++;
        }

        graph->insertEdge(it_users->first, it_users->second, it_jobs->first, it_jobs->second); //insiro nova aresta mapeada

    }

    graph->greedy_algorithm();
    graph->exact_algorithm();
    
    // fim = clock();
    // total = ((fim - inicio) / (double)CLOCKS_PER_SEC);

    // cout << "Time execution: " << total << endl;
    vertex.clear();
    delete graph;

    return 0;
}
