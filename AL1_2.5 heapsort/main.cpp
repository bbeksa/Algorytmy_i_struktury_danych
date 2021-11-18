#include <fstream>
#include <iostream>
#include <stdio.h>
using namespace std;

void kopcowanie(int T[], int n, int i)
{
    int najwiekszy = i;
    int l = 2*i;
    int r = 2*i + 1;

    if (l < n && T[l] > T[najwiekszy])
        najwiekszy = l;

    if (r < n && T[r] > T[najwiekszy])
        najwiekszy = r;

    if (najwiekszy != i)
    {
        swap(T[i], T[najwiekszy]);
        kopcowanie(T, n, najwiekszy);
    }
}

void HeapSort(int T[], int Pocz, int Kon)
{
    int n = Kon - Pocz;
    for (int i = n / 2 - 1 + Pocz; i >= Pocz; i--)
        kopcowanie(T, n, i);

    for (int i=Kon; i>Pocz; i--)
    {
        swap(T[Pocz], T[i]);
        kopcowanie(T, i, Pocz);
    }
}

void PokazTab(int T[], int n)
{
    for (int i=0; i<n; i++)
        cout << T[i] << ", ";
    cout << "\n";
}

int main()
{
    int pocz;
    int kon;
    int T[10];
    int tmp = 0;
    ifstream liczby("wejscie.txt");

    if (!liczby)
    {
        cout << "Nie mozna otworzyc pliku";
        return 1;
    }

    liczby >> pocz;
    liczby >> kon;
    while (!liczby.eof())
        liczby >> T[tmp++];

    liczby.close();


    HeapSort(T, pocz, kon);
    PokazTab(T, 10);


    ofstream wynik("wynik.txt");

    for (int i=0; i<10; i++)
        wynik << T[i] << "\n";

    wynik.close();
}
