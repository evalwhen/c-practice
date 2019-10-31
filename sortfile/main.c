#include "../bitmap/bitmap.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

int main() {
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

    for (i = 0; i < N; i++) {
        if (test(i) != 0 ) {
            fprintf(f2, "%d\n", i);
        }
    }

    free(line);
    fclose(f);
    return 0;
}
