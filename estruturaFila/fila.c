#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

// Priority Queue Functions

Priority_Queue *create_priority_queue()
{
    Priority_Queue *new_priority_queue = (Priority_Queue *)malloc(sizeof(Priority_Queue));
    new_priority_queue->head = NULL;
    return new_priority_queue;
}   
int is_empty(Priority_Queue *pq)
{
    return (pq->head == NULL);
}
void enqueue(Priority_Queue *pq, unsigned char item, int priority)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->item = item;
    new_node->priority = priority;
    new_node->right = NULL;
    new_node->left = NULL;
    if ((is_empty(pq)) || (priority < pq->head->priority))
    {
        new_node->next = pq->head;
        pq->head = new_node;
    }
    else
    {
        Node *current = pq->head;
        while ((current->next != NULL) && (current->next->priority < priority))
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}
void enqueueWithNode(Priority_Queue *pq, Node* no)
{
    if ((is_empty(pq)) || (no->priority <= pq->head->priority))
    {
        no->next = pq->head;
        pq->head = no;
    }
    else
    {
        Node *current = pq->head;
        while ((current->next != NULL) && (current->next->priority < no->priority))
        {
            current = current->next;
        }
        no->next = current->next;
        current->next = no;
    }
}
Node *dequeue(Priority_Queue *pq)
{
    if (is_empty(pq))
    {
        printf("Priority Queue underflow");
        return NULL;
    }
    else
    {
        Node *node = pq->head;
        pq->head = pq->head->next;
        node->next = NULL;
        return node;
    }
}

void criarFila(int *frequencia, Priority_Queue *pq){
    for (int x = 0; x < 256; x++)
        if (frequencia[x] != 0) enqueue(pq, x, frequencia[x]); // Adiciona o byte e sua frequência na fila de prioridade.
}

void criarArvoreDeHuffman(Priority_Queue *pq){

    while(pq->head->next != NULL){ // Espaçando a fila de prioridade em arvóres.
        Node *left = dequeue(pq);
        Node *right = dequeue(pq);
        Node *new_node = (Node *)malloc(sizeof(Node));

        new_node->item = '*';   
        new_node->priority = left->priority + right->priority;
        new_node->left = left;
        new_node->right = right;
        enqueueWithNode(pq, new_node);
    }
    // Teoricamente espaçei a fila de prioridade em nós.

}