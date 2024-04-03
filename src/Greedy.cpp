#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <numeric>
#include "CommonStructs.h"

void simulateGreedyRuns(ProblemInstance& instance, int runs) {
    srand(static_cast<unsigned int>(time(nullptr))); 

    float bestFitness = std::numeric_limits<float>::lowest();
    float worstFitness = std::numeric_limits<float>::max();
    float totalFitness = 0;

    for (int i = 0; i < runs; ++i) {
        Solution sol;

        sol.cityTour = std::vector<int>(instance.cities.size());
        std::iota(sol.cityTour.begin(), sol.cityTour.end(), 0);
        std::random_shuffle(sol.cityTour.begin(), sol.cityTour.end()); 
        
      
        sol.itemsPicked = std::vector<bool>(instance.items.size());
        for (size_t j = 0; j < sol.itemsPicked.size(); ++j) {
            sol.itemsPicked[j] = rand() % 2 == 0; // Randomly pick items
        }

        float fitness = calculateFitness(sol, instance);
        bestFitness = std::max(bestFitness, fitness);
        worstFitness = std::min(worstFitness, fitness);
        totalFitness += fitness;
        logToCSV("C:\\Projects\\Optimization Methods\\Optimization Start-up\\results\\GreedyAlgorithmResults.csv", runs + 1, bestFitness, totalFitness, worstFitness);
    }

    std::cout << "Best Fitness: " << bestFitness << "\n";
    std::cout << "Worst Fitness: " << worstFitness << "\n";
    std::cout << "Average Fitness: " << totalFitness / runs << std::endl;
}

void runGreedyAlgorithm(const std::string& filePath) {
    ProblemInstance instance;
    readInstance(filePath, instance);

    simulateGreedyRuns(instance, 100); 
}
