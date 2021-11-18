#include <iostream>

#include <vector>
#include <sstream>
using namespace std;

class TreeNode
{
    int *keys; //tablica kluczy
    int t; //stopien
    TreeNode **C; //tablica z wskaznikami synow
    int n; //ilosc kluczy
    bool leaf; //czy jest lisciem

    public:
        TreeNode(int temp, bool bool_leaf); //Konstruktor

        void insertNonFull(int k);
        void splitChild(int i, TreeNode *y);
        void traverse();

        TreeNode *search(int k);

        friend class BTree;
        friend class BTreePrinter;
};

class BTree
{
    TreeNode *root; //wskaznik na korzen
    int t;

    public:
        BTree()//konstruktor inicjalizujacy puste drzewo
        {
            root = NULL;
            t = 3;
        }

        void traverse()
        {
            if (root != NULL)
                root->traverse();
        }

        TreeNode *search(int k)//funkcja wyszukiwania klucza w tym drzewie
        {
            return (root == NULL) ? NULL : root->search(k);
        }

        void insert(int k);

        friend class BTreePrinter;
};

TreeNode::TreeNode(int t1, bool leaf1)
{// konstruktor TreeNode
    t = 3;
    leaf = leaf1;

    keys = new int[2 * t - 1]; //Przydziel pamiêæ dla maksymalnej liczby mo¿liwych kluczy
    C = new TreeNode *[2 * t]; //i wskanikow synow

    n = 0; //aktualna liczba kluczy to 0
}

void TreeNode::traverse()
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }

    if (leaf == false)
        C[i]->traverse();
}

TreeNode *TreeNode::search(int k)
{//szuka klucza w calym poddrzewie o korzeniu na ktorym zostalo wywolane
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    if (keys[i] == k)
        return this; //znaleziony klucz

    if (leaf == true)
        return NULL; //klucza nie ma

    return C[i]->search(k); //przechodzimy do odpowiedniego syna
}

void BTree::insert(int k)
{//dodanie nowego klucza do drzewa
    if (root == NULL)
    {//jesli cale drzewo jest puste
        root = new TreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else
    {
        if (root->n == 2 * t - 1)
        {//jezeli korzen jest pelny to wysokosc drzewa rosnie
            TreeNode *s = new TreeNode(t, false);// nowy korzen

            s->C[0] = root;//stary korzen jako dziecko nowego

            s->splitChild(0, root);//dzielimy stary korzen na 2 i przenosimy jeden klucz do nowego korzenia

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            root = s; //zmiana korzenia
        }
        else
            root->insertNonFull(k);//jezeli korzen nie jest pelny wstawiamy bez zmiany
    }
}

void TreeNode::insertNonFull(int k)
{// wstawia klucz k do poddrzewa zakorzenionego w tym wêzele, który jest niepe³ny (n < 2*t-1)
    int i = n - 1; //index najbardziej po prawej

    if (leaf == true)
    {
        while (i >= 0 && keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        n = n + 1;
    }
    else// rekursywne zejœcie w dó³ drzewa
    {
        while (i >= 0 && keys[i] > k)
            i--;

        if (C[i + 1]->n == 2 * t - 1)
        {
            splitChild(i + 1, C[i + 1]);

            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

void TreeNode::splitChild(int i, TreeNode *y)
{//rozbija wêze³ y, który jest i-tym synem wezla z ktorego wywolujemy
    TreeNode *z = new TreeNode(y->t, y->leaf);// nowy wêze³, jezeli y byl lisciem to z tez jest
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t]; //przepisujemy czesc kluczy do z

    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++) // przepisujemy odpowiednich synów do z
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;
    for (int j = n; j >= i + 1; j--)
            C[j + 1] = C[j];   // robimy miejsce na nowego syna w ojcu

    C[i + 1] = z;              // z jest tym synem

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j]; // robimy miejsce na nowy klucz w ojcu

    keys[i] = y->keys[t - 1];  // œrodkowy klucz wêz³a y jest tym nowym kluczem
    n = n + 1;
}

//Klasa do wypisywania drzewa
//------------------------------------------------------------------
class BTreePrinter
{
   struct NodeInfo
   {
      std::string text;
      unsigned text_pos, text_end;
   };

   typedef std::vector<NodeInfo> LevelInfo;

   std::vector<LevelInfo> levels;

   std::string node_text (int const keys[], unsigned key_count);

   void before_traversal ()
   {
      levels.resize(0);
      levels.reserve(10);
   }

   void visit (TreeNode const *node, unsigned level = 0, unsigned child_index = 0);

   void after_traversal ();

public:
   void print (BTree const &tree)
   {
      before_traversal();
      visit(tree.root);
      after_traversal();
   }
};

void BTreePrinter::visit (TreeNode const *node, unsigned level, unsigned child_index)
{
   if (level >= levels.size())
      levels.resize(level + 1);

   LevelInfo &level_info = levels[level];
   NodeInfo info;

   info.text_pos = 0;
   if (!level_info.empty())
      info.text_pos = level_info.back().text_end + (child_index == 0 ? 2 : 1);

   info.text = node_text(node->keys, unsigned(node->n));

   if (node->leaf)
   {
      info.text_end = info.text_pos + unsigned(info.text.length());
   }
   else
   {
      for (unsigned i = 0, e = unsigned(node->n); i <= e; ++i)
         visit(node->C[i], level + 1, i);

      info.text_end = levels[level + 1].back().text_end;
   }

   levels[level].push_back(info);
}

std::string BTreePrinter::node_text (int const keys[], unsigned key_count)
{
   std::ostringstream os;
   char const *sep = "";

   os << "[";
   for (unsigned i = 0; i < key_count; ++i, sep = " ")
      os << sep << keys[i];
   os << "]";

   return os.str();
}

void print_blanks (unsigned n)
{
   while (n--)
      std::cout << ' ';
}

void BTreePrinter::after_traversal ()
{
   for (std::size_t l = 0, level_count = levels.size(); ; )
   {
      auto const &level = levels[l];
      unsigned prev_end = 0;

      for (auto const &node: level)
      {
         unsigned total = node.text_end - node.text_pos;
         unsigned slack = total - unsigned(node.text.length());
         unsigned blanks_before = node.text_pos - prev_end;

         print_blanks(blanks_before + slack / 2);
         std::cout << node.text;

         if (&node == &level.back())
            break;

         print_blanks(slack - slack / 2);

         prev_end += blanks_before + total;
      }

      if (++l == level_count)
         break;

      std::cout << "\n\n";
   }

   std::cout << "\n";
}
//------------------------------------------------------------

int main() {
    BTreePrinter printer;
    BTree t;
    t.insert(6);
    t.insert(19);
    t.insert(17);
    t.insert(11);
    t.insert(3);
    t.insert(12);
    t.insert(8);
    t.insert(20);
    t.insert(22);
    t.insert(23);
    t.insert(13);
    t.insert(18);
    t.insert(14);
    t.insert(16);
    t.insert(1);
    t.insert(2);
    t.insert(24);
    t.insert(25);
    t.insert(4);
    t.insert(26);
    t.insert(5);
    t.insert(7);
    t.insert(10);

    cout << endl;
    printer.print(t);

    int k = 10;
    (t.search(k) != NULL) ? cout << endl
    << k << " znajduje sie w drzewie"
    : cout << endl
    << k << " nie ma w drzewie";

    cout << endl;

    k = 15;
    (t.search(k) != NULL) ? cout << endl
    << k << " znajduje sie w drzewie"
    : cout << endl
    << k << " nie ma w drzewie";

    cout << endl;

    return 0;
}
