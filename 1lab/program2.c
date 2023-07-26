#include <stdio.h>

double ascending_recursion(int i, double x, double *sum) {
    double temp;
    temp = (i == 1) ?
        x :
        -ascending_recursion(i-1, x, sum)
            * x * x * ( 2 * i - 1) / ( 2 * i + 1 );
    *sum+=temp;
    return temp;
}

int main() {
    double sum = 0;
    double x = 0.5;
    int n;
    printf("Enter number :\n");
    scanf("%d", &n);
    ascending_recursion(n, x, &sum);
    printf("Result (2 program) - %f\n", sum);
    return 0;
}

