#include <stdio.h>
#include <stdlib.h>
#include "probabilities.h"
#include "definitions.h"



ProbabilityMatch* get_cumulative_probability(Agent agents[])  {
    /*Given an agent returns the cumulative probabilty of that agent alongside the agent (ProbabilityMatch)*/
    double p = 0;
    ProbabilityMatch* pms = (ProbabilityMatch*)malloc(POPULATION_SIZE * sizeof(ProbabilityMatch));
    for (int i = 0; i < POPULATION_SIZE; i++) {
        p = p + (double)agents[i].prob;
        ProbabilityMatch pm =  {p, agents[i]};
        pms[i] = pm;
 
    }
    return pms;
}