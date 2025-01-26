#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#include "functions.h"
#include "probabilities.h"
#include "definitions.h"
#include "variation.h"


unsigned int fitness(int x) {
    return x*x;
}

char* generate_genotype(int size) {
    char* str = (char*)malloc((size + 1) * sizeof(char));
    if (str == NULL) {
        fprintf(stderr, "%s", "Memory allocation failed");
    }
    for (int i = 0; i < size; i++) {
        int bit = random(0, 1);
        str[i] = bit + '0';
    }
    str[size] = '\0';
    return str;
}

Generation get_initial_selection() {
    Agent agents[POPULATION_SIZE];
    int sum = 0;
    int max = 0;


    for (int i = 0; i < POPULATION_SIZE; i++) {
        // generate the values for the agent.
        char* genotype = generate_genotype(MAX_N_BITSIZE);
        int phenotype = fromBinary(genotype);
        int performance = fitness(phenotype);

        // agent
        // probabilty is calculated later
        Agent a = {i, phenotype, performance, 0, genotype};

        sum = sum + a.fitness;
        if (a.fitness > max) {
            max = a.fitness;
        }

        agents[i] = a;
    }
    
    Generation gen;
    gen.sum = sum;
    gen.max = max;
    gen.size = POPULATION_SIZE;
    gen.average = sum / POPULATION_SIZE;

    // arrays cant be directly referenced since "agents" is a local variable
    // inside the local scope.
    for (int i = 0; i < POPULATION_SIZE; i++) {
        gen.agents[i] = agents[i];
        gen.agents[i].prob = (double)gen.agents[i].fitness / (double)sum;
        struct Agent a = gen.agents[i];
        fprintf(stderr, "%s with fitness(%d) = %d (%f %%)\n", a.genotype, a.phenotype, a.fitness, a.prob);
    }
 
    return gen;
}

Generation get_next_generation(Generation* gen) {
    ProbabilityMatch* prob = get_cumulative_probability(gen->agents);
    double* rand = (double*)malloc(POPULATION_SIZE * sizeof(double));

    Agent agents[POPULATION_SIZE];
    for (int i = 0; i < POPULATION_SIZE; i++) {
        double dbl = random_float(0.0, 1.0);
        // now have to find appropiate agent given this probabability bound "dbl"
        for (int j = 0;  j < POPULATION_SIZE; j++) {
            if (j == (POPULATION_SIZE - 1)) {
                agents[i] = prob[j].agent;
                break;
            }
            // fprintf(stderr, "Testing: %f < %f < %f\n", prob[j].prob, dbl, prob[j + 1].prob);
            if (prob[j].prob >= dbl && dbl <= prob[j + 1].prob) {
                agents[i] = prob[j].agent;
                break;
            } 
            
        }
    }
    // we should now have POPULATION_SIZE agents for our next generation according to their probabilities.

    // next step would be the VARIATION, e.g generate the offsprings and do the mutation.
    Agent* offspring = generate_offsprings(agents);

    free(rand);
    free(prob);
}

int main() {
    srand(time(NULL));
    fprintf(stderr, "%s", "Loaded program.\n");

    Generation gen = get_initial_selection();
    fprintf(stderr, "initial generation: %d, %f, %d\n", gen.sum, gen.average, gen.max);

    get_next_generation(&gen);
    return 0;
}