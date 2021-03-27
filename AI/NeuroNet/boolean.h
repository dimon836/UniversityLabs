//
// Created by Dima on 13.03.2021.
//

#ifndef NEURONET_BOOLEAN_H
#define NEURONET_BOOLEAN_H


class boolean {
public:
    static bool AND(int x1, int x2, int w1 = 1, int w2 = 1, float T = 1.5);
    static bool OR(int x1, int x2, int w1 = 1, int w2 = 1, float T = 0.5);
    static bool NOT(int x, float w = -1.5, float T = -1);
    static bool XOR(int x1, int x2, float T = 0.5);
};


#endif //NEURONET_BOOLEAN_H
