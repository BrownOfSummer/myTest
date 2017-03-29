#! /usr/bin/env python

import tensorflow as tf
import numpy as np
import os
import time
import datetime
import data_helpers
from text_cnn import TextCNN
from tensorflow.contrib import learn

# Parameters
# ==================================================

# Data loading params
tf.flags.DEFINE_string("positive_data_file", "../random_data/random_1_t_R.csv", "Data source for the positive data.")
tf.flags.DEFINE_string("negative_data_file", "../random_data/random_1_t_W.csv", "Data source for the negative data.")
tf.flags.DEFINE_string("qr_data_file", "../random_data/random_1_q_R.csv", "Data source for the right test data.")
tf.flags.DEFINE_string("qw_data_file", "../random_data/random_1_q_W.csv", "Data source for the wrong test data.")

# Model Hyperparameters
tf.flags.DEFINE_integer("embedding_dim", 128, "Dimensionality of character embedding (default: 128)")
tf.flags.DEFINE_string("filter_sizes", "3,4,5", "Comma-separated filter sizes (default: '3,4,5')")
tf.flags.DEFINE_integer("num_filters", 128, "Number of filters per filter size (default: 128)")
tf.flags.DEFINE_float("dropout_keep_prob", 0.5, "Dropout keep probability (default: 0.5)")

# Training parameters
tf.flags.DEFINE_integer("batch_size", 64, "Batch Size (default: 64)")
tf.flags.DEFINE_integer("evaluate_every", 100, "Evaluate model on dev set after this many steps (default: 100)")
tf.flags.DEFINE_integer("checkpoint_every", 50, "Save model after this many steps (default: 100)")
tf.flags.DEFINE_integer("num_checkpoints", 2, "Number of checkpoints to store (default: 5)")
tf.flags.DEFINE_integer("num_epochs", 15, "Number of training epochs (default: 200)")
tf.flags.DEFINE_float("right_weight", 15.0, "The importance of right data (default: 2.0)")
tf.flags.DEFINE_float("l2_reg_lambda", 15.0, "L2 regularization lambda (default: 3.0)")
# Misc Parameters
tf.flags.DEFINE_boolean("allow_soft_placement", True, "Allow device soft device placement")
tf.flags.DEFINE_boolean("log_device_placement", False, "Log placement of ops on devices")

FLAGS = tf.flags.FLAGS
FLAGS._parse_flags()
print("\nParameters:")
for attr, value in sorted(FLAGS.__flags.items()):
    print("{}={}".format(attr.upper(), value))
print("")


# Data Preparation
# ==================================================
start_train = time.time()
# Load data
print("Loading data...")
x_train_r, y_train_r = data_helpers.load_data_and_labels_for_eval(FLAGS.positive_data_file, 'right')
x_train_w, y_train_w = data_helpers.load_data_and_labels_for_eval(FLAGS.negative_data_file, 'wrong')
x_test_r, y_test_r = data_helpers.load_data_and_labels_for_eval(FLAGS.qr_data_file, 'right')
x_test_w, y_test_w = data_helpers.load_data_and_labels_for_eval(FLAGS.qw_data_file, 'wrong')
size = 64 # use the strict size for experiment
print('size =',size)
"""For the training data, without random shuffle"""
vocab_processor = learn.preprocessing.VocabularyProcessor(size)
x = np.array(list(vocab_processor.fit_transform(x_train_r + x_train_w)))
x_train_r = np.array(list(vocab_processor.transform(x_train_r)))
y_train_r = np.array(y_train_r) * FLAGS.right_weight # multiply the weight of the right data
x_train_w = np.array(list(vocab_processor.transform(x_train_w)))
y_train_w = np.array(y_train_w)

"""For testing data, without random shuffle"""
x_test_r = np.array(list(vocab_processor.transform(x_test_r)))
y_test_r = np.array(y_test_r)
x_test_w = np.array(list(vocab_processor.transform(x_test_w)))
y_test_w = np.array(y_test_w)
print("Vocabulary Size: {:d}".format(len(vocab_processor.vocabulary_)))
print("Train/Dev split: {:d}/{:d}".format(len(y_train_w) + len(y_train_r), len(y_test_w)+len(y_test_r)))

# Training
# ==================================================

