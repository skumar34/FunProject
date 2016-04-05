/*############################################################
##################Author: sanjeev kumar#######################
##################Problem: Job Sequencing problem#############
######There are n no. of Jobs and their execution ############
######priorities are given. Find the safest execution#########
######execution path of the jobs.###########################*/

#include<iostream>

using namespace std;

#define TRUE 1
#define FALSE 0

//Job node structure containing job number and flag to indicate whether executed or not.
typedef struct job{
     int job_number;
     job *next;
     int executed;
   };

class Scheduler{
private:
int top;
int *stack;
int n_jobs, n_edge;
job** adj_list;                   //Maintains the execution priorities in the form of the adjacency list of Job Structure.

void push(int);
int pop();

public:
Scheduler(int **test_case)
{
  int i = 0;
  top = -1;
  n_jobs = test_case[0][0];
  n_edge = test_case[0][1];
  adj_list = new job*[n_jobs+1];
  
  stack = new int[n_jobs];
  
  for(int i =0; i <= n_jobs; i++)
    {  
		job *node;
		node = new job;
		node->next = NULL;
		node->executed = 0;
		node->job_number = i;
		adj_list[i] = node;
	}
  
  //adj_list[i] contains all the links to nodes on which execution of node i is dependent.
  while(i < 2*n_edge)
  {
    job *node,*start;
	start = adj_list[test_case[1][i+1]];
	node = new job;
	node->job_number = test_case[1][i];
	node->executed = 0;
	node->next = NULL;
		while(start->next!=NULL)
			start = start->next;
		start->next = node;				//There is link from node i to node j if node i is dependent on the execution of node j
		
	i = i+2;
	}
}

void Job_Sequnece();
~Scheduler()
{
	delete[] stack;
	//for(int i = 0; i<n_jobs; i++)
}
};

void Scheduler::Job_Sequnece()
{
	int i = 0;
	bool cycle=FALSE;
	job *node,*start;

	while(++i <= n_jobs)
	{   start = adj_list[i];
		if(!(start->executed))
		{
			int last,initial;
			node = adj_list[i];
			initial = node->job_number;
			push(node->job_number);
			while(1)
			{
				//Skip dependents of the the job if already executed
				while(node->next!=NULL && adj_list[node->next->job_number]->executed)       
				{
					node = node->next;
					if(node->job_number == initial)      // If the job dependents are dependent on that job itself
					{
						cycle = TRUE;
						cout <<"Cycle is present in the graph";
						return;
					}
				}
				
				//If there is no dependent left for execution or the node is independent of any other nodes execution
				if(node->next == NULL)
				{
					last = pop();
					cout <<" "<<last<<" ";
					adj_list[last]->executed = TRUE;
					if((last = pop())!=FALSE)
					{
						node = adj_list[last];
						push(last);
						continue;
					}
					else
						break;
				}
				node = adj_list[node->next->job_number];
				push(node->job_number);
			}
		}		
	}			
	
}

/*void Scheduler::Job_Sequnece()
{
	int i = 0;
	job *node;
	while(++i <= n_jobs)
	{   if(!(adj_list[i]->executed))
		{
			int last;
			node = adj_list[i];
			push(node->job_number);
			node->executed = 1;
			while(1)
			{
				while((node->next != NULL) && ((node->next)->executed))
				node = node->next;
				
				while(node->next != NULL && adj_list[(node->next)->job_number]->executed != 1)
				{ 
					node = node->next;
					push(node->job_number);
					node->executed = 1;
					node = adj_list[node->job_number];
					node->executed = 1;
				}
				cout<<" "<<pop()<<" ";
				if((last = pop())!= NULL)
				{  
					node = adj_list[last]; 
					push(node->job_number);
				}
				else
					break;
			}
		}	
	}
}*/

void Scheduler::push(int x)
{
	stack[++top] = x;
}

int Scheduler::pop()
{
	if(top == -1)
		return 0;
	else
		return stack[top--];

}

int main()
{
	int **test_case;
	test_case = new int*[2];
	cout<<"Enter the test case \n";
	
	int v,e;
	cin>>v>>e;
	//cout<<v<<" "<<e;
	*test_case = new int[2];
	test_case[0][0]=v;
	test_case[0][1]=e;
	*(test_case+1) = new int[2*e];
	for(int i = 0; i< 2*e; i++)
		cin>>test_case[1][i];
	for(int i = 0; i< 2*e; i++)
		cout<<test_case[1][i];
	Scheduler ob(test_case);
	ob.Job_Sequnece();
	
	//delete test_case[0];
	//delete test_case[1];
	
	return 0;
}