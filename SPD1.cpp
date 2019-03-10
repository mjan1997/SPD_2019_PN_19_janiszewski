#include <string>
#include <fstream>
#include <iostream>
using namespace std;
int liczba_maszyn =0;
int liczba_taskow =0;

struct Zadanie
{
    int czas;

};

struct Maszyna
{

    Zadanie zadania[];
};

struct Fabryka
{
    Maszyna machine[];
};



int main()
{

int liczba_taskow;
int liczba_maszyn;

ifstream file("dane.txt", std::ifstream::in);
file >> liczba_taskow;
file >> liczba_maszyn;
cout << "liczba zadan : " << liczba_taskow<<endl;
    cout << "liczba maszyn : " << liczba_maszyn<<endl;
Fabryka fabryka;
int wartosci[liczba_taskow][liczba_maszyn];

    for(int a=0; a<liczba_taskow;a++)
        {
            for(int b=0; b<liczba_maszyn;b++)
            {
                int temp;
                file >> temp;
                wartosci[a][b] = temp;
                std::cout << temp << " ";
            }
            cout << endl;
        } cout << endl; cout << endl;
        for(int a=0; a<liczba_taskow;a++)
        {
            for(int b=0; b<liczba_maszyn;b++)
            {
                std::cout << wartosci[a][b] << " ";
            }
            cout << endl;
        }
    
    file.close();
    cout << endl;
    cout << endl;
    cout << "liczba maszyn : " << liczba_maszyn<<endl;
    for(int i=0; i<liczba_maszyn;i++)
    {   cout << i << " ";
        for(int j=0; j<liczba_taskow; j++)
        {
           fabryka.machine[i].zadania[j].czas=wartosci[j][i];
           cout << fabryka.machine[i].zadania[j].czas << " ";
        }cout << endl;
    }cout << endl;cout << endl;


for(int x=0; x<liczba_taskow;x++)
cout << fabryka.machine[0].zadania[x].czas << " ";
cout << endl;
    return 0;
}