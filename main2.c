#include "UnleashHell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main2() {
    Grafo grafo = ConstruccionDelGrafo();
    Grafo grafo_copia = CopiarGrafo(grafo);

    for (int i = 0; i < 10; i++){ 
        u32 greedy_original = Greedy(grafo);

        printf("Greedy Original: %u", greedy_original);
        u32 greedy_copia = Greedy(grafo_copia);
        printf("Greedy Copia: %u", greedy_copia);

        AleatorizarVertices(grafo, i);
        AleatorizarVertices(grafo_copia, i);
        
    }
    DestruccionDelGrafo(grafo_copia);
    DestruccionDelGrafo(grafo);
    return 0;
}