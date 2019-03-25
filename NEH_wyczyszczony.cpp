#include <iostream>     
#include <algorithm>    
#include <fstream>
using namespace std;
#define MAX_LICZBA_MASZYN 22 
#define MAX_LICZBA_ZADAN 50

int cmax( int tab[MAX_LICZBA_ZADAN][MAX_LICZBA_MASZYN], int l_zadan, int l_maszyn,int permutation[])
{
	int cMax = 0;
	int endOfTask = 0; 
	int tab_Cmax[MAX_LICZBA_ZADAN+1][MAX_LICZBA_MASZYN+1];
	// zerowanie cmax
		for (int i = 0; i <= l_zadan; ++i){
		for (int j = 0; j <= l_maszyn; ++j)
			tab_Cmax[i][j] = 0;
    }
	// Obliczanie Cmax
	for (int i = 1; i <= l_zadan; ++i){
		for (int j = 1; j <= l_maszyn; ++j)
		    tab_Cmax[i][j] = max(tab_Cmax[i-1][j], tab_Cmax[i][j-1]) + tab[permutation[i -1] -1][j-1];
    }
    return tab_Cmax[l_zadan][l_maszyn];
}
int factorial(int a) {
	for (int i = a-1; i > 0; i--)
		a *= i;
	return a;
}

/*int *b_sort(int num[],int n_tasks)
{
 
    int i,j;
    for(i=0;i<(n_tasks-1);i++)
    {
        for(j=i+1;j<n_tasks;j++)
        {
            int temp;
            if(num[i]<num[j])
            {
                temp = num[i];
                num[i]=num[j];
                num[j]=temp;
            }
        }
    }
    return num;
    
}*/

bool porownanie(int a, int b)
{
    return a>b;
}

