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

void writeNewByte(int *bits, FILE *file) {
    unsigned char byte = 0;
    // Construir o byte a partir dos bits
    for (int i = 0; i < 8; i++) {
        byte |= (bits[i] & 0x01) << (7 - i);
    }
    // Escrever o byte no arquivo
    fputc(byte, file);
}



void writeNewBits(DefaultNode *node, FILE *file, int* bitsToByte, int *contBitsToByte){
    if(node == NULL) return;
    writeNewBits(node->next, file, bitsToByte, contBitsToByte);
    // 01010100
    bitsToByte[*contBitsToByte] = node->item;
    (*contBitsToByte)++;
    
    if(*contBitsToByte == 8){
        writeNewByte(bitsToByte, file);
        *contBitsToByte = 0;
    }
}

void searchNewBinary(FILE *fileEncrypty, Node *tree, int byte, DefaultNode *nodeSearch, int *bitsToByte, int *contBitsToByte){
    
    if(tree != NULL){
        if(tree->item == byte){
            writeNewBits(nodeSearch, fileEncrypty, bitsToByte, contBitsToByte);
            return;
        } // Retornando o caminho até a folha que representa o byte.
        else{
            searchNewBinary(fileEncrypty, tree->left, byte, createDefaultNode(nodeSearch, 0), bitsToByte, contBitsToByte);
            searchNewBinary(fileEncrypty, tree->right, byte, createDefaultNode(nodeSearch, 1), bitsToByte, contBitsToByte);
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
    int bits[8];
    int contBitsToByte = 0;
    while (fscanf(file, "%c", &byte) != EOF)
        searchNewBinary(fileEncrypty,pq, byte, NULL, bits, &contBitsToByte);

    printf("Calculando o lixo...\n");
    int lixo = 0;
    if(contBitsToByte != 0){
        lixo = 8 - contBitsToByte;
    }
    
    int tamanho = 0;
    tamanhoDaArvore(pq, &tamanho);

    // Tenho o tamanho da arvore, o lixo e o arquivo compactado.
    // Agora vou escrever o cabeçalho.

    FILE *fileHeader = fopen("file.7", "wb");

    printf("Escrevendo o cabeçalho do arquivo...\n");
    unsigned char byte1, byte2;
    byte1 = lixo << 5 | tamanho >> 8;
	byte2 = tamanho;
    fputc(byte1, fileHeader);
    fputc(byte2, fileHeader);
    
    preOrderTree(fileHeader, pq);
    fclose(fileEncrypty);
    fileEncrypty = fopen("encrypted.7", "rb");

    unsigned char ch;
    while (fscanf(fileEncrypty, "%c", &ch) != EOF) {
        fputc(ch, fileHeader);    
    }

    if(lixo > 0){
        for(int x = 8 - lixo; x < 8; x++){
            bits[x] = 0;
        }
        writeNewByte(bits, fileHeader);
    }
    
    fclose(fileHeader);
    fclose(fileEncrypty);
    remove("encrypted.7");
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