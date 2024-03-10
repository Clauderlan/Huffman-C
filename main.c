#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// Funções do Huffman
#include "./estruturaFila/fila.h"
#include "./estruturaLinkedList/linked.h"
#include "./funcsBase/huffunctions.h"

int main()
{

    int frequencia[256]; // Array para armazenar a frequência de cada byte.

    char minhaString[30];
    scanf("%s", minhaString); // Lê o nome do arquivo pelo usuário.
    
    
    printf("Lendo a frequência de cada byte...\n");
    leFrequencia(frequencia, minhaString); // Lê o arquivo e armazena a frequência de cada byte no array.

    Priority_Queue *pq = create_priority_queue(); // Inicializando a fila de prioridade.

    printf("Criando a fila de prioridade das frequências...\n");
    criarFila(frequencia, pq); // Adicionando os bytes e suas frequências na fila de prioridade.
    
    printf("Criando a árvore de Huffman...\n");
    criarArvoreDeHuffman(pq); // Criando a árvore de Huffman.
    
    // "pq" agora guarda a raiz da arvóre de Huffman.
    printf("Escrevendo o novo binário do arquivo, agora compactado, resultado em : encrypted.txt\n");
    escreverNovoBin(minhaString, pq->head); // Escrevendo o novo arquivo binário.

    freeAllTree(pq->head);
    free(pq);
    
    return 0;
}