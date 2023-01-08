#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

using namespace std;

void displayBoard(int[][4], int);
bool check(int[][4], int,int&);
void randomSpawn(int [][4]);
void shifting(int a[][4], char,bool&);
void algo(int [][4],bool [][4], int, int, int,int,bool &,bool&);
bool fullFunction(int [][4]);

int main()
{
	const int size = 4;
	int winOrLose = 0;
	char input = 0;
	bool checker = false,shift=true;
	int a[size][size] ;

	cout << "You can only use the following controls:-\na:left, d:right, w:up, s:down, p:to stop, m:to Open menu of controls. \n\n";
	 
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			a[i][j] = 0;
			
		}
	}
	if (!checker)
	{
		randomSpawn(a);
		randomSpawn(a);
	}
	
	displayBoard(a, size);

	Sleep(15);
	
	checker = check(a, size, winOrLose);
	for (; !checker; )
	{
		input = _getch();
		for (; input != 'w'&& input != 'a'&&input!='s'&&input!='d'&&input!='p'&&input!='m'; )
		{
			input = _getch();
		}
		if (input=='p')
		{
			break;
		}
		else if (input=='m')
		{
			system("CLS");
			cout << "\nYou can only use a:left, d:right, w:up, s:down, p:to stop, m:to Open the controls. \n";
			displayBoard(a, size);
		}
		shifting(a, input,shift);
		if (!fullFunction(a) && shift)
		{
			randomSpawn(a);
			Sleep(50);
			system("CLS");
			displayBoard(a, size);
		}
		checker = check(a, size, winOrLose);
		
		

		
	}
	if (shift)
		cout << endl;
	if (input!='p')
	{
		if (winOrLose == 1)
		{
			for (int i = 0; i < 9; i++)
			{
				cout << "\n";
			}
			for (int i = 0; i < 13; i++)
			{
				cout << " ";
			}
			cout << "You Win.";
			for (int i = 0; i < 9; i++)
			{
				cout << "\n";
			}
		}
		else if (winOrLose == 0) {
			for (int i = 0; i < 9; i++)
			{
				cout << "\n";
			}
			for (int i = 0; i < 13; i++)
			{
				cout << " ";
			}
			cout << "You Lost.";
			for (int i = 0; i < 9; i++)
			{
				cout << "\n";
			}
		}
	}
	else {
		cout << "\nYou stopped the game.\n";
	}
	
	system("pause");
	return 0;
}
void displayBoard(int a[][4], int size)
{
	for (int row = 0; row < 4; row++) {
		cout << "=================================" << endl;
		cout << "|       |       |       |       |" << endl;
		for (int col = 0; col < 4; col++) {
			if (a[row][col]>100)
				cout << "|  ";
			else
				cout << "|   ";
			if (a[row][col]==0)
				cout << " ";
			else 
				cout << a[row][col];
			if (a[row][col] > 10 && a[row][col] < 1000)
				cout << "  ";
			else if (a[row][col] > 1000)
				cout << " ";
			else
				cout << "   ";
		}
		cout << "|";
		cout << endl;
		cout << "|       |       |       |       |" << endl;
	}
	cout << "=================================";
}
bool check(int a[][4], int size,int& winOrLose)
{

	int flag = 0;
	int temp_j = 0;
	int temp_i = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (a[i][j] == 1024)
			{
				winOrLose = 1;
				return true;

			}
		}
	}
	if (!fullFunction(a))
	{
		return false;
	}
	for (int i = 0; i < 4; i++)
	{
		temp_i = i;
		if (temp_i == 3)
		{
			temp_i = i - 2;
		}
		for (int j = 0; j < 4; j++)
		{
			temp_j = j;
			if (temp_j == 3)
			{
				temp_j = j - 2;
			}
			if (a[i][j] == a[i][temp_j + 1] || a[temp_i + 1][j] == a[i][j])
			{
				return false;
			}

		}

	}
	winOrLose = 0;
	return true;
}
bool fullFunction(int a[][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (a[i][j] == 0)
			{
				return false;
			}
		}
	}
	return true;
}
void randomSpawn(int a[][4])
{
	int row, col,value;
	bool flag = true;
	srand(time(0));

	row = rand() % 4;
	col = rand() % 4;
	value = 1 + (rand() % 100);
	for (; flag; )
	{
		if (a[row][col] == 0)
		{
			if (value > 0 && value < 70)
				a[row][col] = 1;
			else if (value >= 70 && value <= 100)
				a[row][col] = 2;
			flag = false;
		}
		else  {
			row = rand() % 4;
			col = rand() % 4;
		}
	}
}
void shifting(int a[][4], char input,bool& shift)
{
	int changei,changej;
	bool stoper=true;
	bool addiChecker[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			addiChecker[i][j] = false;
		}
	}
	shift = false;
	if (input=='d'||input=='a')
	{
		for (int row=0;row<4;row++)
		{
			if (input=='a')
			{
				for (int col = 1; col < 4; col++)
				{
					changei = 0;
					changej = -1;
					if (a[row][col] != 0)
					{


						stoper = true;
						for (int j = col; j > 0 && stoper; j--)
						{
							
							algo(a,addiChecker, row, j, changej, changei, stoper,shift);
						}
					}
					
				}
			}
			else {
				for (int col = 2; col > -1; col--)
				{
					changei = 0;
					changej = 1;
					if (a[row][col] != 0)
					{
						stoper = true;
						for (int j = col; j < 3 && stoper; j++)
						{
							algo(a, addiChecker, row, j, changej, changei, stoper,shift);
						}
					}
				}
			}
			
		}
	}
	else if (input == 'w' || input == 's')
	{
		for (int col = 0; col < 4; col++)
		{
			if (input=='w')
			{
				for (int row = 1; row < 4; row++)
				{
					changej = 0;
					changei = -1;
					if (a[row][col] != 0)
					{
						stoper = true;
						for (int i = row; i > 0 && stoper; i--)
						{
							algo(a, addiChecker, i, col, changej, changei, stoper,shift);
						}
					}
				}
			}
			else
			{
				for (int row = 3; row > -1; row--)
				{
					changej = 0;
					changei = 1;
					if (a[row][col] != 0)
					{
						stoper = true;
						for (int i = row; i < 3 && stoper; i++)
						{
							algo(a, addiChecker, i, col, changej, changei, stoper,shift);
						}
					}
				}
			}
		}
	}
}
void algo(int a[][4],bool addiChecker[][4], int i, int j, int changej, int changei,bool& stoper,bool& shift) {
	int size = 4;
	if (a[i+changei][j +changej] == 0)
	{
		a[i+changei][j + changej] = a[i][j];
		a[i][j] = 0;
		shift = true;
		stoper = true;
		Sleep(1);
		system("CLS");
		displayBoard(a, size);

	}
	else if (a[i+changei][j + changej] == a[i][j]&&!addiChecker[i+changei][j+changej])
	{
		a[i+changei][j + changej] += a[i][j];
		a[i][j] = 0;
		shift = true;
		stoper = false;
		addiChecker[i + changei][j + changej] = true;
		Sleep(1);
		system("CLS");
		displayBoard(a, size);
	}
	else {
		stoper = false;
	}
}