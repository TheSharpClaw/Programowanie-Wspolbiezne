#include <conio.h>
#include <iostream>
#include <omp.h>
#include <time.h>

using namespace std;

void uzupelnijTabA(float tabA[200][200]) 
{
	for (int i = 0; i < 200; i++) 
	{
		for (int j = 0; j < 200; j++) 
		{
			do {
				tabA[i][j] = rand() % 20001 - 10000;
			} while (tabA[i][j] == 0);
		}
	}
}

void uzupelnijTabB(float tabB[200][200]) 
{
	for (int i = 0; i < 200; i++) 
	{
		for (int j = 0; j < 200; j++) 
		{
			do {
				tabB[i][j] = rand() % 10000 + 1;
			} while (tabB[i][j] == 0);
		}
	}
}

void wyliczTabC(float tabC[200][200], float tabA[200][200]) 
{
	for (int i = 0; i < 200; i++) 
	{
		for (int j = 0; j < 200; j++) 
		{
			tabC[i][j] = 1 / tabA[i][j];
		}
	}
}

void wyliczTabD(float tabD[200][200], float tabB[200][200]) 
{
	for (int i = 0; i < 200; i++) 
	{
		for (int j = 0; j < 200; j++) 
		{
			tabD[i][j] = sqrt(tabB[i][j]);
		}
	}
}

void dodajAiB(float tabAB[200][200], float tabA[200][200], float tabB[200][200])
{
	for (int i = 0; i < 200; i++) 
	{
		for (int j = 0; j < 200; j++) 
		{
			tabAB[i][j] = tabA[i][j] + tabB[i][j];
		}
	}
}

void pomnozCiD(float tabCD[200][200], float tabC[200][200], float tabD[200][200])
{
	for (int i = 0; i < 200; i++) 
	{
		for (int j = 0; j < 200; j++) 
		{
			tabCD[i][j] = tabC[i][j] * tabD[i][j];
		}
	}
}

float znajdzMaxA(float maxA, float tabA[200][200])
{
	for (int i = 0; i < 200; i++) 
	{
		for (int j = 0; j < 200; j++) 
		{
			if (tabA[i][j] > maxA)
			{
				maxA = tabA[i][j];
			}
		}
	}
	return maxA;
}

float znajdzMinB(float minB, float tabB[200][200])
{
	for (int i = 0; i < 200; i++) 
	{
		for (int j = 0; j < 200; j++) 
		{
			if (tabB[i][j] < minB)
			{
				minB = tabB[i][j];
			}
		}
	}
	return minB;
}

int main() {

	float tabA[200][200];
	float tabB[200][200];

	float tabC[200][200];
	float tabD[200][200];

	float tabAB[200][200];
	float tabCD[200][200];

	srand(time(NULL));

	uzupelnijTabA(tabA);
	uzupelnijTabB(tabB);
	
	float maxA = tabA[0][0];
	float minB = tabB[0][0];

	wyliczTabC(tabC, tabA);
	wyliczTabD(tabD, tabB);
	
	dodajAiB(tabAB, tabA, tabB);
	pomnozCiD(tabCD, tabC, tabD);

	maxA = znajdzMaxA(maxA, tabA);
	minB = znajdzMinB(minB, tabB);

	for (int i = 0; i < 2;  i++) {
		for (int j = 0; j < 2; j++) {
			cout << "TabA[" << i << "][" << j << "]:" << tabA[i][j] << endl;
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			cout << "TabB[" << i << "][" << j << "]:" << tabB[i][j] << endl;
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			cout << "TabC[" << i << "][" << j << "]:" << tabC[i][j] << endl;
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			cout << "TabD[" << i << "][" << j << "]:" << tabD[i][j] << endl;
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			cout << "TabAB[" << i << "][" << j << "]:" << tabAB[i][j] << endl;
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			cout << "TabCD[" << i << "][" << j << "]:" << tabCD[i][j] << endl;
		}
	}
	cout << "maxA: " << maxA << endl;
	cout << "minB: " << minB << endl;

	cout << "Nacisnij klawisz ...";
	_getch();
	return 0;
}