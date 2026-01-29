#include "percolation.h"
#include <stdlib.h>
#include <stdio.h>

static bool is_valid(int n, int row, int col) {
    return (row >= 0 && row < n && col >= 0 && col < n);
}

static int get_index(int n, int row, int col) {
    return row * n + col;
}

Percolation* create_percolation(int n) {
    if (n <= 0) return NULL;

    Percolation* pc = (Percolation*)malloc(sizeof(Percolation));
    if (!pc) return NULL;

    pc->n = n;
    pc->opened_count = 0;
    
    pc->virtual_top = n * n;
    pc->virtual_bottom = n * n + 1;

    pc->grid = (bool*)calloc(n * n, sizeof(bool));
    if (!pc->grid) {
        free(pc);
        return NULL;
    }

    init_dynamic_connectivity(&pc->dc, n * n + 2);

    return pc;
}

void destroy_percolation(Percolation* pc) {
    if (!pc) return;
    
    if (pc->grid) {
        free(pc->grid);
    }
    
    free(pc);
}

int get_opened_count(Percolation* pc) {
    if (!pc) return 0;
    return pc->opened_count;
}

void open_coordinate(Percolation* pc, int i, int j) {
    if (!pc || !is_valid(pc->n, i, j)) return;

    int idx = get_index(pc->n, i, j);

    if (pc->grid[idx]) return;

    pc->grid[idx] = true;
    pc->opened_count++;

    if (i == 0) {
        add_union(&pc->dc, idx, pc->virtual_top);
    }

    if (i == pc->n - 1) {
        add_union(&pc->dc, idx, pc->virtual_bottom);
    }

    int dr[] = {-1, 1, 0, 0};
    int dc_offsets[] = {0, 0, -1, 1};

    for (int k = 0; k < 4; k++) {
        int adj_r = i + dr[k];
        int adj_c = j + dc_offsets[k];

        if (is_valid(pc->n, adj_r, adj_c)) {
            int adj_idx = get_index(pc->n, adj_r, adj_c);
            if (pc->grid[adj_idx]) {
                add_union(&pc->dc, idx, adj_idx);
            }
        }
    }
}

bool is_opened(Percolation* pc, int i, int j) {
    if (!pc || !is_valid(pc->n, i, j)) return false;
    return pc->grid[get_index(pc->n, i, j)];
}

bool is_full(Percolation* pc, int i, int j) {
    if (!pc || !is_valid(pc->n, i, j)) return false;
    
    int idx = get_index(pc->n, i, j);
    return pc->grid[idx] && connected(&pc->dc, idx, pc->virtual_top);
}

bool percolates(Percolation* pc) {
    if (!pc) return false;
    
    return connected(&pc->dc, pc->virtual_top, pc->virtual_bottom);
}