#include "../bitmap/bitmap.h"
#include "../bitmap/memory.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define MAX_N 10000000
/* 如果 bitmap 所能表示的最大整数小于 MAX_N,
   可以通过多趟（pass) 来排序，比如 bitmap 能
   表示的最大整数是100, 但需要排序的最大整数是1000,
   那么可以 10 躺来完成排序 0 - 99, 100 - 199 ...;

   实际上就是空间换时间。
 */

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    FILE* f = fopen("rand_no_dup_int.txt", "r+");
    FILE* f2 = fopen("sort_rand_no_dup_int.txt", "w");

    uint32_t i, total = 0;
    uint32_t npass = MAX_N / BITMAP_MAX_SIZE;

    report_current_mem_usage();
    for (i = 0; i < npass; i++ ) {
        char *line = NULL;
        size_t len = 0;

        while(getline(&line, &len, f) != -1) {
            uint32_t v = strtoimax(line, NULL, 10);
            if (v >= (i * BITMAP_MAX_SIZE) && v < ((i+1) * BITMAP_MAX_SIZE)) {
                v = v % BITMAP_MAX_SIZE;
                set(v);
                total++;
            }
        }

        int j = 0;
        for (j = 0; j < BITMAP_MAX_SIZE; j++) {
            if (test(j) != 0 ) {
                fprintf(f2, "%d\n", (j + i * BITMAP_MAX_SIZE ));
                clr(j);
            }
        }
        free(line);
        rewind(f);
    }
    fclose(f);
    fclose(f2);

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("took %f seconds to execute \n", cpu_time_used);


    return 0;
}
