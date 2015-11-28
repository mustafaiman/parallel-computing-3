#include<stdio.h>
#include<stdlib.h>

#include "util.h"

#define NUM_PEOPLE 18
#define NUM_PICS_PER_PERSON 20
#define HISTOGRAM_INTERVAL 16
#define MAX_DECIMAL_VALUE 256
#define DATA_FOLDER images
#define IMAGE_R 180
#define IMAGE_W 200

int main(int argc, char *argv[]) {
    
    int numberOfTrainingPictures = atoi(argv[1]);
    
    int ***trainingSet = (int ***)malloc(sizeof(int **) * NUM_PEOPLE);
    
    for (int i=0; i<NUM_PEOPLE; i++) {
        trainingSet[i] = alloc_2d_matrix(numberOfTrainingPictures, MAX_DECIMAL_VALUE);
    }
    //trainingSet is a 3d matrix now (person x image x histogramIndex )
    
    int **image;
    char filename[256];
    for (int i=0; i<NUM_PEOPLE; i++) {
        for (int j=0; j<numberOfTrainingPictures; j++) {
            sprintf(filename, "DATA_FOLDER/%d.%d.txt", i+1, j+1);
            image = read_pgm_file(filename, IMAGE_R, IMAGE_R);
            create_histogram(trainingSet[i][j], image, IMAGE_R, IMAGE_W);
        }
    }
}