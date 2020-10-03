

                          //***************haffman coding  ******************//


#include <stdio.h>
#include <stdlib.h>
#define maximum_tree_hight 80
#include<iostream>
using namespace std;

// this  tree node is a
//structure that store character ,frequency,
// and two pointer


struct minimum_heapnode
{
    char character;
    int frequency;
    struct minimum_heapnode *left, *right;
};


struct MinHeap
{
    int sizes;    // sizes of min heap
    int capacity;   // capacity of min heap
    struct minimum_heapnode **Array;
};

// A utility function allocate a new min heap node with given character
// and frequencyuency of the character
struct minimum_heapnode* newNode(char character, int frequency)
{
    struct minimum_heapnode* temp =
          (struct minimum_heapnode*) malloc(sizeof(struct minimum_heapnode));
    temp->left = temp->right = NULL;
    temp->character = character;
    temp->frequency = frequency;
    return temp;
}

//  create a min heap of given capacity
struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->sizes = 0;  // current sizes is 0
    minHeap->capacity = capacity;
    minHeap->Array =
     (struct minimum_heapnode**)malloc(minHeap->capacity * sizeof(struct minimum_heapnode*));
    return minHeap;
}

//  swap two min heap nodes
void Swap_node(struct minimum_heapnode** a, struct minimum_heapnode** b)
{
    struct minimum_heapnode* t = *a;
    *a = *b;
    *b = t;
}

//  minHeapify function.
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->sizes &&
        minHeap->Array[left]->frequency < minHeap->Array[smallest]->frequency)
      smallest = left;

    if (right < minHeap->sizes &&
        minHeap->Array[right]->frequency < minHeap->Array[smallest]->frequency)
      smallest = right;

    if (smallest != idx)
    {
        Swap_node(&minHeap->Array[smallest], &minHeap->Array[idx]);
        minHeapify(minHeap, smallest);
    }
}


//  extract minimum value node
struct minimum_heapnode* extractMin(struct MinHeap* minHeap)
{
    struct minimum_heapnode* temp = minHeap->Array[0];
    minHeap->Array[0] = minHeap->Array[minHeap->sizes - 1];
    --minHeap->sizes;
    minHeapify(minHeap, 0);
    return temp;
}

//   insert a new node to Min Heap
void insertMinHeap(struct MinHeap* minHeap, struct minimum_heapnode* minimum_heapnode)
{
    ++minHeap->sizes;
    int i = minHeap->sizes - 1;
    while (i && minimum_heapnode->frequency < minHeap->Array[(i - 1)/2]->frequency)
    {
        minHeap->Array[i] = minHeap->Array[(i - 1)/2];
        i = (i - 1)/2;
    }
    minHeap->Array[i] = minimum_heapnode;
}

//  build min heap
void buildMinHeap(struct MinHeap* minHeap)
{
    int n = minHeap->sizes - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

//  print an Array of sizes n
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}


// Creates a min heap of capacity equal to sizes and inserts all character of
// character[] in min heap. Initially sizes of min heap is equal to capacity
struct MinHeap* construct_minheap(char character[], int frequency[], int sizes)
{
    struct MinHeap* minHeap = createMinHeap(sizes);
    for (int i = 0; i < sizes; ++i)
        minHeap->Array[i] = newNode(character[i], frequency[i]);
    minHeap->sizes = sizes;
    buildMinHeap(minHeap);
    return minHeap;
}

//  this function makes Huffman tree
struct minimum_heapnode* buildHuffmanTree(char character[], int frequency[], int sizes)
{
    struct minimum_heapnode *left, *right, *top;

    // Step 1: Create a min heap of capacity equal to sizes.  Initially, there are
    // modes equal to sizes.
    struct MinHeap* minHeap = construct_minheap(character, frequency, sizes);

    // Iterate while sizes of heap doesn't become 1
     while(!(minHeap->sizes == 1))
    {
        // Step 2: Extract the two minimum frequency items from min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Step 3:  Create a new internal node with frequencyuency equal to the
        // sum of the two nodes frequencyuencies. Make the two extracted node as
        // left and right children of this new node. Add this node to the min heap
        // '$' is a special value for internal nodes, not used
        top = newNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }

    // Step 4: The remaining node is the root node and the tree is complete.
    return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree.  It uses arr[] to
// store codes
void print_binarycode(struct minimum_heapnode* root, int arr[], int top)
{
    // Assign 0 to left edge and recur
    if (root->left)
    {
        arr[top] = 0;
        print_binarycode(root->left, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if (root->right)
    {
        arr[top] = 1;
        print_binarycode(root->right, arr, top + 1);
    }

    // If this is a leaf node, then it contains one of the input
    // characters, print the character and its code from arr[]

        if( !(root->left) && !(root->right))
    {
        printf("%c: ", root->character);
        printArr(arr, top);
    }
}


//this build haffman tree and print by visiting them
void haffman_code(char character[], int frequency[], int sizes)
{
   //  Construct Huffman Tree
   struct minimum_heapnode* root = buildHuffmanTree(character, frequency, sizes);

   // Print Huffman codes using the Huffman tree built above
   int arr[maximum_tree_hight], top = 0;
   print_binarycode(root, arr, top);
}



int main()
{

    int m ;
    cin>>m;
	char arr[m] ;
	int frequency[m] ;
	for(int j=0;j<m;j++) cin>>arr[j]>>frequency[j];
	int sizes = sizeof(arr)/sizeof(arr[0]);
	haffman_code(arr, frequency, sizes);
	return 0;
}

