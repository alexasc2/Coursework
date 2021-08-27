#Alexander Choi's mp5 submission
#UCI ID: 62339918
#Fully functional, with 1 input layer, 1 tranisition layer, and 1 output layer
#Saves as model.h5
#See testing.py for evaluation of test images

import keras
import numpy as np
from keras.datasets import mnist
from keras.models import Sequential
from keras.models import load_model
from keras.layers import Dense, Dropout
from keras import optimizers
from keras.utils import to_categorical
from keras import backend as keras_backend


(xtraining, ytraining),(xtest,ytest) = mnist.load_data()

#model parameters
model =  Sequential()
batch = 128
classes = 10  #should not change
epochs = 40
n_input_images = 20000 #number of images to train on

#input training data formatting
xtraining = xtraining.reshape(60000,784)  #becomes tuple
xtraining = xtraining.astype('float32')
xtraining = xtraining/255

#one hot encoding
ytraining = keras.utils.to_categorical(ytraining,classes)
ytest = keras.utils.to_categorical(ytest,classes)

#model layers
model.add(Dense(512, input_shape = (784,), activation = 'sigmoid'))
model.add(Dropout(0.2))
model.add(Dense(512, activation = 'sigmoid'))
model.add(Dropout(0.2))
model.add(Dense(10, activation = 'softmax'))

model.compile(loss = 'categorical_crossentropy', optimizer = 'sgd',metrics = ['accuracy'])

fit = model.fit(xtraining[0:n_input_images],ytraining[0:n_input_images],batch_size=batch,epochs = epochs, verbose = 1)

model.save('model.h5')