int main() {
    
    int tab[MAX_LICZBA_ZADAN][MAX_LICZBA_MASZYN];
	int n_tasks = 0;
	int n_mach  = 0; // liczba maszyn
	int k = 0; // aktualna permutacja
	ifstream data("data.txt");
	data >> n_tasks; 
	data >> n_mach;
	int permutation[n_tasks]; //tablica permutacji kolejnosci zadan
	int quantity = factorial(n_tasks);
	int cMax;
	for (int i = 0; i < n_tasks; i++)
	for (int j = 0; j < n_mach; j++)
	{
		data >> tab[i][j];
	//	permutation[i] = i + 1;              
	}
	int tablica_indeksow[n_tasks][2];
	int temp_tablica_czasow[n_tasks];//tablica sum czasow dla poszczegolnych zadan
	for (int i = 0; i < n_tasks; i++)//liczenie sumy czasow wykonania na wszyskich maszynach dla danego zadania
	{
	    int wartosc =0;
	    for (int j = 0; j < n_mach; j++)
	    {
		wartosc = wartosc + tab[i][j];
	    }
	    temp_tablica_czasow[i] = wartosc;
	    for(int n=0; n<n_tasks;n++)
	    {
	        if(n!=i)
	        {
	            if(wartosc == temp_tablica_czasow[n])
	            {
	                wartosc = wartosc + 9876;
	                
	            }
	            
	        }
	        
	    }
	    
        tablica_indeksow[i][0] = i+1;
        tablica_indeksow[i][1] = wartosc;
    
	    
	}
    cout << "Wczytane zadania z ich numerami i suma czasow wykonania na wszystkich maszynach :\n\n";
    for (int i = 0; i < n_tasks; i++) 
    {
        if(temp_tablica_czasow[i] > 9800)
        {
            cout << tablica_indeksow[i][0] << " " << temp_tablica_czasow[i] - 9876<< "\n";
        }
        else
        {
            cout << tablica_indeksow[i][0] << " " << temp_tablica_czasow[i] << "\n";
        }
   //wyswietlenie sum czasow dla poszczegolnych zadan
    }
    cout << "\n";
    
    
	sort(temp_tablica_czasow, temp_tablica_czasow+n_tasks,porownanie);
	int tablica_kolejnosci[n_tasks];
    cout <<"Numery zadan razem z suma czasow wykonania na wszystkich maszynach :\n\n";
	 for (int i = 0; i < n_tasks; i++) 
    {
        int numer=0;
        for(int x=0; x<n_tasks; x++)
        {
            if(tablica_indeksow[x][1] == temp_tablica_czasow[i] && tablica_indeksow[x][1] < 9876)
            {
                numer = tablica_indeksow[x][0];
                tablica_kolejnosci[i] = numer;
              //  cout << "aaaa " << tablica_indeksow[x][1] << "  " << x<< "\n";
            }
            else if(tablica_indeksow[x][1] > 9800 && tablica_indeksow[x][1]-9876 == temp_tablica_czasow[i])
            {
              
                numer = tablica_indeksow[x][0];
                tablica_kolejnosci[i] = numer;
               // cout << "xxxx " << tablica_indeksow[x][1] << "  " << x<< "\n";
                tablica_indeksow[x][1] =0;
            }
        }
        cout << numer << " " <<temp_tablica_czasow[i] << "\n";///////////////////zadania w odpowiedniej kolejności
    }
    cout << "\n";
    //wyswietlenie sum czasow dla poszczegolnych zadan, uporzadkowanych
	int temp_tab[MAX_LICZBA_ZADAN][MAX_LICZBA_MASZYN];
	int indeks=0;
	cout << "\n";
	cout << "Zadnia ustawione w wybranej kolejnosci :\n\n";
	for (int i = 0; i < n_tasks; i++)
	{
	    indeks = tablica_kolejnosci[i];
	    for (int j = 0; j < n_mach; j++)
	    {
		    temp_tab[i][j]= tab[indeks-1][j];
		    permutation[i] = i;      
		    cout << temp_tab[i][j] << " ";
	    }
	    cout << "\n";
	}
	
	cout << "\n";
	
	cout << "Weryfikacja ze mamy dobra kolejnosc :\n\n";
	for(int i=0; i<n_tasks; i++)
	{
	cout << tablica_kolejnosci[i] << "\n";
	}
	cout << "\n";
	
	cout << "tabelka pozwalajaca na prawidlowe dialanie next_permutation z nasza klejnoscia :\n\n";
	int order_table[MAX_LICZBA_ZADAN][MAX_LICZBA_MASZYN];
    for (int i = 1; i <= n_tasks; i++)
	{ 
	    int tymczasowa[i];
	    for (int j = 0; j < i; j++)
	    {   
	        tymczasowa[j] = tablica_kolejnosci[j];
	    }
	       // cout << tymczasowa[j] << "t ";
	        sort(tymczasowa, tymczasowa+i);
	     for (int j = 0; j < i; j++)
	     {
	        order_table[i-1][j] = tymczasowa[j];
	        	cout << order_table[i-1][j] << " ";
	     }
	    	cout << "\n";
	}
	
		cout << "\n";
	cout << "Wszystkie permutacje z cmax'ami najlepszymi :\n\n";
	int maxy[n_tasks];
	for(int h=1;h<=n_tasks;h++)
	{
	    int maxcmax=999999;
    	do {
    	    
        		cMax = cmax(temp_tab, h,n_mach,order_table[h-1]); //liczymy Cmax dla aktualnej kolejności zadań
        		if(cMax<maxcmax){maxcmax=cMax;}
        		for(int z=0;z<h;z++)
        		cout << order_table[h-1][z] << " ";
        		cout<<"--- "<<cMax << 'j' << '\n';
    
    	    } while (next_permutation(order_table[h-1], order_table[h-1] + h));
    	cout << "najlepsze cmax ==" << maxcmax << "\n\n";
    	maxy[h-1] = maxcmax;
	}
		cout << "\n";
		
		
	cout << "Najlepsze mozliwe kolejnosci :\n\n";
   	for(int h=1;h<=n_tasks;h++)
   	{
	    do {
	       		cMax = cmax(temp_tab, h,n_mach,order_table[h-1]); //liczymy Cmax dla aktualnej kolejności zadań
        		if(cMax == maxy[h-1])
        		{
        		    for(int z=0;z<h;z++)
        		    cout << order_table[h-1][z] << " ";
        		    cout<<"--- "<<cMax << 'j' << '\n';

                }
		    }
        	while (next_permutation(order_table[h-1], order_table[h-1] + h));
        	cout << "\n";
	}
	cout << "Najlepsza kolejnosc :\n\n";
	for(int h=1;h<=n_tasks;h++)
   	{
	    do {
	       		cMax = cmax(temp_tab, h,n_mach,order_table[h-1]); //liczymy Cmax dla aktualnej kolejności zadań
        		if(cMax == maxy[h-1])
        		{
        		    for(int z=0;z<h;z++)
        		    cout << order_table[h-1][z] << " ";
        		    cout<<"--- "<<cMax << 'j' << "\n";
break;
                }
		    }
        	while (next_permutation(order_table[h-1], order_table[h-1] + h));

	}
	return 0;
}