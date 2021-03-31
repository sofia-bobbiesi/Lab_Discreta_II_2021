// C program to insert a node in AVL tree
#include "avl-tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// An AVL tree node
struct Node_t {
    u32 key;
    u32 position;
    Node left;
    Node right;
    u32 height;
};

// A utility function to get the height of the tree
u32 height(Node N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
u32 max(u32 a, u32 b) {
    return (a > b) ? a : b;
}

static vertice crear_vertice(u32 nombre) {
    vertice nuevo_vertice = calloc(1,sizeof(struct _vertice_t));
    assert(nuevo_vertice != NULL);

    nuevo_vertice->nombre_real = nombre;
    nuevo_vertice->vecinos = calloc(1,sizeof(vecinos));

    return nuevo_vertice;
}
/* Helper function that allocates a new node with the given key and
        NULL left and right pointers. */
Node newNode(u32 key) {
    Node node = malloc(sizeof(struct Node_t));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially added at leaf
    return (node);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
Node rightRotate(Node y) {
    Node x = y->left;
    Node T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
Node leftRotate(Node x) {
    Node y = x->right;
    Node T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
u32 getBalance(Node N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
Node insert(Node node, u32 key, Grafo G, u32 *position, u32 *pos_v) {
    /* 1. Perform the normal BST insertion */
    if (node == NULL) {
        Node new_node = newNode(key);
        vertice v = crear_vertice(key);
        new_node->position = *position;
        G->vertices[*position] = v;
        G->vertices_ordenados[*position] = v;
        *pos_v = *position;
        *position += 1;
        return new_node;
    }
    if (key < node->key)
        node->left = insert(node->left, key, G, position, pos_v);
    else if (key > node->key)
        node->right = insert(node->right, key, G, position, pos_v);
    else // Equal keys are not allowed in BST
         // the node exists, therefore it also exists in the array
        *pos_v = node->position;
    return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), height(node->right));

    /* 3. Get the balance factor of this ancestor
            node to check whether this node became
            unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pou32er */
    return node;
}

void deleteTree(Node avl) {
    if (avl != NULL) {
        deleteTree(avl->right);
        deleteTree(avl->left);
        free(avl);
        avl = NULL; // evitar danling pointers
    }
}

void avl_to_sorting_array(Node root, vertice *v, vertice **v_orden) {
    if(root != NULL) {
        avl_to_sorting_array(root->left, v, v_orden);
        **v_orden = v[root->position];
        ++*v_orden;
        avl_to_sorting_array(root->right, v, v_orden);
    }
}