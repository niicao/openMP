#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(){
    int seed;
    int n;
    scanf("%d %d", &n, &seed);

    long long int arr[n];
    srand(seed);

    for (int i = 0; i < n; i++){
        arr[i] = rand() % 10;
    }

    long long int sum = 0;

    #pragma omp parallel for reduction (+:sum)
    for(int i = 0; i < n; i++){
        sum += arr[i];
    }
    
    printf("%lld\n", sum);
    // return 0;


    
}