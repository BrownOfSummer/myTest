#! /usr/bin/env python

import tensorflow as tf
import numpy as np
import os
import time
import datetime
import data_helpers
from text_cnn import TextCNN
from tensorflow.contrib import learn
import csv

# Parameters
# ==================================================

# Data Parameters
tf.flags.DEFINE_string("positive_data_file", "../random_data/random_1_q_R.csv", "Data source for the positive data.")
tf.flags.DEFINE_string("negative_data_file", "../random_data/random_1_q_W.csv", "Data source for the positive data.")

# Eval Parameters
tf.flags.DEFINE_integer("batch_size", 64, "Batch Size (default: 64)")
tf.flags.DEFINE_string("checkpoint_dir", "./runs/1489134170/checkpoints/", "Checkpoint directory from training run")
#tf.flags.DEFINE_boolean("eval_train", False, "Evaluate on all training data")
tf.flags.DEFINE_boolean("eval_train", True, "Evaluate on all training data")

# Misc Parameters
tf.flags.DEFINE_boolean("allow_soft_placement", True, "Allow device soft device placement")
tf.flags.DEFINE_boolean("log_device_placement", False, "Log placement of ops on devices")


FLAGS = tf.flags.FLAGS
FLAGS._parse_flags()
print("\nParameters:")
for attr, value in sorted(FLAGS.__flags.items()):
    print("{}={}".format(attr.upper(), value))
print("")

start_eval = time.time()
# CHANGE THIS: Load data. Load your own data here
if FLAGS.eval_train:
    x_raw, y_test = data_helpers.load_data_and_labels_for_eval(FLAGS.positive_data_file, 'right')
    #x_raw, y_test = data_helpers.load_data_and_labels_for_eval(FLAGS.negative_data_file, 'wrong')

    y_test = np.argmax(y_test, axis=1)
else:
    x_raw = ["a masterpiece four years in the making", "everything is off."]
    y_test = [1, 0]

# Map data into vocabulary
vocab_path = os.path.join(FLAGS.checkpoint_dir, "..", "vocab")
vocab_processor = learn.preprocessing.VocabularyProcessor.restore(vocab_path)
x_test = np.array(list(vocab_processor.transform(x_raw)))

print("\nEvaluating...\n")

# Evaluation
# ==================================================
"""Get the checkpoint file"""
try:
    # If the path unchanged
    checkpoint_file = tf.train.latest_checkpoint(FLAGS.checkpoint_dir)
except:
    # If the checkpoint path changed
    ckpt = tf.train.get_checkpoint_state(FLAGS.checkpoint_dir)
    if ckpt and ckpt.model_checkpoint_path:
        latest_checkpoint = ckpt.model_checkpoint_path.split('/')[-1] # model-1350
        global_step = latest_checkpoint.split('-')[-1] # 1350
        checkpoint_file = os.path.join(FLAGS.checkpoint_dir, latest_checkpoint) # path + model-1350
        print(checkpoint_file)
    else:
        print('No checkpoint file found!')

graph = tf.Graph()
with graph.as_default():
    session_conf = tf.ConfigProto(
      allow_soft_placement=FLAGS.allow_soft_placement,
      log_device_placement=FLAGS.log_device_placement)
    sess = tf.Session(config=session_conf)
    with sess.as_default():
        # Load the saved meta graph and restore variables
        saver = tf.train.import_meta_graph("{}.meta".format(checkpoint_file)) # load model-1350-meta
        #saver = tf.train.import_meta_graph('/Users/li_pengju/tensorflow1.0/sample/mission_filter/tmp/1489639416/checkpoints/model-1300.meta')
        saver.restore(sess, checkpoint_file)
        #saver.restore(sess, './1489639416/checkpoints/model-1300')

        # Get the placeholders from the graph by name
        input_x = graph.get_operation_by_name("input_x").outputs[0]
        # input_y = graph.get_operation_by_name("input_y").outputs[0]
        dropout_keep_prob = graph.get_operation_by_name("dropout_keep_prob").outputs[0]

        # Tensors we want to evaluate
        predictions = graph.get_operation_by_name("output/predictions").outputs[0]

        # Generate batches for one epoch
        batches = data_helpers.batch_iter(list(x_test), FLAGS.batch_size, 1, shuffle=False)

        # Collect the predictions here
        all_predictions = []

        for x_test_batch in batches:
            batch_predictions = sess.run(predictions, {input_x: x_test_batch, dropout_keep_prob: 1.0})
            all_predictions = np.concatenate([all_predictions, batch_predictions])

eval_time = time.time() - start_eval
print(eval_time, eval_time/len(y_test))
# Print accuracy if y_test is defined
if y_test is not None:
    correct_predictions = float(sum(all_predictions == y_test))
    print("Total number of test examples: {}".format(len(y_test)))
    print("Accuracy: {:g}".format(correct_predictions/float(len(y_test))))

# Save the evaluation to a csv
predictions_human_readable = np.column_stack((np.array(x_raw), all_predictions))
out_path = os.path.join(FLAGS.checkpoint_dir, "..", "prediction.csv")
print("Saving evaluation to {0}".format(out_path))
with open(out_path, 'w') as f:
    csv.writer(f).writerows(predictions_human_readable)
