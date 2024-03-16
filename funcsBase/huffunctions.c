#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "huffunctions.h"
#include "..\estruturaLinkedList\linked.h"
//Funções do Huffman

void printByteBinary(char *binary, unsigned char byte){
    // Loop para percorrer cada bit do byte
    
    for (int i = 7; i >= 0; i--)
    {
        // Desloca o bit mais significativo (MSB) para a direita por i posições
        // e verifica se o resultado AND com 1 é igual a 1
        // Isso verifica se o bit na posição i é 1 ou 0
        binary[7 - i] = (byte >> i) & 1 ? '1' : '0';
    }
}
void writeNewByte(DefaultNode *nodeByte,FILE *file){
    unsigned char byte = 0;
    for(int i = 0; i < 8; i++){
        byte = byte << 1;
        byte = byte | nodeByte->item;
        nodeByte = nodeByte->next;
    }
    
    fprintf(file, "%c", byte);
}
void writeNewBits(DefaultNode *node, FILE *file, DefaultNode **nodeByte){
    if(node == NULL) return;
    writeNewBits(node->next, file, nodeByte);
    *nodeByte = createDefaultNode(*nodeByte, node->item);
    if((*nodeByte)->currentSize == 8){
        writeNewByte(*nodeByte, file);
        freeAllDefaultNode(*nodeByte);
        *nodeByte = NULL;
    }
    free(node); // Volta limpando toda a lista.
}

void searchNewBinary(FILE *fileEncrypty, Node *tree, int byte, DefaultNode *nodeSearch, DefaultNode **nodeByte){
    
    if(tree != NULL){
        if(tree->item == byte){
            writeNewBits(nodeSearch, fileEncrypty, nodeByte);
            return;
        } // Retornando o caminho até a folha que representa o byte.
        else{
            searchNewBinary(fileEncrypty, tree->left, byte, createDefaultNode(nodeSearch, 0), nodeByte);
            searchNewBinary(fileEncrypty,tree->right, byte, createDefaultNode(nodeSearch, 1), nodeByte);
        }
    }else removeDefaultNode(nodeSearch);
    // Remove o ultimo elemento do caminho até adicionado.
}

void freeAllTree(Node *tree){
    if(tree != NULL){
        freeAllTree(tree->left);
        freeAllTree(tree->right);
        free(tree);
    }
}

int leFrequencia(int *array, char *minhaString)
{

    memset(array, 0, 256 * sizeof(int));
    FILE *file = fopen(minhaString, "rb"); // Lê os bits do arquivo, 'rb' -> Read Binary
    if (file == NULL){ // Se o arquivo não existir, retorna erro.
        perror("Error");
        return 0;
    }

    unsigned char byte;
    while (fscanf(file, "%c", &byte) != EOF){ // Lendo todo o arquivo até o seu final e armazenando a frequência no array.
        array[byte]++;
    }

    fclose(file); // Fecha o arquivo.
    return 1;
}

void escreverNovoBin(char *minhaString, Node *pq){
    FILE *file = fopen(minhaString, "rb"); // Lê os bits do arquivo, 'rb' -> Read Binary
    FILE *fileEncrypty = fopen("encrypted.7", "wb"); // Escreve os bits do arquivo, 'wb' -> Write Binary
    unsigned char byte;
    DefaultNode *nodeByte = (DefaultNode *) malloc((sizeof(DefaultNode)));
    nodeByte = NULL;
    while (fscanf(file, "%c", &byte) != EOF)
        searchNewBinary(fileEncrypty,pq, byte, NULL, &nodeByte);
    printf("Calculando o lixo...\n");
    int lixo = 0;
    if(nodeByte != NULL){
        lixo = 8 - nodeByte->currentSize;
    }
    
    int tamanho = 0;
    tamanhoDaArvore(pq, &tamanho);

    // Tenho o tamanho da arvore, o lixo e o arquivo compactado.
    // Agora vou escrever o cabeçalho.

    FILE *fileHeader = fopen("header.7", "wb");

    printf("Escrevendo o cabeçalho do arquivo...\n");
    unsigned char byte1, byte2;
    byte1 = lixo << 5 | tamanho >> 8;
	byte2 = tamanho;
    fputc(byte1, fileHeader);
    fputc(byte2, fileHeader);
    
    preOrderTree(fileHeader, pq);
    fclose(fileEncrypty);
    fileEncrypty = fopen("encrypted.txt", "rb");

    unsigned char ch;
    while (fscanf(fileEncrypty, "%c", &ch) != EOF) {
        fputc(ch, fileHeader);    
    }

    
    if(lixo > 0){
        while (nodeByte != NULL) {
            byte = (byte << 1) | nodeByte->item;
            nodeByte = nodeByte->next;
        }
        byte = byte << lixo;
        fputc(byte, fileHeader);
    }
    
    fclose(fileHeader);
    fclose(fileEncrypty);
}

void preOrderTree(FILE* file,Node *tree){
    if(tree != NULL){
        fprintf(file, "%c", tree->item);
        preOrderTree(file, tree->left);
        preOrderTree(file, tree->right);
    }
}

void tamanhoDaArvore(Node *tree, int *tamanho){
    if(tree != NULL){
        (*tamanho)++;
        tamanhoDaArvore(tree->left, tamanho);
        tamanhoDaArvore(tree->right, tamanho);
    }
}