#include"grafo.h"

Grafo::Grafo(int V, bool digrafo){
	this->V = V;
	this->digrafo = digrafo;

	adj.resize(V);
	vertices.resize(V);

	this->auxResizeVertice();
}

void Grafo::adicionarVertice(){
	V++;
	adj.resize(V);
	vertices.resize(V);

	this->auxResizeVertice();
}

void Grafo::removerVertice(int v){
	if(v < V){
		V--;
		for(int i = 0; i < V; i++){
			vector<int>::iterator it = adj[i].begin() + v;
			adj[i].erase(it);
		}

		for(int i = 0; i < A; i++){
			if(arestas[i].origem == v || arestas[i].destino == v){
				vector<Aresta>::iterator it = arestas.begin() + i;
				arestas.erase(it);
			}
		}

		vector<vector<int>>::iterator it = adj.begin() + v;
		adj.erase(it);

		vector<int>::iterator it2 = vertices.begin() + v;
		vertices.erase(it2);
	}
	else{
		cout << "Vertice nao existe";
	}
}

void Grafo::adicionarAresta(int v1, int v2, int peso) {
	A++;
	arestas.resize(A);

	int i = A - 1;
	arestas[i].origem = v1;
	arestas[i].destino = v2;
	arestas[i].peso = peso;

	if(this->digrafo){
		adj[v1][v2]+=peso;
	}
	else{
		adj[v1][v2]+=peso;
		adj[v2][v1]+=peso;
	}
}

void Grafo::removerAresta(int v1, int v2){
	A--;

	for(int i = 0; i < A; i++){
		if(arestas[i].origem == v1 && arestas[i].destino == v2){
			vector<Aresta>::iterator it = arestas.begin() + i;
			arestas.erase(it);
		}
	}

	if(this->digrafo){
		if(adj[v1][v2] != 0){
			adj[v1][v2]--;
		}
		else{
			cout << "\nErro! Aresta nao existe.\n";
		}
	}
	else{
		if(adj[v1][v2] != 0){
			adj[v1][v2]--;
			adj[v2][v1]--;
		}
		else{
			cout << "\nErro! Aresta nao existe.\n";
		}
	}
}

int Grafo::obterGrau(int v) {
	int grau = 0;
	for(int i = 0; i < V; i++){
		grau += adj[v][i];
	}
	return grau;
}

void Grafo::printMatriz(){
	cout << "Matriz de Adjacencia"<< endl;
	for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }
	cout << endl;
}

void Grafo::printVertices(){
	cout << "Vertices" << endl;
	for(int i = 0; i < V; i++){
		cout << vertices[i] << " ";
	}
	cout << endl << endl;
}

void Grafo::printArestas(){
	cout << "Arestas" << endl;
	for(int i = 0; i < A; i++){
		cout << arestas[i].origem << " --> " 
		<< arestas[i].destino << "\t peso: "
		<< arestas[i].peso << endl;
	}
	cout << endl;
}

void Grafo::printAll(){
	this->printMatriz();
	this->printVertices();
	this->printArestas();
}

void Grafo::buscaProfudindade(int v){
	bool visitados[V]; // vetor de visitados
 
	// marca todos como não visitados
	for(int i = 0; i < V; i++)
		visitados[i] = false;
 
	this->dfsUtil(v, visitados);
}

void Grafo::buscaLargura(int v){
    bool visitados[V];
    vector<int> fila;

    for(int i = 0; i < V; i++)
        visitados[i] = false;
  
    visitados[v] = true; 
    fila.push_back(v); 
  
    while(!fila.empty()){ 
        v = fila.front(); 
        cout << v << " ";
		vector<int>::iterator it = fila.begin();
        fila.erase(it); 
  
		for(int i = 0; i < V; i++){
			if(adj[v][i] != 0){
				if (!visitados[i]){
					visitados[i] = true; 
					fila.push_back(i); 
				}
			}
		} 
    } 
}

void Grafo::bellmanFord(int origem){
	int distancia[V];
	int predecessor[V];

	for (int i = 0; i < V; i++){
        distancia[i] = INF;
		predecessor[i] = -1;
	}
    distancia[origem] = 0;

	for (int i = 1; i <= V - 1; i++) { 
        for (int j = 0; j < A; j++){
            int u = arestas[j].origem;
            int v = arestas[j].destino;
            int peso = arestas[j].peso;

            if (distancia[u] != INF && distancia[u] + peso < distancia[v]) 
                distancia[v] = distancia[u] + peso;
				predecessor[v] = u;
        }
    }

	for (int i = 0; i < A; i++) { 
        int u = arestas[i].origem;
        int v = arestas[i].destino;
        int peso = arestas[i].peso;

        if (distancia[u] != INF && distancia[u] + peso < distancia[v]){ 
            printf("Grafo tem ciclo negativo"); 
            return;
        } 
    }


	cout << "BellmanFord" << endl;
	this->printSolution(distancia, predecessor);
	

}

