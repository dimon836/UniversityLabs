//
// Created by Dima on 10.06.2021.
//

#ifndef TIMERSOFTWAREFORWINDOWS_GENETICOPTIMIZATION_H
#define TIMERSOFTWAREFORWINDOWS_GENETICOPTIMIZATION_H

#include <vector>

class GeneticOptimization {
    std::vector<int> range;
    double accuracy;
    int max_generation;
    double crossover_rate;
    int bits_num;
    int population_num;
    std::vector<std::vector<int>> population;
    double mutation_rate;
public:
    GeneticOptimization(std::vector<int> range, double accuracy, int max_generation, double crossover_rate);

    std::vector<double> genetic_optimization(const std::string & option_str);

    std::vector<int> selection(const std::vector<double>& yi, int competitors_num, const std::string& option_str);
    std::vector<std::vector<int>> crossover(const std::vector<int>& parent1, const std::vector<int>& parent2) const;
    std::vector<int> mutate(std::vector<int>& chromosome) const;
    double decode(const std::vector<int>& bit_vector);


};
double function(double x);
bool comparing(double a, double b, const std::string& option_str);
template <typename T>
void printVector(const std::vector<T>& v);
template <typename T>
void printDoubleVector(const std::vector<std::vector<T>>& v);
#endif //TIMERSOFTWAREFORWINDOWS_GENETICOPTIMIZATION_H
