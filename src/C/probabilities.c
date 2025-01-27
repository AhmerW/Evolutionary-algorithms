#include <stdio.h>
#include <stdlib.h>
#include "probabilities.h"
#include "definitions.h"



ProbabilityMatch* get_cumulative_probability(Agent agents[]) {
    double p = 0;
    ProbabilityMatch* pms = (ProbabilityMatch*)malloc(POPULATION_SIZE * sizeof(ProbabilityMatch));
    for (int i = 0; i < POPULATION_SIZE; i++) {
        p += agents[i].prob;
        pms[i] = (ProbabilityMatch){p, agents[i]};
    }
    // Ensure the last cumulative probability is exactly 1
    pms[POPULATION_SIZE - 1].prob = 1.0; 
    return pms;
}