#include<iostream>

using namespace std;

#define end1 "\n"
#define TRUE 1
#define FALSE 0

class Percolation
{
private:
  int *site;
  int length;
  int up_virtual_node;
  int down_virtual_node;

public:
  Percolation(int **Grid, const int N)
  {
    length = N;
    site = new int[(length*length)+2];
    for(int i = 0; i < N*N; i++)
    {
       site[i] = i;
       if(Grid[i/N][i%N]==-1)
          site[i] = -1;
       else 
          open(i/N, i%N);
    }

    up_virtual_node = N*N;
    down_virtual_node = up_virtual_node + 1;

    site[up_virtual_node] = up_virtual_node;
    site[down_virtual_node] = down_virtual_node;

    for(int i = 0; i < N; i++)
       Union(i,up_virtual_node);
    for(int i = N*(N-1); i < N*N; i++)
       Union(i,down_virtual_node);
  }

  void open(int i, int j)
  {
    if(isOpen(i,j-1))
      Union(((length*i)+j-1), (length*i)+j);

    else if(isOpen(i,j+1))
      Union(((length*i)+j+1), (length*i)+j);

    else if(isOpen(i-1,j))
      Union(((length*(i-1))+j), (length*i)+j);

    else if(isOpen(i+1,j))
      Union((length*(i+1)+j), (length*(i+1))+j);
  }

  bool isOpen(int i,int j)
  {
     if(site[(length*i)+(length+j)] != -1)
       return TRUE;
     else 
       return FALSE;
  }

  bool isFull(int i, int j)
  {
    return !isOpen(i,j);
  }

  void Union(int i, int j)
  {}

  bool percolate()
  {
   if(connected(up_virtual_node,down_virtual_node))
      return TRUE;
   else 
      return FALSE;
  }
};

int main()
{
 return 0;
}
