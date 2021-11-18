#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Node {
public:
    int key;
    Node *parent;
    int rank;

    Node(int k);
};

Node::Node(int k){
    key = k;
    rank = 0;
    parent = this;
}
// utworzenie drzewa reprezentujacego jednoelementowy zbiór z kluczem k
Node* MakeSet(int k) {
    return new Node(k);
}
// zwraca reprezentanta zbioru do ktorego nalezy element (czyli wezel) x
// Wersja z kompresja: kazdy wezel na sciezce od "x" do korzenia
// jest doczepiany bezposrednio do korzenia, czyli korzen staje sie
// jego ojcem
Node* FindSet(Node* x) {
    if(x != x->parent)
        x->parent = FindSet(x->parent);
    return x->parent;
}
// zamienia zbiory o reprezentantach x,y w jeden zbior bedacy ich suma
// rozlaczna. Wersja z ranga: zbior o mniejszej randze jest doczepiany
// do korzenia zbioru o wiekszej randze; jezeli rangi sa rowne to
// "y" do "x" i ranga "x" wzrasta o 1
void Union(Node* x,Node* y)
{
    if(x->rank >= y->rank) {
        if(x->rank == y->rank)
            x->rank++;
        y->parent = x;
    }
    else
        x->parent = y;
}


class Graph {
    class Edge{// Klasa reprezentujaca krawedz
    public:
        Node *a; //poczatek krawedzi
        Node *b; //koniec krawedzi
        int weight; //waga

        Edge(Node* st, Node* en, int we){//konstruktor
            a = st;
            b = en;
            weight = we;
        }
    };
    // sortowanie krawedzi na podstawie ich wagi
    class comp{
    public:
        inline bool operator() (const Edge *struct1, const Edge *struct2)
        {
            return (struct1->weight < struct2->weight);
        }
    };
    public:
    vector<Node*> vertices;//zbiór wierzcholkow
    vector<Edge*> edges;//zbior krawedzi

    Graph(){}
    Graph(vector<Node*> vertices, vector<Edge*> edges) {
        this->vertices = vertices;
        this->edges = edges;
    }

    void Kurskal(Graph* g) {
        sort(g->edges.begin(), g->edges.end(), comp()); //sortuje krawedzie po wadze niemalejaco
        cout << ("Krawedzie drzewa spinajacego:") << endl;
        for(int i = 0; i < g->edges.size(); i++) {//sprawdzamy krawedzie po kolei
            Node* rs = FindSet(g->edges[i]->a);
            Node* re = FindSet(g->edges[i]->b);
            if(rs != re) {//jezeli nie sa dodane do wynikowego drzewa spinajacego to dodajemy
                cout << rs->key << "-" << re->key << endl;
                Union(rs, re);
            }
        }
    }
    void GraphTest() {
        vector<Node*> vertices;
        for(int i = 0; i <= 3; i++)
            vertices.push_back(MakeSet(i));

        vector<Edge*> edges;
        edges.push_back(new Edge(vertices[0], vertices[1], 10));
        edges.push_back(new Edge(vertices[0], vertices[2], 6));
        edges.push_back(new Edge(vertices[1], vertices[2], 5));
        edges.push_back(new Edge(vertices[1], vertices[3], 15));
        edges.push_back(new Edge(vertices[2], vertices[3], 4));

        Graph* g = new Graph(vertices, edges);
        Kurskal(g);
    }
};


int main()
{
    vector<Node*> nodes;
    for(int i = 0; i <= 9; i++)
        nodes.push_back(MakeSet(i));

    Union(nodes[0], nodes[1]);
    Union(nodes[1], nodes[2]);
    Union(nodes[2], nodes[3]);
    Union(nodes[3], nodes[4]);
    Union(nodes[4], nodes[5]);
    Union(nodes[5], nodes[6]);
    Union(nodes[6], nodes[7]);

    Node* x = nodes[7];

    while (x != x->parent) { //sciazka przed kompresja
        cout << (x->key) << endl;
        x = x->parent;
    }
    cout << endl;
    FindSet(nodes[7]);//kompresja sciezki do korzenia
    x = nodes[7];

    while (x != x->parent) {  //po kompresji sciezki
        cout << (x->key) << endl;
        x = x->parent;
    }

    cout << "---------zad3----------"  << endl;
    Graph g;
    g.GraphTest();

    return 0;
}
