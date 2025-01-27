#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "probabilities.h"
#include "definitions.h"
#include "functions.h"
#include "variation.h"
#include "output.h"

int _binary_hamming_weight(char* genotype, int phenotype) {
    /* Prioritize the literal '1' */
    int score = 0;
    for (int i = 0; genotype[i] != '\0'; i++) {
        if (genotype[i] == '1') {
            score++;
        }
    }
    return score;
}

int _basic_fitness(char* genotype, int phenotype) {
    /* Test set MAX_N = 31 and MAX_N_BITSIZE = 5. Algorithm should give ut 961 = (31 x 31)*/
    return phenotype * phenotype;
}


int _target(char* genotype, int phenotype) {
    /* Go after a specific target */
    char* target = "11111";
    int score = 0;
    for (int i = 0; genotype[i] != '\0' && target[i] != '\0'; i++) {
        if (genotype[i] == target[i]) {
            score++;
        }
    }
    return score;
}

int fitness(char* genotype, int phenotype) {
    return _target(genotype, phenotype);
}


void set_genotype(Agent* agent, char* genotype) {
    agent->genotype = genotype;
    int phenotype = from_binary(agent->genotype);
    agent->phenotype = phenotype;
    agent->fitness = fitness(agent->genotype, phenotype);
}

void apply_mutation(char* genotype) {
    /* NB: only works for binary representations (genotypes) */
    for (int i = 0; i < strlen(genotype); i++) {
        double dbl = random_float(0.0, 1.0);
        if (dbl <= MUTATION_PROB) {
            if (genotype[i] == '0') {
                genotype[i] = '1';
            } else {
                genotype[i] = '0';
            }
        }
    }
}

Agent* generate_offsprings(Agent agents[]) {
    Agent* new_agents = (Agent*)malloc(POPULATION_SIZE * sizeof(Agent));
    bool skip = false;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        // we modify agent[i] and agent[i + 1] in one iteration.
        if (skip)  {
            skip = false;
            continue;
        }
        if ((i + 1) > (POPULATION_SIZE - 1)) {
            fprintf(stderr, "POPULATION_SIZE is an odd-number");
            new_agents[i] = agents[i];
            break;
        }
        new_agents[i] = agents[i];
        new_agents[i + 1] = agents[i + 1];
        // for binaries, this wouldnt work for most other representations.
        // index based splitting, ends at MAX_N_BITSIZE - 1
        // only need one crossover_point since agent[i + 1] needs to have same tail and header length.
        int crossover_point = random(0, MAX_N_BITSIZE - 2);

        char** current = split_string(new_agents[i].genotype, crossover_point);
        char** next = split_string(new_agents[i + 1].genotype, crossover_point);

        // split them by exchanging tails. first genotypes's tail is now the next's tail and vice versa.
        char* first_genotype = (char*)malloc(MAX_N_BITSIZE + 2 * sizeof(char*));
        char* next_genotype = (char*)malloc(MAX_N_BITSIZE + 2 * sizeof(char*));

        // writes to buffer in this case memory location given a format
        snprintf(first_genotype, sizeof(first_genotype), "%s%s", current[0], next[1]);
        snprintf(next_genotype, sizeof(next_genotype), "%s%s", next[0], current[1]);

        // apply mutation to new offsprings
        apply_mutation(first_genotype);
        apply_mutation(next_genotype);

        set_genotype(&new_agents[i], first_genotype);
        set_genotype(&new_agents[i + 1], next_genotype);

        skip = true;
    }

    return new_agents;
}
