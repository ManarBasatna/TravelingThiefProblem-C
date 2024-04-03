#include <iostream>
#include <string>
#include "CommonStructs.h" 


void runGeneticAlgorithm(const std::string& filePath);
void runGreedyAlgorithm(const std::string& filePath);
void runRandomSearch(const std::string& filePath);
void runSimulatedAnnealing(const std::string& filePath);

int main() {
    std::string filePath = "C:\\Projects\\Optimization Methods\\Optimization Start-up\\data\\Instance7.ttp";

    // Header
    std::cout << "======================= Optimization Methods =======================\n";
    std::cout << "Data File: " << filePath << "\n\n";

    // Greedy Algorithm
    std::cout << "----------------------- Running Greedy Algorithm -----------------------\n";
    runGreedyAlgorithm(filePath);
    std::cout << "------------------------------------------------------------------------\n\n";

    // Random Search
    std::cout << "----------------------- Running Random Search -----------------------\n";
    runRandomSearch(filePath);
    std::cout << "----------------------------------------------------------------------\n\n";

    // Simulated Annealing
    std::cout << "----------------------- Running Simulated Annealing -----------------------\n";
    runSimulatedAnnealing(filePath);
    std::cout << "----------------------------------------------------------------------------\n\n";

    // Genetic Algorithm
    std::cout << "----------------------- Running Genetic Algorithm -----------------------\n";
    runGeneticAlgorithm(filePath);
    std::cout << "-------------------------------------------------------------------------\n\n";

    // Footer
    std::cout << "================= Optimization Algorithms Execution Completed =================\n";
    std::cout << "========================== Manar Chikh Basatna 283121 =========================\n";
    
    std::cout << "\nPress ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    return 0;
}