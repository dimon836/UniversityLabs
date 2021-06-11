from math import sin
from Grapghic import Graphic

if __name__ == '__main__':
    rng = (0, 5)
    y = lambda x: x ** (1 / 2) * sin(10 * x)
    graphic = Graphic(y, rng)

    graphic.show_func()
