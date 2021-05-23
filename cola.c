#include "cola.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct circular_queue {
    u32 *items;  // arreglo para guardar los elementos de la cola
    u32 maxsize; // capacidad máxima de la cola
    u32 front;   // puntero al primer elemento de la cola (si hay)
    u32 rear;    // puntero al último elemento de la cola
    u32 size;    // tamaño actual de la cola
};

queue newQueue(u32 size) {
    queue pt = malloc(sizeof(struct circular_queue));

    pt->items = malloc(size * sizeof(u32));
    pt->maxsize = size;
    pt->front = 0;
    pt->rear = UINT32_MAX; // equivalente a poner -1, al sumarle 1 en enqueue se
                           // restablece a 0
    pt->size = 0;

    return pt;
}

void deleteQueue(queue pt) {
    if (pt != NULL) {
        if (pt->items != NULL) {
            free(pt->items);
        }
        free(pt);
    }
}

int isEmptyQueue(queue pt) {
    return !(pt->size);
}

u32 front(queue pt) {
    if (isEmptyQueue(pt)) {
        printf("La cola está vacía, no se puede acceder.\n");
        deleteQueue(pt);
        return 0;
    }
    return pt->items[pt->front];
}

void enqueue(queue pt, u32 x) {
    if ((pt->size) == pt->maxsize) {
        printf("La cola está llena, no se pueden agregar más elementos.\n");
        deleteQueue(pt);
        return;
    }
    pt->rear = (pt->rear + 1) % pt->maxsize; // circular queue
    pt->items[pt->rear] = x;
    pt->size++;
}

void dequeue(queue pt) {
    if (isEmptyQueue(pt)) { // front == rear
        printf("La cola está vacía, no se puede eliminar.\n");
        deleteQueue(pt);
        return;
    }
    pt->front = (pt->front + 1) % pt->maxsize; // circular queue
    pt->size--;
}