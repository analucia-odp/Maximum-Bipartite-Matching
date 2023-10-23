//---------------------------------------------------------------------
// Arquivo	: single_pairs.cpp
// Conteudo	: Implementação dos algoritmos: guloso e exato, para achar um emparelhamento máximo em um grafo bipartido
// Autor	: Ana Lúcia Oliveira de Paula (analop@ufmg.br)
// Historico	: 2023-04-28 - arquivo criado
//---------------------------------------------------------------------
#include "single_pairs.hpp"

Single_Pairs::Single_Pairs(int num_users, int num_jobs) : Graph(num_users, num_jobs)
{

    for (int i = 0; i < (num_jobs + num_users); i++)
    {
        colorsOfNodes.push_back(WHITE);
        married.push_back(INF);   // define todos não emparelhados
        bfs_array.push_back(-1);  // inicia o array bfs que contém os caminhos
        visited.push_back(false); // inicia todos como nao visitados
    }
}

void Single_Pairs::greedy_algorithm()
{
    vector<list_size> sort_by_list_size;
    for (int i = 0; i < numberOfUsers; i++)
    {
        sort_by_list_size.push_back(list_size{graphs[i].size(), i}); // faz uma lista, em cada posição tem o tamanho da lista daquele id referente a posição i
    }
    sort(sort_by_list_size.begin(), sort_by_list_size.end(), [](list_size &x, list_size &y)
         { return x.size < y.size; }); // ordena os usuários pelo tamanho de suas listas

    for (auto user : sort_by_list_size)
    {

        long unsigned int less = INF;
        int id_less = -1;

        for (auto it : graphs[user.ID])
        {
            if (colorsOfNodes[it.ID] == WHITE) // se ele estiver solteiro
            {

                if (graphs[it.ID].size() < less) // vejo qual vaga tem a menor lista
                {
                    less = graphs[it.ID].size();
                    id_less = it.ID;
                }
            }
        }

        if (less != INF) // se existir o candidato ideal
        {
            amountOfPairs++;
            colorsOfNodes[id_less] = BLACK; // faz o emparelhamento
            colorsOfNodes[user.ID] = BLACK;
        }
    }

    sort_by_list_size.clear();
    cout << "Guloso: " << amountOfPairs << endl;
}

bool Single_Pairs::bfs(int v_id)
{
    aux_queue.push_back(v_id);

    while (!aux_queue.empty())
    {
        int id = aux_queue.front();
        aux_queue.pop_front();

        for (auto it : graphs[id])
        {

            if (!visited[it.ID]) // caso o vertice nao tenha sido visitado
            {
                bfs_array[it.ID] = id; // ele nao esta emparelhado com outro, logo o vertice adjacente a ele é o id
                if (married[it.ID] == INF)
                { // encontrei um vertice solteiro no meu caminho (caminho de aumento)
                    int v_ref;
                    int pos_ref = it.ID; // desfaço todos os casamentos e os caso com os vertices solteiros

                    if (bfs_array[v_id] == -1)
                        bfs_array[v_id] = v_id;
                    while (true) // realizo as trocas durante o caminho
                    {
                        v_ref = bfs_array[pos_ref];
                        married[v_ref] = pos_ref;
                        married[pos_ref] = bfs_array[pos_ref];
                        pos_ref = bfs_array[v_ref];
                        if (pos_ref == v_ref) // cheguei no vertice de inicio
                            return true;
                    }
                }
                else
                {
                    aux_queue.push_back(married[it.ID]); // visito o usuario novamente para verificar se ainda existe um caminho de aumento
                    bfs_array[married[it.ID]] = it.ID;   // o vertice adjacente na bfs ao job é o usuario que esta casado com ele
                }
            }

            visited[it.ID] = true; // finalizo o vertice como visitado
        }
    }
    return false;
}

void Single_Pairs::exact_algorithm()
{
    amountOfPairs = 0;
    int find_augment_path = 1;
    while (find_augment_path) // enquanto houver um caminho de aumento
    {
        // //roda a bfs com todos os usuarios solteiros
        find_augment_path = 0;
        for (int i = 0; i < numberOfUsers; i++)
        {
            if (married[i] == INF)
            {
                if (bfs(i))
                { // achou um caminho de aumento, tenho que começar tudo dnv
                    aux_queue.clear();
                    fill(visited.begin() + numberOfUsers, visited.end(), false); // marco como falso os jobs para poder revisita-los
                    find_augment_path = 1;
                }
            }
        }
    }

    for (int i = 0; i < numberOfUsers; i++)
    {
        if (married[i] != INF) // pega todos os usuários casados
            amountOfPairs++;
    }

    cout << "Exato: " << amountOfPairs << endl;
}

Single_Pairs::~Single_Pairs()
{
    colorsOfNodes.clear();
    bfs_array.clear();
    married.clear();
    aux_queue.clear();
    visited.clear();
}