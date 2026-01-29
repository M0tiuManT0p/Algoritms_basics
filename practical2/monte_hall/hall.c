#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {

    int num_simulations = 10000;
    int stay_wins = 0;
    int switch_wins = 0;

    srand(time(NULL));

    for (int i = 0; i < num_simulations; i++) {
        int car_door = rand() % 3;

        int choice = rand() % 3;

        int host_opens;
        do {
            host_opens = rand() % 3;
        } while (host_opens == choice || host_opens == car_door);

        if (choice == car_door) {
            stay_wins++;
        }

        int switch_choice;
        for (int j = 0; j < 3; j++) {
            if (j != choice && j != host_opens) {
                switch_choice = j;
                break;
            }
        }

        if (switch_choice == car_door) {
            switch_wins++;
        }
    }

    printf("Simulations: %d\n", num_simulations);
    printf("Wins staying:  %d (%.2f%%)\n", stay_wins, (double)stay_wins / num_simulations * 100.0);
    printf("Wins switching: %d (%.2f%%)\n", switch_wins, (double)switch_wins / num_simulations * 100.0);

    return 0;
}