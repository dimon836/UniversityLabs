//
// Created by Dima on 13.03.2021.
//

#ifndef NEURONET_NEURO_H
#define NEURONET_NEURO_H

#include <iostream>
#include <utility>
#include <vector>

class Neuro {
    std::vector<float> x_;
    std::vector<float> weight_coefficients_;
public:
    explicit Neuro(std::vector<float> x, std::vector<float> wCoef) :
            x_(std::move(x)), weight_coefficients_(std::move(wCoef)) {};

    void learningNeuron();

    static float forecastFunction(float S);
    static float sigmaDerived(float x);
    std::vector<float> oversightDerivative(const std::vector<float>& E_array,
                                           const std::vector<std::vector<float>>& inputData);

    static float countE(const std::vector<float>& v);

    void showCoefficients();

    float getStudiedNumber(const std::vector<float>& inputDataIndex) const;

    const std::vector<float> &getWeightCoefficients() const;
};

void printVector(const std::vector<float>& v);
void printDoubleVector(const std::vector<std::vector<float>>& v);
float sumVector(const std::vector<float>& v);
std::vector<std::vector<float>> transposeMatrix(const std::vector<std::vector<float>>& v);
float sumOfMultiplyVectors(const std::vector<float>& v1, const std::vector<float>& v2);
std::vector<float> multiplicationVectors(const std::vector<std::vector<float>>& v1, const std::vector<float>& v2);
#endif //NEURONET_NEURO_H
