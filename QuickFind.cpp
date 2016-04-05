/*########################################################################
########QuickFind.cpp : Quick Find Alogorithm for coursera Alogorithm Class#
####################Author: sanjeev kumar ################################
####################creation date: 27. 08. 2013 ##########################
##modification : 28. 08. 2013: Added support for QuickUnion. 
				 29. 09. 2013: Added new improvement method Weighted union,
							  Quick Union using path Compression method and
							  Weighted Quick Union using path compression 
							  method				              
##########################################################################*/


#include<iostream>

using namespace std;

#define end1 "\n"

// default mode : No Flagn Specified. Do the Quick Find.
// QUICK_UNION : Flag For enabling Quick Union
// WEIGHTED_QUNION : Flag For enabling Weighted Quick Union
// QUNION_PATH_COMPRESS : Improvement of Quick Union using Path Compression
// WQUNION_PATH_COMPRESS : IMprovement of WQU using path Compression


class QuickFindUF
{
private:
   int *id;
   int length;
#if defined (QUICK_UNION) || defined (WEIGHTED_QUNION) || defined(QUNION_PATH_COMPRESS)
   int *sz;           //contains size of each connected component
#endif
#if defined (QUICK_UNION) || defined (WEIGHTED_QUNION) || defined (QUNION_PATH_COMPRESS) || defined (WQUNION_PATH_COMPRESS)
  int root(int i)
  {
    while(i != id[i]){
#ifdef QUNION_PATH_COMPRESSION
	id[i] = id[id[i]];
#endif
    	i = id[i];
	}
    return i;
  }
#endif
    
public:
   QuickFindUF(const int N)
   {
    id = new int[N];
#if defined (QUICK_UNION) || defined (WEIGHTED_QUNION) || defined(QUNION_PATH_COMPRESS)
    sz = new int[N];
#endif
    length = N;
    for(int i = 0; i < N; i++)
    {
    	id[i] = i;
#ifdef WEIGHTED_QUNION
	    sz[i] = 1;
#endif
     }
   }

 bool connected(int p, int q)
   {
#if defined (QUICK_UNION) || defined (WEIGHTED_QUNION) || defined (QUNION_PATH_COMPRESS) || defined (WQUNION_PATH_COMPRESS)
     return root(p) == root(q);
#else
     return id[p] == id[q];
#endif
  }

 void Union(int p, int q)
  {
#if defined (QUICK_UNION) || defined (WEIGHTED_QUNION) || defined(QUNION_PATH_COMPRESS)
   int i = root(p);
   int j = root(q);
 #ifdef QUICK_UNION
   id[i] = j;
 #else      					//Merger the smaller connected component to larger one.
   if(sz[i] < sz[j])			
   {
		id[i] = j;
		sz[j] = sz[j] + sz[i];
   }else
   {
        id[j] = i;
		sz[i] = sz[i] + sz[j];
   }
 #endif
#else
   int pid = id[p];
   int qid = id[q];
   for(int i = 0; i < length; i++)
   {
     if(id[i] == pid) id[i] = qid;
   }
#endif
   print();
  }

  void print()
  {
     for(int i = 0; i< length; i++)
	   cout<<id[i]<<" ";
	 cout<<end1;
  }

  ~QuickFindUF()
  {
    delete[] id;
#ifdef WEIGHTED_QUNION
    delete[] sz;
#endif
  }
};

int main()
{
#ifdef QUICK_UNION
cout<<"Union Find Algorithm using QUICK UNION"<<end1;
#elif WEIGHTED_QUNION
cout<<"Union Find Algorithm using WEIGHTED QUICK UNION"<<end1;
#elif QUNION_PATH_COMPRESS
cout<<"Union Find Algorithm using QUICK UNION PATH COMPRESSION"<<end1;
#elif WQUNION_PATH_COMPRESS
cout<<"Union Find Algorithm using WEIGHTED QUICK UNION PATH COMPRESSION"<<end1;
#else
cout<<"Union Find Algorithm using QUICK FIND"<<end1;
#endif

QuickFindUF ob1(10);
cout << "if node 1 and node 6 are connected"<<ob1.connected(1,6)<<end1;
ob1.print();
ob1.Union(1,5);
ob1.Union(2,6);
ob1.Union(8,9);
ob1.Union(8,6);
ob1.Union(2,5);
cout << "if node 1 and node 6 are connected"<<ob1.connected(1,6)<<end1;
ob1.print();
return 1;
}
