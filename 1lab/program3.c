#include <stdio.h>

double descending_recursion(double x, int i, int max, double pre_sum) {
    double sum = - pre_sum * x * x * (2 * i - 1)/ ( 2 * i + 1);

    if (i == max) return sum;
    return sum + descending_recursion(x, i + 1, max, sum);
}

double ascending_recursion(double x, int i, int max) {
    double sum = x;
    return sum + descending_recursion(x, i + 1, max, sum);
}

int main() {
    double x = 0.5;
    int n;
    printf("Enter number :\n");
    scanf("%d", &n);
    printf("Result (3 programm) -  %f\n", ascending_recursion(x, 1, n));
    return 0;
}
