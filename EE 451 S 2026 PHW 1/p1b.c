#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MIN(a,b) (((a)<(b))?(a):(b))

int main(int argc, char *argv[]) {
        // Instruction 2: Parse block size b from command line
        if (argc < 2) {
            printf("Error: ./p1b {block_size}\n");
            return 1;
        }
        int b = atoi(argv[1]);

        int i, j, k;
		struct timespec start, stop; 
		double time;
		int n = 2048; // matrix size is n*n
		
		double **A = (double**) malloc (sizeof(double*)*n);
		double **B = (double**) malloc (sizeof(double*)*n);
		double **C = (double**) malloc (sizeof(double*)*n);
		for (i=0; i<n; i++) {
			A[i] = (double*) malloc(sizeof(double)*n);
			B[i] = (double*) malloc(sizeof(double)*n);
			C[i] = (double*) malloc(sizeof(double)*n);
		}
		
		for (i=0; i<n; i++){
			for(j=0; j< n; j++){
				A[i][j]=i;
				B[i][j]=i+j;
				C[i][j]=0;			
			}
		}
				
		if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
		
		// Your code goes here //
		// Matrix C = Matrix A * Matrix B //	
		//*******************************//
        int ii, jj, kk;
        for (ii = 0; ii < n; ii += b) {
            for (jj = 0; jj < n; jj += b) {
                for (kk = 0; kk < n; kk += b) {
                    for (i = ii; i < ii + b; i++) {
                        for (j = jj; j < jj + b; j++) {
                            double sum = 0;
                            for (k = kk; k < kk + b; k++) {
                                sum += A[i][k] * B[k][j];
                            }
                            C[i][j] += sum;
                        }
                    }
                }
            }
        }		
		//*******************************//
		
		if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}		
		time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
		
		//printf("Number of FLOPs = %lu, Execution time = %f sec,\n%lf MFLOPs per sec\n", 2*n*n*n, time, 1/time/1e6*2*n*n*n);		
		printf("Number of FLOPs = %lu\n", (unsigned long)(2.0*n*n*n));
		printf("Execution time = %.0f ns\n", time * 1e9);
		printf("Execution time = %f sec\n", time);
		printf("%.0f FLOPs per sec\n", (2.0 * n * n * n) / time);
		printf("%.4f MFLOPs per sec\n", ((2.0 * n * n * n) / time) / 1e6);		
		printf("C[100][100]=%f\n", C[100][100]);
		

		// release memory
		for (i=0; i<n; i++) {
			free(A[i]);
			free(B[i]);
			free(C[i]);
		}
		free(A);
		free(B);
		free(C);
		return 0;
}
