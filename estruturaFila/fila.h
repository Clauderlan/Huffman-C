#ifndef FILA_H
#define FILA_H

#include "../funcsBase/huffunctions.h"

typedef struct priority_queue{
    Node *head;
} Priority_Queue;

// Funções públicas do ADT - Fila de prioridade

Priority_Queue* create_priority_queue();
int is_empty(Priority_Queue* pq);
void enqueue(Priority_Queue* pq, unsigned char item, int priority);
void enqueueWithNode(Priority_Queue* pq, Node* no);
Node* dequeue(Priority_Queue* pq);
void criarArvoreDeHuffman(Priority_Queue *pq);
void criarFila(int *frequencia, Priority_Queue *pq);

#endif