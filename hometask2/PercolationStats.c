#include <stdio.h>  
#include <stdlib.h> 
#include <math.h>   
#include <time.h>    
#include "PercolationStats.h"
#include "percolation.h"

PercolationStats* create_percolation_stats(int grid_size, int experiments) {
    PercolationStats* ps = (PercolationStats*)malloc(sizeof(PercolationStats));
    if (ps == NULL) {
        return NULL;
    }
    ps->n = grid_size;
    ps->T = experiments;

    ps->thresholds = (double*)malloc(experiments * sizeof(double));

    if (ps->thresholds == NULL) {
        free(ps);
        return NULL;
    }

    return ps;
}

void destroy_percolation_stats(PercolationStats* ps) {
    if (ps != NULL) {
        if (ps->thresholds != NULL) {
            free(ps->thresholds);
        }
        free(ps);
    }
}

double mean_percolation_threshold(PercolationStats* ps){
    if (ps == NULL || ps->T == 0) {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 0; i < ps->T; i++) {
        sum += ps->thresholds[i];
    }
    return sum / ps->T;
}
void run_experiments(PercolationStats* ps) {
    srand((unsigned int)time(NULL));
    double total_sites = (double)ps->n * ps->n;

    for (int t = 0; t < ps->T; t++) {
        Percolation* pc = create_percolation(ps->n);

        while (!percolates(pc)) {
            int row = rand() % ps->n;
            int col = rand() % ps->n;

            if (!is_opened(pc, row, col)) {
                open_coordinate(pc, row, col);
            }
        }

        ps->thresholds[t] = (double)get_opened_count(pc) / total_sites;

        destroy_percolation(pc);
    }
}
double stddev_percolation_threshold(PercolationStats* ps) {
    if (ps->T <= 1) return 0.0;
    double mu = mean_percolation_threshold(ps);
    double sum_sq = 0.0;
    for (int i = 0; i < ps->T; i++) {
        double diff = ps->thresholds[i] - mu;
        sum_sq += diff * diff;
    }
    return sqrt(sum_sq / (ps->T - 1));
}

void print_statistics(PercolationStats* ps) {
    double mu = mean_percolation_threshold(ps);
    double sigma = stddev_percolation_threshold(ps);
    double margin_of_error = (1.96 * sigma) / sqrt(ps->T);

    printf("Mean                    = %f\n", mu);
    printf("StdDev                  = %f\n", sigma);
    printf("95%% confidence interval = [%f, %f]\n", 
            mu - margin_of_error, mu + margin_of_error);
}
