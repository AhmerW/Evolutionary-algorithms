#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#include "functions.h"
#include "probabilities.h"
#include "definitions.h"
#include "variation.h"
#include "output.h"
#include "selection.h"



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
        int phenotype = from_binary(genotype);
        int performance = fitness(genotype, phenotype);

        // agent
        // probabilty is calculated later
        agents[i] = (Agent){i, phenotype, performance, 0, genotype};

        sum = sum + performance;
        if (performance > max) {
            max = performance;
        }

    }
    
    Agent fittest = agents[0];
    Generation gen;
    gen.sum = sum;
    gen.max = max;
    gen.size = POPULATION_SIZE;
    gen.average = sum / POPULATION_SIZE;

    // arrays cant be directly referenced since "agents" is a local variable
    // inside the local scope.
    // fitness proportionate selection (parent selection)
    for (int i = 0; i < POPULATION_SIZE; i++) {
        if (fitness(agents[i].genotype, agents[i].phenotype) > fittest.fitness) {
            fittest = agents[i];
        }
        gen.agents[i] = agents[i];
        // formula for pFPS
        gen.agents[i].prob = (double)gen.agents[i].fitness / (double)sum; // PFPS(i)
        struct Agent a = gen.agents[i];
        fprintf(stderr, "%s with fitness(%d) = %d (%f %%)\n", a.genotype, a.phenotype, a.fitness, a.prob);
    }
    gen.fittest = fittest;
 
    return gen;
}

Generation get_next_generation(Generation* gen) {
    print_generation(*gen);

    // keep the best agent
    Agent best_agent = gen->agents[0];
    for (int i = 1; i < POPULATION_SIZE; i++) {
        if (gen->agents[i].fitness > best_agent.fitness) {
            best_agent = gen->agents[i];
        }
    }


    // generate cumulative probabilities for selection
    ProbabilityMatch* prob = get_cumulative_probability(gen->agents);
    double* rand = (double*)malloc(POPULATION_SIZE * sizeof(double));

    Agent* agents = (Agent*)malloc(POPULATION_SIZE * sizeof(Agent));
    // part of the selection process - elitism (at least one copy of the N (1) fittest solutions)
    agents[0] = best_agent; 

    // alternatively : tournament selection.
    fitness_proportionate_selection(agents, prob);

    // next step would be the VARIATION, e.g generate the offsprings and do the mutation.
    Agent* offsprings = generate_offsprings(agents);

    // Now given these offsprings, and the previous generations' agents. We have to select the best out of them
    // also known as survival selection (given a set of 'mu' old and 'lambda' new ones)
    // -> elitism

    // create and return the new generation
    Generation new_gen;
    int sum = 0;
    int max = 0;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        sum = sum + offsprings[i].fitness;
        if (offsprings[i].fitness > max) {
            max = offsprings[i].fitness;
        }
    }
    for (int j = 0; j < POPULATION_SIZE; j++) {
        new_gen.agents[j] = offsprings[j];
        new_gen.agents[j].prob = (double)offsprings[j].fitness / (double)sum;
    }
    new_gen.fittest = best_agent;
    new_gen.sum = sum;
    new_gen.max = max;
    new_gen.size = POPULATION_SIZE;
    new_gen.average = sum / POPULATION_SIZE;


    free(rand);
    free(prob);

    return new_gen;
}

int main() {
    srand(time(NULL));
    fprintf(stderr, "Loaded program with POPULATION_SIZE=%d, MAX_N_BITSIZE=%d\n", POPULATION_SIZE, MAX_N_BITSIZE);

    Generation gen = get_initial_selection();
    for (int i = 0;  i < 20; i++) {
        print_generation(gen);

        if (strcmp(gen.fittest.genotype, "11111") == 0) {
            fprintf(stderr, "Found optimal solution (local or global optima)\n");
            print_agent(gen.fittest);
            break;
        }

        gen = get_next_generation(&gen);
        
    }
    
    return 0;
}