#include <iostream>

using namespace std;

struct Node {
	int data;
	Node *parent;
	Node *left;
	Node *right;
	int color; // 1 -> Red, 0 -> Black
};

typedef Node *NodePtr;

class RBTree {
private:
	NodePtr root;
	NodePtr TNULL;

	void initializeNULLNode(NodePtr node, NodePtr parent) {
		node->data = 0;
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->color = 0;
	}

	NodePtr searchTreeHelper(NodePtr node, int key) {
		if (node == TNULL || key == node->data) {
			return node;
		}

		if (key < node->data) {
			return searchTreeHelper(node->left, key);
		}
		return searchTreeHelper(node->right, key);
	}

	void fixDelete(NodePtr x) {
		NodePtr s;
		while (x != root && x->color == 0) {
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->color == 1) {
					// Przypadek 1
					s->color = 0;
					x->parent->color = 1;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == 0 && s->right->color == 0) {
					// Przypadek 2
					s->color = 1;
					x = x->parent;
				}
				else {
					if (s->right->color == 0) {
						// Przypadek 3
						s->left->color = 0;
						s->color = 1;
						rightRotate(s);
						s = x->parent->right;
					}
					// Przypadek 4
					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					leftRotate(x->parent);
					x = root;
				}
			}
			else {
				s = x->parent->left;
				if (s->color == 1) {
					// Przypadek 1
					s->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == 0 && s->right->color == 0) {
					// Przypadek 2
					s->color = 1;
					x = x->parent;
				}
				else {
					if (s->left->color == 0) {
						// Przypadek 3
						s->right->color = 0;
						s->color = 1;
						leftRotate(s);
						s = x->parent->left;
					}

					// Przypadek 4
					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = 0;
	}


	void rbTransplant(NodePtr u, NodePtr v){
		if (u->parent == nullptr) {
			root = v;
		} else if (u == u->parent->left){
			u->parent->left = v;
		} else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void deleteNodeHelper(NodePtr node, int key) {
		NodePtr z = TNULL;
		NodePtr x, y;
		while (node != TNULL){
			if (node->data == key) {
				z = node;
			}

			if (node->data <= key) {
				node = node->right;
			} else {
				node = node->left;
			}
		}

		if (z == TNULL) {
			cout<<"Nie ma takiej liczby w drzewie!"<<endl;
			return;
		}

		y = z;
		int y_original_color = y->color;
		if (z->left == TNULL) {
			x = z->right;
			rbTransplant(z, z->right);
		} else if (z->right == TNULL) {
			x = z->left;
			rbTransplant(z, z->left);
		} else {
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			} else {
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 0){
			fixDelete(x);
		}
	}

	void fixInsert(NodePtr k){
		NodePtr u;
		while (k->parent->color == 1) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left; // uncle
				if (u->color == 1) {
					// Przypadek 1
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->left) {
						// Przypadek 3
						k = k->parent;
						rightRotate(k);
					}
					// Przypadek 2
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			}
			else {
				u = k->parent->parent->right; // uncle

				if (u->color == 1) {
					// Przypadek 1
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->right) {
						// symetryczny Przypadek 3
						k = k->parent;
						leftRotate(k);
					}
					// symetryczny Przypadek 2
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root)
				break;
		}
		// Przypadek 1.2
		root->color = 0;
	}

	void printHelper(NodePtr root, string indent, bool last) {
	   	if (root != TNULL) {
		   cout<<indent;
		   if (last) {
		      cout<<"R----";
		      indent += "     ";
		   } else {
		      cout<<"L----";
		      indent += "|    ";
		   }

           string sColor = root->color?"RED":"BLACK";
		   cout<<root->data<<"("<<sColor<<")"<<endl;
		   printHelper(root->left, indent, false);
		   printHelper(root->right, indent, true);
		}
	}

public:
	RBTree() {
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
	}

	NodePtr searchTree(int k) {
		return searchTreeHelper(this->root, k);
	}

	// najmniejszy wezel
	NodePtr minimum(NodePtr node) {
		while (node->left != TNULL) {
			node = node->left;
		}
		return node;
	}

	// najwiekszy wezel
	NodePtr maximum(NodePtr node) {
		while (node->right != TNULL) {
			node = node->right;
		}
		return node;
	}

