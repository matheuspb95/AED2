#include<iostream>
#include<vector>
#define INF 100100

using namespace std;

class Aresta {
public:
	int origem;
	int destino;
	int peso;
};

class Grafo {
private:
	int V; //qtd de vertices
	int A = 0; //qtd de arestas
	vector< vector<int> > adj;
	bool digrafo;

	vector<Aresta> arestas;
	vector<int> vertices;

	void auxResizeVertice();
	void printSolution(int distancia[], int predecessor[]);
	int distanciaMin(int distancia[], bool visitado[]);
	void dfsUtil(int v, bool visitado[]);

public:
	Grafo(int V, bool digrafo = false);

	void adicionarVertice();
	void removerVertice(int v);

	void adicionarAresta(int v1, int v2, int peso = 1);
	void removerAresta(int v1, int v2);
	
	int obterGrau(int v);
	void printMatriz();
	void printVertices();
	void printArestas();
	void printAll();


	void buscaProfudindade(int v);
	void buscaLargura(int v);
	void dijkstra(int origem);
	void bellmanFord(int origem);
};