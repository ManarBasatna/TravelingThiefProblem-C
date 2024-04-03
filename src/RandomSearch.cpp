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



void randomSearch(const ProblemInstance& instance, int iterations) {
    float bestFitness = std::numeric_limits<float>::lowest();
    float worstFitness = std::numeric_limits<float>::max();
    float totalFitness = 0;

    for (int i = 0; i < iterations; ++i) {
        Solution sol = generateRandomSolution(instance);
        sol.fitness = calculateFitness(sol, instance);
        totalFitness += sol.fitness;

        if (sol.fitness > bestFitness) {
            bestFitness = sol.fitness;
        }
        if (sol.fitness < worstFitness) {
            worstFitness = sol.fitness;
        }

        float averageFitness = totalFitness / iterations;
        logToCSV("C:\\Projects\\Optimization Methods\\Optimization Start-up\\results\\RandomSearchResults.csv", i + 1, bestFitness, sol.fitness, worstFitness);
    }

    float averageFitness = totalFitness / iterations;
    std::cout << "Best Fitness: " << bestFitness << "\n";
    std::cout << "Worst Fitness: " << worstFitness << "\n";
    std::cout << "Average Fitness: " << averageFitness << std::endl;
}

void runRandomSearch(const std::string& filePath) {
    srand(static_cast<unsigned int>(time(nullptr)));

    ProblemInstance instance;
    readInstance(filePath, instance);

    int iterations = 100; 
    randomSearch(instance, iterations);
}

