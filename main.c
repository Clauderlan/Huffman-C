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
    printf("Digite o arquivo a ser compactado : ");
    char minhaString[30];
    scanf("%s", minhaString); // Lê o nome do arquivo pelo usuário.
    
    // Lê o arquivo e armazena a frequência de cada byte no array.
    if(!leFrequencia(frequencia, minhaString)) return 0;
    printf("Lendo a frequência de cada byte...\n");

    Priority_Queue *pq = create_priority_queue(); // Inicializando a fila de prioridade.

    printf("Criando a fila de prioridade das frequências...\n");
    criarFila(frequencia, pq); // Adicionando os bytes e suas frequências na fila de prioridade.
    
    printf("Criando a árvore de Huffman...\n");
    criarArvoreDeHuffman(pq); // Criando a árvore de Huffman.
    
    // "pq" agora guarda a raiz da arvóre de Huffman.
    printf("Escrevendo o novo binário do arquivo, agora compactado, resultado em : encrypted.txt\n");
    escreverNovoBin(minhaString, pq->head); // Escrevendo o novo arquivo binário.
    
   
    printf("Escrevendo o cabeçalho do arquivo...\n");
    FILE *file = fopen("encrypted.txt", "r");
    unsigned long int total_bits = 0;
    while (fgetc(file) != EOF)
        total_bits++;
    fclose(file);

    short lixo = total_bits % 8;
    lixo = 8 - lixo;
    printf("\n oadoadoad %d %d ", total_bits,lixo);
    int tamanho = 0;
    tamanhoDaArvore(pq->head, &tamanho);

    // Tenho o tamanho da arvore, o lixo e o arquivo compactado.
    // Agora vou escrever o cabeçalho.

    FILE *fileHeader = fopen("header.txt", "wb");

    unsigned char byte1, byte2;
    byte1 = lixo << 5 | tamanho >> 8;
	byte2 = tamanho;
    char binary1[9] = { '\0' };
    char binary2[9] = { '\0' };
    printByteBinary(binary1,byte1);
    printByteBinary(binary2,byte2);
    for(int x = 0; x < 16; x++){
        if(x < 8){
            fputc(binary1[x], fileHeader);
        }else{
            fputc(binary2[x - 8], fileHeader);
        }
    }
    preOrderTree(fileHeader, pq->head);
    file = fopen("encrypted.txt", "rb");
    unsigned char ch;
    while (fscanf(file, "%c", &ch) != EOF) {
        fputc(ch, fileHeader);    
    }
    fclose(file);

    if(lixo > 0){
        for(int i = 0; i < lixo; i++){
            fputc('0', fileHeader);
        }
    }
    
    fclose(fileHeader);

    freeAllTree(pq->head);
    free(pq);
    
    return 0;
}