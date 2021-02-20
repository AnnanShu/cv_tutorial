//
// Created by Annan Shu on 2021/1/30.
//

#include <random>
#include <vector>
#include "ann.h"

void NN:: data_loader(const string &path)
{
    ifstream file(path);
    // put data to vector
    vector<vector<float>> dataset;
    string ss;
    while (getline(file, ss)){
        vector<float> data;
        stringstream w(ss);
        float temp;
        while(w >> temp)
        {
            data.push_back(temp);
        }
        // data.size() == 0; should be following
        if(data.empty()){
            continue;
        }
        dataset.push_back(data);
    }
    // shuffle data
    // srand(static_cast<unsigned int> (time(0)));
    shuffle(dataset.begin(), dataset.end(), std::mt19937(std::random_device()()));
    // transfer vector as Mat then save to training set and label
    int rows = static_cast<int>(dataset.size());
    int cols = static_cast<int>(dataset[0].size() - 1);
    // create dataset and label set
    Mat train_data(rows, cols, CV_32FC1);
    Mat labels(rows, 1, CV_32FC1);
    //load data
    auto it = dataset.begin();
    for (int i = 0; i < rows; ++i) {
        // original not auto but float
        auto *data = train_data.ptr<float>(i);
        auto *label = labels.ptr<float>(i);
        for (int j = 0; j < cols + 1; ++j) {
            data[j] = (*it)[j];
            if (cols==j){
                label[0] = (*it)[j];
            }
        }
        it++;
    }
    this->data_ptr = make_shared<Mat>(train_data);
    this->label_ptr = make_shared<Mat>(labels);

}

void NN::add_hidden_layer(const vector<size_t> &num_hiddens) {
//    hiddens_
    hiddens_.clear();
    hiddens_.assign(num_hiddens.begin(), num_hiddens.end());
}

void NN::initial_layer(const size_t &input, const size_t &output) {
    RNG rnger(getTickCount());
    // create weight matrix
    Mat W(static_cast<int>(input), static_cast<int>(output), CV_32FC1);
    // create bias matrix
    Mat b(1, static_cast<int>(output), CV_32FC1, 1.f);
    // weight initialization
    // a: upper bound/ normal mean    b:lower bound / normal std
    rnger.fill(W, RNG::UNIFORM, cv::Scalar::all(-1.f/ sqrt(input)),
               cv::Scalar::all(1.f/ sqrt(input)));
    W_.push_back(W);
    b_.push_back(b);
}

void NN::initial_networks() {
    // initialize the number of neurons
    this->input_ = this->data_ptr->cols;

    // initialize weight
    RNG rnger(getTickCount());
    if (!this->hiddens_.empty()){
        size_t cur_row = this->input_;
        for (unsigned long hidden : this->hiddens_){
            initial_layer(cur_row, hidden);
            cur_row = hidden;
        }
        initial_layer(cur_row, this->classes_);
    }else{
        initial_layer(this->input_, this->classes_);
    }
}

void NN::relu(Mat &X) {
    // get mask for those value greater than 0
//    Mat mask = (X > 0) / 255;
    Mat mask = (X > 0);
    // convert data to float
    Mat mask2f;
    mask.convertTo(mask2f, CV_32FC1);
    //compute relu and out
    multiply(X, mask2f, X);
}

Mat NN::mat_sum(const Mat &X, const int &axis, const int &dtype) {
    Mat sum, sum_expend;
    reduce(X, sum, axis, REDUCE_SUM, dtype);
    if(axis){
        repeat(sum, 1, X.cols, sum_expend);
    }else{
        repeat(sum, X.rows, 1, sum_expend);
    }
    return sum_expend;
}

Mat NN::mat_max(const Mat &X, const int &axis, const int &dtype) {
    Mat max, max_expend;
    // get each line's maximum value
    reduce(X, max, axis, REDUCE_MAX, dtype);
    // matrix augmentation
    if(axis){
        // src, ny, nx, output
        repeat(max, 1, X.cols, max_expend);
    }else{
        repeat(max, X.rows, 1, max_expend);
    }
    return max_expend;
}

int NN::argmax(const Mat& row, float &max_value) {
    int max_point2f[2] = { 0 };
    auto dmax = static_cast<double>(max_value);
    minMaxIdx(row, nullptr, &dmax, nullptr, max_point2f);
    return max_point2f[1];
}

Mat NN::argmaxes(Mat &out) {
    Mat max_row;
    reduce(out, max_row, 1, REDUCE_MAX, CV_32FC1);

    Mat predict(out.rows, 1, CV_32FC1);
    for (int i = 0; i < out.rows; ++i) {
        auto *data = predict.ptr<float>(i);
        auto *max = max_row.ptr<float>(i);
        data[0] = static_cast<float>(argmax(out.row(i), max[0]));
    }

    return predict;
}

void NN::softmax(Mat &out) {
    //
    Mat row_max_expend = mat_max(out, 1, CV_32FC1);
    out -= row_max_expend;
    // input, output
    exp(out, out);
    // guiyi
    Mat row_sum_expend = mat_sum(out, 1, CV_32FC1);
    out /= row_sum_expend;
}

void NN::forward(Mat &X) {
    this->out_.clear();
    this->out_.push_back(X);
    auto it_w = this->W_.begin();
    auto it_b = this->b_.begin();

    Mat out = X;
    size_t num_layers = 1;
    for(; it_w != this->W_.end(); ++it_w, ++it_b){
        // y = x * w + b
        out = out * (*it_w);
        Mat b;
        repeat(*it_b, out.rows, 1, b);
        out += b;

        if (num_layers < this->W_.size()){
            this->relu(out);
            this->out_.push_back(out); // save output for each step;
        }

        ++num_layers;
    }
    // calculate softmax output
    softmax(out);
    this->out_.push_back(out);
}

float NN::L2_regular() {
    auto it = this->W_.begin();
    float regular = 0.0;
    while(it != this->W_.end()){
        Mat temp;
        multiply(*it, *it, temp);
        regular += static_cast<float>(sum(temp)[0]);
        ++it;
    }
    return regular;
}

float NN::loss(Mat &y) {
    float sum = 0.0;
    Mat out = this->out_.back();
    for (int i = 0; i < y.rows; ++i) {
        auto *data = y.ptr<float>(i);
        auto *predict = out.ptr<float>(i);
        
        sum -= log(predict[static_cast<int>(data[0])]);
    }
    return sum;
}

void NN::backward() {
    auto it_out = out_.rbegin();        // get output iterator
    auto it_w = W_.rbegin();            // get weights iterator
    int num_trains = it_out->rows;      // the size of training size
    dW_.clear(); db_.clear();           // clear current gradient

    Mat dL = (*it_out).clone();         // 后层积累梯度
    // calculate softmax classifier layer's gradient
    for (int i = 0; i < dL.rows; ++i) {
        // Use auto when initializing with a template cast to avoid duplicating the type name
        auto *data = dL.ptr<float>(i);
        auto *l = label_ptr->ptr<float>(i);

        data[static_cast<int>(l[0])] -= 1;
    }
    Mat db;         // bias layer gradient
    Mat dw;
    Mat W = *it_w;  // save previous layer's weight
    while (it_w != W_.rend()){
        ++it_out;
        if (it_w != W_.rend()){
            dL = dL * W.t();
        }
    }

}
// export OpenCV_DIR="/opt/homebrew/Cellar/opencv/4.5.1_2/lib/cmake/opencv4"