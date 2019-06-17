#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int IleZadan, IleOperacji;
class Zadanie
{
public:
	int r;			//czas dostepnosci zadania
	int p;			// czas wykonania zadania
	int q;			// czas dostarczenia zadania
	int nr_zadania; // numer zadania
	Zadanie()
	{
		r = 0;
		p = 0;
		q = 0;
		nr_zadania = 0;
	}
};

int find(vector<Zadanie> dane, int nr_zadania)
{
	for (int i = 0; i < dane.size(); i++)
	{
		if (nr_zadania == dane[i].nr_zadania)
			return i;

	}
}

Zadanie rmin(vector<Zadanie> dane)
{
	int rMin = 10000;
	Zadanie task;
	for (int i = 0; i < dane.size(); i++)
	{
		if (rMin >= dane[i].r)
		{
			task = dane[i];
			rMin = dane[i].r;
		}

	}
	return task;
}

Zadanie qmax(vector<Zadanie> dane)
{
	Zadanie task;
	int qMax = 0;
	for (int i = 0; i < dane.size(); i++)
	{
		if (qMax < dane[i].q)
		{
			task = dane[i];
			qMax = dane[i].q;
		}

	}
	return task;
}

int znajdz_max(int a, int b) ///////////
{
	return (a > b) ? a : b;
}
void wypisz(vector<Zadanie> dane)
{
	for (int i = 0; i < IleZadan; i++)
		cout << dane[i].nr_zadania << " ";
	cout << endl;
}

int Cmax(vector<Zadanie> dane)
{
	vector<int> C(IleZadan);
	vector<int> S(C.size() + 1);
	S[0] = 0;
	S[1] = znajdz_max(dane[0].r, 0 + 0);
	C[0] = S[1] + dane[0].p;
	for (int j = 2; j <= IleZadan; j++)
	{
		S[j] = znajdz_max(dane[j - 1].r, S[j - 1] + dane[j - 2].p);
		C[j - 1] = S[j] + dane[j - 1].p;
	}
	for (int i = 0; i < C.size(); i++)
	{
		C[i] = C[i] + dane[i].q;
	}
	vector<int>::iterator it = max_element(begin(C), end(C));
	int index = distance(C.begin(), it);
	return C[index]; 
}

int findB(vector<Zadanie> dane)
{
	vector<int> tmp2(IleZadan);
	vector<int> tmp1(tmp2.size() + 1);
	tmp1[0] = 0;
	tmp1[1] = znajdz_max(dane[0].r, 0 + 0);
	tmp2[0] = tmp1[1] + dane[0].p;
	for (int j = 2; j <= IleZadan; j++)
	{
		tmp1[j] = znajdz_max(dane[j - 1].r, tmp1[j - 1] + dane[j - 2].p);
		tmp2[j - 1] = tmp1[j] + dane[j - 1].p;
	}
	for (int i = 0; i < tmp2.size(); i++)
	{
		tmp2[i] = tmp2[i] + dane[i].q;
	}
	vector<int>::iterator it = max_element(begin(tmp2), end(tmp2));
	int index = distance(tmp2.begin(), it);
	return index;
}

int findA(vector<Zadanie> dane)
{
	int aa=0;
	int tmp2=0;
	tmp2 =dane[0].r;
	for (int i = 1; i < dane.size(); i++)
	{
		tmp2 = tmp2 + dane[i-1].p;
		if (dane[i].r > tmp2)
		{
			tmp2 = dane[i].r;
			aa = i;
		}
		}
	return aa;
}


vector<Zadanie> Schrage(vector<Zadanie> dane)
{
	int i = 1;
	vector<Zadanie> czesciowaKolejnosc;
	vector<Zadanie> nGotowe(0);
	vector<Zadanie> nNieuszeregowane(IleZadan);
	nNieuszeregowane = dane;
	Zadanie j;
	int t = rmin(nNieuszeregowane).r;
	while (nGotowe.size() != 0 || nNieuszeregowane.size() != 0)
	{
		while (nNieuszeregowane.size() != 0 && rmin(nNieuszeregowane).r <= t)
		{
			j = rmin(nNieuszeregowane);

			nGotowe.push_back(j);
			nNieuszeregowane.erase(nNieuszeregowane.begin() + find(nNieuszeregowane, j.nr_zadania));

		}
		if (nGotowe.size() == 0)
			t = rmin(nNieuszeregowane).r;
		else
		{
			j = qmax(nGotowe);
			nGotowe.erase(nGotowe.begin() + find(nGotowe, j.nr_zadania));
			czesciowaKolejnosc.push_back(j);
			i++;
			t = t + j.p;
		}
	}
	return czesciowaKolejnosc;
}

