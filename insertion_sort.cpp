#include<iostream>

using namespace std;

class Sort{
  private:
    int *arr;
    int size;

    void set_param(int *list, int n){
      arr = list;
      size = n;
    }
    void swap(int *p, int *q){
      int temp = *p;
      *p = *q;
      *q = temp;
    }

    int bsearch(int *list, int n){
        low = 0;
        high = n-1;
        while

    }

  public:
    void insertionSort(int *list, int N)
    {
      //implementation with linear search of correcy location of the
      //selected element
      set_param(list,N);

      for(int i = 1; i < size; i++)
      {
        //select the first element and assume that list upto the selected index
        // is sorted. If not do the sorting
        int j = i;
        while((j > 0) & (arr[j] < arr[j-1])){
          swap(arr+j,arr+j-1);
          j--;
        }
      }
			for(int i = 0; i<size; i++)
			{
				cout<<arr[i]<<" ";
			}
    }

    void insertionSortbs(int *list, int N)
    {
      set_param(list,N);

      for(int i = 1; i < size; i++)
      {
        //select the first element and assume that list upto the selected index
        // is sorted. If not do the sorting
        int j = i;

        // first check whether the selected element is at correct position
        if(arr[j] < arr[j-1]){
          // do the binary search for finding the correct location of the element
          // Set the size of the sorted subarray
          int n = j;
        // search the index of the correct position of the element
          int k = bsearch(arr,arr[j],n);
          int m = arr[k];
        // shift all the elements on step right for accomodating the jth element
          for(int l = j;j>k;l--){
            arr[l]=arr[l-1];
          }
          arr[k] = m;

        }
      }
			for(int i = 0; i<size; i++)
			{
				cout<<arr[i]<<" ";
			}
    }
};

int main()
{
  int list[5];
  for(int i = 0; i<5; i++)
	{
		cin>>list[i];
	}

  Sort ob;
  ob.insertionSort(list,5);

  return 0;
}
