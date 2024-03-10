#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "huffunctions.h"
#include "..\estruturaLinkedList\linked.h"
//Funções do Huffman

void printByteBinary(unsigned char byte)
{
    // Loop para percorrer cada bit do byte
    char binary[9] = { '\0' };
    for (int i = 7; i >= 0; i--)
    {
        // Desloca o bit mais significativo (MSB) para a direita por i posições
        // e verifica se o resultado AND com 1 é igual a 1
        // Isso verifica se o bit na posição i é 1 ou 0
        binary[7 - i] = (byte >> i) & 1 ? '1' : '0';
    }
    
    printf("%s ", binary);
}
void writeNewByte(DefaultNode *node, FILE *file){
    if(node == NULL) return;
    writeNewByte(node->next, file);
    fprintf(file, "%d", node->item);
    free(node); // Volta limpando toda a lista.
}

void searchNewBinary(Node *tree, int byte, DefaultNode *nodeBinary){
    
    if(tree != NULL){
        if(tree->item == byte){
            FILE *file = fopen("encrypted.txt", "a");
            writeNewByte(nodeBinary, file);
            fclose(file);
            return;
        } // Retornando o caminho até a folha que representa o byte.
        else{
            searchNewBinary(tree->left, byte, createDefaultNode(nodeBinary, 0));
            searchNewBinary(tree->right, byte, createDefaultNode(nodeBinary, 1));
        }
    }else removeDefaultNode(nodeBinary);
    // Remove o ultimo elemento do caminho até adicionado.
}

void freeAllTree(Node *tree){
    if(tree != NULL){
        freeAllTree(tree->left);
        freeAllTree(tree->right);
        free(tree);
    }
}

void leFrequencia(int *array, char *minhaString)
{

    memset(array, 0, 256 * sizeof(int));
    FILE *file = fopen(minhaString, "rb"); // Lê os bits do arquivo, 'rb' -> Read Binary
    if (file == NULL){ // Se o arquivo não existir, retorna erro.
        perror("Error");
        return;
    }

    unsigned char byte;
    while (fscanf(file, "%c", &byte) != EOF){ // Lendo todo o arquivo até o seu final e armazenando a frequência no array.
        array[byte]++;
    }

    fclose(file); // Fecha o arquivo.
}



void escreverNovoBin(char *minhaString, Node *pq){
    FILE *file = fopen(minhaString, "rb"); // Lê os bits do arquivo, 'rb' -> Read Binary
    unsigned char byte;
    while (fscanf(file, "%c", &byte) != EOF)
        searchNewBinary(pq, byte, NULL);
    fclose(file);
}