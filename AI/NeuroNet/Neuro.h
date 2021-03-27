//
// Created by Dima on 13.03.2021.
//

#ifndef NEURONET_NEURO_H
#define NEURONET_NEURO_H

#include <iostream>
#include <vector>

class Neuro {
    std::vector<float> x;
    std::vector<float> weightCoefficients;
public:
    Neuro  (std::vector<float>& x,
            std::vector<float>& weightCoefficients);
    void learningNeuron(std::vector<float>& checkingArray);

    static float forecast(float Si);
    static float oversightDerivative(float Yi, float yi, float Si);

    float countS(int index);

    static float delta_average(const std::vector<float>& delta_wi);
    void adjustment(float delta_wi);

    void showCoefficients() const;
};


#endif //NEURONET_NEURO_H
