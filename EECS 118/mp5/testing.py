#Alexander Choi's mp5 helper file
#Tests trained model from model.h5 and tests using mnist testing images
#prints accuracy in cmd line

import keras
import sys
from keras.datasets import mnist
from keras import backend as kback
from keras.models import Sequential
from keras.models import load_model
from keras.layers import Dense

#model parameters
(xtraining, ytraining),(xtest,ytest) = mnist.load_data()
batch = 128
classes = 10  #should not change
epochs = 3

if(len(sys.argv)-1 > 1):
	print("Too many arguments")
	exit()
elif(len(sys.argv)-1 <= 0):
	print("Enter file name")
	exit()

model = load_model(sys.argv[1])

#input test data formatting
xtest = xtest.astype('float32')
xtest = xtest.reshape(10000,784)
xtest = xtest/255

ytest = keras.utils.to_categorical(ytest,classes)

results = model.evaluate(xtest,ytest,verbose = 2)

print("Accuracy = ",results[1])