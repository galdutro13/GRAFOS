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

void busca2lar(std::vector<GRAFO>& grafo, int i) {
    std::queue<int> fila;
    int j = 0;
    grafo[i].flag = 1;

    fila.push(i);

    while(fila.front() && !fila.empty()) {
        i = fila.front();
        fila.pop();

        NO* p = grafo[i].inicio;
        while(p) {
            if(grafo[p->adj].flag == 0) {
                grafo[p->adj].flag = 1;
                grafo[p->adj].via = j;
                fila.push(p->adj);
            }
            p = p->prox;
        }
        j++;
        grafo[i].flag = 2;
    }
}

int main() {
    tamanho = 15;

    std::vector<GRAFO> grafo = init2grafo();

    insert2grafo(grafo, 1, 5);
    insert2grafo(grafo, 2, 1);
    insert2grafo(grafo, 2, 14);
    insert2grafo(grafo, 2, 5);
    insert2grafo(grafo, 3, 11);
    insert2grafo(grafo, 3, 12);
    insert2grafo(grafo, 3, 5);
    insert2grafo(grafo, 3, 7);
    insert2grafo(grafo, 4, 2);
    insert2grafo(grafo, 4, 1);
    insert2grafo(grafo, 4, 12);
    insert2grafo(grafo, 5, 13);
    insert2grafo(grafo, 6, 1);
    insert2grafo(grafo, 7, 13);
    insert2grafo(grafo, 7, 11);
    insert2grafo(grafo, 7, 6);
    insert2grafo(grafo, 7, 4);
    insert2grafo(grafo, 8, 12);
    insert2grafo(grafo, 8, 4);
    insert2grafo(grafo, 9, 3);
    insert2grafo(grafo, 9, 2);
    insert2grafo(grafo, 9, 1);
    insert2grafo(grafo, 10, 3);
    insert2grafo(grafo, 11, 6);
    insert2grafo(grafo, 11, 13);
    insert2grafo(grafo, 12, 8);
    insert2grafo(grafo, 12, 11);
    insert2grafo(grafo, 12, 2);
    insert2grafo(grafo, 12, 1);
    insert2grafo(grafo, 12, 9);
    insert2grafo(grafo, 12, 10);
    insert2grafo(grafo, 12, 5);
    insert2grafo(grafo, 13, 7);
    insert2grafo(grafo, 13, 2);
    insert2grafo(grafo, 13, 9);
    insert2grafo(grafo, 13, 6);
    insert2grafo(grafo, 14, 6);
    insert2grafo(grafo, 14, 13);
    insert2grafo(grafo, 14, 9);
    insert2grafo(grafo, 14, 5);

    int count = 0;
    busca2prof(grafo, 3, &count);

    zera2flag(grafo);

    busca2lar(grafo, 3);

    return 0;
}