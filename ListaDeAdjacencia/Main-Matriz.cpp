#include"grafo.h"

using namespace std;

int main() {
    Grafo grafo(4, false);

    grafo.adicionarAresta(0, 1);
    grafo.adicionarAresta(0, 2);
    grafo.adicionarAresta(1, 2);
    grafo.adicionarAresta(2, 0);
    grafo.adicionarAresta(2, 3);
    grafo.adicionarAresta(3, 3);

    grafo.imprimirLista();
    grafo.dijkstra(0);

    return 0;
}