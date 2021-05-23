#include "UnleashHell.h"
#include "auxiliares.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define reset "\e[0m"

void RandomizarPermutaciones(u32* perm, u32 len, u32 R){
    // Inicializa los indices en [0 ... len-1]
    for (u32 i = 0u; i < len; ++i){
        perm[i] = i;
    }
    srand(R); 
    // Algoritmo de Fisher-Yates limitado al R dado.
   int j;
    for (u32 i = len - 1; i > 0; --i){
        // Elige un índice aleatorio de 0 a i.
        j = rand() % (i+1);
        swap(&perm[i], &perm[j]);
    }
}

void MayorMenor(u32* perm, u32 len){
    for (u32 k = 0; k < len; ++k){
        perm[k] = len-k-1;
    }
}

int main(int argc, char *argv[]) {
    clock_t begin = clock();
    // Inciso 1
    if(argc != 7){
        fprintf(stderr, BRED "ERROR: Formato inválido\n");
        fprintf(stderr,"Cerrando el programa...\n"reset);
        exit(1);
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int c = atoi(argv[3]);
    int d = atoi(argv[4]);
    int e = atoi(argv[5]);
    int f = atoi(argv[6]);

    Grafo G = ConstruccionDelGrafo();
    if(G == NULL){
        fprintf(stderr, BRED "ERROR: No se pudo cargar el grafo\n");
        fprintf(stderr,"Cerrando el programa...\n"reset);
        exit(1);
    }

    // Inciso 2
    printf(BMAG "Número de vértices para G: %u\n", NumeroDeVertices(G));
    printf("Número de lados para G: %u\n", NumeroDeLados(G));
    printf("Delta de G: %u\n\n", Delta(G));

    // Inciso 3
    if(Bipartito(G)){
        fprintf(stderr, BGRN "El grafo G es bipartito\n");
        fprintf(stderr, BRED "Cerrando el programa...\n"reset);
        DestruccionDelGrafo(G);
        exit(0);
    }
    printf(BGRN "El grafo G NO es bipartito\n\n");

    // Inciso 4-5
    char check = 0;
    OrdenNatural(G);
    u32 color = Greedy(G);
    u32 superGreedyto = 1+b+3*c*d; //Contador de llamadas a Greedy
    u32 mejor_color_G = color;
    printf(BBLU "El coloreo fue de %u colores para el orden natural\n\n"reset, color);
    int mejor_semilla = f;
    for (int i = 0; i < a; ++i) {
        check = AleatorizarVertices(G, f+i);
        if (check) {
            fprintf(stderr, BRED "ERROR: No se pudo aleatorizar\n"reset);
            break;
        }
        color = Greedy(G);
        superGreedyto++;
        printf("El coloreo fue de %u por aleatorización de colores\n", color);
        if(color < mejor_color_G){
            mejor_color_G = color;
            mejor_semilla = f + i;
        }
    }
    // Si la mejor semilla no fue la última, vuelvo a ordenar
    if(mejor_semilla != (f + a - 1)) {
        check = AleatorizarVertices(G, mejor_semilla);
        if (check) {
            fprintf(stderr, BRED "ERROR: No se pudo aleatorizar\n"reset);
        }
        mejor_color_G = Greedy(G);
        superGreedyto++;
    }
    printf(BMAG "\nEl mejor coloreo fue en %u colores para la semilla %u\n\n"reset, mejor_color_G, mejor_semilla);
    
    // Inciso 6
    u32 *perm = calloc(mejor_color_G, sizeof(u32));
    for (int i = 0; i < b; ++i) {
        RandomizarPermutaciones(perm, mejor_color_G, f+i);
        check = OrdenPorBloqueDeColores(G, perm);
        if (!check) {
            fprintf(stderr, BRED "ERROR: Perm NO es una permutación, no se pudo ordenar\n"reset);
        }
        mejor_color_G = Greedy(G);
        printf("El coloreo fue de %u por bloques de colores\n", mejor_color_G);
    }
    printf("El coloreo fue de %u para %u reordenes por bloques de colores\n", mejor_color_G, b);
    
    // Inciso 7
    printf("\n");
    u32 mejor_color_H = mejor_color_G;
    u32 mejor_color_W = mejor_color_G;
    u32 SuperColor = 0;
    for (int i = 0; i < c; ++i) {
        // NOTE: capaz habría que hacer un realloc o volver a crear perm
        Grafo H = CopiarGrafo(G);
        Grafo W = CopiarGrafo(G);
        for (int j = 0; j < d; ++j) {
            // Estrategia A:
            RandomizarPermutaciones(perm, mejor_color_G, f+j);
            check = OrdenPorBloqueDeColores(G, perm);
            if (!check) {
                fprintf(stderr, BRED "ERROR: Perm NO es una permutación, no se pudo ordenar\n"reset);
            }
            mejor_color_G = Greedy(G);     

            // Estrategia B:
            MayorMenor(perm,mejor_color_H);
            check = OrdenPorBloqueDeColores(H, perm);
            if (!check) {
                fprintf(stderr, BRED "ERROR: Perm NO es una permutación, no se pudo ordenar\n"reset);
            }
            mejor_color_H = Greedy(H);

            // Estrategia C:
            u32 idx_rand = 0;

            if (mejor_color_H != mejor_color_W) {
                MayorMenor(perm,mejor_color_H);
            }

            for (u32 k = 0; k < mejor_color_W; ++k) {
                idx_rand = rand() % e;
                if (idx_rand == 0) {
                    swap(&perm[k], &perm[rand() % mejor_color_W]);
                }
            }
            check = OrdenPorBloqueDeColores(W, perm);
            if (!check) {
                fprintf(stderr, BRED "ERROR: Perm NO es una permutación, no se pudo ordenar\n"reset);
            }
            mejor_color_W = Greedy(W);
            
            printf("El coloreo obtenido fue de G: %u, H: %u, W: %u colores\n", mejor_color_G, mejor_color_H, mejor_color_W);
        }
        printf(BMAG"\n★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★\n\n"reset);
        // Dejamos el grafo con el mejor coloreo en G, descartando los otros
        SuperColor = min(min(mejor_color_G, mejor_color_H), mejor_color_W);
        if (SuperColor == mejor_color_H) {
            DestruccionDelGrafo(G);
            G = CopiarGrafo(H);
            mejor_color_G = mejor_color_H;
        }
        else if (SuperColor == mejor_color_W) {
            DestruccionDelGrafo(G);
            G = CopiarGrafo(W);
            mejor_color_G = mejor_color_W;
        }
        DestruccionDelGrafo(H);
        DestruccionDelGrafo(W);
        mejor_color_H = mejor_color_G;
        mejor_color_W = mejor_color_G;
    }
    
    // Inciso 8
    printf(BMAG"\nEl último coloreo obtenido fue de %u colores\n", mejor_color_G);
    printf("Se realizaron %u coloreos con Greedy\n", superGreedyto);

    free(perm);
    DestruccionDelGrafo(G);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("El tiempo de corrida del programa fue de: %fs\n"reset, time_spent);
    return 0;
}