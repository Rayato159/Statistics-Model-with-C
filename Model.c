#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float sum(float *x, int index){
    float sum = 0;
    int i;
    for(i=0; i<index; i++){
        sum += x[i];
    }
    return sum;
}

float sum_square(float *x, int index){
    float sum= 0;
    int i;
    for(i=0; i<index; i++){
        sum += pow(x[i], 2);
    }
    return sum;
}

float sum_xy(float *x, float *y, int index){
    float sum = 0;
    int i;
    for(i=0; i<index; i++){
        sum += x[i]*y[i];
    }
    return sum;
}

float predict(float a, float b, float x){
    return ((a*x) + b);
}

int main(){
    int n = 0, i;
    printf("input_n : ");
    scanf("%d", &n);
    printf("\n");

    float* x = (float *)malloc(n*sizeof(float));
    float* y = (float *)malloc(n*sizeof(float));

    printf("input_x : ");
    for(i=0; i<n; i++){
        scanf("%f", &x[i]);
    }

    printf("input_y : ");
    for(i=0; i<n; i++){
        scanf("%f", &y[i]);
    }
    
    printf("\n");

    float sum_x = sum(x, n), sum_y = sum(y, n);
    float sum_XY = sum_xy(x, y, n);
    float sum_square_x = sum_square(x, n);
    float a = 0.0000, b = 0.0000;

    a = ((sum_y*sum_square_x)-(sum_x*sum_XY))/((n*sum_square_x)-(pow(sum_x, 2)));
    b = ((n*sum_XY)-(sum_x*sum_y))/((n*sum_square_x)-(pow(sum_x, 2)));

    printf("Your model : y_hat = %.4fx + %.4f", a, b);

    float predict_x;

    printf("\n\nLet's predict!!!\n input_x : ");
    scanf("%f", &predict_x);
    printf("result : %.4f", predict(a, b, predict_x));

    return 0;
}