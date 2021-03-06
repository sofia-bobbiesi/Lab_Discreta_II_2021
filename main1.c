#include "UnleashHell.h"
#include "auxiliares.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main1() {
    Grafo graph = ConstruccionDelGrafo();

    // Greedy(graph);

    // u32 perm[4] = {3,2,0,1};
    // OrdenPorBloqueDeColores(graph,perm);
    // imprimir_grafo(graph);
    char bip_check1 = Bipartito(graph);

    OrdenNatural(graph);
    u32 coloreo = NumeroDeVertices(graph);
    u32 mejor_coloreo = coloreo;
    for (int i = 0; i < 1000; i++){
        AleatorizarVertices(graph,i);
        coloreo = Greedy(graph);
        if (coloreo < mejor_coloreo){
            mejor_coloreo = coloreo;
        }
    }
    printf("El mejor coloreo con greedy fue de %u colores.\n",mejor_coloreo);

    char bip_check2 = Bipartito(graph);

    if (bip_check2 != bip_check1){
        printf("Hubo un error al hacer bipartito.");
    }
    else if (bip_check1 == 1 && bip_check2 == 1){
        printf("El grafo es bipartito.");
    }
    else if (bip_check1 == 0 && bip_check2 == 0){
        printf("El grafo no es bipartito.");
    }

    DestruccionDelGrafo(graph);
    return 0;
}