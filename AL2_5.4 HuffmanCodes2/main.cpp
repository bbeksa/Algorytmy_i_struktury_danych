#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#define MAX_TREE_HT 100

struct MinHeapNode
{
	char data;
	unsigned freq;
	struct MinHeapNode *left, *right;
};

struct MinHeap //kolekcja wezlow
{
	unsigned size;
	unsigned capacity;

	struct MinHeapNode** array;
};

struct MinHeapNode* newNode(char data, unsigned freq) //funkcja przyznacza nowy wezel o podanym znaku i czestotliwosci
{
	struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));

	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;

	return temp;
}

struct MinHeap* createMinHeap(unsigned capacity) //funkcja tworzaca kolekcje o podanej pojemnosci
{
	struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));

	minHeap->size = 0;

	minHeap->capacity = capacity;

	minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) //zamiana 2 min wezlow
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) //budowanie kopca
{
	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
		smallest = left;

	if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
		smallest = right;

	if (smallest != idx)
    {
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}

int isSizeOne(struct MinHeap* minHeap)
{
	return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)//wyciaganie njmniejszej wartosci z kopca
{
	struct MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];

	--minHeap->size;
	minHeapify(minHeap, 0);

	return temp;
}

void insertMinHeap(struct MinHeap* minHeap,struct MinHeapNode* minHeapNode) //dodawanie wezla do kopca
{
	++minHeap->size;
	int i = minHeap->size - 1;

	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
    {
		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap)
{
	int n = minHeap->size - 1;
	int i;

	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}

int isLeaf(struct MinHeapNode* root)
{
	return !(root->left) && !(root->right);
}

void printArr(int arr[], int n)
{
	int i;
	for (i = 0; i < n; ++i)
		cout<< arr[i];

	cout<<"\n";
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)
{
	struct MinHeap* minHeap = createMinHeap(size);

	for (int i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], freq[i]);

	minHeap->size = size;
	buildMinHeap(minHeap);

	return minHeap;
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)
{
	struct MinHeapNode *left, *right, *top;

	struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

	while (!isSizeOne(minHeap))
    {
		left = extractMin(minHeap);
		right = extractMin(minHeap);

		top = newNode('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		insertMinHeap(minHeap, top);
	}
	return extractMin(minHeap);
}

void printCodes(struct MinHeapNode* root, int arr[], int top)
{
	if (root->left)
    {
		arr[top] = 0;
		printCodes(root->left, arr, top + 1);
	}

	if (root->right)
    {
		arr[top] = 1;
		printCodes(root->right, arr, top + 1);
	}

	if (isLeaf(root))
    {
        if (root->freq > 0)
        {
            cout<< root->data << "(" << root->freq << ")" <<": ";
            printArr(arr, top);
		}
	}
}

void HuffmanCodes(char data[], int freq[], int size)
{
	struct MinHeapNode* root = buildHuffmanTree(data, freq, size);

	int arr[MAX_TREE_HT], top = 0;

	printCodes(root, arr, top);
}


int main()
{
    ifstream  fin("bitwa.txt");
    char ch;
    char cha[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'w', 'v', 'x', 'y', 'z', ' ', '.', ','};
    int fr[29];
    for (int i = 0; i < 29; i++)
        fr[i] = 0;
    int ii;
    while(fin)
    {
        fin.get(ch);
        ii=ch;
        if(ii == 65 || ii == 97)
            fr[0]++;
        if(ii == 66 || ii == 98)
            fr[1]++;
        if(ii == 67 || ii == 99)
            fr[2]++;
        if(ii == 68 || ii == 100)
            fr[3]++;
        if(ii == 69 || ii == 101)
            fr[4]++;
        if(ii == 70 || ii == 102)
            fr[5]++;
        if(ii == 71 || ii == 103)
            fr[6]++;
        if(ii == 72 || ii == 104)
            fr[7]++;
        if(ii == 73 || ii == 105)
            fr[8]++;
        if(ii == 74 || ii == 106)
            fr[9]++;
        if(ii == 75 || ii == 107)
            fr[10]++;
        if(ii == 76 || ii == 108)
            fr[11]++;
        if(ii == 77 || ii == 109)
            fr[12]++;
        if(ii == 78 || ii == 110)
            fr[13]++;
        if(ii == 79 || ii == 111)
            fr[14]++;
        if(ii == 80 || ii == 112)
            fr[15]++;
        if(ii == 81 || ii == 113)
            fr[16]++;
        if(ii == 82 || ii == 114)
            fr[17]++;
        if(ii == 83 || ii == 115)
            fr[18]++;
        if(ii == 84 || ii == 116)
            fr[19]++;
        if(ii == 85 || ii == 117)
            fr[20]++;
        if(ii == 86 || ii == 118)
            fr[22]++;
        if(ii == 87 || ii == 119)
            fr[21]++;
        if(ii == 88 || ii == 120)
            fr[23]++;
        if(ii == 89 || ii == 121)
            fr[24]++;
        if(ii == 90 || ii == 122)
            fr[25]++;
        if(ii == 44)
            fr[28]++;
        if(ii == 46)
            fr[27]++;
        else
            if(ch== ' ')
                fr[26]++;
    }
    int size = sizeof(cha) / sizeof(cha[0]);

    HuffmanCodes(cha, fr, size);

    return 0;
}
