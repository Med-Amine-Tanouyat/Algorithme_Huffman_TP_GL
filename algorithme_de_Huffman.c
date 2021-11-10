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