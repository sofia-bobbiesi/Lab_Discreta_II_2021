#ifndef GRAFIST21_H
#define GRAFIST21_H

typedef unsigned int u32;
typedef struct _vertice_t *vertice;
typedef struct lado_t *vecinos;

struct GrafoSt{
	u32 n_vertices;
	u32 m_lados;
    u32 delta; //mayor grado del grafo ∆(G)
	vertice *vertices;
};

/* 
    Permite una definicion circular donde
    cada vecino es un vertice en si mismo.
*/ 
struct lado_t {
    u32 peso_u2v;
    vertice vertice_j;
};

/* 
    De esta forma guardamos solo una vez los
    vertices y los accedemos siempre con puntero 
*/
struct _vertice_t {
	u32 nombre_real;
	u32 grado; //numero de vecinos
    u32 color;
	vecinos *vecinos;
};

#endif
