#include <iostream>
#include <bits/stdc++.h>

using namespace std;
//Wyliczanie tablicy prefiksów pi
void prefixFunction(char* P, int m, int* pi)
{
	int k = 0; //dlugosc poprzedniegi najdluzszego prefiksu-sufiksu
	pi[0] = 0;

	int q = 1;
	while (q < m){
		if (P[q] == P[k]) {
			k++;
			pi[q] = k;
			q++;
		}
		else{
			if (k != 0) {
				k = pi[k - 1];//bez zwiekszania q
			}
			else{
				pi[q] = 0;
				q++;
			}
		}
	}
}


void KMP(char* P, char* T)
{
	int m = strlen(P);
	int n = strlen(T);

	int pi[m]; //zawiera najdluzsze wartosci prefiksy-sufiksy dla wzorca
	//to co na kartkowce
	prefixFunction(P, m, pi);

	int i = 0; //indeks T
	int q = 0; //indeks P
	while (i < n) {
		if (P[q] == T[i] || T[i] == '?') {
			q++;
			i++;
		}

		if (q == m) {//sprawdzamy czy dlugosc jest taka jak z wzorcem jesli tak wypisujemy
			cout << "Wzorzec znaleziono w indeksie: " << (i - m + 1) << endl;
			q = pi[q - 1];
		}
		//zniezgodnosc po q dopasowaniach
		else if (i < n && (P[q] != T[i] && T[i] != '?')) { // pomijamy pi[0]...pi[q-1] ktore pasuja
			if (q != 0)
				q = pi[q - 1];
			else
				i = i + 1;
		}
	}
}

int main()
{
	char T[] = "xxxababcadtucjyfvgbi";
	char T1[] = "xab?xxab??cadtucjyfvababcagbi";
	char T2[] = "xxxxxgbi";
	char P[] = "ababca";

	for(int i=0; i<strlen(T); i++)
       	cout <<  T[i];
    cout << endl << "   ";
    for(int i=0; i<strlen(P); i++)
       	cout <<  P[i];
    cout << endl;
	KMP(P, T);

	cout << "-------------------" << endl;
    for(int i=0; i<strlen(T1); i++)
       	cout <<  T1[i];
    cout << endl << "      ";
    for(int i=0; i<strlen(P); i++)
       	cout <<  P[i];
    cout << "        ";
    for(int i=0; i<strlen(P); i++)
       	cout <<  P[i];
    cout << endl;
	KMP(P, T1);

    cout << "-------------------" << endl;
    KMP(P, T2);
	return 0;
}
