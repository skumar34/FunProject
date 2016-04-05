/*******************************************************************************************
********************************************************************************************
*******************Author : Sanjeev Kumar***************************************************
*******************Creation Date: 07. 10. 2013**********************************************
*************07.10.2013	 :1. Graph Represented in Adjacency list for*********************
*************07.10.2013	 :2. Calculte the Breadth First Search. void BFS(unsigned int)***
*************07.10.2013	 :3. Find the Depth First Search. void DFS(unsigned int)*********
*************08.10.2013	 :4. Find the bipartite group in the graph***********************
*************	 :	void BipartiteGroup();*************************************************
*******************************************************************************************/

#include<iostream>
#include<cstdio>

using namespace std;

#define __UNDIRECTED_GRAPH__ 0
#define __PRINT_ADDRESS__ 1
#define NO_COLOR 0
#define RED 1
#define BLUE 2
#define TRUE 1
#define FALSE 0

class GraphAlgo
{
private:

  int *E1,*E2,E,V; //Edge E1-->E2, E - no. of edges, V- no. of vertex in the graph.
  struct Graph_node{ // Denotes a node/vertex of the graph
    int vertex;
    Graph_node *next;
  };
  Graph_node *adj_list; // Array for adjacency list

  short int *color; // Maintains an array for making the two groups in the a graph i.e Bipartition
  bool *visited; //For keep track of the nodes which are already visited
  int count; //For counting the no. of vertices in a single connected component
  int *queue;	 //Required for implementing the queue data structure for tracking the to be traced nodes in BFS
  int front,last;	 //indexes used for implementing the queue
  bool bipartite_status;	 //Variable keeps the status if the the graph is bipartite or not.

  void enqueue(int);
  int dequeue();
  int* adjacent(int);	 //return the vertices adjacent to given vertex
  void CheckBipartition(unsigned int);	 // Check for bipartite graph in the given graph using modified BFS. Updates the result in bipartite_status variable.

public:
GraphAlgo(const char *input_file)
{
//Intialization of variables to default
  bipartite_status = TRUE;
  E = 0;
  V = 0;
  count = 0;
  front = -1;
  last = -1;
  E1 = NULL;
  E2 = NULL;
  adj_list = NULL;
  visited = NULL;
  queue = NULL;
  color = NULL;
//////////////////////////////////////

  freopen(input_file, "r", stdin);	 //Read the input file.
  cin>> V >> E;

//////////////////Memory Allocation////////////////////
  E1 = new int[E];
  E2 = new int[E];

  adj_list = new Graph_node[V];
  visited = new bool[V];
  queue = new int[V-1];
  color = new short int[V];
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
// Initialise the empty adjacency list and create a adjacency list using the
// the graph inputed
  for(int i =0; i < V; i++)
  {
    (adj_list+i)->vertex = i;
    (adj_list+i)->next = NULL;
    visited[i] = 0;
    color[i] = NO_COLOR;
  }

// representation of graph in adjacency list
  for(int i = 0; i < E; i++)
  {
    Graph_node *start,*node;

    cin >> E1[i] >> E2[i];

    cout <<E1[i]<<" "<<E2[i]<<" \n";

// Create a node from E1[i] to E1[i]
    start = (adj_list+E1[i]);
    node = new Graph_node;
    node->vertex = E2[i];
    node->next = NULL;

    while(start->next!=NULL)
      start = start->next;
    start->next = node;


//Since the graph is undirected. So created node from E2[i] to E1[i]
#if defined (__UNDIRECTED_GRAPH__)
/*    start = (adj_list+E2[i]);
    node = new Graph_node;
    node->vertex = E1[i];
    node->next = NULL;

    while(start->next!=NULL)
      start = start->next;
    start->next = node;*/
#endif
  }
/////////////////////////////////////////////////////
}

void print_adjlist();
void DFS(unsigned int);
void BFS(unsigned int);
unsigned int ConnectedComponents();
void BipartiteGroup();

~GraphAlgo()
{
  cout<<"Exiting the Graph";
  delete[] E1;
  delete[] E2;
  for(int i = 0; i < V; i++)
  {
    Graph_node *node2,*node = (adj_list+i);

    if(node->next!=NULL)
    node = node->next;

    do
    {
      node2 = node;
      node = node->next;

      delete node2;
    }while(node != NULL);
  }
  delete[] adj_list;
  delete[] visited;
  delete[] queue;
  delete[] color;
}
};

//Implementation of enqueue
void GraphAlgo::enqueue(int v)
{
  if(++front >= V)
    return;
  queue[front] = v;
}

//Implementation of dequeue
int GraphAlgo::dequeue()
{
  if(front == last)
    return -1;
  return queue[++last];
}

