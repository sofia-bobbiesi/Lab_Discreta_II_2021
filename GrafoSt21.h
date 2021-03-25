#ifndef GRAFIST21_H
#define GRAFIST21_H

typedef unsigned int u32;
typedef struct _vertice_t *vertice;
typedef struct lado_t *vecinos;
struct GrafoSt{
	u32 n_vertices;
	u32 m_lados;
    u32 delta; //mayor grado del grafo ∆(G)
	vertice *vertice_array[];
};

struct lado_t {
    u32 peso_u2v;
    vertice *vecino_u;
};

struct _vertice_t {
	u32 nombre_real;
	u32 etiqueta;
	u32 grado;
    u32 color;
	vecinos *vecinos[];
};
/* 
    De esta forma guardamos solo una vez los
    vertices y los accedemos siempre con puntero 
*/


#endif
