/*############################################################
###############Author : Sanjeev Kumar#########################
###############Date of Creation: 26. 09. 2013#################
##############Description: Merge Sort Algorithm###############
#############################################################*/

#include<iostream>

using namespace std;

template <class T>
class MERGE_SORT
{
private:
	T *a,*aux;
	int size;
	void merge(T *,int, int, int);		//Merge the individual compoenents
	int less(T,T);						//Compares the two elements
public:
	MERGE_SORT(T *inputarr, int n)
	{
		a = inputarr;
		size = n;
		sort(0,n-1);
	}
	void sort(int,int);
	~MERGE_SORT()
	{
		cout<<"GoodBye\n";
	}
};

template <class T>
void MERGE_SORT<T>::merge(T *a,int lo, int mid, int hi)
{		
		if(less(a[mid],a[mid+1])) return;					//Added to reduce unneccessary merging if the elements are already sorted.
		aux = new T[size];
		for(int i = 0; i<= size; i++)
			aux[i] = a[i];
			
		int i = lo, j = mid+1;
		for(int k = lo; k <= hi; k++)
		{
			if(i>mid)	a[k] = aux[j++];
			else if(j > hi)		a[k] = aux[i++];
			else if(less(aux[j],aux[i]))	a[k] = aux[j++];
			else	a[k] = aux[i++];
		}
		delete[] aux;
}
template <class T>		
void MERGE_SORT<T>::sort(int lo,int hi)
{		
	if(lo >= hi)	return;
	int mid = lo + ((hi-lo)/2);
	sort(lo,mid);
	sort(mid+1,hi);
	merge(a,lo,mid,hi);
}
template <class T>	
int MERGE_SORT<T>::less(T a,T b)	
{
	if(a<b)	return 1;
	else return 0;
}

int main()
{
int n;
cout<<"Input the no. of elements in array: ";
cin>>n;
int *arr;
arr = new int[n];

for(int i =0;i<n;i++)
{
cin>>arr[i];
}
MERGE_SORT<int> ob1(arr,n); 
for(int i =0;i<n;i++)
{
cout<<"\n"<<arr[i];
}
delete[] arr;
return 0;
}
