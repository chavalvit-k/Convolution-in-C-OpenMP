#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(){
    // ---- input and malloc A, F ----
    int NA, NF;
    scanf("%d %d", &NA, &NF);
    int *A = malloc(sizeof(int) * NA);
    int *F = malloc(sizeof(int) * NF);

    for(int i = 0; i < NA; i++){
        scanf("%d", &A[i]);
    }
    for(int i = 0; i < NF; i++){
        scanf("%d", &F[i]);
    }
    // ---- end input and malloc----

    // implement here
    int *FF = malloc(sizeof(int) * NF);

    for (int i=0 ; i<NF ; i++) {
        FF[i] = F[NF-i-1];
    }

    int NR = NA - NF + 1;
    int *R = malloc(sizeof(int) * NR);

    double start_time = omp_get_wtime();

    #pragma omp parallel for
    for (int i=0 ; i<NR ; i++) {
        int sum_of_product = 0;
        for (int j=0 ; j<NF ; j++) {
            sum_of_product += A[i+j] * FF[j];
        }
        R[i] = sum_of_product;
    }

    double end_time = omp_get_wtime();

    for (int i=0 ; i<NR ; i++) {
        printf("%d\n", R[i]);
    }

    printf("Computation Time: %f seconds\n", end_time - start_time);
    // ---- free memory ----
    free(F);
    free(A);
    free(FF);
    free(R); 
    // ---- end free ----

    return 0;
}