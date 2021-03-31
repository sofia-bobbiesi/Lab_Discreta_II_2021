#ifndef AVLTREE_H
#define AVLTREE_H

#include "RomaVictor.h"

typedef struct Node_t *Node;
typedef struct Tuple_t *Tuple;

// A utility function to get the height of the tree
u32 height(Node N);

// A utility function to get maximum of two u32egers
u32 max(u32 a, u32 b);

/* Helper function that allocates a new node with the given key and
        NULL left and right pou32ers. */
Node newNode(u32 key);

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
Node rightRotate(Node y);

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
Node leftRotate(Node x);

// Get Balance factor of node N
u32 getBalance(Node N);

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
Node insert(Node node, u32 key, Grafo G, u32 *position, u32 *pos_v);

//
void deleteTree(Node avl);

void avl_to_sorting_array(Node root, vertice *v, vertice **v_orden);

#endif