//
// Created by Annan Shu on 2021/2/21.
//
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

/*
 * Threshold operation
 *  - threshold binary
 *  - truncate
 *  - threshold to zero
 *  - threshold to zero inverse
 *
 * */

const char input_image[] = "/Users/annanshu/Documents/picture/03.jpg";
const char input_image2[] = "/Users/annanshu/Documents/picture/02.jpg";
const char input_win[] = "Input Image";
const char output_win[] = "Threshold ";

int threshold_value = 127;
const int threshold_max = 255;
int thresh_type = 2;
const int thresh_max = 5;
Mat src, gray_src, dst;

void threshold_demo(int, void*);

void test01()
{
    src = imread(input_image);
    if (src.empty()){
        cout << "Couldn't load the image: " << input_image << endl;
        return;
    }
    namedWindow(input_win, WINDOW_AUTOSIZE);
    namedWindow(output_win, WINDOW_AUTOSIZE);
    imshow(input_win, src);
    createTrackbar("Threshold Type: ", output_win, &thresh_type, thresh_max, threshold_demo);
    createTrackbar("Threshold Value: ", output_win, &threshold_value, threshold_max, threshold_demo);
    waitKey(0);
}

void threshold_demo(int, void*){
    cvtColor(src, gray_src, COLOR_BGR2GRAY);
    threshold(gray_src, dst, threshold_value, threshold_max, thresh_type);
    imshow(output_win, dst);
}


