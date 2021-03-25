#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Linear_Regression{
    float a;
    float b;
};

float sum(float *x, int index){
    float sum = 0;
    int i;
    for(i=0; i<index; i++){
        sum += x[i];
    }
    return sum;
}

float sum_squared(float *x, int index){
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

float TSS(float *y, float average, int index){
    float tss = 0.0;
    int i;
    for(i=0; i<index; i++){
        tss += ((y[i] - average)*(y[i] - average));
    }
    return tss;
}

float RSS(float *x, float *y, float a, float b, int index){
    float rss = 0.0;
    int i;
    for(i=0; i<index; i++){
        rss += ((y[i] - (a*x[i]+b))*(y[i] - (a*x[i]+b)));
    }
    return rss;
}

float RSS_new(float *x, float *y, float a, float initial, int index){
    float sum = 0.0;
    int i;
    for(i=0; i<index; i++){
        sum += -2*((-a*x[i]) - initial + y[i]);
    }
    return sum;
}

float predict(float a, float b, float x){
    return ((a*x) + b);
}

int main(){
    int n = 0, i;
    printf("input_n: ");
    scanf("%d", &n);
    printf("\n");

    float* x = (float *)malloc(n*sizeof(float));
    float* y = (float *)malloc(n*sizeof(float));

    printf("input_x: ");
    for(i=0; i<n; i++){
        scanf("%f", &x[i]);
    }

    printf("input_y: ");
    for(i=0; i<n; i++){
        scanf("%f", &y[i]);
    }
    
    printf("\n");

    float sum_x = sum(x, n), sum_y = sum(y, n);
    float sum_XY = sum_xy(x, y, n);
    float sum_squared_x = sum_squared(x, n);

    struct Linear_Regression Model;

    Model.a = ((n*sum_XY)-(sum_x*sum_y))/((n*sum_squared_x)-(pow(sum_x, 2)));
    Model.b = ((sum_y*sum_squared_x)-(sum_x*sum_XY))/((n*sum_squared_x)-(pow(sum_x, 2)));

    printf("Before Optimize\n");
    printf("Your model: %.4fx + %.4f\n", Model.a, Model.b);

    float y_bar = sum_y/n;
    float rss = 0.0, tss = 0.0;
    float r_squared = 0.0;
    float alpha = Model.a, beta = Model.b;

    rss = RSS(x, y, alpha, beta, n);
    tss = TSS(y, y_bar, n);
    r_squared = 1-(rss/tss);

    printf("R_squared: %.4f\n\n", r_squared);

    //Let's Optimize with Gradient Descent
    printf("Optimize!!!\n");

    float old = 0.0, new = 0.0, step = 0.0 ,factor = 0.1;
    float result = 0.0;

    do{
        result = RSS_new(x, y, Model.a, new, n);
        step = result*factor;
        new = old - step;
        old = new;
    }while(-1*step > 1.0e-6);

    //new_intercept
    Model.b = old;
    printf("Your model: %.4fx + %.4f\n", Model.a, Model.b);

    alpha = Model.a, beta = Model.b;
    rss = RSS(x, y, alpha, beta, n);
    tss = TSS(y, y_bar, n);
    r_squared = 1-(rss/tss);

    printf("R_squared: %.4f\n\n", r_squared);

    free(x);
    free(y);

    return 0;
}