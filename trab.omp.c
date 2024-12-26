#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>


int main(){
    int img_size;
    int filter_size;
    int random_seed;

    scanf("%d %d %d", &img_size, &filter_size, &random_seed);

    int** img = (int**) malloc(img_size * sizeof(int*));
    for (int i = 0; i < img_size; i++){
        img[i] = (int*) malloc(img_size * sizeof(int));
    }

    int** img_res = (int**) malloc(img_size * sizeof(int*));
    for (int i = 0; i < img_size; i++){
        img_res[i] = (int*) malloc(img_size * sizeof(int));
    }

    float** filter = (float**) malloc(filter_size * sizeof(float*));
    for (int i = 0; i < filter_size; i++){
        filter[i] = (float*) malloc(filter_size * sizeof(float));
    }


    srand(random_seed);
    for (int i = 0; i < img_size; i++){
        for (int j = 0; j < img_size; j++){
            img[i][j] = rand() % 256;
        }
    }

    for (int i = 0; i < filter_size; i++){
        for (int j = 0; j < filter_size; j++){
            filter[i][j] = (float)(rand()%10)/10;
        }
    }

    int i, j, k, l;

    omp_set_nested(1);

    #pragma omp parallel for collapse(2) private(i, j, k, l)
    for (i = 0; i < img_size; i++){
        for (j = 0; j < img_size; j++){
            float sum = 0;
            for ( k = 0; k < filter_size; k++){
                for (l = 0; l < filter_size; l++){
                    int img_i = i - filter_size/2 + k;
                    int img_j = j - filter_size/2 + l;
                    if (img_i >= 0 && img_i < img_size && img_j >= 0 && img_j < img_size){
                        sum += img[img_i][img_j] * filter[k][l];
                    }
                }
            }
            // printf("%f\n", sum);
            img_res[i][j] = fmin((int)sum, 255);
        }
    }

    int min_val = 255;
    int max_val = 0;
    #pragma omp parallel for reduction(min: min_val) reduction(max: max_val) collapse(2)
    for(int i = 0; i < img_size; i++){
        for(int j = 0; j < img_size; j++){
            if(img_res[i][j] < min_val){
                min_val = img_res[i][j];
            }
            if(img_res[i][j] > max_val){
                max_val = img_res[i][j];
            }
        }
    }

    printf("%d %d\n", max_val, min_val);



    for(int i = 0; i < img_size; i++){
        free(img[i]);
        free(img_res[i]);
    }
    free(img);
    free(img_res);

    for(int i = 0; i < filter_size; i++){
        free(filter[i]);
    }
    free(filter);

    return 0;
}