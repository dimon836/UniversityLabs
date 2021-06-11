#include <iostream>
#include <cmath>
#include <vector>
#include "GeneticOptimization.h"


int main() {
    std::vector<int> range;
    range.push_back(0);
    range.push_back(5);
    GeneticOptimization genetic(range, 0.001, 100, 0.9);

	std::vector<double> answers_min;
	answers_min = genetic.genetic_optimization("min");
	double x_min, y_min;
	x_min = answers_min[0];
	y_min = answers_min[1];

	std::vector<double> answers_max;
	answers_max = genetic.genetic_optimization("max");
	double x_max, y_max;
	x_max = answers_max[0];
	y_max = answers_max[1];

	std::cout << "x_min:" << x_min << std::endl;
	std::cout << "y_min:" << y_min << std::endl;
	std::cout << "x_max:" << x_max << std::endl;
	std::cout << "y_max:" << y_max << std::endl;

}
