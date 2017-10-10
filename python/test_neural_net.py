#!/usr/bin/env python
import numpy as np


def sigmoid(x, deriv=False):
    if deriv:
        return (x*(1-x))# (sigmoid(x)*(1-sigmoid(x)))
    return (1/(1+np.exp(-x)))

def tanh(x, deriv=False):
    if deriv:
        return (1 - (np.tanh(x) ** 2))
    return (np.tanh(x)+1)

def activation_function(x, deriv=False):
    return tanh(x, deriv)


def main():
    # input data and biases
    input_data = np.array([
        [0,0,1],
        [0,1,1],
        [1,0,1],
        [1,1,1]])
    # output of 'and' function
    output_data = np.array([[0],[0],[0],[1]])

    # set seed for random number generator so it will return the same number each time
    # useful for debugging
    np.random.seed(1)

    # synapses between input data and hidden layer
    # syn0 = 2*np.random.random((3,4)) - 1
    # syn1 = 2*np.random.random((4,1)) - 1
    syn0 = np.array([
        [-7.89263975, -6.00355936, -9.85764914, -7.522343  ],
        [-7.88369555, -6.04315582, -9.84766637, -7.50929985],
        [ 7.14186025,  5.2738996 ,  9.10725403,  6.76905569]])
    syn1 = np.array([
        [-4.62100674],
        [-3.83982359],
        [-5.18877708],
        [-4.41734134]])

    layer0 = input_data
    for j in range(10000):
        # break
        # calculate forward
        # tmp = np.dot(layer0, syn0)
        # print tmp
        # print tmp[0,0]
        # print activation_function(tmp[0,0])
        layer1 = activation_function(np.dot(layer0, syn0))
        # print layer1
        # print syn1
        layer2 = activation_function(np.dot(layer1, syn1))
        # print layer2
        # print output_data

        # back propagation
        # print layer2_error
        layer2_error = output_data - layer2
        layer2_delta = layer2_error * activation_function(layer2, deriv=True)

        layer1_error = np.dot(layer2_delta, syn1.T)
        layer1_delta = layer1_error * activation_function(layer1, deriv=True)

        # update weights
        # syn0 += layer0.T.dot(layer1_delta)
        # syn1 += layer1.T.dot(layer2_delta)
        syn0 += np.dot(layer0.T, layer1_delta)
        syn1 += np.dot(layer1.T, layer2_delta)
        # print syn0
        # print syn1
        # print layer1
        # print layer1[0,0]
        # exit(0)
    print layer0
    print syn0
    print syn1

    layer1 = activation_function(np.dot(input_data, syn0))
    layer2 = activation_function(np.dot(layer1, syn1))
    print('['+', '.join("%2.8f" % val for val in layer2)+']')


if __name__ == '__main__':
    main()
