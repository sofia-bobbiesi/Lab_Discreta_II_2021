#include "RomaVictor.h"
#include <stdio.h>

int main() {
    Grafo graph = ConstruccionDelGrafo();
    imprimir_grafo(graph);
    DestruccionDelGrafo(graph);
    return 0;
}