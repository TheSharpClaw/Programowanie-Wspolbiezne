#include <conio.h>
#include <iostream>
#include <omp.h>
#include <ctime>
#include <string>

using namespace std;

void czekaj(int milis) {
	time_t koniec;
	koniec = clock() + milis;
	while (koniec > clock()) {};
}

int main() {
	int czasOperacji;
	int nrWatku = 0;

	float tabA[200][200];
	float tabB[200][200];

	float tabC[200][200];
	float tabD[200][200];

	float tabAB[200][200];
	float tabCD[200][200];

	float tabCsumming = 0;
	float tabDsumming = 0;

	srand(time(NULL));

	czasOperacji = clock();

#pragma omp parallel num_threads(8)
	{
		for (int i = 0; i < 200; i++)
		{
			czekaj(1);
			for (int j = 0; j < 200; j++)
			{
#pragma omp single
				{
					do {
						tabA[i][j] = rand() % 20001 - 10000;
					} while (tabA[i][j] == 0);
				}
#pragma omp single
				{
					tabB[i][j] = rand() % 9999 + 1;
				}
			}
		}
#pragma omp barrier
#pragma omp master
		{
			cout << "Czas etapu 1 (uzupelnienie tablicy A i B): " << clock() - czasOperacji << endl;
			czasOperacji = clock();
		}
	
		float maxA = tabA[0][0];
		float minB = tabB[0][0];

		for (int i = 0; i < 200; i++)
		{
			czekaj(1);
			for (int j = 0; j < 200; j++)
			{
#pragma omp single
				{
					tabC[i][j] = 1 / tabA[i][j];
				}
#pragma omp single
				{
					tabD[i][j] = sqrt(tabB[i][j]);
				}
#pragma omp single
				{
					tabAB[i][j] = tabA[i][j] + tabB[i][j];
				}
#pragma omp single
				{
					if (tabA[i][j] > maxA)
						maxA = tabA[i][j];
				}
#pragma omp single
				{
					if (tabB[i][j] < minB)
						minB = tabB[i][j];
				}
			}
		}
#pragma omp barrier
#pragma omp master
		{
			cout << "Czas etapu 2 (wyliczenie tablic C i D, dodanie tablic A i B," << endl << "znalezienie min z tablicy A i znalezienie max z tablicy B): " << clock() - czasOperacji << endl;
			czasOperacji = clock();
		}

		for (int i = 0; i < 200; i++)
		{
			czekaj(1);
			for (int j = 0; j < 200; j++)
			{
#pragma omp single
				{
					tabCD[i][j] = tabC[i][j] * tabD[i][j];
				}
#pragma omp single
				{
					tabCsumming = tabCsumming + tabC[i][j];
				}
#pragma omp single
				{
					tabDsumming = tabDsumming + tabD[i][j];
				}
			}
		}
#pragma omp single
		{
			cout << "maxA: " << maxA << endl;
		}
#pragma omp single
		{
			cout << "minB: " << minB << endl;
		}
#pragma omp single
		{
			cout << "zsumowaneC: " << tabCsumming << endl;
		}
#pragma omp single
		{
			cout << "zsumowaneD: " << tabDsumming << endl;
		}		
#pragma omp barrier
#pragma omp master
		{
			cout << "Czas trwania operacji 3 (zsumowanie elementow i pomnozenie tablic C i D, wypisanie min i max): " << clock() - czasOperacji << endl;
			cout << "Nacisnij klawisz ...";
		}
	}
	_getch();
	return 0;	
}