#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include <string.h>
#define MAX_HEIGHT 50

//la structure d'un noeud de l'arbre de Huffman
typedef struct HuffmanTreeNode {
    char letter;
    int freq;
    struct HuffmanTreeNode *left, *right;
} HuffmanTreeNode;

//fonction qui crée un nouveau noeud de l'arbre
HuffmanTreeNode  *newTreeNode(char c, int freq) {
	HuffmanTreeNode *t = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode));
	t->letter = c;
	t->freq = freq;
	t->left = t->right = NULL;
	 
	return t;
}

//La structure de l'arbre de Huffman
typedef struct HuffmanTree {
    //la capcité de l'arbre
    int capacity;
    //la taille totale de l'arbre de Huffman
    int size;
    //Un tableau de pointeurs vers les noeuds de l'arbre
	HuffmanTreeNode** array;
} HuffmanTree;

//fonction qui crée l'arbre de Huffman à partir d'une capacité donnée(allocation mémoire & affectation des champs de struct)
struct HuffmanTree* createHuffmanTree(int cap) {
    HuffmanTree* huffmanTree = (HuffmanTree*)malloc(sizeof(HuffmanTree));
    
    huffmanTree->size = 0;
    huffmanTree->capacity = cap;
    huffmanTree->array = (struct HuffmanTreeNode**)malloc(huffmanTree->capacity * sizeof(struct HuffmanTreeNode*));
        
    return huffmanTree;
}

//fonction qui sert à la permutation de deux éléments
void swap(HuffmanTreeNode** a, HuffmanTreeNode** b) 
{ 
    HuffmanTreeNode *t = *a; //pointeur temporaire
    *a = *b; 
    *b = t; 
}

//fonction qui permet de réaliser la propriété de min-Heap(dans l'arbre de Huffman)
void minHeapify(HuffmanTree* huffmanTree, int i) {
 
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
 
    if (left < huffmanTree->size && huffmanTree->array[left]->freq < huffmanTree->array[smallest]->freq)
        smallest = left;
 
    if (right < huffmanTree->size && huffmanTree->array[right]->freq < huffmanTree->array[smallest]->freq)
        smallest = right;
 
    if (smallest != i) {
        swap(&huffmanTree->array[smallest], &huffmanTree->array[i]);
        minHeapify(huffmanTree, smallest);
    }
}

//fonction pour construire l'arbre de Huffman(minHeapify à chaque insertion)
void buildHuffmanTree(HuffmanTree* huffmanTree) {
    int n = huffmanTree->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(huffmanTree, i);
}

//fonction qui extrait le noeud de fréquence minimun de l'arbre
HuffmanTreeNode* extractMin(HuffmanTree* huffmanTree) {
 
    HuffmanTreeNode* t = huffmanTree->array[0];
    huffmanTree->array[0] = huffmanTree->array[huffmanTree->size - 1];
 
    --huffmanTree->size;
    minHeapify(huffmanTree, 0);
 
    return t;
}

//fonction pour insérer un noeud à l'arbre de Huffman
void insertHuffmanTreeNode(HuffmanTree* huffmanTree, HuffmanTreeNode* huffmanTreeNode) {
 
    ++huffmanTree->size;
    int i = huffmanTree->size - 1;
 
    while (i && huffmanTreeNode->freq < huffmanTree->array[(i - 1) / 2]->freq) {
        huffmanTree->array[i] = huffmanTree->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
 
    huffmanTree->array[i] = huffmanTreeNode;
}

HuffmanTree* createAndBuildTree(char data[], int freq[], int size) {
 
    HuffmanTree* huffmanTree = createHuffmanTree(size);
	int i;
    for (i = 0; i < size; ++i)
        huffmanTree->array[i] = newTreeNode(data[i], freq[i]);
 
    huffmanTree->size = size;
    buildHuffmanTree(huffmanTree);
 
    return huffmanTree;
}

HuffmanTreeNode* fullTree(char data[], int freq[], int size) {
    HuffmanTreeNode *left, *right, *top;
 
    //on crée un arbre de Huffman de capacity=size
    HuffmanTree* huffmanTree = createAndBuildTree(data, freq, size);
 
    while (!(huffmanTree->size == 1)) {
 
        //on prend les deux minimuns consécutifs pour remplir l'arbre
        left = extractMin(huffmanTree);
        right = extractMin(huffmanTree);
 
        //on ajoute la somme des fréquences des deux noeds mins en tant que père de ces derniers
        top = newTreeNode('*', left->freq + right->freq);
        top->left = left;
        top->right = right;
 
        insertHuffmanTreeNode(huffmanTree, top);
    }

    return extractMin(huffmanTree);
}

//fonction qui réalise le codage dans l'arbre à partir de la racine
void affectCode(struct HuffmanTreeNode* root, int arr[], int top) {
 
    //on affecte le bit 0 pour le fils gauche
    if (root->left) {
        arr[top] = 0;
        affectCode(root->left, arr, top + 1);
    }
    //on affecte le bit 1 pour le fils droite
    if (root->right) {
 
        arr[top] = 1;
        affectCode(root->right, arr, top + 1);
    }
    //on affiche le charactere et son code binaire
    if (!(root->left) && !(root->right)) {
        printf("Codage compresse de %c: ", root->letter);
        int i;
	    for (i = 0; i < top; i++)
	        printf("%d", arr[i]);
	        
	    printf("\n");
    }
}

//fonction principale de l'algorithme
void huffmanAlgo(char data[], int freq[], int size) {
    //on construit l'arbre de Huffman
    HuffmanTreeNode* root = fullTree(data, freq, size);
    
    //on affiche les codes binaires des charactères
    int arr[MAX_HEIGHT], top = 0;
    affectCode(root, arr, top);
}

int main() {
	char input[] = {'a', 'b', 'c', 'd'};
    int freq[] = {5, 1, 6, 3};
 	  
    int size = sizeof(input) / sizeof(input[0]);
    huffmanAlgo(input, freq, size);
	 
	return 0;
}
