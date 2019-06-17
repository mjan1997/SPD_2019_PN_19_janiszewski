#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;


class Zadanie {
public:
	int r; //czas dostepnosci zadania
	int p; // czas wykonania zadania
	int q; // czas dostarczenia zadania
	int nr_zadania; // numer zadania
	Zadanie() {
		r = 0;
		p = 0;
		q = 0;
		nr_zadania=0;
	}
};
/*zwraca najkr�tszy czas*/
Zadanie znajdz_min(vector<Zadanie> wek, vector<int> nNieuszeregowane, char czas);

/*zwraca najdluzszy czas*/
Zadanie znajdz_max(vector<Zadanie> wek, vector<int> nGotowe, char czas);

/*algorytm schrage z przerwaniami; zwraca cmax*/
int schragePMTN(vector<Zadanie> &wek);

/*algorytm schrage bez przerwan; zwraca wektor kolejnosci*/
vector<int> schrage(vector<Zadanie> wek);

/*funkcja celu zwracajaca cmax*/
int cmax(vector<int> kolejnosc, vector<Zadanie> wek,  int lZadan);








int C_MAX(vector<int> kolejnosc, vector<Zadanie> wek)
{
int a=0;
int C=0;
for(int i = 0; i < kolejnosc.size(); i++) // C_MAX z calego wektora kolejnosci
{
a = std::max(wek[i].r,a) + wek[i].p;
C = std::max(C,a+wek[i].q);
}
return C;
}

int C_MAX(vector<int> kolejnosc, vector<Zadanie> wek,int indeks)
{
int a=0;
int C=0;
for(int i = 0; i <= indeks; i++) //C_MAX do elementu o indeksie = indeks
{
a = std::max(wek[i].r,a) + wek[i].p;
C = std::max(C,a+wek[i].q);
}
return C;	
}








int znajdz (vector<int> kolejnosc, int b)
{   int indeks=0;
    bool found = false;
    for (auto & elem : kolejnosc)
    {
        if (elem == b)
        {   indeks = elem;
            found = true;
            break;
        }
    }
    return indeks;
}

int findB (int U, vector<int> kolejnosc, vector<Zadanie> wek)
{
	int C_MAX_start = C_MAX(kolejnosc, wek);
    int tmp = 0;
    int p=0;
    int rozmiar = kolejnosc.size();
	int wynik =0;
    for (int i =rozmiar-1; i>=0; i--)   // ew kolejnosc.size() -1
	{
	    //cout << wek[i].r << " " << wek[i].p << " " << wek[i].q << endl;
	    //p=max(p,wek[i].r)+wek[i].p; ////////////////////////////////////////zamiast tego \/
	    //cout << "suma :" << p+wek[i].q<<endl;
        	//if(U== p+wek[i].q) /// U = 1513, co jest zgodne z instrukcja, ale p+....q =! 1513 nigdy. -> zeszyt

			if(C_MAX(kolejnosc,wek,i) != C_MAX_start)
			{
				wynik = i+1;
				break;
			}
	}
	return wynik;
}

int findA(int U,vector<int> kolejnosc,vector <Zadanie> wek, int b)
{
	int p;
	int q=wek[b].q;
int indexB=0;
	//vector<int>::iterator indexB;

			indexB = znajdz(kolejnosc, b);
		//	int oo=*indexB;
		int oo = indexB;
		cout << endl;
		cout << oo << endl;
	for (auto & i : kolejnosc)  // .size() -1
	{
		p=0;
		//vector<int>::iterator index;
		int index;
		index= znajdz(kolejnosc,i);
		int o=index;
		for(int d=o;d<oo+1;d++)
		{
			p+=wek[kolejnosc[d]].p;
		}
		if(wek[i].r+p+q==U)
		{
			return i;
		}
	}
	return 0;
}
int findC(vector<int> kolejnosc,vector <Zadanie> wek, int aa, int bb)
{
	int j=0;
	vector<int>::iterator A;
	A=find(kolejnosc.begin(), kolejnosc.end(), aa);
	int a=*A;
	vector<int>::iterator B;
	B=find(kolejnosc.begin(), kolejnosc.end(), bb);
	int b=*B;


	for(int i=a;i<=b+1;i++) // .size() -1
	{
		if(wek[kolejnosc[i]].q<wek[kolejnosc[b]].q)
            j=kolejnosc[i];
        if(j!=0)
			return j;

	}
	return 0;
}

