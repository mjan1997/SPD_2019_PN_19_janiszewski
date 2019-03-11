#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
int liczba_taskow;
int liczba_maszyn;
ifstream file("dane.txt", std::ifstream::in);
file >> liczba_taskow;
file >> liczba_maszyn;
//liczba_taskow = 20;
//liczba_maszyn = 5;
/*
std::cout << "liczba zadan : " << liczba_taskow<<std::endl;
    std::cout << "liczba maszyn : " << liczba_maszyn<<std::endl;
*/
int wartosci[liczba_taskow][liczba_maszyn];

    for(int a=0; a<liczba_taskow;a++)
        {
            for(int b=0; b<liczba_maszyn;b++)
            {
                int temp;
                file >> temp;
                wartosci[a][b] = temp;
               // std::cout << wartosci[a][b] << " ";
            }
           // cout << endl;
        }
        
        
/*        int wartosci[liczba_taskow][liczba_maszyn] = { 
{54,  79,  16,  66,  58}, 
{83,   3,  89,  58,  56},
 {15,  11,  49,  31,  20 },
 {71,  99 , 15 , 68,  85},
 {77 , 56  ,89  ,78 , 53},
 {36  ,70,  45,  91  ,35},
 {53,  99 , 60 , 13,  53},
 {38 , 60  ,23  ,59 , 41},
 {27  , 5,  57,  49  ,69},
 {87,  56 , 64 , 85,  13},
 {76 ,  3  , 7  ,85 , 86},
 {91  ,61,   1,   9  ,72},
 {14,  73 , 63 , 39,   8},
 {29 , 75  ,41  ,41 , 49},
 {12  ,47,  63,  56  ,47},
 {77,  14 , 47 , 40,  87},
 {32 , 21  ,26  ,54 , 58},
 {87  ,86,  75,  77  ,18},
 {68,   5 , 77 , 51,  68},
 {94 , 77  ,40  ,31 , 28}};
  */          
            
            
        
      /*  
        std::cout << std::endl; std::cout << std::endl;
        for(int a=0; a<liczba_taskow;a++)
        {
            for(int b=0; b<liczba_maszyn;b++)
            {
                std::cout << wartosci[a][b] << " ";
            }
            std::cout << std::endl;
        }
    */
    file.close();
    cout << endl;
    cout << endl;
    cout << "liczba maszyn : " << liczba_maszyn<<endl;
    std::cout << "liczba zadan : " << liczba_taskow<<std::endl;
    for(int i=0; i<liczba_maszyn;i++)
    {   cout <<"maszyna : " << i << " ";
    
        for(int j=0; j<liczba_taskow; j++)
        {
           
           //[j][i];
          cout << wartosci[j][i] << " ";
        }
        cout << "\n";
    }
    return 0;
}