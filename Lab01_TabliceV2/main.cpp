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
	float tabCmultiplyD[200][200];

	float tabCsumming = 0;
	float tabDsumming = 0;

	srand(time(NULL));

	czasOperacji = clock();

#pragma omp parallel num_threads(2)
	{
		nrWatku = omp_get_thread_num();

		for (int i = 0; i < 200; i++)
		{
			czekaj(1);
			for (int j = 0; j < 200; j++)
			{
				if (nrWatku == 0)
				{
					do {
						tabA[i][j] = rand() % 20001 - 10000;
					} while (tabA[i][j] == 0);
				}
				else 
				{
					tabB[i][j] = rand() % 9999 + 1;
				}			
			}
		}
	}
	cout << "Czas etapu 1 (uzupelnienie tablicy A i B): " << clock() - czasOperacji << endl;

	czasOperacji = clock();

	float maxA = tabA[0][0];
	float minB = tabB[0][0];

#pragma omp parallel num_threads(5)
	{
		nrWatku = omp_get_thread_num();

		for (int i = 0; i < 200; i++)
		{
			czekaj(1);
			for (int j = 0; j < 200; j++)
			{
				if (nrWatku == 0)
				{
					tabC[i][j] = 1 / tabA[i][j];
				}
				else if(nrWatku == 1)
				{
					tabD[i][j] = sqrt(tabB[i][j]);
				}
				else if (nrWatku == 2)
				{
					tabAB[i][j] = tabA[i][j] + tabB[i][j];
				}
				else if (nrWatku == 3)
				{
					if (tabA[i][j] > maxA)
						maxA = tabA[i][j];
				}
				else
				{
					if (tabB[i][j] < minB)
						minB = tabB[i][j];				
				}
			}
		}
	}

	cout << "Czas etapu 2 (wyliczenie tablic C i D, dodanie tablic A i B," << endl << "znalezienie min z tablicy A i znalezienie max z tablicy B): " << clock() - czasOperacji << endl;
	czasOperacji = clock();

#pragma omp parallel num_threads(2)
	{
		nrWatku = omp_get_thread_num();

		if (nrWatku == 0 || nrWatku == 1)
		{
			for (int i = 0; i < 200; i++)
			{
				czekaj(1);
				for (int j = 0; j < 200; j++)
				{
					if (nrWatku == 0)
					{
						tabCmultiplyD[i][j] = tabC[i][j] * tabD[i][j];
					}
					else if(nrWatku == 1)
					{
						tabCsumming = tabCsumming + tabC[i][j];
					}
					else {
						tabDsumming = tabDsumming + tabD[i][j];
					}
				}
			}
		}
		else
		{
			czekaj(200);
			cout << "maxA: " << maxA << endl;
			cout << "minB: " << minB << endl;
			cout << "zsumowaneC: " << tabCsumming << endl;
			cout << "zsumowaneD: " << tabDsumming << endl;
		}
	}

	cout << "Czas trwania operacji 3 (zsumowanie i pomnozenie tablic C i D, wypisanie min i max): " << clock() - czasOperacji << endl;
	cout << "Nacisnij klawisz ...";
	
	_getch();
	return 0;
}