int maximum(int x, int y, int z) {
	int max = x;

	if (y > max) {
		max = y;
	}

	if (z > max) {
		max = z;
	}

	return max;

}
int Carlier(vector<Zadanie> wek,  int l_Zadan){
    vector <int> kolejnosc;
    vector<int> kolejnoscTMP = schrage(wek);
    vector<int> order =schrage(wek);////////////////////////////////////
    vector<int> K;
    Zadanie j;
    int a,b,c;
    int tempR, tempQ;
    int i = 0;
    int UB = 999999;
    int LB=0;
    int U;
    int hKc;


    U = cmax(order, wek, l_Zadan);//1 correct//////////////////////////////
    if(U<UB){ // 2 correct
        UB=U;//3 correct
        kolejnosc= kolejnoscTMP;//4 correct
    }
    b=findB(U,kolejnosc,wek); // 6 correct
    a=findA(U,kolejnosc,wek,b);// 7 correct
    c=findC(kolejnosc,wek,a,b);// 8 correct



	if(c=0) //9 correct
        return UB; //10 correct
cout << "wartosc : " << b-c-1 << endl;
    for(int x=0;x<(b-c-1);x++){ //12 correct
        K[x]=c+1;
        cout << "K[x] : " << K[x] << endl;
}

        for(int y=K[0]; y<b;y++){ //13 correct
       
            j=znajdz_min(wek,K,'r');
            j.p =j.p+wek[kolejnosc[y]].p;
            j=znajdz_min(wek,K,'q');
        }
        int h=j.r+j.p+j.q;

        //tempR=wek[c].r;
        wek[c].r=max(wek[c].r, j.r+j.p);// 14 correct
        LB=schragePMTN(wek);//15 correct
        hKc = min(j.r, wek[c].r)+j.p+wek[c].p+min(j.q,wek[c].q);
        LB=maximum(h,hKc,LB);// 16 correct
        if(LB<UB) //17 correct
            Carlier(wek,l_Zadan);//18 correct
        //wek[kolejnosc[c]].r=tempR;//20 correct

        //tempQ=wek[kolejnosc[c]].q;
        wek[c].q=max(wek[c].r, j.q+j.p);//21 correct
        LB=schragePMTN(wek);//22 correct
        hKc = min(j.r, wek[c].r)+j.p+wek[c].p+min(j.q,wek[c].q);
        LB=maximum(h,hKc,LB);//23 correct
        if(LB<UB)//24 correct
            Carlier(wek,l_Zadan);//25 correct
        //wek[kolejnosc[c]].q=tempQ;//27 correct;



}


int main()
{
    int l_Zadan;
    int k; //ilosc kolumn;
    /*wczytywanie danych do macierzy*/
    ifstream data("in50.txt");
	data >> l_Zadan;
	data >> k;
	vector<Zadanie> wek(l_Zadan);
	for (int j = 0; j < l_Zadan; j++) {
        {
			data >> wek[j].r;
			data >> wek[j].p;
			data >> wek[j].q;
			wek[j].nr_zadania = j + 1;
		}
	}

	//procedure CARLIER
	cout<<maximum(1,10,3);
	int x=Carlier(wek,l_Zadan);
	cout<<x;


/*

	vector<int> kolejnosc = schrage(wek);
    int Cmax = cmax(kolejnosc, wek, l_Zadan);
	int cmax2=schragePMTN(wek);


	cout << "Cmax wynosi: " << Cmax <<"j"<< endl<<endl;
	cout << "CmaxPMTN wynosi: " << cmax2 <<"j"<< endl<<endl;
    cout << "Kolejnosc wykonywania zadan: " << endl;
	for (int i = 0; i < kolejnosc.size(); i++) cout << kolejnosc[i] << "  ";


        cout<<endl<<"KONIEC PROGRAMU";
	return 0;*/
}

