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
    int *R_SEQ = malloc(sizeof(int) * NR);

    double start_time_seq = omp_get_wtime();

    for (int i=0 ; i<NR ; i++) {
        int sum_of_product = 0;
        for (int j=0 ; j<NF ; j++) {
            sum_of_product += A[i+j] * FF[j];
        }
        R_SEQ[i] = sum_of_product;
    }

    double end_time_seq = omp_get_wtime();

    double computation_time_seq = end_time_seq - start_time_seq;
    printf("Sequential Computation Time: %f seconds\n", end_time_seq - start_time_seq);

    int *R_PAR = malloc(sizeof(int) * NR);

    double start_time_par = omp_get_wtime();

    omp_set_num_threads(8);
    #pragma omp parallel for
    for (int i=0 ; i<NR ; i++) {
        int sum_of_product = 0;
        for (int j=0 ; j<NF ; j++) {
            sum_of_product += A[i+j] * FF[j];
        }
        R_PAR[i] = sum_of_product;
    }

    double end_time_par = omp_get_wtime();

    double computation_time_par = end_time_par - start_time_par;
    printf("Parallel Computation Time: %f seconds\n", end_time_par - start_time_par);

    printf("Speed-up: %f\n", computation_time_seq / computation_time_par);

    // ---- free memory ----
    free(F);
    free(A);
    free(FF);
    free(R_SEQ);
    free(R_PAR);
    // ---- end free ----

    return 0;
}