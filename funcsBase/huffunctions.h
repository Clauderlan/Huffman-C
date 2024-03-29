#ifndef HUFFUNCTIONS_H
#define HUFFUNCTIONS_H


// Structs base do Huffman

typedef struct node{
    unsigned char item;
    int priority;
    struct node *next;
    struct node*left;
    struct node*right;
} Node;

// Linked List
typedef struct defaultNode{
    int item;
    int currentSize;
    struct defaultNode *next;
} DefaultNode;


//Funções do Huffman

void printByteBinary(char *binary, unsigned char byte);
void searchNewBinary(FILE *fileEncrypty, Node *tree, int byte, DefaultNode *nodeSearch, int *bitsToByte, int *contBitsToByte);
void writeNewBits(DefaultNode *node, FILE *file, int* bitsToByte, int *contBitsToByte);
void writeNewByte(int *bits, FILE *file);
void freeAllTree(Node *tree);
int leFrequencia(int *array, char *minhaString);
void escreverNovoBin(char *minhaString, Node *pq);
void preOrderTree(FILE* file,Node *tree);
void tamanhoDaArvore(Node *tree, int *tamanho);
#endif