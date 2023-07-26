#include <stdio.h>

double descending_recursion(int i, double x, int max, double sum, double pre_sum) {
    double temp;
    temp = (i == 1) ?
           x :
           - pre_sum * x * x * ( 2 * i - 1 ) / ( 2 * i + 1 );
    sum+=temp;
    if (i == max) return sum;
    return descending_recursion(i + 1, x, max, sum, temp);
}

int main() {
    int n;
    double x = 0.5;
    printf("Enter number :\n");
    scanf("%d", &n);
    double result = descending_recursion(1, x, n, 0, 0);
    printf("Result (first program) - %f\n", result);
    return 0;
}
