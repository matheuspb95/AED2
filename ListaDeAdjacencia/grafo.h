#include<iostream>
#include<vector>
#define INF 100100

using namespace std;


class Grafo
{   
private:
    int V;
    vector<vector<int>> adj;
	bool digrafo;
	
	void printSolution(int distancia[], int predecessor[]);
	int distanciaMin(int distancia[], bool visitado[]);

public:
    //Cria grafo
    Grafo(int V, bool digrafo);

    void adicionarAresta(int v1, int v2);  
    bool removerAresta(int v1, int v2);    
    void adicionarVertice();
    void removerVertice(int v);
    int obterGrauDeSaida(int v);
    int obterGrauDeEntrada(int v);
    void buscaProfudindadeAux(int v, bool visitado[]);
    void buscaProfudindade(int v);
    int buscaLargura(int v);
    void imprimirLista();

	void dijkstra(int origem);
	void bellmanFord(int origem);

};
