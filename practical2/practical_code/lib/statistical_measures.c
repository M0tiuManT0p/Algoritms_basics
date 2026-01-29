#include "statistical_measures.h"
#include <math.h>
#include <stdio.h>

double mean(double* experiments, int n) {
    if (n == 0) return 0.0;
    
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += experiments[i];
    }
    return sum / n;
}

double stddev(double* experiments, int n) {
    if (n < 2) return 0.0; 

    double m = mean(experiments, n);
    double sum_sq_diff = 0.0;

    for (int i = 0; i < n; i++) {
        sum_sq_diff += pow(experiments[i] - m, 2);
    }

    return sqrt(sum_sq_diff / (n - 1));
}

void confidence_interval(double* experiments, int n, double* ci) {
    if (n == 0) {
        ci[0] = 0.0;
        ci[1] = 0.0;
        return;
    }

    double m = mean(experiments, n);
    double sd = stddev(experiments, n);
    double margin_of_error = 1.96 * (sd / sqrt(n));

    ci[0] = m - margin_of_error;
    ci[1] = m + margin_of_error;
}