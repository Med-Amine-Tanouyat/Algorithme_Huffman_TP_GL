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
