#ifndef DEFS_H_
#define DEFS_H_

#define POPULATION_SIZE 4
#define MAX_N 31
#define MAX_N_BITSIZE 5 //  log2(MAX_N)
#define MUTATION_PROB 0.1


struct Agent {
    int id, phenotype, fitness;
    double prob;
    char* genotype;
};
typedef struct Agent Agent;

struct Generation {
    struct Agent agents[POPULATION_SIZE];
    int size, sum, max;
    double average;
};

typedef struct Generation Generation;


struct ProbabilityMatch {
    double prob;
    Agent agent;
};

typedef struct ProbabilityMatch ProbabilityMatch;

#endif