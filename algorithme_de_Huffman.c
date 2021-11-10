#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include <string.h>
#define MAX_HEIGHT 50

//the structure of a node of the Huffman tree
typedef struct HuffmanTreeNode {
    char letter;
    int freq;
    struct HuffmanTreeNode *left, *right;
} HuffmanTreeNode;
//function which creates a new tree node
HuffmanTreeNode  *newTreeNode(char c, int freq) {
	HuffmanTreeNode *t = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode));
	t->letter = c;
	t->freq = freq;
	t->left = t->right = NULL;
	 
	return t;
}
//La structure de l'arbre de Huffman
typedef struct HuffmanTree {
    //la capcitï¿½ de l'arbre
    int capacity;
    //la taille totale de l'arbre de Huffman
    int size;
    //Un tableau de pointeurs vers les noeuds de l'arbre
	HuffmanTreeNode** array;
} HuffmanTree;

//fonction qui crï¿½e l'arbre de Huffman ï¿½ partir d'une capacitï¿½ donnï¿½e(allocation mï¿½moire & affectation des champs de strct)
struct HuffmanTree* createHuffmanTree(int cap) {
    HuffmanTree* huffmanTree = (HuffmanTree*)malloc(sizeof(HuffmanTree));
    
    huffmanTree->size = 0;
    huffmanTree->capacity = cap;
    huffmanTree->array = (struct HuffmanTreeNode**)malloc(huffmanTree->capacity * sizeof(struct HuffmanTreeNode*));
        
    return huffmanTree;
}
//fonction qui sert à la permutation de deux éléments
void swap(HuffmanTreeNode** a, HuffmanTreeNode** b) { 
    HuffmanTreeNode *t = *a; //pointeur temporaire
    *a = *b; 
    *b = t; 
}

//fonction qui permet de réaliser la propriété de min-Heap(dans l'arbre de Huffman)
void minHeapify(HuffmanTree* huffmanTree, int i) {
 
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
 
 	//on place chaque noeud conveablement dans l'arbre d'apres sa frequence
    if (left < huffmanTree->size && huffmanTree->array[left]->freq < huffmanTree->array[smallest]->freq)
        smallest = left;
 
    if (right < huffmanTree->size && huffmanTree->array[right]->freq < huffmanTree->array[smallest]->freq)
        smallest = right;
 
    if (smallest != i) {
        swap(&huffmanTree->array[smallest], &huffmanTree->array[i]);
        minHeapify(huffmanTree, smallest);
    }
}
