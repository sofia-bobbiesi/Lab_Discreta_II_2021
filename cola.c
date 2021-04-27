#include "cola.h"
#include <stdlib.h>
#include <stdio.h>

struct circular_queue{
    u32 *items;     // arreglo para guardar los elementos de la cola
    u32 maxsize;    // capacidad máxima de la cola
    u32 front;      // puntero al primer elemento de la cola (si hay)
    u32 rear;       // puntero al último elemento de la cola
    u32 size;       // tamaño actual de la cola
};

queue newQueue(u32 size){
    queue pt = malloc(sizeof(struct circular_queue));

    pt->items = malloc(size * sizeof(u32));
    pt->maxsize = size;
    pt->front = 0;
    pt->rear = -1; //FIXME: te odio u32 y tus no negativos :(
    pt->size = 0;
 
    return pt;
}

int isEmpty(queue pt){
    return !size(pt);
}

u32 front(queue pt){
    if (isEmpty(pt)){
        printf("La cola está vacía, no se puede acceder.\n");
        exit(EXIT_FAILURE);
    } 
    return pt->items[pt->front];
}
 
void enqueue(queue pt, u32 x){
    if (size(pt) == pt->maxsize){
        printf("La cola está llena, no se pueden agregar más elementos.\n");
        exit(EXIT_FAILURE);
    }

    pt->rear = (pt->rear + 1) % pt->maxsize; // circular queue
    pt->items[pt->rear] = x;
    pt->size++;
 
    // printf("front = %d, rear = %d\n", pt->front, pt->rear);
}
 
void dequeue(queue pt){
    if (isEmpty(pt)){ // front == rear
        printf("La cola está vacía, no se puede eliminar.\n");
        exit(EXIT_FAILURE);
    } 
    pt->front = (pt->front + 1) % pt->maxsize;  // circular queue
    pt->size--;
 
    //printf("front = %d, rear = %d\n", pt->front, pt->rear);
}