int findC(vector<Zadanie> dane,int a,int b)
{
	int cc = 999999;
	for (int i = a; i < b; i++)
		if (dane[i].q < dane[b].q)
		{
			cc = i;
		}
				return cc;
}


int schragePMTN(vector<Zadanie> dane)
{
	int cmax = 0;
	vector<Zadanie> nGotowe(0);
	vector<Zadanie> nNieuszeregowane(IleZadan);
	nNieuszeregowane = dane;
	Zadanie j;
	Zadanie l;
	int t = 0;
	l.q = 9999;
	l.p = 0;

	while (nGotowe.size() != 0 || nNieuszeregowane.size() != 0)
	{
		while (nNieuszeregowane.size() != 0 && rmin(nNieuszeregowane).r <= t)
		{
			j = rmin(nNieuszeregowane);

			nGotowe.push_back(j);
			nNieuszeregowane.erase(nNieuszeregowane.begin() + find(nNieuszeregowane, j.nr_zadania));

			if (j.q > l.q)
			{
				l.p = t - j.r;
				t = j.r;

				if (l.p > 0)
				{
					nGotowe.push_back(l);
				}
			}
		}
		if (nGotowe.size() == 0)
			t = rmin(nNieuszeregowane).r;
		else
		{
			j = qmax(nGotowe);
			nGotowe.erase(nGotowe.begin() + find(nGotowe, j.nr_zadania));
			l = j;
			t = t + j.p;
			cmax = znajdz_max(cmax, t + j.q);
		}
	}
	return cmax;
}
bool koniec=false;
int UB = 999999;
vector<Zadanie> piG;

vector<Zadanie> Carlier(vector<Zadanie> dane)
{
	if (koniec == false)
	{
		int pom;
		int aa = findA(Schrage(dane)), bb = findB(Schrage(dane));
		int cc = findC(Schrage(dane), aa, bb); 
		vector<int>K(dane.size());
		int LB;
		int rK = 999999, pK = 0, qK = 999999, hK;
		int rKc = 999999, pKc = 0, qKc = 999999, hKc;
		vector<Zadanie> pi = Schrage(dane);
		vector<Zadanie> daneOryginal=pi;
		int U = Cmax(pi);
		if (U < UB)
		{
			UB = U;
			piG = pi;
		}
		if (cc == 999999)
		{
			cout << UB << "  :  " << endl;
			koniec = true;
			return piG;
		}
		for (int i = cc + 1; i < bb + 1; i++) {
			K[i - (cc + 1)] = i;
			if (rK > pi[i].r)
    			{
    				rK = pi[i].r;
    			}
			if (qK > pi[i].q)
    			{
    				qK = pi[i].q;
    			}
			pK += pi[i].p;
		}
		pi[cc].r = znajdz_max(pi[cc].r, (rK + pK));
		LB = schragePMTN(pi);
		hK = rK + pK + qK;

		for (int i = cc; i < bb + 1; i++) {
			K[i - (cc)] = i;
			if (rKc > pi[i].r)
    			{
    				rKc = pi[i].r;
    			}
			if (qKc > pi[i].q)
    			{
    				qKc = pi[i].q;
    			}
			pKc += pi[i].p;
		}
		hKc = rKc + pKc + qKc;
		pom = znajdz_max(hKc, hK);
		LB = znajdz_max(LB, pom);
		if (LB < UB)
		{
			Carlier(pi);
		}
		pi = daneOryginal; 
		pi[cc].q = znajdz_max(pi[cc].q, (qK + pK));
		LB = schragePMTN(pi);
		pom = znajdz_max(hK, hKc);
		LB = znajdz_max(LB, pom);
		if (LB < UB)
		{
			Carlier(pi);
		}
		pi = daneOryginal; 
	}
	return piG;
}

int main()
{
    
    ifstream data("in50.txt");
	data >> IleZadan;
	data >> IleOperacji;
	vector<Zadanie> dane(IleZadan);
	for (int j = 0; j < IleZadan; j++)
	{
		{
			data >> dane[j].r;
			data >> dane[j].p;
			data >> dane[j].q;
			dane[j].nr_zadania = j + 1;
		}
	}
	
	
	cout << endl << "Cmax  Schrage: " << Cmax(Schrage(dane)) << endl;
	wypisz(Schrage(dane));
	cout << "Cmax SchragePMTN:" << schragePMTN(dane) << endl;
	
	
	cout << "a: " << findA(Schrage(dane)) << endl;
	cout << "b:" << findB(Schrage(dane)) << endl;
	cout << "c: " << findC(Schrage(dane), findA(Schrage(dane)), findB(Schrage(dane))) << endl;
	
	
	cout << "kolejnosc Caliera: ";
	wypisz(Carlier(dane));
	cout << "Cmax Caliera: ";
	cout<<Cmax(Carlier(dane)) << endl;
	cout << "gotowe" << endl;
}