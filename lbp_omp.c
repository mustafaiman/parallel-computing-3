#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<omp.h>
#include<time.h>

#include "util.h"

#define NUM_PEOPLE 18
#define NUM_PICS_PER_PERSON 20
#define HISTOGRAM_INTERVAL 16
#define MAX_DECIMAL_VALUE 256
#define IMAGE_R 180
#define IMAGE_W 200

double distance(int *a, int *b, int size) {
    double distance = 0;
    
    for (int i=0; i<size; i++) {
        if (a[i] + b[i] != 0) {
            distance += ((double)(a[i] - b[i]))*(a[i]-b[i])/(a[i]+b[i])/2;
        }
    }
    return distance;
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

    for (int i=1; i<num_rows - 1; i++) {
        //printf("p:%d\n", omp_get_thread_num());
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

int main(int argc, char *argv[]) {
    
    clock_t seq_clk = clock();
    
    int numberOfTrainingPictures = atoi(argv[1]);
    
    int ***trainingSet = (int ***)malloc(sizeof(int **) * NUM_PEOPLE);
    
    for (int i=0; i<NUM_PEOPLE; i++) {
        trainingSet[i] = alloc_2d_matrix(numberOfTrainingPictures, MAX_DECIMAL_VALUE);
    }
    //trainingSet is a 3d matrix now (person x image x histogramIndex )
    
    double seq_time = clock() - seq_clk;
    
    double parallel_clk = omp_get_wtime();
    
    #pragma omp parallel
    {
        #pragma omp for
        for (int i=0; i<NUM_PEOPLE; i++) {
            char filename[256];
            for (int j=0; j<numberOfTrainingPictures; j++) {
                sprintf(filename, "images/%d.%d.txt", i+1, j+1);
                int **image = read_pgm_file(filename, IMAGE_R, IMAGE_R);
                create_histogram(trainingSet[i][j], image, IMAGE_R, IMAGE_W);
                free(image);
            }
        }
    }
    
    int correct_answers = 0;
    #pragma omp parallel
    {
        #pragma omp for reduction(+:correct_answers)
        for (int i=0; i<NUM_PEOPLE; i++) {
            for (int j=numberOfTrainingPictures; j<NUM_PICS_PER_PERSON; j++) {
                int *test_histogram = (int *)malloc(sizeof(int) * MAX_DECIMAL_VALUE);
                char filename[256];
                sprintf(filename, "images/%d.%d.txt", i+1, j+1);
                int **image = read_pgm_file(filename, IMAGE_R, IMAGE_R);
                create_histogram(test_histogram, image, IMAGE_R, IMAGE_W);
            
                int predicted = find_closest(trainingSet, NUM_PEOPLE, numberOfTrainingPictures, MAX_DECIMAL_VALUE, test_histogram) + 1;
            
                printf("%s %d %d\n", filename+7, predicted, i+1);
                if(i+1 == predicted) {
                    correct_answers++;
                }
            }
        }
    }
    printf("Accuracy: %d correct answers for %d tests\n", correct_answers, NUM_PEOPLE * (NUM_PICS_PER_PERSON - numberOfTrainingPictures));
    printf("Parallel time: %lf\n", omp_get_wtime() - parallel_clk);
    printf("Sequential time: %lf\n", seq_time/CLOCKS_PER_SEC);
    return 0;
}