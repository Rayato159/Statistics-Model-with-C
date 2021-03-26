#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double func(double x){
    return sin(x);
}

double derivative(double (*f)(double), double x){
    const double h = 1.0e-6;
    return (f(x+h)-f(x-h))/(2*h);   //1st order central diff
}

int main(){
    double y = derivative(func, 5.0);
    printf("%.4f", y);
    return 0;
}