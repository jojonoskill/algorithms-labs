#include <stdio.h>

double cycle(double x, int n) {
    double t,res;
    t=x;
    res=t;
    for (int i = 2; i <= n; i++) {
        t = -t * x * x * (2 * i - 1) / (2 * i + 1);
        res+=t;
    }
    return res;
}

int main() {
    double x = 0.5;
    int n;
    printf("Enter number :\n");
    scanf("%d", &n);
    printf("Result - 4 program - %f\n", cycle(x, n));
    return 0;
}

//0.436321