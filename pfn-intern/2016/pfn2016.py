# -*- coding: utf-8 -*-
"""
Implementation of Auto encoder from scrach.
"""


def matrix_check(l):
    try:
        row = len(l[0])
    except TypeError:
        print('This is one-dimension vector.')
        l = [l]
        row = len(l[0])
    finally:
        col = len(l)
        for i in range(0, col):
            if len(l[i]) != row:
                return False
        return True

def vector_check(l):
    try:
        row = len(l[0])
    except TypeError:
        return True
    return False


def shape_check(x, W, b):
    if matrix_check(W) and vector_check(x) and vector_check(b):
        if len(x) == len(W[0]) and len(b) == len(W):
            return True
    return False


def multiple_scalar(vec, scalar):
    if type(vec[0]) is float:
        return [i * scalar for i in vec]
    else:
        return [multiple_scalar(i, scalar) for i in vec]


def subtract_vector(vec1, vec2):
    if len(vec1) != len(vec2):
        raise ValueError
    if type(vec1[0]) is float:
        return [vec1[i] - vec2[i] for i in range(0, len(vec1))]
    else:
        return [subtract_vector(vec1[i], vec2[i]) for i in range(0, len(vec1))]

def transpose(matrix):
    if matrix_check(matrix):
        return [[matrix[j][i] for j in range(0, len(matrix))] for i in range(0, len(matrix[0]))]


def outer(x, y):
    """
    Input vectors... x = (x1 , ... , xn ), y = (y1, ... , ym)
    Output shape... (n, m)
    Output_(i, j) = x_i × y_j
    """
    return [[x[i] * y[j] for j in range(0, len(y))] for i in range(0, len(x))]


def affine(x, W, b):
    """
    Inputs... x = (n, ), W = (m, n), b = (m, )
    Output shape... (m, )
    """
    if shape_check(x, W, b):
        return [sum([W[i][j] * x[j] for j in range(0, len(x))]) + b[i] for i in range(0, len(W))]
    return False


def rms(x, y):
    if vector_check(x) and vector_check(y):
        return sum([(x[i] - y[i]) ** 2 for i in range(0, len(x))])
    else:
        raise ValueError



class AutoEncoder(object):
    def __init__(self, n_input, n_nodes=5, eta=0.1):
        self.n_input = n_input
        self.n_nodes = n_nodes
        self.eta = eta

    def __call__(self, x):
        self.x = x
        self.h = affine(self.x, self.W1, self.b1)
        self.y = affine(self.h, self.W2, self.b2)
        return self.y

    def initialize_Wb(self, initial_W=0., initial_b=0.1):
        self.W1 = [[initial_W for i in range(self.n_input)] for i in range(self.n_nodes)]
        self.b1 = [initial_b for i in range(self.n_nodes)]
        self.W2 = [[initial_W for i in range(self.n_nodes)] for i in range(self.n_input)]
        self.b2 = [initial_b for i in range(self.n_input)]

    def forward(self, x):
        self.loss = rms(x, self(x)) / 2.        

    def backward(self):
        gy = subtract_vector(self.y, self.x)
        gW2 = outer(gy, self.h)
        gb2 = gy
        gh = affine(gy, transpose(self.W2), [0] * len(self.W2[0]))
        gW1 = outer(gh, self.x)
        gb1 = gh
        self.W2 = subtract_vector(self.W2, multiple_scalar(gW2, self.eta))
        self.b2 = subtract_vector(self.b2, multiple_scalar(gb2, self.eta))
        self.W1 = subtract_vector(self.W1, multiple_scalar(gW1, self.eta))
        self.b1 = subtract_vector(self.b1, multiple_scalar(gb1, self.eta))

    def iteration(self, inputs, n_iteration):
        for i in range(n_iteration):
            for x in inputs:
                self.forward(x)
                self.backward()
            print('Epoch {}... Loss: {}'.format(i, self.loss))


if __name__ == '__main__':
    x = [-0.5, -0.3, -0.1, 0.5, .3, .1, -.4, -.2, .0, .4, .2]
    c = AutoEncoder(len(x))
    c.initialize_Wb()
    c.iteration([x], 30)

