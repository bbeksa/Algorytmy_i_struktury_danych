#include <fstream>
#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;
//m korzystne 8191, niekorzystne 8192
#define TABLE_SIZE 8192
//#define TABLE_SIZE 8192

int tmpp = 1;

class Hash {
    int* ilosc;
	string* nazwisko;
	int curr_size;

public:
    int getCurrSize(){
        return curr_size;
    }

	bool isFull()
	{
		return (curr_size == TABLE_SIZE);
	}

    int stringToInt(string x)
    {
        int num, a = 111;
        for(size_t i = 0; i < x.length(); i++)
        {
            num = num + (a * x[i]);
        }
        return num;
    }

	int hash1(int key)
	{
		return (key % TABLE_SIZE);
	}

	Hash()
	{
		ilosc = new int[TABLE_SIZE];
		nazwisko = new string[TABLE_SIZE];
		curr_size = 0;
		for (int i = 0; i < TABLE_SIZE; i++){
			ilosc[i] = -1;
			nazwisko[i] = "";
		}
	}

	void insertHash(string skey, int liczba)
	{
		if (isFull())
			return;
        //cout << tmpp++ << endl;
        int key = stringToInt(skey);
		int index = hash1(key);
		if (nazwisko[index] != "" && nazwisko[index] != "DEL") {
			int i = 1;
			while (1) {
				int newIndex = (index + i * i) % TABLE_SIZE;

				if (nazwisko[newIndex] == "" || nazwisko[newIndex] == "DEL") {
					nazwisko[newIndex] = skey;
					ilosc[newIndex] = liczba;
					break;
				}
				i++;
			}
		}

		else
			nazwisko[index] = skey;
            ilosc[index] = liczba;
		curr_size++;
	}

	void deleteItem(string skey)
    {
        int key = stringToInt(skey);
        int index = hash1(key);

        if (nazwisko[index] == skey) {
            nazwisko[index] = "DEL";
            ilosc[index] = -1;
        }
        else {
			int i = 1;
			while (1) {
				int newIndex = (index + i * i) % TABLE_SIZE;

				if (nazwisko[newIndex] == skey) {
					nazwisko[newIndex] = "DEL";
					ilosc[newIndex] = -1;
					break;
				}
				i++;
			}
		}
    }

    void deleteItems(int amount)
    {
        int i = 0;
        while(amount > 0 && i < TABLE_SIZE){
            if (nazwisko[i] != "" && nazwisko[i] != "DEL") {
                nazwisko[i] = "DEL";
                ilosc[i] = -1;
                amount--;
                i++;
            }
            i++;
        }
    }

	void displayHash()
	{
		for (int i = 0; i < TABLE_SIZE; i++) {
			if (nazwisko[i] != "" && nazwisko[i] != "DEL")
				cout << i << " --> " << ilosc[i] << " " << nazwisko[i] << endl;
			else
				cout << i << " -->" << endl;
		}
	}

	int liczDLE()
	{
	    int wynik = 0;
		for (int i = 0; i < TABLE_SIZE; i++) {
			if (nazwisko[i] == "DEL")
				wynik++;
		}
		return wynik;
	}
};

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

	Hash h;


	for (int i = 0; i < (TABLE_SIZE*8/10); i++) {
		h.insertHash(N[i], L[i]);
	}

	h.deleteItems(h.getCurrSize()/2);

	for (int i = 8192; i < 20000; i++) {
		h.insertHash(N[i], L[i]);
		if(h.getCurrSize() == (TABLE_SIZE*8/10))
            break;
	}

	h.displayHash();
	cout << "ile pozycji w tablicy jest wypelnionych znacznikiem DEL: " << h.liczDLE() << endl;

	return 0;
}
