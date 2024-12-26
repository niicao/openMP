#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(){
    int n;
    scanf("%d", &n);

    int biggest = 0;
    int* arr = (int*)malloc(n * sizeof(int));

    #pragma omp parallel for reduction(max:biggest)
        for (int i = 0; i < n; i++){
            arr[i] = 1;
            if (i == n/2) arr[i] = n;
            if (arr[i] > biggest){
                biggest = arr[i];
            }
        }
    
    printf("%d\n", biggest);
    return 0;
}