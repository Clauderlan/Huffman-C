#include <stdio.h>
#include <stdlib.h>
#include "linked.h"

// Funções base da lista encadeada

DefaultNode* createDefaultNode(DefaultNode *node, int item){
    DefaultNode *new_node = (DefaultNode *) malloc(sizeof(DefaultNode));
    if(node == NULL){
        new_node->currentSize = 1;
    }else{
        //rintf("%d\n", new_node->currentSize);
        new_node->currentSize = node->currentSize + 1;
    }
    new_node->next = node;
    new_node->item = item;
    return new_node;
}
void removeDefaultNode(DefaultNode *node){
    DefaultNode *aux = node;
    node = node->next;
    free(aux);
}
void freeAllDefaultNode(DefaultNode *node){
    if(node != NULL){
        freeAllDefaultNode(node->next);
        free(node);
    }
}