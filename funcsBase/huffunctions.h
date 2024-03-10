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
    struct defaultNode *next;
} DefaultNode;


//Funções do Huffman

void printByteBinary(unsigned char byte);
void searchNewBinary(Node *tree, int byte, DefaultNode *nodeBinary);
void writeNewByte(DefaultNode *node, FILE *file);
void freeAllTree(Node *tree);
void leFrequencia(int *array, char *minhaString);
void escreverNovoBin(char *minhaString, Node *pq);

#endif