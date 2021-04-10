#include "RomaVictor.h"
#include <stdio.h>

int main() {
    Grafo graph = ConstruccionDelGrafo();
    //Grafo copito = CopiarGrafo(graph);
    FijarOrden(0, graph, 2);
    FijarOrden(1, graph, 1);
    FijarOrden(2, graph, 0);
    imprimir_grafo(graph);
    //FijarColor(50,2,copito);
    //imprimir_grafo(copito);
    printf("Orden vecino %u\n",OrdenVecino(0,1,graph));
    //printf("color vecino: %u\n",ColorVecino(0,3,copito));
    // DestruccionDelGrafo(copito);
    DestruccionDelGrafo(graph);
    return 0;
}