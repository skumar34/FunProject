#include<iostream>
#include<cstdio>

using namespace std;

int V, E;
int E1[1000000], E2[1000000];
int Answer[1000], AnswerN;

typedef struct Graph{
int vertex;
int visited = 0;
Graph *next
};

int fornt, last;
void queue_init();
void enqueue(int *,int);
int dequeue(int *);
void CheckGroups(int *,int,int);
#define NO_COLOR 0
#define RED 1
#define GREEN 2

int main(int argc, char** argv)
{
int test_case;
/*
freopen function below opens input.txt file in read only mode, and afterward,
the program will read from input.txt file instead of standard(keyboard) input.
To test your program, you may save input data in input.txt file,
and use freopen function to read from the file when using cin function.
You may remove the comment symbols(//) in the below statement and use it.
Use #include<cstdio> or #include<stdio.h> to use the function in your program.
But before submission, you must remove the freopen function or rewrite comment symbols(//).
*/
freopen("sample_input.txt", "r", stdin);

/*
Your program should handle 10 test cases given.
*/
for(test_case = 1; test_case <= 10; ++test_case)
{
int i;
/*
Read each test case from standard input.
*/
cin >> V >> E;
node = new int[V+1];
Graph **graph_node;
graph_node = new Graph*[V+1];

for(i = 0; i < V+1; i++)
{
Graph *node;
node = new Graph[];
node->vertex = i;
node->next = NULL;
graph_node[i] = node;
}
for(i = 0; i < E; i++)
{
cin >> E1[i] >> E2[i];

Graph *node,*start;

#if defined (UNDIRECTED_GRAPH) //Only in the case of undirected graph. To reduce redundancy as if a is connected to b, then b is also connected to a.
if(E2[i] < E1[i])
{
E1[i] = E1[i] + E2[i];
E2[i] = E1[i] -E2[i];
E1[i] = E1[i] - E2[i];
}
#endif
start = graph_node[E1[i]];
node = new Graph[];
node->vertex = E2[i];
node->next = NULL;

while(start->next!=NULL)
start = start->next;
start->next = node;
}

int *node_color; //Array maintains the node color either GREEN or RED. if two nodes are connected then one is either RED and another is GREEN
node_color = new int[V+1];
AnswerN = 0;
/////////////////////////////////////////////////////////////////////////////////////////////	
CheckGroups(node_color,V,E);
if(AnswerN != -1)
for(int i = 1; i <= V; i++)
{
if(node_color[i] == RED || node_color[i] == NO_COLOR)
{
Answer[AnswerN++] = i;
}
}
/////////////////////////////////////////////////////////////////////////////////////////////
// AnswerN = -1;


// Print the answer to standard output(screen).
cout << "#" << test_case << " " << AnswerN;
for(i = 0; i < AnswerN; i++)
{
cout << " " << Answer[i];
}
cout << endl;
delete[] node_color;
}

return 0;//Your program should return 0 on normal termination.
}

void CheckGroups(int *node_color,int V, int E)
{

for(int i = 0; i < V+1; i++)
node_color[i] = NO_COLOR; //NO_COLOR means that the ndoes are not visited yet. The node remains NO_COLOR if there is no edge connecting thate vertex.

int *queue;
queue = new int[V];
queue_init();

for(int i = 1; i < V+1; i++)
{
start = graph_node[i];
if(node_color[start->vertex] == NO_COLOR)
node_color[Start->vertex] = RED;
while(1)
{

if(node_color[start->vertex] == NO_COLOR)
{
if(node_color[start->next->vertex] == NO_COLOR)
{
node_color[E1[i]] = RED;
node_color[E2[i]] = GREEN;
}else
if(node_color[E2[i]] == RED)
node_color[E1[i]] = GREEN;
else
node_color[E1[i]] = RED;
}else
if(node_color[E1[i]] == RED)
{
if(node_color[E2[i]] == NO_COLOR)
node_color[E2[i]] = GREEN;
else if(node_color[E2[i]] == RED) // The nodes are in the same group but are connected
{
AnswerN = -1;
return;
}
}else
{
if(node_color[E2[i]] == NO_COLOR)
node_color[E2[i]] = RED;
else if(node_color[E2[i]] == GREEN) // The nodes are in the same group but are connected
{
AnswerN = -1;
return;
}
}
}

}

void queue_init()
{
front = -1;
last = -1;
}

void enqueue(int *queue, int no)
{
queue[++front] = no;
}

int dequeue(int *queue)
{
if(front == last)
return -1;
else 
return queue[++last];
}
