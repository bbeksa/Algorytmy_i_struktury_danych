#include <fstream>
#include <iostream>
#include <stdio.h>
#include<bits/stdc++.h>
using namespace std;

    int stringToInt(string x)
    {
        int num, a = 111;
        for(size_t i = 0; i < x.length(); i++)
        {
            num = num + (a * x[i]);
        }
        return num;
    }

	int hashFunction(int x, int n)
	{
		return (x % n);
	}

	void insertItem(int table[], int n, string key)
    {
        int num = stringToInt(key);
        int index = hashFunction(num, n);
        table[index]++;
    }

	displayHash(int table[], int n)
	{
	    int z = 0, m = 0;
	    double sum = 0.0, il = 0.0;
        for (int i = 0; i < n; i++)
        {
            cout << "T[" << i << "] = " << table[i] << endl;
            if(table[i] == 0)
                z++;
            else
            {
                if(table[i] > m)
                    m = table[i];
                sum = sum + table[i];
                il = il + 1.0;
            }
        }
        cout << "Ilosc zerowych pozycji w tablicy T: " << z << endl;
        cout << "Maksymalna wartosc w T: " << m << endl;
        cout << "Srednia wartosc pozycji niezerowych: " << sum/il << endl;
    }

int main()
{   //m korzystne 1873, niekorzystne 2048
    int k = 1873, nk = 2048;

    int table[k];
    for(int i = 0; i < k; i++)
            table[i] = 0;


    string a[3744];
    int tmp = 0;
    ifstream klucze("3700.txt");

    if (!klucze)
    {
        cout << "Nie mozna otworzyc pliku";
        return 1;
    }

    while (!klucze.eof())
    {
        klucze >> a[tmp++];
    }

    klucze.close();


    int n = sizeof(a)/sizeof(a[0]);

    for (int i = 0; i < n; i++)
        insertItem(table, k, a[i]);

    displayHash(table, k);

    return 0;
}

