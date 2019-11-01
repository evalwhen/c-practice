#include "../bitmap/bitmap.h"
#include "../bitmap/memory.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_N 10000000
#define BITMAP_MAX 100
// 使用小容量的 bitmap 完成磁盘文件内容排序
int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    FILE* f2 = fopen("sort_rand_no_dup_int.txt", "w");

    uint32_t i, total = 0;
    int npass = MAX_N / BITMAP_MAX;

    for (i = 0; i < npass; i++ ) {
        FILE* f = fopen("rand_no_dup_int.txt", "r+");
        char *line = NULL;
        size_t len = 0;

        while(getline(&line, &len, f) != -1) {
            int v = strtoimax(line, NULL, 10);
            if (v >= (i * BITMAP_MAX) && v < ((i+1) * BITMAP_MAX)) {
                v = v % BITMAP_MAX;
                set(v);
                total++;
            }
        }

        int j = 0;
        for (j = 0; j < BITMAP_MAX; j++) {
            if (test(j) != 0 ) {
                fprintf(f2, "%d\n", (j + i * BITMAP_MAX ));
                clr(j);
//                exit(0);
            }
        }

        free(line);
        fclose(f);
    }
    fclose(f2);

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("took %f seconds to execute \n", cpu_time_used);


    return 0;
}