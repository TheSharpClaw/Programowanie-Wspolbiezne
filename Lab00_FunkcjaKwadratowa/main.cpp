#include<iostream>
#include<conio.h>

using namespace std;

class Delta
{
private:
	float a, b, c, x1, x2;

public:
	Delta(float a, float b, float c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}

	float policzDelta()
	{
		if(a != 0)
			return (pow(b, 2) - 4 * a*c);
	}	

	float policzX0()
	{
		return ((-b) / (2 * a));
	}

	float policzX1(int delta)
	{
		return ((-b - sqrt(delta)) / (2 * a));
	}

	float policzX2(int delta)
	{
		return ((-b + sqrt(delta)) / (2 * a));
	}
};

int main()
{
	float tabLiczby[3];
	
	for (int i = 1; i < 4; i++)
	{
		cout << "Podaj liczbe nr" << i << ":" << endl;
		cin >> tabLiczby[i-1];
		system("cls");
	}
	cout << "Podane liczby: " << tabLiczby[0] << ", " << tabLiczby[1] << ", " << tabLiczby[2] << endl;	

	Delta delta(tabLiczby[0], tabLiczby[1], tabLiczby[2]);

	int policzonaDelta = delta.policzDelta();;

	cout << "Delta = " << policzonaDelta << endl;
	if (policzonaDelta < 0)
	{					
		cout << "Zespolony x1 = " << delta.policzX1(abs(policzonaDelta)) << endl;
		cout << "Zespolony x2 = " << delta.policzX2(abs(policzonaDelta)) << endl;
	}
	else if (policzonaDelta == 0) {
		cout << "x0 = " << delta.policzX0() << endl;
	}
	else 
	{				
		cout << "x1 = " << delta.policzX1(policzonaDelta) << endl;
		cout << "x2 = " << delta.policzX2(policzonaDelta) << endl;
	}

	_getch();
	return 0;
}