#ifndef COLA_CIRCULAR_H
#define COLA_CIRCULAR_H

#include "RomaVictor.h"

// Estructura de datos para representar una cola circular
typedef struct circular_queue *queue;

// Crea e inicializa una cola
queue newQueue(u32 size);

// Devuelve si la cola pt está vacía, 1 si está vacía, 0 si no lo está
int isEmpty(queue pt);

// Devuelve el primer elemento de la cola pt
u32 front(queue pt);

// Añade el elemento 'x' a la cola pt
void enqueue(queue pt, u32 x);

// Desencola el primer elemento de la cola pt
void dequeue(queue pt);

// Elimina la cola pt, liberando la memoria
void deleteQueue(queue pt);
#endif