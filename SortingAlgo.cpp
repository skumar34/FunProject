#include <iostream>

using namespace std;

class Sort{
	private:
		char *array;
		int Size;

		void set_param(char *p,int n)
		{
			array = (char *)p;
			Size = n;
		}

		void CreateMaxHeap()
		{
			for(int i = Size/2; i >= 1; i-- )
			{
				Sink(i,Size);
			}
		}

		void Sink(int k,int N){
			while(2*k <= N)
			{
				int j = 2*k;
				if(j < N && less(array+j,array+j+1)) j++;
				if(!less(array+k,array+j))	break;
				exch(array+k,array+j);
				k = j;
			}
		}

		void exch(char *p, char *q){
			char temp = *p;
			*p = *q;
			*q = temp;
		}

		int less(char *p, char *q){
			if(*p<*q)	return 1;
			else return 0;
		}
	public:
		Sort():array(NULL),Size(0){}

		void HeapSort(char *arr, int N){
			set_param(arr,N);
			CreateMaxHeap();
			for(int i = Size;i>1;i--)
			{
				exch(array+1,array+i);
				Sink(1,i-1);
			}
		}

    // Implementation of insertion sort

		~Sort()
		{
			array = NULL;
			Size = 0;
			}

};

int main()
{
	char *list;
	int N;
	cout<<"Enter the size of the array: ";
	cin>>N;
	list = (char *) new char[N+1];
	for(int i = 1; i<=N; i++)
	{
		cin>>list[i];
	}

	Sort ob1;
	ob1.insertionSort(list,N);
	cout<<endl;

	cout<<endl;
	return 0;
}
