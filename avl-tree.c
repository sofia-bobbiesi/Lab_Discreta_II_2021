// Programa en C utilizado para insertar un nodo en un arbol AVL
#include "avl-tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Estructura de un nodo para un arbol AVL
struct Node_t {
    u32 key;
    u32 position;
    Node left;
    Node right;
    u32 height;
};

// Función utilitaria para obtener la altura del arbol
u32 height(Node N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Función utilitaria para obtener el maximo entre dos enteros u32
u32 max(u32 a, u32 b) {
    return (a > b) ? a : b;
}

static vertice crear_vertice(u32 nombre,u32 size) {
    vertice nuevo_vertice = calloc(1,sizeof(struct _vertice_t));
    assert(nuevo_vertice != NULL);

    nuevo_vertice->nombre_real = nombre;
    nuevo_vertice->vecinos = calloc(size,sizeof(vecinos));
    nuevo_vertice->size=size;

    return nuevo_vertice;
}

/* Función auxiliar que aloja memoria para un nuevo nodo, dada una llave y
    punteros NULL hacia izquierda y derecha */
Node newNode(u32 key) {
    Node node = malloc(sizeof(struct Node_t));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // El nuevo nodo es inicialmente agregado como una hoja
    return (node);
}

// Función utilitaria para rotar un subarbol hacia la derecha
Node rightRotate(Node y) {
    Node x = y->left;
    Node T2 = x->right;

    // Realizar la rotación
    x->right = y;
    y->left = T2;

    // Actualizar alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Devolver nueva raíz
    return x;
}

// Función utilitaria para rotar un subarbol hacia la izquierda
Node leftRotate(Node x) {
    Node y = x->right;
    Node T2 = y->left;

    // Realizar rotación
    y->left = x;
    x->right = T2;

    // Actualizar alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Devolver nueva raíz
    return y;
}

// Obtener el factor de balance de un nodo N
u32 getBalance(Node N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

/* Función recursiva para insertar un nuevo Nodo en un subarbol "G", manteniendo
    el balance del mismo. Devuelve la nueva raíz del subarbol.*/
Node insert(Node node, u32 key, Grafo G, u32 *position, u32 *pos_v) {
    /* 1. Realizar la inserción normal BST */
    if (node == NULL) {
        Node new_node = newNode(key);
        vertice v = crear_vertice(key,(1));
        new_node->position = *position;
        v->posicion = *position;
        G->vertices[*position] = v;
        *pos_v = *position;
        *position += 1;
        return new_node;
    }
    if (key < node->key){
        node->left = insert(node->left, key, G, position, pos_v);
    }
    else if (key > node->key){
        node->right = insert(node->right, key, G, position, pos_v);
    }
    else{ /* Las llaves idénticas no están permitidas en un BST
                El nodo ya existe, por lo tanto ya existe en el arreglo */
        *pos_v = node->position;
        return node;
    }

    /* 2. Actualizar la altura de éste nodo ancestro */
    node->height = 1 + max(height(node->left), height(node->right));

    /* 3. Se obtiene el factor de balance de éste nodo ancestro
            para checkear si fue desbalanceado o no */
    int balance = getBalance(node);

    // Si fue desbalanceado, entonces existen 4 casos:

    // Caso Izquierda-Izquierda
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Caso Derecha-Derecha
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Caso Izquierda-Derecha
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso Derecha-Izquierda
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* Devuelve la nueva raíz del subarbol */
    return node;
}

// Elimina el árbol, liberando la memoria correspondiente al mismo
void deleteTree(Node avl) {
    if (avl != NULL) {
        deleteTree(avl->right);
        deleteTree(avl->left);
        free(avl);
        avl = NULL; // Evitar danling pointers
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