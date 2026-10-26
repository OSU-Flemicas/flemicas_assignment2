#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodeObject node;

typedef struct NodeObject{
    int data;
    node *next;
} node;

node* createNode(int data){
    node* newNode = malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;    
    return newNode;
}

void printNodeList(node* list){
    while(list != NULL){
        printf("Node data is %d\n", list->data);
        list = list->next;
    }
}

void freeNode(node* node){
    free(node);
}

void freeNodeList(node* list){
    node* curr;
    while(list != NULL){
        curr = list;
        list = list->next;
        freeNode(curr);
    }
}

void externalFunctionList(node **head, node **tail, int num_items){
    node *newNode;
    printf("create a linked list of 3 nodes\n");
    for(int i = 0; i < num_items; i++){
        newNode = createNode(i);
        
        if(*head == NULL){
            *head = newNode;
            *tail = newNode;
        }else{
            // printf("tail node test: %d", ;
            (*tail)->next = newNode; // modifying double pointers https://stackoverflow.com/questions/14525444/how-to-increment-a-dereferenced-double-pointer accessed 10.25.26
            *tail = newNode;
        }
        
    }
}


int main(int argc, char * argv[]) {
  
    node *head = NULL;
    node *tail = NULL;
    
    externalFunctionList(&head, &tail, 3);

    printf("%d\n",tail->data);

    printNodeList(head);
    freeNodeList(head);
  
    return 0;
}

//gcc --std=gnu99 -Wall -o linkedList linkedList.c