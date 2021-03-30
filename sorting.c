#include <stdio.h>
#include "sorting.h"


u32 get_max (vertice *a, u32 n){
   u32 max = a[0]->nombre_real;
   for (u32 i = 1; i < n; i++)
      if (a[i]->nombre_real > max)
         max = a[i]->nombre_real;
   return max;
}
void radix_sort (Grafo G, u32 n){
   u32 bucket[10][10], bucket_cnt[10];
   u32 i, j, k, r, NOP = 0, divisor = 1, lar, pass;
   lar = get_max (G->vertices, n); //VO DECI?
   while (lar > 0){
      NOP++;
      lar /= 10;
   }
   for (pass = 0; pass < NOP; pass++){
      for (i = 0; i < 10; i++){
         bucket_cnt[i] = 0;
      }
      for (i = 0; i < n; i++){
         r = (G->vertices[i]->nombre_real / divisor) % 10;
         bucket[r][bucket_cnt[r]] = G->vertices[i]->nombre_real;
         bucket_cnt[r] += 1;
      }
      i = 0;
      for (k = 0; k < 10; k++){
         for (j = 0; j < bucket_cnt[k]; j++){
            G->vertices[i]->nombre_real = bucket[k][j];
            i++;
         }
      }
      divisor *= 10;
     printf  ("After pass %d : ", pass + 1);
      for (i = 0; i < n; i++)
         printf ("%d ", G->vertices[i]->nombre_real);
      printf ("\n");
   }
}

void mostrar(vertice *a, u32 n){
   printf ("Sorted items : ");
   for (u32 i = 0; i < n; i++)
      printf ("%d ", a[i]->nombre_real);
   printf ("\n");
}