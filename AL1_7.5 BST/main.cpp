#include <iostream>
using namespace std;

char switchh = 'r';

class BST
{
public:
	int data;
	BST *left, *right;

	BST()
	: data(0)
	, left(NULL)
	, right(NULL)
	{}

	BST(int value)
    {
        data = value;
        left = right = NULL;
    }

    //dodawanie
	BST* Insert(BST* root, int value)
    {
        if (!root)
        {
            if(switchh == 'r')
                switchh = 'l';
            if(switchh == 'l')
                switchh = 'r';

            //jezeli korzen jest pusty to go ustawiamy
            return new BST(value);
        }

        if (value == root->data)
        {
            if(switchh == 'r')
                root->right = Insert(root->right, value);
            if(switchh == 'l')
                root->left = Insert(root->left, value);
        }
        else if (value > root->data)
        {
            //jesli wartosc wkladaniego elementu jest wieksza niz korzenia  to na prawo
            root->right = Insert(root->right, value);
        }
        else if (value < root->data)
        {
            //jesli wartosc wkladaniego elementu jest mniejsza niz korzenia  to na lewo
            root->left = Insert(root->left, value);
        }
        return root;
    }

	void Inorder(BST* root)
    {
        if (!root) {
            return;
        }
        Inorder(root->left);
        cout << root->data << endl;
        Inorder(root->right);
    }

};

struct BST* searchN(struct BST* root, int data)
{
    if (root == NULL || root->data == data)
       return root;

    if (root->data < data)
       return searchN(root->right, data);

    return searchN(root->left, data);
}

struct BST* minValueNode(struct BST* BST)
{
    struct BST* current = BST;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct BST* deleteNode(struct BST* root, int data)
{
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);

    else if (data > root->data)
        root->right = deleteNode(root->right, data);

    else {
        // jeden lub brak syna
        if (root->left == NULL) {
            struct BST* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct BST* temp = root->left;
            free(root);
            return temp;
        }

        // dwoch synow (szykamy najmniejszego z prawego poddrzewa i wstawiamy na jego miejsce)
        struct BST* temp = minValueNode(root->right);

        // kopiujemy syna ktorym zastapimy usuwany element
        root->data = temp->data;

        // usuwamy syna ktory stoi teraz na miejscu usunietego elementu
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void printBT(const string& prefix, const BST* node, bool isLeft)
{
    if( node != NULL )
    {
        cout << prefix;

        cout << "L---";

        cout << node->data << endl;

        printBT( prefix + (isLeft ? "|   " : "   "), node->left, true);
        printBT( prefix + (isLeft ? "|   " : "   "), node->right, false);
    }
}
void printBT(const BST* node)
{
    printBT(" ", node, false);
}

int main()
{
	BST b, *root = NULL;
	root = b.Insert(root, 50);
	b.Insert(root, 30);
	b.Insert(root, 20);
	b.Insert(root, 40);
	b.Insert(root, 70);
	b.Insert(root, 60);
	b.Insert(root, 80);
	b.Insert(root, 120);
	b.Insert(root, 25);

	b.Inorder(root);
	printBT(root);

	deleteNode(root, 70);
	deleteNode(root, 80);

	printBT(root);

	if(searchN(root, 12) == NULL)
        cout << "Podanej wartosci nie ma" << endl;
    else
        cout << "Znalazlem!" << endl;

    if(searchN(root, 80) == NULL)
        cout << "Podanej wartosci nie ma" << endl;
    else
        cout << "Znalazlem!" << endl;

    if(searchN(root, 50) == NULL)
        cout << "Podanej wartosci nie ma" << endl;
    else
        cout << "Znalazlem!" << endl;


	b.Insert(root, 80);
	b.Insert(root, 25);
	b.Insert(root, 120);
	b.Insert(root, 120);

	b.Inorder(root);
	printBT(root);

	return 0;
}
