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
tf.flags.DEFINE_boolean("re_train", True, "Evaluate on all training data")
tf.flags.DEFINE_float("dropout_keep_prob", 0.5, "Dropout keep probability (default: 0.5)")
tf.flags.DEFINE_integer("checkpoint_every", 50, "Save model after this many steps (default: 100)")
tf.flags.DEFINE_integer("num_checkpoints", 2, "Number of checkpoints to store (default: 5)")
tf.flags.DEFINE_integer("num_epochs", 2, "Number of training epochs (default: 200)")
tf.flags.DEFINE_string("checkpoint_dir", "./", "Checkpoint directory from training run")

# Misc Parameters
tf.flags.DEFINE_boolean("allow_soft_placement", True, "Allow device soft device placement")
tf.flags.DEFINE_boolean("log_device_placement", False, "Log placement of ops on devices")


FLAGS = tf.flags.FLAGS
FLAGS._parse_flags()
print("\nParameters:")
for attr, value in sorted(FLAGS.__flags.items()):
    print("{}={}".format(attr.upper(), value))
print("")

start_train = time.time()
# CHANGE THIS: Load data. Load your own data here
if FLAGS.re_train:
    x_raw, y_test = data_helpers.load_data_and_labels_for_eval(FLAGS.positive_data_file, 'right')
    #x_raw, y_test = data_helpers.load_data_and_labels_for_eval(FLAGS.negative_data_file, 'wrong')
    y_test = np.array(y_test)
    #y_test = np.argmax(y_test, axis=1)
else:
    x_raw = ["a masterpiece four years in the making", "everything is off."]
    y_test = [1, 0]

# Map data into vocabulary
vocab_path = os.path.join(FLAGS.checkpoint_dir, "..", "vocab")
vocab_processor = learn.preprocessing.VocabularyProcessor.restore(vocab_path)
x_test = np.array(list(vocab_processor.transform(x_raw)))

print("\nRetraining...\n")

# Evaluation
# ==================================================
"""Get the checkpoint file"""
try:
    # If the path unchanged
    checkpoint_file = tf.train.latest_checkpoint(FLAGS.checkpoint_dir)
    save_step = checkpoint_file.split('/')[-1].split('-')[-1]
    print('checkpoint_file:',checkpoint_file)
except:
    # If the checkpoint path changed
    ckpt = tf.train.get_checkpoint_state(FLAGS.checkpoint_dir)
    if ckpt and ckpt.model_checkpoint_path:
        latest_checkpoint = ckpt.model_checkpoint_path.split('/')[-1] # model-1350
        save_step = latest_checkpoint.split('-')[-1] # 1350
        checkpoint_file = os.path.join(FLAGS.checkpoint_dir, latest_checkpoint) # path + model-1350
        print('checkpoint_file:',checkpoint_file)
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
        input_y = graph.get_operation_by_name("input_y").outputs[0]
        dropout_keep_prob = graph.get_operation_by_name("dropout_keep_prob").outputs[0]

        # Tensors we want to retrain
        predictions = graph.get_operation_by_name("output/predictions").outputs[0]
        loss = graph.get_operation_by_name("loss/loss").outputs[0]
        accuracy = graph.get_operation_by_name("accuracy/accuracy").outputs[0]
        global_step = graph.get_operation_by_name("global_step").outputs[0]
        #print(global_step, sess.run(global_step))

        # Get the train_op
        train_op = tf.get_collection('train_op')[0]

        # Define the one train operation
        def train_step(x_batch, y_batch):
            """
            A single training step
            """
            feed_dict = {
              input_x: x_batch,
              input_y: y_batch,
              dropout_keep_prob: FLAGS.dropout_keep_prob,
            }
            _, step, summaries, batch_loss, batch_accuracy = sess.run(
                [train_op, global_step, train_summary_op, loss, accuracy],
                feed_dict)
            time_str = datetime.datetime.now().isoformat()
            print("{}: step {}, loss {:g}, acc {:g}".format(time_str, step, batch_loss, batch_accuracy))
            train_summary_writer.add_summary(summaries, step)

        # Collect the predictions here
        all_predictions = []
        # Output directory for models and summaries
        timestamp = str(int(time.time()))
        out_dir = os.path.abspath(os.path.join(os.path.curdir, "runs", timestamp))
        print("Writing to {}\n".format(out_dir))
        # Summaries for loss and accuracy
        loss_summary = tf.summary.scalar("loss", loss)
        acc_summary = tf.summary.scalar("accuracy", accuracy)

        # Train Summaries
        train_summary_op = tf.summary.merge([loss_summary, acc_summary])
        train_summary_dir = os.path.join(out_dir, "summaries", "train")
        train_summary_writer = tf.summary.FileWriter(train_summary_dir, sess.graph)

        # Checkpoint directory. Tensorflow assumes this directory already exists so we need to create it
        checkpoint_dir = os.path.abspath(os.path.join(out_dir, "checkpoints"))
        checkpoint_prefix = os.path.join(checkpoint_dir, "model")
        if not os.path.exists(checkpoint_dir):
            os.makedirs(checkpoint_dir)
        saver = tf.train.Saver(tf.global_variables(), max_to_keep=FLAGS.num_checkpoints)

        # Write vocabulary
        vocab_processor.save(os.path.join(out_dir, "vocab"))

        # Generate batches for one epoch
        batches = data_helpers.batch_iter(list(zip(x_test, y_test)), FLAGS.batch_size, FLAGS.num_epochs, shuffle=False)
        for batch in batches:
            x_test_batch, y_test_batch = zip(*batch)
            train_step(x_test_batch, y_test_batch)
            current_step = tf.train.global_step(sess, global_step)
            if (current_step - int(save_step)) % FLAGS.checkpoint_every == 0:
                path = saver.save(sess, checkpoint_prefix, global_step=current_step)
                print("Saved model checkpoint to {}\n".format(path))

train_time = time.time() - start_train
