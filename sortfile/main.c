#include "../bitmap/bitmap.h"
#include "../bitmap/memory.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    FILE* f = fopen("rand_no_dup_int.txt", "r+");
    FILE* f2 = fopen("sort_rand_no_dup_int.txt", "w");


    uint32_t i, total = 0;
    char *line = NULL;
    size_t len = 0;

    while(getline(&line, &len, f) != -1) {
        int i = strtoimax(line, NULL, 10);
        set(i);
        total++;
    }

    long size, rss;

    get_memory_usage_kb(&rss, &size);
    fprintf(stdout, "Current memory usage: VmRSS = %ld, VmSize = %ld\n", rss, size);

    for (i = 0; i < N; i++) {
        if (test(i) != 0 ) {
            fprintf(f2, "%d\n", i);
        }
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("took %f seconds to execute \n", cpu_time_used);


    long size1, rss1;
    get_memory_usage_kb(&rss1, &size1);
    fprintf(stdout, "Current memory usage: VmRSS = %ld, VmSize = %ld\n", rss1, size1);


    free(line);
    fclose(f);
    return 0;
}
