#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

struct lista
{
    lista * next;
    string napis;
};

void wstaw (string x, lista * & head)
{
    lista * p = new lista;

    p->napis = x;
    p->next = head;
    head = p;
}

void drukuj (lista * p)
{
    unsigned i;

    for( i = 1; p; p = p->next )
        cout << "Element #" << i++ << "  napis = " << p->napis << endl;
    cout << endl;
}

lista * szukaj (string x, lista * p)
{
    while(p)
    {
        if(p->napis == x)                //jesli element listy jest rowny szukanemu napisowi
            return p;                    //to zwracamy wskaznik na ten element
        p = p->next;                     //inaczej przesuwamy siê do kolejnego elementu listy
    }
    return NULL;                         //jesli zaden element nie byl taki jak szukany zwracamy null
}

void usun (string x, lista * head)
{
    lista *wsk = head;                    //jako element bie¿¹cy przyjmujemy pierwszy element listy
    while (wsk->next != NULL)
    {
        if (wsk->next->napis == x)        //jesli nastepny element listy jest rowny szukanemu napisowi
        {
            lista *usuwany = wsk->next;
            wsk->next = usuwany->next;    //usuwamy go
            free(usuwany);
        }
        else
        {
            wsk = wsk->next;              //inaczej przesuwamy siê do kolejnego elementu listy
        }
    }
}

void kasuj (lista ** p)
{
    lista * wsk = *p;
    lista * next;

    while (wsk != NULL)
    {
        next = wsk->next;
        free(wsk);
        wsk = next;
    }

    *p = NULL;
}

void usunduplikaty( lista * head )
{
    lista * p, * pc, * r;
    pc = head;                             //jako element bie¿¹cy przyjmujemy pierwszy element listy
    while( pc )
    {
        p = pc;
        while( p->next )                   //testujemy nastepny
        if( p->next->napis == pc->napis )  //jeœli nastepny jest duplikatem usuwamy go
        {
            r = p->next;
            p->next = r->next;
            delete r;
        }
        else
            p = p->next;                  //inaczej przesuwamy siê do kolejnego elementu listy
        pc = pc->next;
    }
}

lista * bezpowtorzen(lista * L)
{

    lista *kopowany = L;

    lista * kopia = new lista;
    kopia->napis = kopowany->napis;
    kopia->next = NULL;

    lista *const head = kopia;

    kopowany = kopowany->next;

    while (kopowany != NULL)
    {
       kopia = kopia->next = new lista;
       kopia->napis = kopowany->napis;
       kopia->next = NULL;
       kopowany = kopowany->next;
    }
    usunduplikaty(head);
    return head;
}

lista * scal(lista * a, lista * b)
{
    lista * kopia = new lista;

    lista *kopiowany = a;
    kopia->napis = kopiowany->napis;
    kopia->next = NULL;

    lista *const head = kopia;

    kopiowany = kopiowany->next;

    while (kopiowany != NULL)
    {
       kopia = kopia->next = new lista;
       kopia->napis = kopiowany->napis;
       kopia->next = NULL;
       kopiowany = kopiowany->next;
    }

    kopiowany = b;
    kopia->napis = kopiowany->napis;
    kopia->next = NULL;

    kopiowany = kopiowany->next;

    while (kopiowany != NULL)
    {
       kopia = kopia->next = new lista;
       kopia->napis = kopiowany->napis;
       kopia->next = NULL;
       kopiowany = kopiowany->next;
    }

    kasuj (&a);
    kasuj (&b);
    return head;
}

int main( )
{
    lista * L = NULL;

    wstaw ( "napis1", L );
    wstaw ( "napis2", L );
    wstaw ( "napis3", L );
    wstaw ( "napis3", L );
    cout << "Lista L: " << endl;
    drukuj ( L );

    wstaw ( "napis4", L );
    wstaw ( "napis5", L );
    wstaw ( "napis5", L );
    cout << "Lista L: " << endl;
    drukuj ( L );

    cout << "Adres \"napis2\": " << szukaj ( "napis2", L ) << endl << endl;

    usun( "napis5", L );
    cout << "Lista L: " << endl;
    drukuj ( L );

    cout << "Adres \"napis2\": " << szukaj ( "napis2", L ) << endl << endl;

    lista * L2 = bezpowtorzen(L);
    cout << "Lista L2: " << endl;
    drukuj ( L2 );

    lista * L3 = scal( L, L2 );
    cout << "Lista L3: " << endl;
    drukuj ( L3 );

    kasuj (&L3);
    drukuj(L3);

    return 0;
}
