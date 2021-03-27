//
// Created by Dima on 13.03.2021.
//

#include <cmath>
#include "Neuro.h"
const int start_iteration_index = 3;

Neuro::Neuro(std::vector<float>& value, std::vector<float>& weightCoefficients) :
        x(value), weightCoefficients(weightCoefficients) {}

void Neuro::learningNeuron(std::vector<float>& checkingArray) {
    int limit = 100000;
    float speed = 0.01;
    float E = 0, reserve_E = 0;
    int index = start_iteration_index;
    int iterations = 0;
    float S;
    float Y;
    std::vector<float> Ei_shtrih;
    std::vector<float> delta_wi;
    float delta_wi_average;
    for (int i = 0; i < limit; ++i) {
        for (int j = 0, index_x = index; j < weightCoefficients.size(); ++j, ++index_x) {
            S = countS(index_x);
            Y = forecast(S);
            E += std::pow(Y - x[index], 2);
            Ei_shtrih.push_back(oversightDerivative(Y, x[index_x], S));
            delta_wi.push_back(speed * Ei_shtrih[delta_wi.size()]);
            delta_wi_average = delta_average(delta_wi);
            adjustment(delta_wi_average);
        }
        index++;
        if(index == x.size()) {
            index = start_iteration_index;
            showCoefficients();
        }
        Ei_shtrih.clear();
        delta_wi.clear();
        if(std::abs(E-reserve_E) < 0.0001) {
            iterations = i;
            break;
        }
    }
    std::cout << std::endl;
    std::cout << "Iterations: " << iterations << std::endl;
}

float Neuro::forecast(float Si) {
    return 1 / ((1 + std::exp(-Si)) * 10);
}

float Neuro::oversightDerivative(const float Yi, const float yi, const float Si) {
    float xi = yi;
    return (Yi - yi) * (std::exp(-Si) / (std::pow(1 + std::exp(-Si), 2)) * xi);
}

float Neuro::countS(const int index) {
    return (x[index - 3] * weightCoefficients[0] +
            x[index - 2] * weightCoefficients[1] +
            x[index - 1] * weightCoefficients[2]);
}

float Neuro::delta_average(const std::vector<float>& delta_wi) {
    float delta_wi_sum = 0;
    for (float i: delta_wi) {
        delta_wi_sum += i;
    }
    return delta_wi_sum / delta_wi.size();
}

// корректировка
void Neuro::adjustment(const float delta_wi) {
    for (float & weightCoefficient : weightCoefficients) {
        weightCoefficient += delta_wi;
    }
}

void Neuro::showCoefficients() const {
    std::cout << std::endl << "##################### Weight coefficients #####################" << std::endl;
    for (float i: weightCoefficients) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}
