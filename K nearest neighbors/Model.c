#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float pol(float x1, float x2, float y1, float y2){
    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

void minimum(float *min, float *A, int index, int *index_data){
    *min = A[0];
    int i, index_r = 0;
    for(i=1; i<index; i++){
        if(*min > A[i]){
            *min = A[i];
            index_r = i;
        }
    }
    *index_data = index_r; 
}

int main(){
    float data[6][2] = {{1.4, 0.2}, {1.4, 0.2}, {1.3,0.2}, {4.7,1.4}, {4.5,1.5}, {4.9,1.5}};
    char *A[6] = {"Setosa", "Setosa", "Setosa", "Versicolor", "Versicolor", "Versicolor"};
    float target[1][2] = {{4.8, 1.4}};
    int size = sizeof(data)/sizeof(data[0]);

    float *r = (float*)malloc(size*sizeof(float)); 
    int i;

    for(i=0; i<6; i++){
       r[i] = pol(data[i][0], target[0][0], data[i][1], target[0][1]);
       printf("data[%d] = %.2f\n", i, r[i]);
    }

    float min = 0.0;
    int index_data = 0;

    minimum(&min, r, size, &index_data);
    printf("\nmin = %.2f @index = %d\n", min, index_data);
    printf("Result is %s\n", A[index_data]);

    return 0;
}