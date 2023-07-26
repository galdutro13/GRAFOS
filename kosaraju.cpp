#include <iostream>
#include <vector>
#include <queue>
#include "LateConst.h"

LateConstant<int> tamanho;

struct NO {
    int adj;
    NO* prox;

    explicit NO(int adj2, NO* next) : adj(adj2), prox(next) {}
};

struct GRAFO {
    int flag;
    int via;
    int distancia;
    NO* inicio;

    //construtor para utiliza-lo no std::vetor
    explicit GRAFO() : flag(0), via(0), distancia(0), inicio(nullptr) {}

    //construtor para instanciar um GRAFO com início de valor i.
    explicit GRAFO(int i, int flag_value = 0, int via_value = 0, int distancia_value = 0)
            : flag(flag_value), via(via_value), distancia(distancia_value), inicio(nullptr) {
    }

};

std::vector<GRAFO> init2grafo() {
    std::vector<GRAFO> grafo(tamanho + 1);
    for(int i = 0; auto& g : grafo) {
        g = GRAFO(i);
        i++;
    }
    return grafo;
}

void zera2flag(std::vector<GRAFO>& grafo) {
    for(auto& g : grafo) {
        g.flag = 0;
    }
}

void reset2metadata(std::vector<GRAFO>& grafo) {
    for(auto& g : grafo) {
        g.flag = 0;
        g.via = 0;
        g.distancia = 0;
    }
}

NO* recursive2search(NO* busca, int objetivo) {

    if(busca->adj != objetivo && busca->prox == nullptr) {
        return recursive2search(busca->prox, objetivo);
    }

    //retorna o nó atual, e não o proximo, para facilitar as operações como deleção de aresta, etc.
    return busca;
}

void recursive2insert(NO* busca, NO* adjacencia) {
    if(busca->prox != nullptr && busca->prox->adj < tamanho + 1) {
        recursive2insert(busca->prox, adjacencia);
        return;
    }
    busca->prox = adjacencia;
}

void insert2grafo(std::vector<GRAFO>& grafo, int inicio, int aresta) {
    NO* adjacencia = new NO(aresta, nullptr);

    if(grafo[inicio].inicio == nullptr) {
        grafo[inicio].inicio = adjacencia;
        return;
    }

    if(grafo[inicio].inicio->prox != nullptr &&
       grafo[inicio].inicio->adj < tamanho + 1) {

        recursive2insert(grafo[inicio].inicio->prox, adjacencia);
        return;
    }

    grafo[inicio].inicio->prox = adjacencia;
}

void delete2aresta(std::vector<GRAFO>& grafo, int inicio, int aresta) {
    NO* busca = grafo[inicio].inicio;

    NO* resultado = recursive2search(busca, aresta);

    if(resultado != nullptr) {
        if(resultado->prox != nullptr) {
            int prox = resultado->prox->adj;
            delete resultado;

            insert2grafo(grafo, inicio, prox);
        } else {
            delete resultado;
            grafo[inicio].inicio = nullptr;
        }
    }
}

bool existe2aresta(std::vector<GRAFO>& grafo, int inicio, int aresta) {
    NO* busca = grafo[inicio].inicio;
    if(recursive2search(busca, aresta) == nullptr)
        return false;
    else return true;
}

void busca2prof(std::vector<GRAFO>& grafo, int i, int* count) {
    grafo[i].flag = 1;

    NO* p = grafo[i].inicio;
    while(p) {
        if (grafo[p->adj].flag == 0) {
            busca2prof(grafo, p->adj, count);
        }
        p = p->prox;
    }
    grafo[i].flag = 2;
    (*count)++;

}

std::vector<GRAFO> transposta(std::vector<GRAFO>& grafo) {
    std::vector<GRAFO> transposta = init2grafo();

    for (int n = 0; auto& g : grafo) {
        NO* adj = g.inicio;
        while (adj) {
            if (existe2aresta(grafo, n,adj->adj))
                insert2grafo(transposta, adj->adj, n);
            adj = adj->prox;
        }
        n++;
    }
    return transposta;
}

void DFS1(std::vector<GRAFO>& grafo, int v, int& count) {
    grafo[v].flag = 1;

    NO* p = grafo[v].inicio;
    while(p) {
        if (grafo[p->adj].flag == 0) {
            DFS1(grafo, p->adj, count);
        }
        p = p->prox;
    }

    grafo[count++].via = v;
}


void DFS2(std::vector<GRAFO>& grafo, std::vector<int>& componente, int v, int& comp_index) {
    grafo[v].flag = 1;
    componente[v] = comp_index;

    NO* p = grafo[v].inicio;
    while(p) {
        if (grafo[p->adj].flag == 0) {
            DFS2(grafo, componente, p->adj, comp_index);
        }
        p = p->prox;
    }
}

std::vector<int> Kosaraju(std::vector<GRAFO>& grafo) {
    reset2metadata(grafo);
    int index = 0;

    for(int i = 1; auto& g : grafo) {
        if (g.flag == 0)
            DFS1(grafo, i, index);
        i++;
    }

    std::vector<GRAFO> transp = transposta(grafo);

    int comp_index = 1;
    std::vector<int> componentes(tamanho+1);

    while(index > 0) {
        int v = grafo[--index].via;
        if(transp[v].flag == 0) {
            DFS2(transp, componentes, v, comp_index);
            comp_index++;
        }
    }

    return componentes;
}

int main() {
    tamanho = 5;

    std::vector<GRAFO> grafo = init2grafo();

    insert2grafo(grafo, 2, 5);
    delete2aresta(grafo, 2, 5);

    insert2grafo(grafo, 2, 5);
    insert2grafo(grafo, 3, 2);
    insert2grafo(grafo, 3, 5);

    int count = 0;
    busca2prof(grafo, 3, &count);

    zera2flag(grafo);

    std::vector<GRAFO> transp = transposta(grafo);

    return 0;
}