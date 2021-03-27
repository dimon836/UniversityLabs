//
// Created by Dima on 13.03.2021.
//

#include "boolean.h"

bool boolean::AND(int x1, int x2,
                  const int w1, const int w2,
                  const float T) {
    int S = x1*w1 + x2*w2;
    return S >= T;
}

bool boolean::OR(int x1, int x2,
        const int w1, const int w2,
        const float T) {
    int S = x1*w1 + x2*w2;
    return S >= T;
}

bool boolean::NOT(int x,
         const float w,
         const float T) {
//    float S = x*w;
//    return S >= T;
    return !x;
}

bool boolean::XOR(int x1, int x2,
         const float T) {
    return (x1 + x2)%2 == 1;
}