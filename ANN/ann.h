//
// Created by Annan Shu on 2021/1/30.
//

#ifndef ML_ANN_H
#define ML_ANN_H
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// size_t is actually an integer (long) variable vary in different architecture of systems 4/8 bit in 32/64 bit system

/*
 * This is an neural network implemented by c++
 * I will implement a lot of operations of the method
 * */
class NN {
public:
    explicit NN(size_t classes, size_t input=0,
       float reg = 0.005, float learning_rate=0.0001,
       size_t max_epoches = 5000, size_t batch_size = 128):
       input_(input), classes_(classes), reg_(reg), learning_rate_(learning_rate),
       max_epoches_(max_epoches), batch_size_(batch_size),
       data_ptr(nullptr), label_ptr(nullptr) {}
    ~NN()= default;

    void data_loader(const string &path);    // load data
    void add_hidden_layer(const vector<size_t> &num_hiddens={});    // add hidden layer
    void initial_networks();// initialize network
    void forward(Mat &x); // forward
    void backward();// backward
    float loss(Mat &y);    // compute loss
    void update_weight();   // update weights
    void train(const string& filepath, const vector<size_t> &num_hiddens);//train network
    void save_weights(const string &save_path);// save weights
    void load_weights(const string &load_path);// load weights
    Mat predict(Mat &data); // prediction
    // other method
    inline float get_learning_rate() const {return this->learning_rate_;}
    inline void set_learning_rate(float learning_rate) { this-> learning_rate_=learning_rate;}
    inline float get_reg() const {return this->reg_;}
    inline void set_reg(float reg){this->reg_ = reg;}
    inline size_t get_epoch() const {return this->max_epoches_;}

private:
    // network related function
    void get_batch(Mat &batch_X, Mat &batch_y);
    void initial_layer(const size_t &input, const size_t &output); // single layer initialization
    static void relu(Mat &X); // relu activation function
    static void softmax(Mat &out); // softmax classifier
    float L2_regular(); // l2 regularization

    // other matrix related methods
    // cal row/col sum
    static Mat mat_sum(const Mat &X, const int &axis, const int &dtype);
    //计算矩阵行/列方向的最大值，并进行矩阵增广
    static Mat mat_max(const Mat &X, const int &axis, const int &dtype);
    // argmax
    static int argmax(const Mat& row, float &max_value); // single line of sub_titles
    static Mat argmaxes(Mat &out);

    float reg_;             // regularization
    float learning_rate_;
    size_t max_epoches_;
    size_t batch_size_;

private:
    // input data, label data
    shared_ptr<Mat> data_ptr, label_ptr;
    size_t input_; // input size
    size_t classes_; // class number
    vector<size_t> hiddens_;

    vector<Mat> W_;     // save weights
    vector<Mat> b_;     // save bias
    vector<Mat> out_;   // save output of every layers
    vector<Mat> dW_;    // save gradient of every layer's weights
    vector<Mat> db_;    // save gradient of every layer's bias

};


#endif //ML_ANN_H
