#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "probabilities.h"
#include "definitions.h"
#include "functions.h"
#include "variation.h"
#include "output.h"

// parent selection
Agent* fitness_proportionate_selection(Agent agents[], ProbabilityMatch prob[]) {
    for (int i = 1; i < POPULATION_SIZE; i++) {
        double dbl = random_float(0.0, 1.0);
        // now have to find appropiate agent given this probabability bound "dbl"
        // fitness proportionate selection in action.
        // this suffers from premature convergence due to all solutions "converging" to the fittest individual.
        // higher probability individuals are prioritized. too much "selection pressure."
        // towards the end of the search, the selection pressure is too low..
        for (int j = 0; j < POPULATION_SIZE; j++) {
            if (j == (POPULATION_SIZE - 1) || (prob[j].prob >= dbl && dbl <= prob[j + 1].prob)) {
                agents[i] = prob[j].agent;
                break;
            }
        }       
    }


}

void tournament_selection() {}

// survival selcetion (elitism)
void survival_selection(Agent old[], Agent new[]) {}