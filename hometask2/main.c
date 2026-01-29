#include "PercolationStats.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    int n = 100;
    int T = 100;

    PercolationStats* ps = create_percolation_stats(n, T);
    if (!ps) {
        printf("Failed to initialize stats.\n");
        return 1;
    }

    printf("Running %d experiments on %dx%d grid...\n", T, n, n);
    run_experiments(ps);

    print_statistics(ps);

    destroy_percolation_stats(ps);

    return 0;
}