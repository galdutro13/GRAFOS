#include <iostream>
#include <vector>
#include <queue>
#include "LateConst.h"

LateConstant<int> tamanho;

struct NO {
    int adj;
    NO* prox;
    int id;

    explicit NO() : adj(0), prox(nullptr), id(0) {}
    explicit NO(int adj2, NO* next) : adj(adj2), prox(next), id(0) {}
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

void zera2flag(std::vector<GRAFO> grafo) {
    for(auto& g : grafo) {
        g.flag = 0;
    }
}

NO* recursive2search(NO* busca, int objetivo) {
    if(busca->prox == nullptr)
        return nullptr;

    if(busca->prox->adj != objetivo) {
        return recursive2search(busca, objetivo);
    }

    //retorna o nó atual, e não o proximo, para facilitar as operações como deleção de aresta, etc.
    return busca;
}

void recursive2insert(NO* busca, NO* adjacencia) {
    if(busca->prox != nullptr) {
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

    if(grafo[inicio].inicio->prox != nullptr) {
        recursive2insert(grafo[inicio].inicio->prox, adjacencia);
        return;
    }

    grafo[inicio].inicio->prox = adjacencia;
}

void delete2aresta(std::vector<GRAFO>& grafo, int inicio, int aresta) {
    NO* busca = grafo[inicio].inicio;

    NO* resultado = recursive2search(busca, aresta);

    if(resultado != nullptr) {
        if(resultado->prox->prox != nullptr) {
            NO* prox = resultado->prox->prox;
            delete resultado->prox;
            resultado->prox = prox;
        } else {
            delete resultado->prox;
            resultado->prox = nullptr;
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
            grafo[p->adj].inicio->id = 777;
            busca2prof(grafo, p->adj, count);
        }
        p = p->prox;
    }
    grafo[i].flag = 2;
    (*count)++;

}

void busca2lar(std::vector<GRAFO>& grafo, int i) {
    std::queue<int> fila;
    grafo[i].flag = 1;

    fila.push(i);

    while(fila.front() && !fila.empty()) {
        i = fila.front();
        fila.pop();

        NO* p = grafo[i].inicio;
        while(p) {
            if(grafo[p->adj].flag == 0) {
                grafo[p->adj].flag = 1;
                fila.push(p->adj);
            }
            p = p->prox;
        }

        grafo[i].flag = 2;
    }
}

NO* find_suspeito(std::vector<GRAFO> grafo, int codspam) {
    std::vector<int> nos_afetados(tamanho + 1);
    std::queue<NO> nos_suspeitos;

    for(int i = 1; auto& g : grafo) {
        if(g.inicio->id == 777)
             nos_afetados[i] = g.inicio->adj;
        i++;
    }

    for (int i = 1; auto& g : grafo) {
        if(g.inicio->id == 0) {

            int valadj = g.inicio->adj;
        }
    }

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

    busca2lar(grafo, 3);
    find_suspeito(grafo, 0);

    return 0;
}