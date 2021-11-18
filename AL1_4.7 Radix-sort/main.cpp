#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

//********************radixsort********************
size_t getMax(string arr[], int n)
{
    size_t maks = arr[0].size();
    for (int i = 1; i < n; i++)
    {
        if (arr[i].size()>maks)
            maks = arr[i].size();
    }
    return maks;
}

void countSort(string N[], int wielkosct, size_t k, int L[])
{
    string *nn = NULL;
    int *c = NULL;
    int *licz = NULL;
    nn = new string[wielkosct];
    c = new int[255];
    licz = new int[wielkosct];

    for (int i = 0; i <255; i++)
        c[i] = 0;

    for (int i = 0; i <wielkosct; i++)                              //c[N[i][k]] ilosc liter w slowach
        c[k < N[i].size() ? (int)(unsigned char)N[i][k] + 1 : 0]++; //Je¿eli k jest wiêksze od N[i].size()
                                                                    //to (int)(unsigned char)N[i][k] + 1
    for (int i = 1; i <255; i++)                                    //a przeciwnym razie (int)(unsigned char)N[i][k] + 0

        c[i] += c[i - 1];

    for (int i = wielkosct - 1; i >= 0; i--)
    {
        nn[c[k < N[i].size() ? (int)(unsigned char)N[i][k] + 1 : 0] - 1] = N[i];
        licz[c[k < N[i].size() ? (int)(unsigned char)N[i][k] + 1 : 0] - 1] = L[i];
        c[k < N[i].size() ? (int)(unsigned char)N[i][k] + 1 : 0]--;
    }

    for (int l = 0; l < wielkosct; l++)
    {
        N[l] = nn[l];
        L[l] = licz[l];
    }

    delete[] nn;
    delete[] c;
    delete[] licz;
}

void radixsort(string N[], int n, int L[])
{
    size_t maks = getMax(N, n);
    for (size_t rnapisu = maks; rnapisu > 0; rnapisu--)
        countSort(N, n, rnapisu - 1, L);
}

//********************heapSort********************
void heapify(string N[], int wielkosct, int i, int L[])
{
    int largest, l, r;
    largest = i;
    l = 2 * i + 1;
    r = 2 * i + 2;

    if(l < wielkosct)
    {
        if(strcmp(N[l].c_str(), N[largest].c_str()) > 0)
            largest = l;
    }
    if(r < wielkosct)
    {
        if(strcmp(N[r].c_str(), N[largest].c_str()) > 0)
            largest = r;
    }
    if(largest != i)
    {
        swap(N[largest], N[i]);
        swap(L[largest], L[i]);
        heapify(N, wielkosct, largest, L);
    }
}

void heapsort(string N[], int wielkosct, int L[])
{
    for(int i = wielkosct / 2 - 1; i >= 0; i--)
    {
        heapify(N, wielkosct, i, L);
    }
    for(int i = wielkosct - 1; i > 0; i--)
    {
        swap(N[0], N[i]);
        swap(L[0], L[i]);
        heapify(N, i, 0, L);
    }
}

//********************main********************
int main()
{
    int L[20000];
    string N[20000];
    int tmp = 0;
    ifstream nazwiska("nazwiskaASCII.txt");

    if (!nazwiska)
    {
        cout << "Nie mozna otworzyc pliku";
        return 1;
    }

    while (!nazwiska.eof())
    {
        nazwiska >> L[tmp];
        nazwiska >> N[tmp++];
    }

    nazwiska.close();

    int L2[20000];
    string N2[20000];
    for (int i=0; i<20000; i++)
    {
        L2[i] = L[i];
        N2[i] = N[i];
    }
    int n = sizeof(N) / sizeof(N[0]);

//********************czas********************
    double czas;
    cout.setf(ios::fixed);
    cout.precision(5);
    clock_t start, koniec;
    start=clock();

    radixsort(N,n,L);

    koniec=clock();
    czas=(koniec-start)/(double)CLOCKS_PER_SEC;


    double czas2;
    cout.setf(ios::fixed);
    cout.precision(5);
    clock_t start2, koniec2;
    start2=clock();

    heapsort(N2,n,L2);

    koniec2=clock();
    czas2=(koniec2-start2)/(double)CLOCKS_PER_SEC;
//********************koniec********************

    ofstream wynikr("wynikradix.txt");

    for (int i=0; i<20000; i++)
        wynikr << L[i] << " " << N[i] << "\n";

    wynikr.close();

    ofstream wynikh("wynikheap.txt");

    for (int i=0; i<20000; i++)
        wynikh << L2[i] << " " << N2[i] << "\n";

    wynikh.close();

    cout << "Czas dzialania radixsort: " << czas << " s" << endl;
    cout << "Czas dzialania heapsort: " << czas2 << " s" << endl;

	return 0;
}
