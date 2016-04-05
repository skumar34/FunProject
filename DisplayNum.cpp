#include<iostream>
#include<string>

using namespace std;

class Number
{
string one[3],two[3],three[3],four[3],five[3],six[3],seven[3],eight[3];
string nine[3],zero[3];
public:
	Number()
	{
		one[0] = "   ";
		one[1] = "  |";
		one[2] = "  |";

		two[0] = " _ ";
		two[1] = " _|";
		two[2] = "|_ ";

		three[0] = " _ ";
		three[1] = " _|";
		three[2] = " _|";

		four[0] = "   ";
		four[1] = "|_|";
		four[2] = "  |";

		five[0] = " _ ";
		five[1] = "|_ ";
		five[2] = " _|";

		six[0] = " _ ";
		six[1] = "|_ ";
		six[2] = "|_|";

		seven[0] = " _ ";
		seven[1] = "  |";
		seven[2] = "  |";

		eight[0] = " _ ";
		eight[1] = "|_|";
		eight[2] = "|_|";

		nine[0] = " _ ";
		nine[1] = "|_|";
		nine[2] = " _|";

		zero[0] = " _ ";
		zero[1] = "| |";
		zero[2] = "|_|";

		
	}
	
	void displayNum(int cnt)
	{
		switch(cnt)
			{
			case 0:
				printNum(zero[0],zero[1],zero[2]);
				break;
				
			case 1:
				printNum(one[0],one[1],one[2]);
				break;
				
			case 2:
				printNum(two[0],two[1],two[2]);
				break;
				
			case 3:
				printNum(three[0],three[1],three[2]);
				break;
				
			case 4:
				printNum(four[0],four[1],four[2]);
				break;
				
			case 5:
				printNum(five[0],five[1],five[2]);
				break;
				
			case 6:
				printNum(six[0],six[1],six[2]);
				break;
				
			case 7:
				printNum(seven[0],seven[1],seven[2]);
				break;
				
			case 8:
				printNum(eight[0],eight[1],eight[2]);
				break;
				
			case 9:
				printNum(nine[0],nine[1],nine[2]);
				break;
				
			}
	}

	virtual void printNum(string one,string two,string three)
	{
		cout<<one<<endl;
		cout<<two<<endl;
		cout<<three<<endl;
		cout<<"\x1b[A"<<"\x1b[A"<<"\x1b[A";
		
	}

	void space(int cnt)
	{
		while(cnt){
			cout<<"\t";
			cnt--;
		}
	}
	
};

class Clock : public Number{
	int hh,mm,sec;
	int escape_len;

public:

	Clock() : hh(0), mm(0), sec(0), escape_len(0){
	cout<<"\t\t\tWelcome to digital Clock\n\n"<<endl;

		displayNum(0);
		escape_len = 1;
		displayNum(0);
		//cout <<"\t-\n\t-"<<"\x1b[A";
		escape_len = 2;
		displayNum(0);
		escape_len = 3;
		displayNum(0);
		escape_len = 4;
		//cout <<"\t\t-\n\t\t-"<<"\x1b[A";
		displayNum(0);
		escape_len = 5;
		displayNum(0);
	
	}

	virtual void printNum(string one,string two,string three)
	{
		space(escape_len);
		cout<<one<<endl;
		space(escape_len);
		cout<<two<<endl;
		space(escape_len);
		cout<<three<<endl;
		cout<<"\x1b[A"<<"\x1b[A"<<"\x1b[A";
		
	}

	void startClock()
	{
		for(;sec <60 ; sec++)
		{
			escape_len = 5;
			displayNum(sec%10);
			escape_len = 4;
			displayNum(sec/10);
			sleep(1);
		}
		sec = 0;
		escape_len = 4;
		displayNum(0);
		escape_len = 5;
		displayNum(0);
		mm++;
		if(mm > 59)
		{
			hh++;
			mm = 0;
		}
		escape_len = 3;
		displayNum(mm%10);
		escape_len = 2;
		displayNum(mm/10);

		if(hh > 23)
		{
			hh = 0;
			mm = 0;
		}
		escape_len = 1;
		displayNum(hh%10);
		escape_len = 0;
		displayNum(hh/10);
	}
	
};

int main()
{
Clock ob;
//ob.show();
//unsigned int *p;
//ob.displayNum(8);
/*p = (unsigned int *)&ob;
for(int i = 0; i < sizeof(ob)/sizeof(unsigned int); i++)
{
	unsigned int temp = *p;
	for(int j = 0; j < sizeof(unsigned int)*8 ; j++)
	{
		cout<< (temp & 1);
		temp = temp >> 1;
	}
	cout <<endl;
	p++;
}*/

while(1)
{
ob.startClock();
}
return -1;
}
