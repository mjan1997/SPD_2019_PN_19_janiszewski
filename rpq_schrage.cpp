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
/*zwraca najkrótszy czas*/
Zadanie znajdz_min(vector<Zadanie> wek, vector<int> nNieuszeregowane, char czas);

/*zwraca najdluzszy czas*/
Zadanie znajdz_max(vector<Zadanie> wek, vector<int> nGotowe, char czas);

/*algorytm schrage z przerwaniami; zwraca cmax*/
int schragePMTN(vector<Zadanie> &wek);

/*algorytm schrage bez przerwan; zwraca wektor kolejnosci*/
vector<int> schrage(vector<Zadanie> wek);

/*funkcja celu zwracajaca cmax*/
int cmax(vector<int> kolejnosc, vector<Zadanie> wek,  int lZadan);


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



	vector<int> kolejnosc = schrage(wek);
    int Cmax = cmax(kolejnosc, wek, l_Zadan);
	int cmax2=schragePMTN(wek);


	cout << "Cmax wynosi: " << Cmax <<"j"<< endl<<endl;
	cout << "CmaxPMTN wynosi: " << cmax2 <<"j"<< endl<<endl;
    cout << "Kolejnosc wykonywania zadan: " << endl;
	for (int i = 0; i < kolejnosc.size(); i++) cout << kolejnosc[i] << "  ";


        cout<<endl<<"KONIEC PROGRAMU";
	return 0;
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
                // jezeli tak chwila t przesuwana jest do momentu dostepnosci najwcześniejszego zadania ze zbioru
               //  i wznawiany proces aktualizowania zbioru zadań gotowych
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
