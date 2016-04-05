/*
In S-Topcoder Contest,

You should use the statndard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>

using namespace std;
int rules[1000][6];
int matrix[1000][1000];
int Answer;
int check_weight(int,int,int);

int calculate(int N)
{
  int max_weight=0;
  for(int i =0 ;i<N-1 ;i++)
   for(int j = i+1 ; j<N ;j++)
    {
	if((rules[j][0] <= rules[i][1]) && (rules[j][1] >= rules[i][0]))
	   if((rules[j][2] <= rules[i][3]) && (rules[j][3] >= rules[i][2]))
	      if((rules[j][4] <= rules[i][5]) && (rules[j][5] >= rules[i][4]))
                   matrix[i][j] = 1;
    }
   for(int i = 0; i < N-1;i++)
   {
    for(int j = i+1; j< N;j++)
    {
		int wt = 0;
		if(matrix[i][j] == 1)
		{
			wt = check_weight(i,j,N);
			if(wt > max_weight)
				max_weight = wt;
		}
    }
   }
   return max_weight+1;
}

int check_weight(int row,int col,int N)
{
	int w =1;
	for(int i = col+1; i<N; i++)
	{
		if(matrix[col][i] == 1)
		{	if(matrix[row][i] == 1)
			{
				w = 1 + check_weight(col,i,N);
			}
		}
	}
	return w;
}
int main(int argc, char** argv)
{
	int T, test_case;
	/*
	   The freopen function below opens input.txt file in read only mode, and afterward,
	   the program will read from input.txt file instead of standard(keyboard) input.
	   To test your program, you may save input data in input.txt file,
	   and use freopen function to read from the file when using cin function.
	   You may remove the comment symbols(//) in the below statement and use it.
	   Use #include<cstdio> or #include <stdio.h> to use the function in your program.
	   But before submission, you must remove the freopen function or rewrite comment symbols(//).
	 */	

	// freopen("input.txt", "r", stdin);
    int N;
	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{

		/////////////////////////////////////////////////////////////////////////////////////////////
		cin>>N;
		if(N <= 30)
		{
		for(int i = 0; i < N; i++)
			for(int j = i; j < N; j++)
			{
				matrix[i][j] = 0;
			}
		
		for(int rule = 0; rule < N; rule++)
		{	
		  for(int j = 0; j < 6; j++)
		  {
			cin>>rules[rule][j];
		  }
		}
		Answer = calculate(N);
		/////////////////////////////////////////////////////////////////////////////////////////////
		}else
		Answer = 0;
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
