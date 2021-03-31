#include "sorting.h"
#include <stdio.h>

u32 get_max(vertice *a, u32 n) {
    u32 max = a[0]->nombre_real;
    for (u32 i = 1; i < n; i++)
        if (a[i]->nombre_real > max)
            max = a[i]->nombre_real;
    return max;
}
void radix_sort(vertice *a, u32 n) {
    vertice bucket[256][256];
    u32 bucket_cnt[256];
    u32 i, j, k, r, NOP = 0, divisor = 1, lar, pass;
    lar = get_max(a, n);
    while (lar > 0) {
        NOP++;
        lar /= 10;
    }
    for (pass = 0; pass < NOP; pass++) {
        for (i = 0; i < 10; i++) {
            bucket_cnt[i] = 0;
        }
        for (i = 0; i < n; i++) {
            r = (a[i]->nombre_real / divisor) % 10;
            bucket[r][bucket_cnt[r]] = a[i]; 
            bucket_cnt[r] += 1;
        }
        i = 0;
        for (k = 0; k < 10; k++) {
            for (j = 0; j < bucket_cnt[k]; j++) {
                a[i] = bucket[k][j];
                i++;
            }
        }
        divisor *= 10;
    }
}