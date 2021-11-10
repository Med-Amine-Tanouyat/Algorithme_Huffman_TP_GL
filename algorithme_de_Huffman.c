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
    //la capcit� de l'arbre
    int capacity;
    //la taille totale de l'arbre de Huffman
    int size;
    //Un tableau de pointeurs vers les noeuds de l'arbre
	HuffmanTreeNode** array;
} HuffmanTree;

//fonction qui cr�e l'arbre de Huffman � partir d'une capacit� donn�e(allocation m�moire & affectation des champs de strct)
struct HuffmanTree* createHuffmanTree(int cap) {
    HuffmanTree* huffmanTree = (HuffmanTree*)malloc(sizeof(HuffmanTree));
    
    huffmanTree->size = 0;
    huffmanTree->capacity = cap;
    huffmanTree->array = (struct HuffmanTreeNode**)malloc(huffmanTree->capacity * sizeof(struct HuffmanTreeNode*));
        
    return huffmanTree;
}