with tf.Graph().as_default():
    session_conf = tf.ConfigProto(
      allow_soft_placement=FLAGS.allow_soft_placement,
      log_device_placement=FLAGS.log_device_placement)
    sess = tf.Session(config=session_conf)
    with sess.as_default():
        cnn = TextCNN(
            sequence_length=x_train_r.shape[1],
            num_classes=y_train_r.shape[1],
            vocab_size=len(vocab_processor.vocabulary_),
            embedding_size=FLAGS.embedding_dim,
            filter_sizes=list(map(int, FLAGS.filter_sizes.split(","))),
            num_filters=FLAGS.num_filters,
            l2_reg_lambda=FLAGS.l2_reg_lambda)

        # Define Training procedure
        global_step = tf.Variable(0, name="global_step", trainable=False)
        optimizer = tf.train.AdamOptimizer(1e-3)
        grads_and_vars = optimizer.compute_gradients(cnn.loss)
        train_op = optimizer.apply_gradients(grads_and_vars, global_step=global_step)

        # Output directory for models and summaries
        timestamp = str(int(time.time()))
        out_dir = os.path.abspath(os.path.join(os.path.curdir, "runs", timestamp))
        print("Writing to {}\n".format(out_dir))

        # Summaries for loss and accuracy
        loss_summary = tf.summary.scalar("loss", cnn.loss)
        acc_summary = tf.summary.scalar("accuracy", cnn.accuracy)

        # Train Summaries
        #train_summary_op = tf.summary.merge([loss_summary, acc_summary, grad_summaries_merged])
        train_summary_op = tf.summary.merge([loss_summary, acc_summary])
        train_summary_dir = os.path.join(out_dir, "summaries", "train")
        train_summary_writer = tf.summary.FileWriter(train_summary_dir, sess.graph)
        
        # Test summaries
        qr_summary_op = tf.summary.merge([loss_summary, acc_summary])
        qr_summary_dir = os.path.join(out_dir, "summaries", "qr")
        qr_summary_writer = tf.summary.FileWriter(qr_summary_dir, sess.graph)
        qw_summary_op = tf.summary.merge([loss_summary, acc_summary])
        qw_summary_dir = os.path.join(out_dir, "summaries", "qw")
        qw_summary_writer = tf.summary.FileWriter(qw_summary_dir, sess.graph)

        # Checkpoint directory. Tensorflow assumes this directory already exists so we need to create it
        checkpoint_dir = os.path.abspath(os.path.join(out_dir, "checkpoints"))
        checkpoint_prefix = os.path.join(checkpoint_dir, "model")
        if not os.path.exists(checkpoint_dir):
            os.makedirs(checkpoint_dir)
        saver = tf.train.Saver(tf.global_variables(), max_to_keep=FLAGS.num_checkpoints)

        # Write vocabulary
        vocab_processor.save(os.path.join(out_dir, "vocab"))

        # Initialize all variables
        sess.run(tf.global_variables_initializer())

        def train_step(x_batch, y_batch):
            """
            A single training step
            """
            feed_dict = {
              cnn.input_x: x_batch,
              cnn.input_y: y_batch,
              cnn.dropout_keep_prob: FLAGS.dropout_keep_prob,
            }
            _, step, summaries, loss, accuracy = sess.run(
                [train_op, global_step, train_summary_op, cnn.loss, cnn.accuracy],
                feed_dict)
            time_str = datetime.datetime.now().isoformat()
            print("{}: step {}, loss {:g}, acc {:g}".format(time_str, step, loss, accuracy))
            train_summary_writer.add_summary(summaries, step)
        
        def qr_test_step(x_batch, y_batch, writer=None):
            """
            Evaluates model on a dev set
            """
            feed_dict = {
              cnn.input_x: x_batch,
              cnn.input_y: y_batch,
              cnn.dropout_keep_prob: 1.0,
            }
            step, summaries, loss, accuracy = sess.run(
                [global_step, qr_summary_op, cnn.loss, cnn.accuracy],
                feed_dict)
            time_str = datetime.datetime.now().isoformat()
            print("{}: step {}, loss {:g}, acc {:g}".format(time_str, step, loss, accuracy))
            if writer:
                writer.add_summary(summaries, step)
            return accuracy, loss
        def qw_test_step(x_batch, y_batch, writer=None):
            """
            Evaluates model on a dev set
            """
            feed_dict = {
              cnn.input_x: x_batch,
              cnn.input_y: y_batch,
              cnn.dropout_keep_prob: 1.0,
            }
            step, summaries, loss, accuracy = sess.run(
                [global_step, qw_summary_op, cnn.loss, cnn.accuracy],
                feed_dict)
            time_str = datetime.datetime.now().isoformat()
            print("{}: step {}, loss {:g}, acc {:g}".format(time_str, step, loss, accuracy))
            if writer:
                writer.add_summary(summaries, step)

        # Generate batches
        len_train_r = len(y_train_r)
        len_train_w = len(y_train_w)
        for _ in range(FLAGS.num_epochs):
            # to reduce the wrong data to same length of the right data
            shuffle_inx = np.random.permutation(np.arange(len_train_w))
            x_train = x_train_w[shuffle_inx]
            y_train = y_train_w[shuffle_inx]
            shuffle_inx = np.random.permutation(np.arange(len_train_r))
            x_train = np.array(list(x_train[shuffle_inx]) + list(x_train_r)) # array->list->array
            y_train = np.array(list(y_train[shuffle_inx]) + list(y_train_r))
            assert len(y_train) == len(x_train)
            batches = data_helpers.batch_iter(
                list(zip(x_train, y_train)), FLAGS.batch_size, 1)
            # Training loop. For each batch...
            for batch in batches:
                x_batch, y_batch = zip(*batch)
                train_step(x_batch, y_batch)
                current_step = tf.train.global_step(sess, global_step)
                if current_step % FLAGS.evaluate_every == 0:
                    print("\nEvaluation:")
                    #this_accuracy, this_loss = qr_test_step(x_test_r, y_test_r, writer=qr_summary_writer)
                    #qw_test_step(x_test_w, y_test_w, writer=qw_summary_writer)
                    print("")
                if current_step % FLAGS.checkpoint_every == 0:
                    path = saver.save(sess, checkpoint_prefix, global_step=current_step)
                    print("Saved model checkpoint to {}\n".format(path))
end_train = time.time()
print('Train costs', end_train - start_train)
