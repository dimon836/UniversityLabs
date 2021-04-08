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
    std::cout << "x_|" << "Y" << std::endl;
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

//    std::vector<std::vector<float>> v1;
//    std::vector<float> v2;
//    v1.push_back({1, 2, 3, 4});
//    v1.push_back({5, 6, 7, 8});
//    v1.push_back({9, 10, 11, 12});
//
//    v2.push_back(1);
//    v2.push_back(2);
//    v2.push_back(3);
//    v2.push_back(4);
    /// first 13 elements
    std::vector<float> array_var4 = {0.13, 5.97, 0.57, 4.02,
                                     0.31, 5.55, 0.15, 4.54,
                                     0.65, 4.34, 1.54, 4.70, 0.58};
    std::vector<float> checking_array(array_var4);
    checking_array.push_back(5.83);
    checking_array.push_back(0.03);
    std::vector<float> w_coef({1, 1, 1});
    printVector(w_coef);
    std::vector<std::vector<float>> inputData;
    inputData.reserve(checking_array.size() - 3);
    for (int j = 0; j < checking_array.size() - 3; ++j) {
        // 3 elements
        inputData.push_back({checking_array[j], checking_array[j + 1], checking_array[j + 2]});
    }

    Neuro neuro(array_var4, w_coef);
    neuro.learningNeuron();
    neuro.showCoefficients();
    for (int i = 0; i < array_var4.size() - 1; ++i) {
        std::cout << i << ") Correct array: {" << checking_array[i] << ", "
                                               << checking_array[i + 1] << ", "
                                               << checking_array[i + 2] << "} Studied number: {";
        std::cout << neuro.getStudiedNumber(inputData[i]) << "} Right answer: {";
        std::cout << checking_array[i + 3] << '}' << std::endl;
    }
}
