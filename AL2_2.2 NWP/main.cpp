#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

#define MAX 25 //max dlugosc napisow

int lookup[MAX][MAX]; //dlugosc NWP X i Y, tabelka

//wyliczymy d³ugoœæ NWP
//tabelka jak z przykladu
void NWPLength(string X, string Y, int m, int n)
{
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (X[i - 1] == Y[j - 1]) {
				lookup[i][j] = lookup[i - 1][j - 1] + 1; //lookup jest globalne zeby tego nie przekazywac caly czas
			}
			else {
				lookup[i][j] = max(lookup[i - 1][j], lookup[i][j - 1]);
			}
		}
	}
}

//znalezienie WSZYSTKICH NWP dla X i Y
vector<string> NWP(string X, string Y, int m, int n)
{
	if (m == 0 || n == 0) //ktorys z napisow jest pusty
	{
		vector<string> v(1);
		return v; // zwrcamy wektor z pustym napisem
	}

	else if (X[m - 1] == Y[n - 1]) //jezei ostatni znak jest taki sam
	{
		vector<string> nwp = NWP(X, Y, m - 1, n - 1); // to znajdujemy wszsytkie NWP dla napisow bez ostatniego zanku

		for (string &str: nwp) {
			str.push_back(X[m - 1]);// i na koniec dalaczamy go do wszystkich znalezionych
		}

		return nwp;
	}
//jezeli ostatni znak X i Y nie jest taki sam
	else if (lookup[m - 1][n] > lookup[m][n - 1])//jesli kratka nad ma wieksza wartosc niz ta po lewej
		return NWP(X, Y, m - 1, n);//pomijamy aktualny znak od X

	else if (lookup[m][n - 1] > lookup[m - 1][n])//odwrotnie niz wyzej
		return NWP(X, Y, m, n - 1);//pomijamy znak Y

    else//jesli wartosci sa takie same
    {   //rozpatrujemy oba znaki
        vector<string> top = NWP(X, Y, m - 1, n);
        vector<string> left = NWP(X, Y, m, n - 1);

        //scalamy 2 wektory
        top.insert(top.end(), left.begin(), left.end());

        return top;
    }
}

//wszsytkie najdluzsze podciagi i eleminujemy powtorzenia
set<string> NWP(string X, string Y)
{
	int m = X.length(), n = Y.length();

	NWPLength(X, Y, m, n);//liczenie dlugosci w lookup

	vector<string> v = NWP(X, Y, m, n);//dostajemy wektor ze wszsytkimi NWP

	set<string> NWP(make_move_iterator(v.begin()), // set nie moze miec powtorzen wiec zmieniamy vektor  na set
					make_move_iterator(v.end()));

	return NWP;
}

int main()
{

	string X = "abbaac", Y = "bacbacba";

	set<string> nwp = NWP(X, Y);

	for (string str: nwp)
		cout << str << endl;

    for(int i=0; i<9; i++){
        for(int j=0 ; j<9; j++)
            cout << lookup[i][j];
        cout<< endl;
    }


	return 0;
}
