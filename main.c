#include "RomaVictor.h"
#include <stdio.h>

int main() {
    Grafo graph = ConstruccionDelGrafo();
    printf("Bipartito: %u (0 si no es bipartito, 1 si lo es)\n", Bipartito(graph));
    DestruccionDelGrafo(graph);
    return 0;
}