void Grafo::dijkstra(int origem){
	int distancia[V];
	int predecessor[V];
	bool visitados[V]; 

	for (int i = 0; i < V; i++){
        distancia[i] = INF;
		predecessor[i] = -1;
		visitados[i] = false;
	}
    distancia[origem] = 0;

	for (int count = 0; count < V - 1; count++) { 
        int u = this->distanciaMin(distancia, visitados); 
  
        visitados[u] = true; 
  
        for (int v = 0; v < V; v++) 
            if (!visitados[v] && adj[u][v] && distancia[u] != INF
                && distancia[u] + adj[u][v] < distancia[v]){

                distancia[v] = distancia[u] + adj[u][v];
				predecessor[v] = u;
			}
    }

	cout << "Dijkstra" << endl;
	this->printSolution(distancia, predecessor);

}

void Grafo::auxResizeVertice(){
	for(int i = 0; i < V; i++){
        adj[i].resize(V);
		vertices[i] = i;
    }
}

void Grafo::printSolution(int distancia[], int predecessor[]){
	cout << "Vertice   Distancia da origem	Predecessor\n" << endl; 
    for (int i = 0; i < V; ++i){
        cout << i << " \t\t " << distancia[i] << " \t\t " << predecessor[i] << endl; 
	}
	cout << endl;
}

int Grafo::distanciaMin(int distancia[], bool visitado[]){
	int min = INF;
	int minIndex; 
  
    for (int v = 0; v < V; v++){
        if (visitado[v] == false && distancia[v] <= min){
            min = distancia[v];
			minIndex = v;
		}
	}
	
	return minIndex;
}

void Grafo::dfsUtil(int v, bool visitados[]){
    visitados[v] = true; 
    cout << v << " "; 
  
	for(int i = 0; i < V; i++){
		if(adj[v][i] != 0){
			if (!visitados[i]){
            	dfsUtil(i, visitados);
			}
		}
	}
}



void Grafo::prim(int origem){
    vector<Aresta> franja;
	vector<int> mst;
	mst.push_back(origem);
	int orig = origem;
	int custo = 0;
	cout << "Prim";
	while(mst.size() < adj.size()){
		int peso = INF;
		int selected = orig;
		for(uint i = 0; i < arestas.size(); i++){
			if(arestas[i].origem == orig){
				franja.push_back(arestas[i]);
				if(arestas[i].peso < peso){
					peso = arestas[i].peso;
					selected = i;
				}
			}
		}
		for(uint i = 0; i < franja.size(); i++){
			cout << "Franja: ";
			cout << franja[i].origem << "-" << franja[i].destino << "/";
		}
		for(uint i = 0; i < franja.size();){
			if(franja[i].destino == selected){
				franja.erase(franja.begin() + i);
			}else{
				i++;
			}
		}
		custo += franja[selected].peso;
		mst.push_back(selected);
		franja.erase(franja.begin() + selected);
		orig = selected; 
	}
	cout  << "mst gerada pelo prim:"<<endl;
	for(uint i = 0; i < mst.size(); i++){
		cout << mst[i] << "-";
	}
	cout << "custo: " << custo;
}

int main() {
    Grafo grafo(8, false);
	
    grafo.adicionarAresta(5, 4, 35);
    grafo.adicionarAresta(7, 4, 37);
    grafo.adicionarAresta(7, 5, 28);
    grafo.adicionarAresta(0, 7, 16);
    grafo.adicionarAresta(1, 5, 32);
    grafo.adicionarAresta(0, 4, 38);
    grafo.adicionarAresta(2, 3, 17);
    grafo.adicionarAresta(7, 1, 19);
    grafo.adicionarAresta(0, 2, 26);
    grafo.adicionarAresta(1, 2, 36);
    grafo.adicionarAresta(1, 3, 29);
    grafo.adicionarAresta(7, 2, 34);
    grafo.adicionarAresta(2, 6, 40);
    grafo.adicionarAresta(3, 6, 52);
    grafo.adicionarAresta(0, 6, 58);	
    grafo.adicionarAresta(6, 4, 93);

    grafo.prim(0);

    return 0;
}