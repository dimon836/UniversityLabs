//
// Created by Dima on 10.06.2021.
//

#include <iostream>
#include <cmath>
#include <iomanip>
#include "GeneticOptimization.h"

double function(double x) {
    return std::sqrt(x) * std::sin(10 * x);
}

bool comparing(double a, double b, const std::string& option_str) {
    if (option_str == "max")
        return a > b;
    return a < b;
}

// printing the vector
template <typename T>
void printVector(const std::vector<T>& v) {
	std::cout << '{' << v[0];
	for (int i = 1; i < v.size(); ++i) {
		std::cout << ", " << v[i];
	}
	std::cout << '}' << std::endl;
}

// printing double array vector
template <typename T>
void printDoubleVector(const std::vector<std::vector<T>>& v) {
	for (int i = 0; i < v.size(); ++i) {
		std::cout << i << ") ";
		printVector(v[i]);
	}
}

GeneticOptimization::GeneticOptimization(std::vector<int> range, const double accuracy,
                                         const int max_generation, const double crossover_rate) :
                                         range(std::move(range)), accuracy(accuracy), max_generation(max_generation),
                                         crossover_rate(crossover_rate){
    bits_num = 32;
    population_num = 100;
    mutation_rate = 1.0/(double)bits_num;
    for (int i = 0; i < population_num; ++i) {
        std::vector<int> append_vector;
        append_vector.reserve(bits_num);
        for (int j = 0; j < bits_num; ++j) {
            append_vector.push_back(rand()%2);
        }
        population.push_back(append_vector);
        append_vector.clear();
    }
}

std::vector<double> GeneticOptimization::genetic_optimization(const std::string & option_str) {
    std::cout << "GeneticOptimization searching for: " << option_str << std::endl;
    std::vector<int> x_best;
    double y_best = function(decode(population[0]));
	for (int i = 0; i < max_generation; ++i) {
		x_best.clear();
		std::vector<double> decoded_population;
		decoded_population.reserve(population.size());
		for (auto &pop: population) {
			decoded_population.push_back(decode(pop));
		}
		///printing
//		printVector(decoded_population);
		std::vector<double> Yi;
		Yi.reserve(decoded_population.size());
		for (auto x: decoded_population) {
			Yi.push_back(function(x));
		}
		///printing
//		printVector(Yi);
		decoded_population.clear();
		for (int j = 0; j < population_num; ++j) {
			if(comparing(Yi[j], y_best, option_str)) {
				x_best = population[j];
				y_best = Yi[j];
			}
		}
		if(i % 10 == 0) {
			std::cout << i << " Best: f_" << option_str << '(' << decode(x_best) << ") = " << y_best << std::endl;
		}
		std::vector<std::vector<int>> selected_population;
		selected_population.reserve(population_num);
		for (int j = 0; j < population_num; ++j) {
			selected_population.push_back(selection(Yi, 3, option_str));
		}
		///printing
//		printDoubleVector(selected_population);
		Yi.clear();
		std::vector<std::vector<int>> new_population;
		new_population.reserve(population_num);
		for (int j = 0; j < population_num; j+=2) {
			std::vector<int> parent1 = selected_population[j];
			std::vector<int> parent2 = selected_population[j + 1];
			std::vector<std::vector<int>> vector_crossover;
			vector_crossover = crossover(parent1, parent2);
//			std::cout << j << std::endl;
//			printDoubleVector(vector_crossover);
			for (std::vector<int> child: vector_crossover) {
//				printVector(child);
				child = mutate(child);
//				std::cout << j << ')';
//				printVector(child);
				new_population.push_back(child);
			}
			///printing
//			printDoubleVector(new_population);
			parent1.clear();
			parent2.clear();
			vector_crossover.clear();
		}
		///printing
//		std::cout << "POPULATION" << std::endl;
//		printDoubleVector(population);
		selected_population.clear();
		population.insert(population.cbegin(), new_population.cbegin(), new_population.cend());
		///printing
//		printDoubleVector(new_population);
//		printDoubleVector(population);
		new_population.clear();
	}
	std::cout << "Best: f_" << option_str << '(' << decode(x_best) << ") = " << y_best << std::endl;
	std::cout.fill('-');
	std::cout << std::setw(20);
	std::cout << std::endl;
	std::vector<double> ret_vector;
	ret_vector.push_back(decode(x_best));
	ret_vector.push_back(y_best);
    return ret_vector;
}

std::vector<int> GeneticOptimization::selection(const std::vector<double>& yi, int competitors_num, const std::string& option_str) {
    int selected = rand()%population.size();
    std::vector<int> vector_random;
    vector_random.reserve(competitors_num-1);
    for (int i = 0; i < competitors_num-1; ++i) {
    	int random = int(rand()%population.size());
        vector_random.push_back(random);
    }
    for (int i: vector_random) {
        if (comparing(yi[i], yi[selected], option_str)) {
            selected = i;
        }
    }
    return population[selected];
}

std::vector<std::vector<int>> GeneticOptimization::crossover(const std::vector<int> &parent1, const std::vector<int> &parent2) const {
    std::vector<int> child1 = parent1;
    std::vector<int> child2 = parent2;
    if((rand()%1000) / 1000.0 < crossover_rate) {
    	child1.clear();
    	child2.clear();
        unsigned long long point = 1 + rand()%(parent1.size() - 2);
        child1.insert(child1.cbegin(), parent1.cbegin(), parent1.cbegin() + (int)point);
        child1.insert(child1.cend(), parent2.cbegin() + (int)point, parent2.cend());

        child2.insert(child2.cbegin(), parent2.cbegin(), parent2.cbegin() + (int)point);
        child2.insert(child2.cend(), parent1.cbegin() + (int)point, parent1.cend());
    }
    std::vector<std::vector<int>> children;
    children.push_back(child1);
    children.push_back(child2);
    return children;
}

std::vector<int> GeneticOptimization::mutate(std::vector<int>& chromosome) const {
//	std::cout << "Before" << std::endl;
//	printVector(chromosome);
    for (int &i : chromosome) {
        if ((rand()%1000) / 1000.0 < mutation_rate) {
            i = 1 - i;
        }
    }
//	std::cout << "After" << std::endl;
//	printVector(chromosome);
	return chromosome;
}

double GeneticOptimization::decode(const std::vector<int>& bit_vector) {
    double largest = std::pow(2, bits_num);
    std::vector<int> sub_vector;
    sub_vector.insert(sub_vector.cbegin(),bit_vector.cbegin(), bit_vector.cbegin() + bits_num);
    int num = 0;
    for(int i = (int)sub_vector.size() - 1; i >= 0; i--) {
        num += sub_vector[i] * (int)pow(2, i);
    }
	double value = range[0] + (num / largest) * (range[1] - range[0]);
    return value;
}
