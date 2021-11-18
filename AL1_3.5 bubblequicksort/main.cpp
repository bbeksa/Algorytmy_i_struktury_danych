#include<iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int partition(int tablica[], int p, int r)
{
    int x = tablica[p];
    int i = p, j = r, w;
    while (true)
    {
        while (tablica[j] > x)
            j--;
        while (tablica[i] < x)
            i++;
        if (i < j)
        {
            w = tablica[i];
            tablica[i] = tablica[j];
            tablica[j] = w;
            i++;
            j--;
        }
        else
            return j;
    }
}

void quicksort(int tablica[], int p, int r)
{
    int q;
    if (p < r)
    {
        q = partition(tablica,p,r);
        quicksort(tablica, p, q);
        quicksort(tablica, q+1, r);
    }
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubblesort(int arr[], int p, int n)
{
    int i, j;
    for (i = p; i < n-1; i++)
    {
        for (j = p; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
    }
}

void bubblequicksort(int tablica[], int p, int r)
{
    int q;
    if ((r-p + 1) < 10)
    {
        bubblesort(tablica, p, (r-p + 1));
    }
    else if (p < r)
    {
        q = partition(tablica,p,r);
        quicksort(tablica, p, q);
        quicksort(tablica, q+1, r);
    }
}

void wyswietltab(int tab[], int n)
{
    for(int i=0; i<n; i++)
        cout << "tab[" << i << "] = " << tab[i] << endl;
}

int main()
{
    int ilosc_liczb, i;
    cout << "Podaj ilosc liczb do posortowania: ";
    cin >> ilosc_liczb;
    int *tablica = new int [ilosc_liczb];
    int *tablica2 = new int [ilosc_liczb];
    int *tablica3 = new int [ilosc_liczb];
    int *tablica4 = new int [ilosc_liczb];

    srand( time( NULL ) );
    int liczba = 20002;
    int liczba2 = 30100;
    for (i = 0; i < ilosc_liczb; i++)
    {
        tablica[i] = ( std::rand() % 5000 );

        liczba -= ( std::rand() % 30 );
        tablica2[i] = liczba;

        tablica3[i] = ( std::rand() % 5000 );

        liczba2 -= ( std::rand() % 30 );
        tablica4[i] = liczba2;
    }

    double czas;
    cout.setf(ios::fixed);
    cout.precision(5);
    clock_t start, koniec;
    start=clock();
    quicksort(tablica,0,ilosc_liczb-1);
    koniec=clock();
    czas=(koniec-start)/(double)CLOCKS_PER_SEC;

    double czas2;
    cout.setf(ios::fixed);
    cout.precision(5);
    clock_t start2, koniec2;
    start2=clock();
    quicksort(tablica2,0,ilosc_liczb-1);
    koniec2=clock();
    czas2=(koniec2-start2)/(double)CLOCKS_PER_SEC;

    double czas3;
    cout.setf(ios::fixed);
    cout.precision(5);
    clock_t start3, koniec3;
    start3=clock();
    bubblequicksort(tablica3,0,ilosc_liczb-1);
    koniec3=clock();
    czas3=(koniec3-start3)/(double)CLOCKS_PER_SEC;

    double czas4;
    cout.setf(ios::fixed);
    cout.precision(5);
    clock_t start4, koniec4;
    start4=clock();
    bubblequicksort(tablica4,0,ilosc_liczb-1);
    koniec4=clock();
    czas4=(koniec4-start4)/(double)CLOCKS_PER_SEC;

    cout<<"Czas sortowania(dane losowe): "<< czas << " s" << endl;
    cout<<"Czas sortowania(dane niekorzystne): "<< czas2 << " s" << endl;
    cout<<"Czas sortowania bubblequicksort(dane losowe): "<< czas3 << " s" << endl;
    cout<<"Czas sortowania bubblequicksort(dane niekorzystne): "<< czas4 << " s" << endl;

    wyswietltab(tablica3, ilosc_liczb);

    delete [] tablica;
    delete [] tablica2;
    delete [] tablica3;
    delete [] tablica4;

    return 0;
}
