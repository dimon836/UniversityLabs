//
// Created by Dima on 13.03.2021.
//

#include <cmath>
#include "Neuro.h"

// size of weight coefficients(didn't want to make func getWeightCoefficients() static).
const int size = 3;

// printing the vector
void printVector(const std::vector<float>& v) {
    std::cout << '{' << v[0];
    for (int i = 1; i < v.size(); ++i) {
        std::cout << ", " << v[i];
    }
    std::cout << '}' << std::endl;
}

// printing double array vector
void printDoubleVector(const std::vector<std::vector<float>>& v) {
    for (int i = 0; i < v.size(); ++i) {
        std::cout << i << ") ";
        printVector(v[i]);
    }
}

// sum of vector elements
float sumVector(const std::vector<float>& v) {
    float sum = 0;
    for (auto i: v) {
        sum += i;
    }
    return sum;
}

float sumOfMultiplyVectors(const std::vector<float>& v1, const std::vector<float>& v2) {
    float sum = 0;
    for (int i = 0; i < v1.size(); ++i) {
        sum += v1[i] * v2[i];
    }
    return sum;
}

std::vector<std::vector<float>> transposeMatrix(const std::vector<std::vector<float>>& v) {
    std::vector<std::vector<float>> v_transpose;
    for (int j = 0; j < v[0].size(); ++j) {
        std::vector<float> v_line;
        for (const auto & line : v) {
            v_line.push_back(line[j]);
        }
        v_transpose.push_back(v_line);
    }
    return v_transpose;
}

// Only for vectors with range 3xN * Nx1, it will be transposed.
std::vector<float> multiplicationVectors(const std::vector<std::vector<float>>& v1, const std::vector<float>& v2) {
    std::vector<std::vector<float>> vector1;
    std::vector<std::vector<float>> vector2;
    vector2.reserve(v2.size());
    if (v1.size() != size) {
        vector1 = transposeMatrix(v1);
    } else {
        vector1 = v1;
    }
    for (float i : v2) {
        vector2.push_back({i});
    }

    std::vector<float> v_ans;
    v_ans.reserve(size);
    for (int i = 0; i < size; ++i) {
        v_ans.push_back(sumOfMultiplyVectors(vector1[i], v2));
    }

    return v_ans;
}

void Neuro::learningNeuron() {
    int limit = 100000;
    float speed = 0.01;
    int iterations = limit;
    float E, E1 = 0;

    std::vector<std::vector<float>> inputData;
    std::vector<float> expected;
    for (int i = 0; i < x_.size() - 3; ++i) {
        // 3 elements
        inputData.push_back({x_[i], x_[i + 1], x_[i + 2]});
        // elements after 3 elements
        expected.push_back(x_[i + 3]);
    }
    std::cout << "Vector x_: ";
    printVector(x_);
    std::cout << "Input data: \n";
    printDoubleVector(inputData);
    std::cout << "Vector expected: ";
    printVector(expected);
    std::vector<float> output;
    std::vector<float> E_array;
    for (int i = 0; i < limit; ++i) {

        for (int j = 0; j < x_.size() - 3; ++j) {
            // multiplied vectors
            output.push_back(forecastFunction(inputData[j][0] * weight_coefficients_[0] +
                                              inputData[j][1] * weight_coefficients_[1] +
                                              inputData[j][2] * weight_coefficients_[2]));
            E_array.push_back(output[j] - expected[j]);
        }
        E = countE(E_array);
//        showCoefficients();
        if (std::abs(E - E1) < 0.0001) {
            iterations = i;
            break;
        }
        E1 = E;
        std::vector<float> deltaAverage = oversightDerivative(E_array, inputData);
        std::vector<float> correctedDelta;
        correctedDelta.reserve(deltaAverage.size());
        for (float j : deltaAverage) {
            correctedDelta.push_back(-speed * j);
        }
        for (int j = 0; j < weight_coefficients_.size(); ++j) {
            weight_coefficients_[j] += correctedDelta[j];
        }
        if (i == 0) {
            std::cout << "Vector output: ";
            printVector(output);
            std::cout << "Vector E_array: ";
            printVector(E_array);
            std::cout << "Vector deltaAverage: ";
            printVector(deltaAverage);
            std::cout << "Vector correctedDelta: ";
            printVector(correctedDelta);
        }
        output.clear();
        E_array.clear();

        deltaAverage.clear();
        correctedDelta.clear();
    }
    inputData.clear();
    expected.clear();
    std::cout << std::endl;
    std::cout << "Iterations: " << iterations << std::endl;
}

// функция прогноза
float Neuro::forecastFunction(const float S) {
    return (1 / (1 + std::exp(-S))) * 10;
}

float Neuro::sigmaDerived(const float x) {
    return (float)(std::exp(-x)) / (float)(10 * std::pow(1 + std::exp(-x), 2));
}

std::vector<float> Neuro::oversightDerivative(const std::vector<float>& E_array,
                                              const std::vector<std::vector<float>>& inputData) {
    std::vector<float> v_ret;
    std::vector<float> v_return;
    v_ret.reserve(size);

    for (int i = 0; i < inputData.size(); ++i) {
        v_ret.push_back(E_array[i] * sigmaDerived(inputData[i][0] * weight_coefficients_[0] +
                                                  inputData[i][1] * weight_coefficients_[1] +
                                                  inputData[i][2] * weight_coefficients_[2]));
    }

    v_return = multiplicationVectors(inputData, v_ret);

    return v_return;
}

float Neuro::countE(const std::vector<float>& v) {
    float sum = 0;
    for (float i : v) {
        sum += std::pow(i, 2);
    }
    return sum;
}

void Neuro::showCoefficients() {
    std::cout << std::endl << "##################### Weight coefficients #####################" << std::endl;
    for (float i: weight_coefficients_) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

const std::vector<float> &Neuro::getWeightCoefficients() const {
    return weight_coefficients_;
}

float Neuro::getStudiedNumber(const std::vector<float>& inputDataIndex) const {
    std::vector<float> w = getWeightCoefficients();
    return forecastFunction(inputDataIndex[0] * w[0] +
                            inputDataIndex[1] * w[1] +
                            inputDataIndex[2] * w[2]);
}
