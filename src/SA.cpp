#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <cmath>
#include <limits>
#include "CommonStructs.h" 


void mutate(Solution& sol, const ProblemInstance& instance) {
    int idx1 = rand() % sol.cityTour.size();
    int idx2 = rand() % sol.cityTour.size();
    std::swap(sol.cityTour[idx1], sol.cityTour[idx2]);
    
    int itemIdx = rand() % sol.itemsPicked.size();
    sol.itemsPicked[itemIdx] = !sol.itemsPicked[itemIdx];
}
void simulatedAnnealing(const ProblemInstance& instance, int iterations, double startTemp, double endTemp, double coolingRate) {
    Solution currentSolution = generateRandomSolution(instance);
    currentSolution.fitness = calculateFitness(currentSolution, instance);
    Solution bestSolution = currentSolution;
    
    float worstFitness = std::numeric_limits<float>::max();
    float totalFitness = currentSolution.fitness;
    float bestFitness = currentSolution.fitness; 

    std::string csvPath = "C:\\Projects\\Optimization Methods\\Optimization Start-up\\results\\SimulatedAnnealingResults.csv";
    double temp = startTemp;
    for (int i = 0; temp > endTemp && i < iterations; ++i, temp *= coolingRate) {
        Solution newSolution = currentSolution;
        mutate(newSolution, instance);
        newSolution.fitness = calculateFitness(newSolution, instance);

        // Update best, worst, and total fitness
        if (newSolution.fitness > bestFitness) {
            bestFitness = newSolution.fitness;
            bestSolution = newSolution;
        }
        if (newSolution.fitness < worstFitness) worstFitness = newSolution.fitness;
        totalFitness += newSolution.fitness;

        float deltaFitness = newSolution.fitness - currentSolution.fitness;
        if (deltaFitness > 0 || exp(deltaFitness / temp) > static_cast<double>(rand()) / RAND_MAX) {
            currentSolution = newSolution;
        }

        float averageFitness = totalFitness / (i + 1); 
        logToCSV(csvPath, i + 1, bestFitness, averageFitness, worstFitness);
    }
    
    
    std::cout << "Best Fitness: " << bestFitness << std::endl;
    std::cout << "Worst Fitness: " << worstFitness << std::endl;
    std::cout << "Average Fitness: " << totalFitness / iterations << std::endl;
}


void runSimulatedAnnealing(const std::string& filePath) {
    srand(static_cast<unsigned int>(time(nullptr)));

    ProblemInstance instance;
    readInstance(filePath, instance);

    double startTemp = 10000.0;
    double endTemp = 1.0;
    double coolingRate = 0.99;
    int iterations = 100; 

    simulatedAnnealing(instance, iterations, startTemp, endTemp, coolingRate);
}