	// nastepca podanego wezla
	NodePtr successor(NodePtr x) {
		if (x->right != TNULL) {
			return minimum(x->right);
		}

		NodePtr y = x->parent;
		while (y != TNULL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	// poprzednik podanego wezla
	NodePtr predecessor(NodePtr x) {
		if (x->left != TNULL)
			return maximum(x->left);

		NodePtr y = x->parent;
		while (y != TNULL && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}

	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != TNULL)
			y->left->parent = x;

		y->parent = x->parent;
		if (x->parent == nullptr)
			this->root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;

		y->left = x;
		x->parent = y;
	}

	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != TNULL)
			y->right->parent = x;
		y->parent = x->parent;
		if (x->parent == nullptr)
			this->root = y;
		else if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;

		y->right = x;
		x->parent = y;
	}

	void insert(int key) {
		NodePtr node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1; // kazdy nowy jest czerwona

		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != TNULL) {
			y = x;
			if (node->data < x->data)
				x = x->left;
			else
				x = x->right;
		}

		node->parent = y;
		if (y == nullptr)
			root = node;
		else if (node->data < y->data)
			y->left = node;
		else
			y->right = node;

		//jezeli nowy wezel to root > return
		if (node->parent == nullptr){
			node->color = 0;
			return;
		}

		// jezeli dzidek to null > return
		if (node->parent->parent == nullptr) {
			return;
		}
		fixInsert(node);
	}

	NodePtr getRoot(){
		return this->root;
	}

	void deleteNode(int data) {
		deleteNodeHelper(this->root, data);
	}

    void Print() {
	    if (root) {
    		printHelper(this->root, "", true);
	    }
	    cout << endl;
	}

};

int maxDepth(Node* node)
{
    if (node == NULL)
        return -1;
    else
    {
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);

        if (lDepth > rDepth)
            return(lDepth + 1);
        else
            return(rDepth + 1);
    }
}

int minDepth(Node *root)
{
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 0;

    if (!root->left)
        return minDepth(root->right) + 1;

    if (!root->right)
        return minDepth(root->left) + 1;

    return min(minDepth(root->left), minDepth(root->right)) + 1;
}


int main() {
	cout << "Przyklad z zadania 1:" << endl;
	RBTree z1;
    z1.insert(38);
    z1.Print();
    z1.insert(31);
    z1.Print();
    z1.insert(22);
    z1.Print();
    z1.insert(8);
    z1.Print();
    z1.insert(20);
    z1.Print();
    z1.insert(5);
    z1.Print();
    z1.insert(10);
    z1.Print();
    z1.insert(9);
    z1.Print();
    z1.insert(21);
    z1.Print();
    z1.insert(27);
    z1.Print();
    z1.insert(29);
    z1.Print();
    z1.insert(25);
    z1.Print();
    z1.insert(28);
    z1.Print();
    cout << "-----------------------------------------" << endl;

    cout << "Przyklad z zadania 2:" << endl;
    z1.deleteNode(5);
    z1.Print();
    z1.deleteNode(38);
    z1.Print();
    z1.deleteNode(8);
    z1.Print();
    z1.deleteNode(10);
    z1.Print();
    z1.deleteNode(22);
    z1.Print();
    z1.deleteNode(20);
    z1.Print();
    z1.deleteNode(29);
    z1.Print();
    z1.deleteNode(31);
    z1.Print();
    cout << "-----------------------------------------" << endl;


    cout << "Glebokosc maksymalna i minimalna:" << endl;
    RBTree G;
    G.insert(50);
    G.insert(1);
    G.insert(70);
    G.insert(60);
    G.insert(80);
    G.insert(79);
    G.insert(77);
    G.insert(61);
    G.insert(2);
    G.insert(3);
    G.Print();
    cout << "maksymalna glebokosc: " << maxDepth(G.getRoot()) << endl;
    cout << "minimalna glebokosc: " << minDepth(G.getRoot()) << endl << endl;


    RBTree G2;
    for(int i = 1; i <= 1000; i++)
        G2.insert(i);
    cout << "maksymalna glebokosc drzewa 1000 elementow: " << maxDepth(G2.getRoot()) << endl;
    cout << "minimalna glebokosc drzewa 1000 elementow: " << minDepth(G2.getRoot()) << endl;

	return 0;
}
