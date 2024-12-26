#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int main(){
    int n;

    scanf("%d", &n);
    int sum = 0;
    omp_set_dynamic(0);
    omp_set_num_threads(10);

    #pragma omp parallel for reduction(+:sum)
        for (int i = 1; i <= n; i++){
            int div_sum = 0;
            for (int j = 1; j <= i/2; j++){
                if (i % j == 0){
                    div_sum += j;
                }
            }
            if (div_sum == i){
                sum += i;
            }
        }

    printf("%d\n", sum);
    


    return 0;
}