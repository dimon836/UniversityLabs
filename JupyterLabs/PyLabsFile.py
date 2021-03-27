import numpy as np
from scipy.integrate import odeint
from math import pow, sqrt

a = 0
b = 1


def getF(y, t):
    return y[0] - 4*y[1] + 2, t + y[1]


def solve_euler(t, h):
    y = [[0.0, 0.0]]
    for i in range(1, len(t)):
        res = list(np.array(y[i - 1]) + np.dot(h, np.array(getF(y[i - 1], t[i - 1]))))
        y.append(res)
    return y


def solve_runge_kutta(t, h):
    y = [[0, 0]]
    for i in range(1, len(t)):
        n1 = np.dot(h, getF(y[i-1], t[i-1]))
        n2 = np.dot(h, getF([y[i-1][0] + n1[0] / 2, y[i-1][1] + n1[1] / 2], t[i-1] + h / 2))
        n3 = np.dot(h, getF([y[i-1][0] + n2[0] / 2, y[i-1][1] + n2[1] / 2], t[i-1] + h / 2))
        n4 = np.dot(h, getF([y[i-1][0] + n3[0], y[i-1][1] + n3[1]], t[i-1] + h))
        res = list(np.array(y[i - 1]) + (1/6) * (n1 + 2*n2 + 2*n3 + n4))
        y.append(res)
    return y



def get_t(h):
    return np.array([a + i * h for i in range(int(b / h) + 1)])



def check_accuracy(h, flag = True):
    results = []
    e = 1
    while e > 0.01:
        if flag:
            results = [solve_runge_kutta(get_t(h), h), solve_runge_kutta(get_t(h/2), h/2)]
        else:
            results = [solve_euler(get_t(h), h), solve_euler(get_t(h / 2), h / 2)]
        e = sqrt((1.0/len(get_t(h))) * sum(sum((results[0][i][j] - results[1][i*2][j]) ** 2 for i in range(len(get_t(h)))) for j in range(1)))
        h = h/2
    return results[0]



if __name__ == '__main__':
    h = 0.5
    t = get_t(h)
    y0 = [0.0, 0.0]
    y1 = check_accuracy(h, False)
    y2 = check_accuracy(h, True)
    real = odeint(getF, y0, t)
    print('t           x(E)        y(E)        x(R-K)      y(R-K)      real x      real y')
    print('{:<10}  {:<10}  {:<10}  {:<10}  {:<10}  {:<10}  {:<10}'.format(t[0], y1[0][0], y1[0][1], y2[0][0], y2[0][1], real[0][0], real[0][1]))
    print('{:<10}  {:<10.5}  {:<10.5}  {:<10.5}  {:<10.5}  {:<10.5}  {:<10.5}'.format(t[2], y1[len(y1)-1][0], y1[len(y1)-1][1], y2[len(y2)-1][0], y2[len(y2)-1][1],
                                                                          real[len(real)-1][0], real[len(real)-1][1]))