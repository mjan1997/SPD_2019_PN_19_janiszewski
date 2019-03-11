#include <iostream>     
#include <algorithm>    
#include <fstream>
using namespace std;

int cmax(int timeM1[], int timeM2[], int n, int permutation[])
{
	int cMax = 0;
	int endOfTask = 0; // czas zakonczenie zadania na M1

	for (int i = 0; i < n; i++)
	{
		endOfTask = endOfTask + timeM1[permutation[i] - 1];
		if (cMax < endOfTask)
			cMax = endOfTask + timeM2[permutation[i] - 1];
		else
			cMax += timeM2[permutation[i] - 1];
	}
	return cMax;
}

int factorial(int a) {
	for (int i = a; i > 0; i--)
		a *= i;
	return a;
}

int main() {
	int n_tasks = 1;
	int k = 0; // aktualna permutacja
	ifstream data("data.txt");
	data >> n_tasks; 
	int timeM1[n_tasks], timeM2[n_tasks]; // czas wykonywania zadania przez 1 oraz 2 maszyne
	int permutation[n_tasks]; //tablica permutacji kolejnosci zadan
	int quantity = factorial(n_tasks);
	int cMax[quantity];
	for (int i = 0; i < n_tasks; i++)
	{
		data >> timeM1[i] >> timeM2[i]; 
		permutation[i] = i + 1;              
	}
	do {
		cMax[k] = cmax(timeM1, timeM2, n_tasks, permutation); //liczymy Cmax dla aktualnej kolejnosci zadan
		cout << permutation[0] << ' ' << permutation[1] << ' ' << permutation[2] << ' ' << permutation[3] << ' ' << permutation[4] << ' ' << '-' << ' ' << cMax[k] << 'j' << '\n';
		k++;

	} while (next_permutation(permutation, permutation + n_tasks));

	return 0;
}