// Print the adjacency list
void GraphAlgo::print_adjlist()
{
  Graph_node *node;
  for(int i =0; i < V ; i++)
  {
    node = (adj_list+i);
    cout<<"|"<<node->vertex
        #if defined (__PRINT_ADDRESS__)
          //  <<"("<<node<<")"<<"|"
        #endif
        ;
    while(node->next!=NULL)
    {
      node = node->next;
      cout<<"-->"<<node->vertex
        #if defined (__PRINT_ADDRESS__)
          //  <<"("<<node<<")"
        #endif
        ;
    }
    cout<<"-->NULL"<<"\n";
  }
}

//Print the Depth first search of the given vertex.
void GraphAlgo::DFS(unsigned int v)
{
  if(v >= (unsigned int)V)
  {
    cout<<"\nThe requested vertex is not present in the graph\n";
    return;
  }
  if(!visited[v])
  {
    count++;
    visited[v] = 1;
  }
  Graph_node *node = (adj_list+v);
  cout <<" "<<v<<" ";
  node = node->next;
  while(node != NULL)
  {
    if(!visited[node->vertex])
    DFS(node->vertex);
    node = node->next;
  }
}

//Print the Breadth First Search of the given vertex.
void GraphAlgo::BFS(unsigned int v)
{
  if(v >= (unsigned int)V)
  {
    cout<<"\nThe requested vertex is not present in the graph\n";
    return;
  }
  count++;
  Graph_node *node = (adj_list+v);
  if(!visited[v])
  {
    cout<<" "<<node->vertex<<" ";
    visited[v] = 1;
  }
  while(node->next!=NULL)
  {
    node = node->next;
    if(!visited[node->vertex])
    {
      count++;
      cout<<" "<<node->vertex<<" ";
      visited[node->vertex] = 1;
      enqueue(node->vertex);
    }
  }
  while((v = dequeue())!= -1)
  BFS(v);
}

//Find the no. of connected compoenents and their members
// Task : Add the code and modify the function to return the list
// of the all connected components
unsigned int GraphAlgo::ConnectedComponents()
{
  int i = 0;
  unsigned int comp = 0;
  while(count != V)
  {
    if(!visited[i])
    {
      DFS(i);
      comp++;
      cout <<"\n";
    }
  i++;
  }
  return comp;
}

//Find whether the graph can be Bipartite or not.
void GraphAlgo::CheckBipartition(unsigned int v)
{
  unsigned int cl=NO_COLOR;
  if(v >= (unsigned int)V)
  {
    cout<<"\nThe requested vertex is not present in the graph\n";
    return;
  }
  if(!visited[v])	 // If the node is no visited yet.
  {
    count++;
    visited[v] = 1;
    color[v] = RED;
    cl = BLUE;
  }else	 //If already visited the check for the color and update the variable for it's child color
  {
    if(color[v] == RED)
    cl = BLUE;
    if(color[v] == BLUE)
    cl = RED;
  }

  Graph_node *node = (adj_list+v); // Get that node
  while(node->next!=NULL) // searches the nodes along the breadth of the parent node
  {
    node = node->next;
    if(!visited[node->vertex])	 //If the node is not yet visited then it should be coloured with the opposite of the color of it's parent.
    {
      count++;	 // Count maintians the track of no. of vertex visited yet.
      visited[node->vertex] = 1;
      color[node->vertex] = cl;
      cout<<" "<< node->vertex <<"("<<cl<<")"<<" ";
      enqueue(node->vertex);
    }else	 //If the node is already visited before than the node must be either RED or BLUE colored.
    {
      if(color[node->vertex]!=cl) //If the child is already colored and is same as the parent then there no bipartition in the graph.
      {
        bipartite_status = FALSE;
        return;
      }
    }
  }
  while((v = dequeue())!= -1)
  CheckBipartition(v);
}

void GraphAlgo::BipartiteGroup()
{
  for(unsigned int i =0; i < V; i++)
  if(!visited[i] && bipartite_status && (count!=V))	 //Check for a node only if that node is not visited, still bipartition exist and all the vertex are not traversed yet.
    CheckBipartition(i);
  else if(!bipartite_status)
  {
    cout<<"There is no bipartite group exist for the graph";
    return;
  }
  cout<<"\n";
  for(int i =0; i<V; i++)
  if(color[i] == RED)
  cout <<" "<<i<<" ";

}

int main()
{
//GraphAlgo ob("tiny_graph.txt");
// The structure of tiny_graph.txt file should be like
// First line contains the number of vertex space sparted the Edges
// For second line contains the edges between vertex like 3 4
// For convenience start the vertex number from 0 to n-1
GraphAlgo ob("tiny_graph.txt");
ob.print_adjlist();
//ob.DFS(0);
//ob.BFS(3);
//cout<<"There are "<<ob.ConnectedComponents()<<" no. of connected components in the graph.\n";
ob.BipartiteGroup();
return 0;
}
