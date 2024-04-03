#include "CommonStructs.h"
#include <fstream>

void readInstance(const std::string& filePath, ProblemInstance& instance) {
    std::ifstream file(filePath);
    std::string line;
    City city;
    Item item;
    while (getline(file, line)) {
        std::istringstream iss(line);
        if (line.find("PROBLEM NAME") != std::string::npos) {
            iss.ignore(256, ':');
            iss >> instance.name;
        } else if (line.find("DIMENSION") != std::string::npos) {
            
        } else if (line.find("NUMBER OF ITEMS") != std::string::npos) {
            
        } else if (line.find("CAPACITY OF KNAPSACK") != std::string::npos) {
            iss.ignore(256, ':');
            iss >> instance.knapsackCapacity;
        } else if (line.find("MIN SPEED") != std::string::npos) {
            iss.ignore(256, ':');
            iss >> instance.minSpeed;
        } else if (line.find("MAX SPEED") != std::string::npos) {
            iss.ignore(256, ':');
            iss >> instance.maxSpeed;
        } else if (line.find("RENTING RATIO") != std::string::npos) {
            iss.ignore(256, ':');
            iss >> instance.rentingRatio;
        } else if (std::isdigit(line[0])) {
            iss >> city.id >> city.x >> city.y;
            instance.cities.push_back(city);
        } else if (line.find("ITEMS") != std::string::npos) {
            while (getline(file, line)) {
                std::istringstream itemsStream(line);
                itemsStream >> item.id >> item.profit >> item.weight >> item.cityId;
                instance.items.push_back(item);
            }
        }
    }
}

float calculateFitness(const Solution& sol, const ProblemInstance& instance) {
    
    float totalProfit = 0.0;
    for (size_t i = 0; i < sol.itemsPicked.size(); ++i) {
        if (sol.itemsPicked[i]) {
            totalProfit += instance.items[i].profit;
        }
    }
    return totalProfit;
}


Solution generateRandomSolution(const ProblemInstance& instance) {
    Solution sol;
    sol.cityTour.resize(instance.cities.size());
    std::iota(sol.cityTour.begin(), sol.cityTour.end(), 0);
    std::random_shuffle(sol.cityTour.begin(), sol.cityTour.end());

    sol.itemsPicked.resize(instance.items.size());
    for (size_t i = 0; i < instance.items.size(); ++i) {
        sol.itemsPicked[i] = rand() % 2 == 0;
    }
    return sol;
}


void logToCSV(const std::string& filepath, int iteration, float bestFitness, float averageFitness, float worstFitness) {
    std::ofstream csvFile(filepath, std::ios::app); 
    if (!csvFile.is_open()) {
        std::cerr << "Failed to open CSV file for logging.\n";
        return;
    }
    if (iteration == 1) {
        csvFile << "Iteration;Best Fitness;Average Fitness;Worst Fitness\n";
    }
    // Log the data
    csvFile << iteration << ";" << bestFitness << ";" << averageFitness << ";" << worstFitness << "\n";
    csvFile.close();
}

