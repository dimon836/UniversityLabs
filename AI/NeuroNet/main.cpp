#include <iostream>
#include <vector>
#include "Neuro.h"
#include "boolean.h"

int main() {
    std::cout << "Checking logical AND:" << std::endl;
    std::cout << "x1 " << "x2 |" << "Y" << std::endl;
    for (int i = 0; i <= 1; ++i) {
        for (int j = 0; j <= 1; ++j) {
            std::cout << i << "  " << j << "  |" << boolean::AND(i, j) << std::endl;
        }
    }
    std::cout << "Checking logical OR:" << std::endl;
    std::cout << "x1 " << "x2 |" << "Y" << std::endl;
    for (int i = 0; i <= 1; ++i) {
        for (int j = 0; j <= 1; ++j) {
            std::cout << i << "  " << j << "  |" << boolean::OR(i, j) << std::endl;
        }
    }
    std::cout << "Checking logical NOT:" << std::endl;
    std::cout << "x|" << "Y" << std::endl;
    for (int i = 0; i <= 1; ++i) {
        std::cout << i << "|" << boolean::NOT(i) << std::endl;
    }
    std::cout << "Checking logical XOR:" << std::endl;
    std::cout << "x1 " << "x2 |" << "Y" << std::endl;
    for (int i = 0; i <= 1; ++i) {
        for (int j = 0; j <= 1; ++j) {
            std::cout << i << "  " << j << "  |" << boolean::XOR(i, j) << std::endl;
        }
    }
    /// first 13 elements
    std::vector<float> array_var4 = {0.13, 5.97, 0.57, 4.02,
                                     0.31, 5.55, 0.15, 4.54,
                                     0.65, 4.34, 1.54, 4.70, 0.58};
    std::vector<float> checking_array(array_var4);
    checking_array.push_back(5.83);
    checking_array.push_back(0.03);
    std::vector<float> w_coef;
    w_coef.reserve(3);
    w_coef.push_back(1);
    w_coef.push_back(1);
    w_coef.push_back(1);
    Neuro neuro(array_var4, w_coef);
    neuro.learningNeuron(checking_array);
}
