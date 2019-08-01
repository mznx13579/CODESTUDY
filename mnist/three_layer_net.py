﻿from functions import sigmoid, softmax
import numpy as np

class ThreeLayerNet:

    def __init__(self, input_size, hidden_1_size, hidden_2_size, output_size, weight_init_std=0.03):
        # (input_size, hidden_1_size, hidden_2_size, output_size) = (784, 50, 30, 10)

        # 가중치 초기화
        self.params = {}
        self.params['W1'] = weight_init_std * np.random.randn(input_size, hidden_1_size) # Xavier / np.sqrt(input_size)
        self.params['b1']  = np.zeros(hidden_1_size)
        self.params['W2'] = weight_init_std * np.random.randn(hidden_1_size, hidden_2_size) # Xavier / np.sqrt(hidden_1_size)
        self.params['b2']  = np.zeros(hidden_2_size)
        self.params['W3'] = weight_init_std * np.random.randn(hidden_2_size, output_size) # Xavier / np.sqrt(hidden_2_size)
        self.params['b3']  = np.zeros(output_size)

    def predict(self, x):
        W1, W2, W3 = self.params['W1'], self.params['W2'], self.params['W3']
        b1, b2, b3 = self.params['b1'], self.params['b2'], self.params['b3']

        # x.shape: (600, 784) 또는 (100, 784)

        a1 = np.dot(x, W1) + b1		# W1.shape: (784, 50)
        z1 = sigmoid(a1)			# z1.shape:  (600, 50) 또는 (100, 50)
        a2 = np.dot(z1, W2) + b2		# W2.shape: (50, 10)
        z2 = sigmoid(a2)            # z2.shape
        a3 = np.dot(z2, W3) + b3    # W3.shape
        y = softmax(a3)			# y.shape:    (600, 10) 또는 (100, 10)
        
        return y

    def accuracy(self, x, t):
        # x.shape: (600, 784) 또는 (100, 784)
        # t.shape: (600, 10) 또는 (100, 10)

        y = self.predict(x)			# y.shape: (600, 10) 또는 (100, 10)
        y = np.argmax(y, axis=1)		# y.shape: (600, ) 또는 (100, )
        t = np.argmax(t, axis=1)		# t.shape: (600, ) 또는 (100, )
        
        accuracy = np.sum(y == t) / float(x.shape[0])
        return accuracy

    def gradient(self, x, t):
        W1, W2, W3 = self.params['W1'], self.params['W2'], self.params['W3']
        b1, b2, b3 = self.params['b1'], self.params['b2'], self.params['b3']
        grads = {}

        ##########    순전파 파트    ###########
        a1 = np.dot(x, W1) + b1
        z1 = sigmoid(a1)
        a2 = np.dot(z1, W2) + b2
        z2 = sigmoid(a2)
        a3 = np.dot(z2, W3) + b3
        y  = softmax(a3)

        ##########    역전파 파트    ###########
        dLda3 = (y - t)

        grads['W3'] = np.dot(z2.T, dLda3)
        grads['b3'] = dLda3[0]

        dLdz2 = np.dot(dLda3, W3.T)
        dLda2 = z2 * (1-z2) * dLdz2

        grads['W2'] = np.dot(z1.T, dLda2)
        grads['b2'] = dLda2[0]
        
        dLdz1 = np.dot(dLda2, W2.T)
        dLda1 = z1 * (1-z1) * dLdz1

        grads['W1'] = np.dot(x.T, dLda1)
        grads['b1'] = dLda1[0]

        return grads
