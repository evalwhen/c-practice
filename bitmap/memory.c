#include "memory.h"
#include <sys/time.h>
#include <sys/resource.h>

int get_memory_usage_kb(long* vmrss_kb, long* vmsize_kb) {

  FILE* proc_file = fopen("/proc/self/status", "r");

  int read_size = 8192;
  char buffer[read_size];

  fread(buffer, sizeof(char), read_size, proc_file);
  fclose(proc_file);

  char delim[] = "\n";
  char* line = strtok(buffer, delim);

  short found_vmsize = 0;
  short found_vmrss = 0;

  while (line != NULL && (found_vmrss == 0 || found_vmsize == 0)) {

    char* vmsize_ptr = strstr(line, "VmSize");

    if (vmsize_ptr != NULL) {
        sscanf(line, "%*s %ld", vmsize_kb);
        found_vmsize = 1;
    }

    char* vmrss_ptr = strstr(line, "VmRSS");

    if (vmrss_ptr != NULL) {
      // line 为什么指一行
      // 因为 strtok 使用了静态变量
        sscanf(line, "%*s %ld", vmrss_kb);
        found_vmrss = 1;
    }

    line = strtok(NULL, delim);
  }

  return (found_vmrss == 1 && found_vmsize == 1) ? 0 : 1;
}

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

void report_current_mem_usage(int id) {
    long vmsize, vmrss;
    get_memory_usage_kb(&vmrss, &vmsize);
    fprintf(stdout, "%2d: Current memory usage: VmRSS = %ld, VmSize = %ld\n", id, vmrss, vmsize);
}
