#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "probabilities.h"
#include "definitions.h"


Agent* generate_offsprings(Agent agents[]) {
    Agent* new_agents = (Agent*)malloc(POPULATION_SIZE * sizeof(Agent));
    bool skip = false;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        if (skip)  {
            skip = false;
            continue;
        }
        if (i + 1 >= (POPULATION_SIZE - 1)) {
            fprintf(stderr, "POPULATION_SIZE is an odd-number");
            new_agents[i] = agents[i];
            break;
        }
        int current_crossover_point = random(0, MAX_N_BITSIZE);
        int next_crossover_point = random(0, MAX_N_BITSIZE);

        skip = true;
    }
}