/*  Este archivo fue basado en el siguiente código:
 https://www.geeksforgeeks.org/avl-tree-set-1-insertion/ */
#ifndef AVLTREE_H
#define AVLTREE_H

#include "RomaVictor.h"

typedef struct Node_t *Node;

/* Función utilitaria para obtener la altura del arbol */
u32 height(Node N);

/*
    Función auxiliar que aloja memoria para un nuevo nodo, dada una llave y
    punteros NULL hacia izquierda y derecha
*/
Node newNode(u32 key);

/*  Función utilitaria para rotar un subarbol hacia la derecha */
Node rightRotate(Node y);

/*  Función utilitaria para rotar un subarbol hacia la izquierda */
Node leftRotate(Node x);

/* Obtener el factor de balance de un nodo N */
u32 getBalance(Node N);

/*
    Función recursiva para insertar un nuevo Nodo en un subarbol "G",
   manteniendo el balance del mismo. Devuelve la nueva raíz del subarbol.
*/
Node insert(Node node, u32 key, Grafo G, u32 *position, u32 *pos_v);

/*  Elimina el árbol, liberando la memoria correspondiente al mismo */
void deleteTree(Node avl);

/*
    Permite construir un arreglo ordenado basandose en la idea de un
    recorrido preorder para un AVL. Como cada nodo indica la posición de un
    vértice, el arreglo final consta de los vértices referenciados en el
    árbol de manera ordenada, evitando así la complejidad de hacer un
    ordenamiento mediante algún algoritmo costoso.
*/
void avl_to_sorting_array(Node root, vertice *v, vertice **v_orden);

#endif