vector<int> schrage(vector<Zadanie> wek) {
    /*przypisanie macierzy glownej do macierzy pomocniczej*/
	vector<Zadanie> wek2 = wek;
	vector<int> kolejnosc;
	/* INICJALIZACJA ALGORYTMU*/
	int i=0; //NUMER ZADANIA W KOLEJNOSCI
	vector<int> czesciowaKolejnosc(0); // SKLADA SIE Z USZEREGOWANYCH ZADAN
	Zadanie j; // ZADANIE GOTOWE DO WYKONANIA
	vector<int> nGotowe(0); // zbior zadan gotowych do uszeregowania
	vector<int> nNieuszeregowane(wek.size()); //zbior zadan nieuszeregowanych
	for (int i = 0; i < nNieuszeregowane.size(); i++)
        nNieuszeregowane[i] = i+1;
	int t = znajdz_min(wek, nNieuszeregowane, 'r' ).r;
	/* BUDOWANIE ZBIORU ZADAN GOTOWYCH DO USZEREGOWANIA */
	//dopoki jeden wektor ma chociaz 1 element
	
	while (nGotowe.size() != 0 || nNieuszeregowane.size() != 0) {
	
            //dopoki sa jakies nieuszeregowane zadania i ktores z nich jest gotowe do realizacji
		while (nNieuszeregowane.size() != 0 && znajdz_min(wek, nNieuszeregowane, 'r').r <= t) {
			j = znajdz_min(wek, nNieuszeregowane, 'r'); // przypisanie elementu o najmniejszym r
			nGotowe.push_back(j.nr_zadania); // dodanie tego elementu do wektora gotowych do uszeregowania
			vector<int>::iterator doUsuniecia;
			doUsuniecia = find(nNieuszeregowane.begin(), nNieuszeregowane.end(), j.nr_zadania);
			int index;
			nNieuszeregowane.erase(doUsuniecia); //usuwanie elementu z nNieuszeregowane ktory zostal dodany do nGotowe
		}
		
        /* AKTUALIZACJA CHWILI CZASOWEJ T GDY NIE MA ZADAN GOTOWYCH DO USZEREGOWANIA*/
		// jezeli zadne zadanie nie jest obecnie wykonywane
		if (nGotowe.size() == 0) {
                // jezeli tak chwila t przesuwana jest do momentu dostepnosci najwcze�niejszego zadania ze zbioru
               //  i wznawiany proces aktualizowania zbioru zada� gotowych
			t = znajdz_min(wek, nNieuszeregowane, 'r').r;
		}
        // JESLI ZBIOR nGotowy NI JEST PUSTY DO CZESCIOWEGO USZEREGOWANIA DODAWANE JEST ZADANIA Z TEGO ZBIORU O NADJLUZSZYM CZASIE DOSTARCZANIA
		else {
			j = znajdz_max(wek, nGotowe, 'q'); //przypisanie do obecnego zadania maksymalnego q
			vector<int>::iterator doUsuniecia;
			doUsuniecia = find(nGotowe.begin(), nGotowe.end(), j.nr_zadania);
			czesciowaKolejnosc.resize(czesciowaKolejnosc.size() + 1); //zmieniamy rozmiar czesciowejKolejnosci
			czesciowaKolejnosc[i] = j.nr_zadania; // dodajemy aktualne zadanie do czesciowej kolejnosci
			nGotowe.erase(doUsuniecia);
            i++;
			t = t + wek[j.nr_zadania - 1].p; // aktualizacja chwili czasowej
		}
		

	}
    /*CZESCIOWA KOLEJNOSC ZAWIERA WSZYTSKIE ZADANIA ZE ZBIORU n STAD POSIADA GOTOWA KOLEJNOSC ZADAN*/

	kolejnosc = czesciowaKolejnosc;
	return kolejnosc;
}
int schragePMTN(vector<Zadanie> &wek) {
	/* INICJALIZACJA ALGORYTMU*/
	int cmax =0;
	Zadanie j,l; // zadanie gotowe do wykonania / obecnie wykonywane
	l.p=0;
	l.q=9999999;
	vector<int> nGotowe(0);
	vector<int> nNieuszeregowane(wek.size());
	for (int i = 0; i < nNieuszeregowane.size(); i++)
        nNieuszeregowane[i] = i+1;
	int t = 0;
	/* BUDOWANIE ZBIORU ZADAN GOTOWYCH DO USZEREGOWANIA */
	while (nGotowe.size() != 0 || nNieuszeregowane.size() != 0) {
		while (nNieuszeregowane.size() != 0 && znajdz_min(wek, nNieuszeregowane, 'r').r <= t) {
			j = znajdz_min(wek, nNieuszeregowane, 'r');
			nGotowe.push_back(j.nr_zadania);
			vector<int>::iterator doUsuniecia;
			doUsuniecia = find(nNieuszeregowane.begin(), nNieuszeregowane.end(), j.nr_zadania);
			nNieuszeregowane.erase(doUsuniecia);
			//gdy do nGotowe dodamy zadanie j* sprawdzane jest czy ma wiekszy czas dostarczania od obecnie wykonywanego zadania L
			//jezeli tak to zadanie jest przerywane; czas wykonywania skracany
			if(wek[j.nr_zadania - 1].q > wek[l.nr_zadania - 1].q)
            {
                wek[l.nr_zadania - 1].p = t - wek[j.nr_zadania - 1].r;
                t = wek[j.nr_zadania - 1].r;
                // pozostaka czesc czasu(jezeli istnieje) wkladana do zbioru zadan gotowych do realizaci
                if(wek[l.nr_zadania - 1].p>0)
                    nGotowe.push_back(l.nr_zadania);
            }
		}
        /* AKTUALIZACJA CHWILI CZASOWEJ T GDY NIE MA ZADAN GOTOWYCH DO USZEREGOWANIA*/
		if (nGotowe.size() == 0) {
			t = znajdz_min(wek, nNieuszeregowane, 'r').r;
		}

		else {
			j = znajdz_max(wek, nGotowe, 'q'); // przypisanie do obecnego zadania wart_max q
			vector<int>::iterator doUsuniecia;
			doUsuniecia = find(nGotowe.begin(), nGotowe.end(), j.nr_zadania);
			nGotowe.erase(doUsuniecia); //ze zbioru gotowych do uszeregowania usuwany zadanie gotowe do wykonania
 			l = j; // uaktualnienie zadania l
			t = t + wek[j.nr_zadania - 1].p;
			cmax = max(cmax,t+wek[j.nr_zadania - 1].q); //liczmy cmax
		}
	}
	cout << "cmax PTMN: " << cmax<<endl;;
	return cmax;
}
//funkcja celu to czas zakonczenia i dostearczenia wszytskich zadan
int cmax(vector<int> kolejnosc, vector<Zadanie> wek, int lZadan) {
    vector<int> C(lZadan); //wektor momentow zakonczenia zadan
	vector<int> S(C.size()+1); //momenty rozpoczecia wykonywania zadania
	S[0] = 0;
	//wczesniejsze zadanie nie moze zaczac sie wczesniej niz czas jego przygotowania i czas zakonczenia zadania poprzedniego
	S[1] = max(wek[kolejnosc[0] - 1].r, 0 + 0);
	C[0] = S[1] + wek[kolejnosc[0] - 1].p;
		for (int j = 2; j <= lZadan; j++) {
			S[j] = max(wek[kolejnosc[j-1] - 1].r, S[j - 1] + wek[kolejnosc[j - 2] - 1].p);
			C[j-1] = S[j] + wek[kolejnosc[j - 1]-1].p; //wyliczamy momenty zakonczenia zadan
		}
		/*dodawanie czasu dostarczania*/
		for(int i=0; i<C.size();i++)
            C[i] = C[i] + wek[kolejnosc[i]-1].q;
            /*szukanie indexu maksymalnej wartosci Cm ktora jest cmax'em*/
        vector<int>::iterator it = max_element(begin(C), end(C));
        int index = distance(C.begin(), it);
        	cout << "Cmax: " << C[index]<<endl;;
	return C[index];
}
Zadanie znajdz_min(vector<Zadanie> wek, vector<int> nNieuszeregowane, char czas)
{
	Zadanie Min;
	//ustawiamy odpowiednia duza wartosc zeby czs r/p/q byl mniejszy
	Min.r = 100000;
	Min.p = 100000;
	Min.q = 100000;
	int k;
	for (int i = 0; i < wek.size(); i++) {

            for (int j=0; j < nNieuszeregowane.size(); j++){
                    /* sprawdzenie czy nalezy do zbioru nieuszeregowanych */
                if (nNieuszeregowane[j] == wek[i].nr_zadania)
                {
                    k=i;
                    break;
                }
                else
                  k=-1;
                }
		/* skoro nalezy to sprawdzamy czy czas jest mniejszy od stalej czasowej */
		if(k>=0)
		{

		    switch(czas)
		    {
		        case 'r':
		            // sprawdzamy czy jest mniejsze od poprzednie minimum aby wiedziec czy mamy najmniejsza wartosc
		        if (wek[i].r < Min.r)
                Min = wek[i];
                break;
                case 'p':
		        if (wek[i].p < Min.p)
                Min = wek[i];
                break;
                case 'q':
		        if (wek[i].q < Min.q)
                Min = wek[i];
                break;
		    }
		}
	}
	return Min;

}
Zadanie znajdz_max(vector<Zadanie> wek, vector<int> nGotowe, char czas) {
	Zadanie Max;
	int k;
	Max.r =0 ;
	Max.p=0;
	Max.q=0;
	for (int i = 0; i < wek.size(); i++) {
        /* sprawdzenie czy nalezy do zbioru gotowych */
             for (int j=0; j < nGotowe.size(); j++){
                if (nGotowe[j] == wek[i].nr_zadania)
                {
                    k=i;
                    break;
                }
                else
                  k=-1;
                }

        /* skoro nalezy to sprawdzamy czy czas jest mniejszy od stalej czasowej */
        if(k>=0)
		{
			 switch(czas)
		    {
		        case 'r':
		        if (wek[i].r > Max.r)
                Max = wek[i];
                break;
                case 'p':
		        if (wek[i].p > Max.p)
                Max = wek[i];
                break;
                case 'q':
		        if (wek[i].q > Max.q)
                Max = wek[i];
                break;
		    }
		}
	}
	return Max;
}