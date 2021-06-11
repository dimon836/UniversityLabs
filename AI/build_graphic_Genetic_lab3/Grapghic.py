import numpy as np
import matplotlib.pyplot as plt


class Graphic:
    def __init__(self, func, rng):
        self.function = func
        self.range = rng

    def show_func(self):
        x = np.linspace(*self.range, 1000)
        plt.title('Function:')
        plt.plot(x, list(map(self.function, x)))
        plt.show()
