#ifndef COMMONSTRUCTS_H
#define COMMONSTRUCTS_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <string>


struct City {
    int id;
    float x, y;
};

struct Item {
    int id;
    float profit, weight;
    int cityId;
};

struct ProblemInstance {
    std::string name;
    std::vector<City> cities;
    std::vector<Item> items;
    float knapsackCapacity;
    float minSpeed, maxSpeed;
    float rentingRatio;
};

struct Solution {
    std::vector<int> cityTour;
    std::vector<bool> itemsPicked;
    float fitness = -1.0f;
};

void logToCSV(const std::string& filepath, int iteration, float bestFitness, float averageFitness, float worstFitness);
void readInstance(const std::string& filePath, ProblemInstance& instance);
float calculateFitness(const Solution& sol, const ProblemInstance& instance);
Solution generateRandomSolution(const ProblemInstance& instance);


#endif // COMMONSTRUCTS_H
