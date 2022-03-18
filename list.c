#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {

    List * lista = (List*)malloc(sizeof(List));
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
  
    return lista;
}

void * firstList(List * list) {

    if(list->head == NULL) return NULL;
  
    if(list->head != NULL) list->current = list->head;
    return (list->current->data);
}

void * nextList(List * list) {

    if(list->current == NULL) return NULL;

    if(list->current->next == NULL) return NULL;

    if(list->current->next != NULL) list->current = list->current->next;
  
    return (list->current->data);
}

void * lastList(List * list) {

    if(list->current == NULL) return NULL;  

    while(list->current->next != NULL){
        list->current = list->current->next;
    }
  
    return list->current->data;
}

void * prevList(List * list) {

    if(list->current==NULL) return NULL;

    if(list->current->prev != NULL){
        list->current = list->current->prev;
        return list->current->data;
    } 

    return NULL;
}

void pushFront(List * list, void * data){
    Node* new = createNode(data);
    
    //Verifico que la lista no esté vacia
    if (list->head!=NULL){
        new->next=list->head;
        list->head->prev=new;
        list->head=new;
    }

    list->head=new;
    list->current=new;
    list->tail=new;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data){

    Node *new=createNode(data);

    //en caso de que esté vacio
    if(list->current==NULL) list->current=new;

    //en caso de que sea el último nodo
    if(list->current->next==NULL){
        new->prev=list->current;
        list->current->next=new;
        list->tail=new;
    }

    //en caso de que sea el primer nodo
    if(list->current->prev==NULL){
        new->prev=list->current;
        new->next=list->current->next;
        list->current->next=new;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list){
    void *eliminado = list->current->data;
    Node *resp = list->current; 

    //en caso que sea el primer nodo
    if(resp->prev == NULL){
        list->head = resp->next;
        list->head->prev = NULL;
        list->current = resp->next;
        free(resp);
        return eliminado;
    } 

    //en caso de que sea el último nodo
    if(resp->next == NULL){
        list->tail = resp->prev;
        list->tail->next  = NULL;
        list->current = resp->prev;
        free(resp);
        return eliminado;
    }

    //en caso de que este vacío
    if(list != NULL){
        resp->prev->next = list->current->next;
        resp->next->prev = list->current->prev;
        list->current = resp->next;
        free(resp);
        return eliminado;
    }
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}