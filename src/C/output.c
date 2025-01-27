#include <stdio.h>
#include <stdlib.h>

#include "definitions.h"


void print_agent(Agent agent) {
    fprintf(stderr, "[AGENT %d] G: %s P: %d \n", agent.id, agent.genotype, agent.phenotype);
}

void print_generation(Generation gen) {
    fprintf(stderr, "%s", "----------------\n");
    fprintf(stderr, "Generation: SUM: %d AVG: %f MAX: %d \n", gen.sum, gen.average, gen.max);
    for (int i = 0; i < POPULATION_SIZE; i++) {
        // print_agent(gen.agents[i]);
    }
}