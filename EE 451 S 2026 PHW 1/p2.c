#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <omp.h>

#define h  800 
#define w  800
#define MAT_ITER 30

#define input_file  "input.raw"
#define output_file "output.raw"

int main(int argc, char** argv){
    int i;
    FILE *fp;

  	unsigned char *a = (unsigned char*) malloc (sizeof(unsigned char)*h*w);
    
	// the matrix is stored in a linear array in row major fashion
	if (!(fp=fopen(input_file, "rb"))) {
		printf("can not opern file\n");
		return 1;
	}
	fread(a, sizeof(unsigned char), w*h, fp);
	fclose(fp);
   
    // measure the start time here
    double start_time = omp_get_wtime();
    //  Your code goes here
    float means[4] = {0.0f, 85.0f, 170.0f, 255.0f};
    long sums[4];
    int counts[4];

    int num_pixels = w * h;

    for (int iter = 0; iter < MAT_ITER; iter++) {
        
        for (int k = 0; k < 4; k++) {
            sums[k] = 0;
            counts[k] = 0;
        }

        for (int j = 0; j < num_pixels; j++) {
            unsigned char pixel = a[j];
            float min_dist = FLT_MAX;
            int closest_cluster = -1;

            for (int k = 0; k < 4; k++) {
                float dist = fabsf(pixel - means[k]);
                if (dist < min_dist) {
                    min_dist = dist;
                    closest_cluster = k;
                }
            }
            sums[closest_cluster] += pixel;
            counts[closest_cluster]++;
        }

        for (int k = 0; k < 4; k++) {
            if (counts[k] > 0) {
                means[k] = (float)sums[k] / counts[k];
            }
        }
    }

    for (int j = 0; j < num_pixels; j++) {
        unsigned char pixel = a[j];
        float min_dist = FLT_MAX;
        int closest_cluster;

        for (int k = 0; k < 4; k++) {
            float dist = fabsf(pixel - means[k]);
            if (dist < min_dist) {
                min_dist = dist;
                closest_cluster = k;
            }
        }
        a[j] = (unsigned char)means[closest_cluster];
    }		
	
		
	//
	
	// measure the end time here
    double end_time = omp_get_wtime();
    
    // print out the execution time here
    printf("Time Execution: %f seconds\n", end_time - start_time);		
	
	if (!(fp=fopen(output_file,"wb"))) {
		printf("can not opern file\n");
		return 1;
	}	
	fwrite(a, sizeof(unsigned char),w*h, fp);
    fclose(fp);
    
    return 0;
}