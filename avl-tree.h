#ifndef AVLTREE_H
#define AVLTREE_H

#include "RomaVictor.h"

typedef struct Node_t *Node;
typedef struct Tuple_t *Tuple;

// Función utilitaria para obtener la altura del arbol
u32 height(Node N);

// Función utilitaria para obtener el maximo entre dos enteros u32
u32 max(u32 a, u32 b);

/* Función auxiliar que aloja memoria para un nuevo nodo, dada una llave y
    punteros NULL hacia izquierda y derecha */
Node newNode(u32 key);

// Función utilitaria para rotar un subarbol hacia la derecha
Node rightRotate(Node y);

// Función utilitaria para rotar un subarbol hacia la izquierda
Node leftRotate(Node x);

// Obtener el factor de balance de un nodo N
u32 getBalance(Node N);

/* Función recursiva para insertar un nuevo Nodo en un subarbol "G", manteniendo
    el balance del mismo. Devuelve la nueva raíz del subarbol.*/
Node insert(Node node, u32 key, Grafo G, u32 *position, u32 *pos_v);

// Elimina el árbol, liberando la memoria correspondiente al mismo
void deleteTree(Node avl);

void avl_to_sorting_array(Node root, vertice *v, vertice **v_orden);

#endif