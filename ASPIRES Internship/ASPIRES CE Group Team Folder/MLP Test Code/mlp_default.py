
from __future__ import division, print_function, absolute_import

import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
import time

for CRAZY_FOR_LOOP in range(0,5):
	#for increment in range(1,11):
			#time
			start_time = time.time()

			#import MNIST data
			from tensorflow.examples.tutorials.mnist import input_data
			mnist = input_data.read_data_sets("MNIST_data",one_hot=True)

			#Default Parameters:
			#

			#Network parameters
			learning_rate = 0.001
			training_epochs = 100
			batch_size = 256
			display_step = 10
			examples_to_show=10

			n_hidden_1= 100
			n_hidden_2=256
			n_out=10
			n_input = 784 #Mnist data input

			#tensorflow Graph input (only pictures)
			X = tf.placeholder("float", [None, n_input])
			Y =  tf.placeholder("float", [None, n_out])

			weights = {
				'h1' : tf.Variable(tf.random_normal([n_input,n_hidden_1])),
				#'h2' : tf.Variable(tf.random_normal([n_hidden_1, n_hidden_2])),
				'out' : tf.Variable(tf.random_normal([n_hidden_1, n_out])),
			}
			biases = {
				'b1' : tf.Variable(tf.random_normal([n_hidden_1])),
				#'b2' : tf.Variable(tf.random_normal([n_hidden_2])),
				'out' : tf.Variable(tf.random_normal([n_out])),
			}

			def forward(x):
				layer1 = tf.nn.relu(tf.add(tf.matmul(x,weights['h1']), biases['b1']))
				#layer2 = tf.nn.sigmoid(tf.add(tf.matmul(layer1,weights['h2']), biases['b2']))
				out_layer= tf.add(tf.matmul(layer1, weights['out']), biases['out'])
				return out_layer

			#construct model
			y_true = forward(X)
			y_pred = Y


			#Define loss and optimizer, minimize the squared error
			cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels=y_pred, logits=y_true))
			optimizer = tf.train.AdamOptimizer(learning_rate).minimize(cost)

			#Initializing the variables
			init = tf.global_variables_initializer()

			#Initialize Saver to save weight values
			weights_saver = tf.train.Saver(var_list = weights)
			biases_saver = tf.train.Saver(var_list = biases)

			#Launch session
			sess = tf.Session()
			sess.run(init)

			total_batch = int(mnist.train.num_examples/batch_size)

			#Training cycle
			for epoch in range(training_epochs):
				#Loop over all batches
				for i in range(total_batch):
					batch_xs, batch_ys = mnist.train.next_batch(batch_size)
				#Run optimization op (backprop) and cost op (to get loss value)
					_, c = sess.run([optimizer,cost], feed_dict={X:batch_xs,Y:batch_ys})
				#display logs per epoch step
				if epoch % display_step ==0:
					print("Epoch:", '%04d' % (epoch+1), "cost=", "{:.9f}".format(c))

			correct_prediction = tf.equal(tf.argmax(y_true,1),tf.argmax(y_pred,1))
			accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
			print(sess.run(accuracy*100, feed_dict={X: mnist.test.images, Y: mnist.test.labels}),'% accuracy')
			print("--- %s seconds ---" % (time.time() - start_time))

			print("Optimization Finished!")