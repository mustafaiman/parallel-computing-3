#include<float.h>

#include "util.h"

int **alloc_2d_matrix(int r, int c)
{
    int ** a;
    int i; 
    a = (int **)malloc(sizeof(int *) * r);
    if (a == NULL) {
        perror("memory allocation failure");
        exit(0);
    } 
    for (i = 0; i < r; ++i) {
        a[i] = (int *)malloc(sizeof(int) * c);
        if (a[i] == NULL) {
            perror("memory allocation failure");
            exit(EXIT_FAILURE);
        }
    }
    return a;
}
 
void dealloc_2d_matrix(int **a, int r, int c)
{
    	int i;
   	for (i = 0; i < r; ++i)
        	free(a[i]);
    	free(a);
}

int **read_pgm_file(char * file_name, int h, int w)
{
	FILE * file;
    	int i,j, int_tmp;
    	int** data=alloc_2d_matrix(h,w);
    	
    	if ((file = fopen(file_name, "r+")) == NULL)
	{
	    printf("ERROR: file open failed\n");
	    return(NULL);
	}
	
	for (i = 0; i < (h); i++)
	{
            for (j = 0; j < (w); j++)
	    {
		fscanf(file,"%d", &int_tmp);
		data[i][j] = int_tmp;	
	    }
        }    
    fclose(file);
    return data;
}

int find_closest(int ***training_set, int num_persons, int num_training, int size, int *test_image) {
    double min_distance = DBL_MAX;
    double current_distance;
    int person=0;
    for (int i=0; i<num_persons; i++) {
        for (int j=0; j<num_training; j++) {
            current_distance = distance(training_set[i][j], test_image, size);
            if (current_distance < min_distance) {
                min_distance = current_distance;
                person = i;
            }
        }
    }
    return person;
}

int neighbor_r[] = {
    -1, -1, -1, 0, 0, 1, 1, 1
};

int neighbor_c[] = {
    -1, 0, 1, -1, 1, -1, 0, 1
};

void create_histogram(int *hist, int **img, int num_rows, int num_cols) {
    memset(hist, 0, sizeof(int) * (1<<NUM_NEIGHBORS));
    for (int i=1; i+1<num_rows; i++) {
        for (int j=1; j+1<num_cols; j++) {
            int value = 0;
            for (int k = 0; k< NUM_NEIGHBORS; k++) {
                if (img[i][j] < img[i + neighbor_r[k]][j + neighbor_c[k]]) {
                    value = (value << 1) + 1;
                } else {
                    value = (value << 1) + 0;
                }
            }
            hist[value] += 1;
        }
    }
}

double distance(int *a, int *b, int size) {
    double distance = 0;
    
    for (int i=0; i<size; i++) {
        if (a[i] + b[i] != 0) {
            distance += ((double)(a[i] - b[i]))*(a[i]-b[i])/(a[i]+b[i])/2;
        }
    }
    return distance;
}