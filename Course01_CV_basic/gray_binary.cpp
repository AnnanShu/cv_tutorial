//
// Created by Annan Shu on 2021/2/21.
//

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;

const char input_image[] = "/Users/annanshu/Documents/picture/01.jpg";
const char input_image2[] = "/Users/annanshu/Documents/picture/02.jpg";

void test01()
{
    Mat src, gray_src, bin_src, bin_src2;
    src = imread(input_image);
    if (src.empty()){
        cout << "Couldn't load the image: " << input_image << endl;
        return;
    }
//    RNG rng(getTickCount());
    const char input_win[] = "Input Image";
    const char output_win[] = "Gray Image";
    const char bin_win[] = "Binary Image";

    cvtColor(src, gray_src, COLOR_BGR2GRAY);
    adaptiveThreshold(gray_src, bin_src, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
    adaptiveThreshold(~gray_src, bin_src2, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
    namedWindow("binary_src2", WINDOW_AUTOSIZE);
    namedWindow(output_win, WINDOW_AUTOSIZE);
    namedWindow(bin_win, WINDOW_AUTOSIZE);
    imshow("binary_src2", bin_src2);
    imshow(output_win, gray_src);
    imshow(bin_win, bin_src);
    waitKey(0);
    destroyAllWindows();
}
