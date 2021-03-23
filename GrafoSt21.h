#ifndef GRAFIST21_H
#define GRAFIST21_H

typedef unsigned int u32;
typedef struct _vertice_t *vertice;

struct GrafoSt{
	u32 n_vertices;
	u32 m_lados;
	u32 color;
    u32 delta; //mayor grado del grafo ∆(G)
	vertice *vertice_array[];
};

struct _vertice_t {
	u32 nombre_real;
	u32 etiqueta;
	u32 grado;
    u32 color;
	vertice *vecinos[];
};

/* De esta forma guardamos solo una vez los
vertices y los accedemos siempre con puntero */

typedef struct lado_t {
   u32 vertice_u;
   u32 vertice_v;
};


#endif
