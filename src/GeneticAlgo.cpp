#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <limits>
#include "CommonStructs.h" 

void readInstance(const std::string& filePath, ProblemInstance& instance);
Solution generateRandomSolution(const ProblemInstance& instance);
void mutate(Solution& sol, const ProblemInstance& instance);
float calculateFitness(const Solution& sol, const ProblemInstance& instance);
void geneticAlgorithm(const ProblemInstance& instance, int populationSize, int generations, float Px, float Pm, int tournamentSize);


void runGeneticAlgorithm(const std::string& filePath) {
    srand(static_cast<unsigned int>(time(nullptr)));

    ProblemInstance instance;
    readInstance(filePath, instance);

    geneticAlgorithm(instance, 100, 100, 0.7, 0.1, 5);
}


void initializePopulation(std::vector<Solution>& population, const ProblemInstance& instance, int populationSize) {
    population.clear();
    for (int i = 0; i < populationSize; ++i) {
        Solution sol;
        sol.cityTour.resize(instance.cities.size());
        std::iota(sol.cityTour.begin(), sol.cityTour.end(), 0);
        std::random_shuffle(sol.cityTour.begin(), sol.cityTour.end());

        sol.itemsPicked.resize(instance.items.size(), false);
        for (size_t j = 0; j < instance.items.size(); ++j) {
            sol.itemsPicked[j] = rand() % 2 == 0;
        }
        population.push_back(sol);
    }
}

Solution tournamentSelection(const std::vector<Solution>& population, int tournamentSize) {
    Solution best;
    float bestFitness = std::numeric_limits<float>::lowest();
    for (int i = 0; i < tournamentSize; ++i) {
        int idx = rand() % population.size();
        if (population[idx].fitness > bestFitness) {
            best = population[idx];
            bestFitness = best.fitness;
        }
    }
    return best;
}

void crossover(Solution& offspring, const Solution& parent1, const Solution& parent2, float Px, const ProblemInstance& instance) {
    if (static_cast<float>(rand()) / RAND_MAX < Px) {
        int crossoverPoint = rand() % parent1.cityTour.size();
        for (int i = crossoverPoint; i < parent1.cityTour.size(); ++i) {
            offspring.cityTour[i] = parent2.cityTour[i];
        }
    } 
}

void mutate(Solution& sol, float Pm, const ProblemInstance& instance) {
    // Mutate tour
    if (static_cast<float>(rand()) / RAND_MAX < Pm) {
        int idx1 = rand() % sol.cityTour.size();
        int idx2 = rand() % sol.cityTour.size();
        std::swap(sol.cityTour[idx1], sol.cityTour[idx2]);
    }
    // Mutate items
    for (size_t i = 0; i < sol.itemsPicked.size(); ++i) {
        if (static_cast<float>(rand()) / RAND_MAX < Pm) {
            sol.itemsPicked[i] = !sol.itemsPicked[i];
        }
    }
}

void geneticAlgorithm(const ProblemInstance& instance, int populationSize, int generations, float Px, float Pm, int tournamentSize) {
    std::vector<Solution> population;
    initializePopulation(population, instance, populationSize);


    float grandTotalFitness = 0.0;  // To calculate the grand average fitness over all generations
    float overallBestFitness = std::numeric_limits<float>::lowest();
    float overallWorstFitness = std::numeric_limits<float>::max();

    for (int gen = 0; gen < generations; ++gen) {
        float genTotalFitness = 0.0;
        float genBestFitness = std::numeric_limits<float>::lowest();
        float genWorstFitness = std::numeric_limits<float>::max();
        



        std::vector<Solution> newPopulation;
        for (int i = 0; i < populationSize; ++i) {
            Solution offspring = tournamentSelection(population, tournamentSize);
            Solution parent2 = tournamentSelection(population, tournamentSize);
            crossover(offspring, offspring, parent2, Px, instance);
            mutate(offspring, Pm, instance);
            offspring.fitness = calculateFitness(offspring, instance);

            genTotalFitness += offspring.fitness;
            if (offspring.fitness > genBestFitness) genBestFitness = offspring.fitness;
            if (offspring.fitness < genWorstFitness) genWorstFitness = offspring.fitness;

            newPopulation.push_back(offspring);
        }

        population = newPopulation; // Update the population with the new generation
        float genAverageFitness = genTotalFitness / populationSize;

                        
        
        if (genBestFitness > overallBestFitness) overallBestFitness = genBestFitness;
        if (genWorstFitness < overallWorstFitness) overallWorstFitness = genWorstFitness;

        grandTotalFitness += genTotalFitness;

logToCSV("C:\\Projects\\Optimization Methods\\Optimization Start-up\\results\\GeneticAlgorithmResults.csv", gen + 1, genBestFitness, genTotalFitness, genWorstFitness);


    }

    float grandAverageFitness = grandTotalFitness / (populationSize * generations);

    std::cout << "Best Fitness: " << overallBestFitness << std::endl;
    std::cout << "Worst Fitness: " << overallWorstFitness << std::endl;
    std::cout << "Average Fitness: " << grandAverageFitness << std::endl;
}
