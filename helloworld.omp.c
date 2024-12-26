#include <stdio.h>
#include <omp.h>

int main() {
    int num_t;
    scanf("%d", &num_t);
    omp_set_dynamic(0);
    omp_set_num_threads(num_t);

    #pragma omp parallel 
    {
        printf("Hello, World!\n");
    }
}