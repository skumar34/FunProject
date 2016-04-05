#include <iostream>
#include <fstream>

using namespace std;

//Undirected graph
class Graph
{
private:
	unsigned int E;
	unsigned int V;
struct Graph_node{ 						// Denotes a node/vertex of the graph
	int vertex;
	Graph_node *next;
	};
Graph_node *adj; 						// Array for adjacency list

public:
	Graph()
	{
		E = 0;
		V = 0;
	}
	
	Graph(int V)      //Create a V vertex graph with no edges
	{

		/////////////Memory Allocation for Adjacency List////////////

		adj = (Graph_node *) new Graph_node[V];

		for(int i = 0; i < V; i++)
		{
			adj[i].vertex = i;
			adj[i].next = NULL;
		}

		/////////////////////////////////////////////////////

	}
	
	Graph(char *file)   //Read a graph from input stream
	{
		ifstream In;
		In.open(file);
		E = 0;
		V = 0;
		if(!In.is_open())
		{
			cout<< "Unable to open the input file";
			return;
		}
		
		In >> V;
		Graph(V);
		In >> E;
		for(int i = 0; i < E; i++)
		{
			int v,w;
			In >> v >> w;
			addEdge(v,w);
		}
		
	}

	int Vertices()					//Return number of vertices
	{
		return V;
	}

	int Edges()                 //Returns number of Edges
	{
		return E;
	}

	void printGraph()
	{
		for(int i = 0; i < V; i++)
		{
			cout << "\n"<< adj[i].vertex << "==>";

			if(adj[i].next != NULL)
			{
				Graph_node *temp;
				temp = adj[i].next;
				do{
					cout << temp->vertex << "-->";
					temp = temp->next;
				}while(temp);
			}
			
		}
	}
	
	void addEdge(int v, int w); 	   //Add edge v-w in the graph

	~Graph()
	{
		for(int i = 0; i < V; i++)			//Free Each and every node
		{
			if(adj[i].next != NULL)
			{
				Graph_node *temp1,*temp2;
				temp1 = adj[i].next;
				while(temp1){
					temp2 = temp1->next;
					delete temp1;
					temp1 = temp2;
				}
			}
			
		}
		if(V != 0)
			delete[] adj;						//Frees the memory allocated to graph
		adj = NULL;
	}
};

void Graph::addEdge(int v,int w)
{
	Graph_node *N1, *N2, *temp;
	N1 = new Graph_node;
	N1->vertex = w;
	N2->vertex = v;

	temp = adj[v].next;
	adj[v].next = N1;
	N1->next = temp;

	temp = adj[w].next;
	adj[w].next = N2;
	N2->next = temp;
}

int main()
{

	Graph ob1("test_input.txt");
	ob1.printGraph();
	
return 0;
}