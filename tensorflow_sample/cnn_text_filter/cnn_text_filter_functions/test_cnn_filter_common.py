import os
import numpy as np
from cnn_filter_common import *
positive_data_file = "../random_data/new_split/t_R1.csv"
negative_data_file = "../random_data/new_split/t_W1.csv"

#split_text(positive_data_file, negative_data_file)
#generate_vocab(positive_data_file, negative_data_file)


#vocab_path = os.path.join("./vocab_dir/", "vocab")
#vocab_processor = learn.preprocessing.VocabularyProcessor.restore(vocab_path)
#print(vocab_processor.max_document_length)
training_r = "./right/training.log"
training_w = "./wrong/training.log"
#training_r = "../random_data/new_split/t_R1.csv"
#training_w = "../random_data/new_split/t_W1.csv"
#cnn_train(training_r, training_w)
cnn_retrain(training_r, training_w)
#cnn_query(positive_data_file, training_r)
