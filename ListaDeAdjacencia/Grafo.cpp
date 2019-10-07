//Grafos - Lista de adjacência
#include"grafo.h"

//Criar Grafos
Grafo::Grafo(int V, bool digrafo)
{
    this->V = V;
    this->digrafo = digrafo;
    adj.resize(V);

}

//Adicionar aresta
void Grafo::adicionarAresta(int v1, int v2)
{
    //adiciona vértice v2 a lista de vertices adjacentes de v1
    adj[v1].push_back(v2);
    if(!digrafo)
        adj[v2].push_back(v1);
}

//Remover aresta
bool Grafo::removerAresta(int v1, int v2)
{
    vector <int> :: iterator vertAdj;
    int c = 0;   
    for(vertAdj = adj[v1].begin(); vertAdj < adj[v1].end(); vertAdj++){
        if(*vertAdj == v2){
            adj[v1].erase(adj[v1].begin() + c);
        }
        c++;
    }
    if(!digrafo){
        c = 0;
        for(vertAdj = adj[v2].begin(); vertAdj < adj[v2].end(); vertAdj++){
            if(*vertAdj == v1){
                adj[v2].erase(adj[v2].begin() + c);
            }
            c++;
        }
    }
    cout << "\n";
}

void Grafo::adicionarVertice(){
    ++V;
    adj.resize(V);
}

//Remover vertice
void Grafo::removerVertice(int v){
    adj.erase(adj.begin() + v);
    V--;
    adj.resize(V);
    
    vector <int> :: iterator vertAdj;
    int c = 0;
    
    for(int i = 0; i < V; i++){
        for(vertAdj = adj[i].begin(); vertAdj < adj[i].end(); vertAdj++){
            if(*vertAdj == v){
                adj[i].erase(adj[i].begin() + c);
            }
            c++;
        }
        c = 0;
    }
}

//Obter Grau de um vértice v
int Grafo::obterGrauDeSaida(int v)
{
    //basta retonar o tamanho da lista
    return adj[v].size();
    
}

int Grafo::obterGrauDeEntrada(int v)
{
    return adj[v].size();

    vector <int> :: iterator vertAdj;
    int c = 0;
    int grau = 0;
    for(int i = 0; i < V; i++){
        for(vertAdj = adj[i].begin(); vertAdj < adj[i].end(); vertAdj++){
            if(i = v){
                break;
            }
            if(*vertAdj == v){
                grau++;
            }
            c++;
        }
        c = 0;
    }
    return grau;
    
}

void Grafo::buscaProfudindadeAux(int v, bool visitado[])
{
    //Marca o vertice como visitado e o imprime
    visitado[v] = true;
    cout << v << " ";
    vector<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); i++){
        if(!visitado[*i]){
            buscaProfudindadeAux(*i, visitado);
        }
    }

}

void Grafo::buscaProfudindade(int v) 
{
    bool *visitado = new bool[V];
    for(int i = 0; i < V; i++){
        visitado[i] = false;
    }
    buscaProfudindadeAux(v, visitado);
}



int Grafo::buscaLargura(int busca)
{
    vector<int> fila;
    vector<int> caminho;
    int atual = 0;
    fila.push_back(atual);
    while(atual != busca){
        for(vector <int> :: iterator it = adj[atual].begin(); it != adj[atual].end(); it++){
            bool achou = false;
            for(vector <int> :: iterator it2 = caminho.begin(); it2 != caminho.end(); it2++){
                if(*it2 == atual){
                    achou = true;
                }        
            }
            if(!achou){
                fila.push_back(*it);
            }
        }
        caminho.push_back(atual);

        fila.erase(fila.begin());

        atual = fila[0];
        if(caminho.size() == V){
            cout << "Elemento não econtrado";
            return -1;
        }
    
    }
    cout << "Elemento encontrado: "<< atual << endl;
    cout << "Caminho: ";

    for(vector <int> :: iterator it = caminho.begin(); it != caminho.end(); it++){
        cout << *it << ",";
    }
    return atual;
}

void Grafo::dijkstra(int origem)
{
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

        vector <int> :: iterator vertAdj;
        for(vertAdj = adj[u].begin(); vertAdj < adj[u].end(); vertAdj++){
            if(!visitados[*vertAdj] && distancia[u] != INF
                 && distancia[u] + *vertAdj < distancia[*vertAdj]){
                     distancia[*vertAdj] = distancia[u] + *vertAdj;
				    predecessor[*vertAdj] = u;
            }
        } 
    }

	cout << "Dijkstra" << endl;
	this->printSolution(distancia, predecessor);
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



//imprime Lista
void Grafo::imprimirLista()
{
    vector <int> :: iterator vertAdj;

    for(int i = 0; i < V; i++){
        cout << "Vertice " << i << ": ";
        for(vertAdj = adj[i].begin(); vertAdj < adj[i].end(); vertAdj++){
            cout << *vertAdj << " ";
        }
        cout << "\n";
    }
  
}
