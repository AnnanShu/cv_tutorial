//
// Created by Annan Shu on 2021/2/21.
//

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

/*
 * image pyramid
 * zoom in: cv::pyrUp
 * zoom in: cv::pyrDown
 * gaussian pyramid: down-sample from bottom to top
 *      - apply gaussian blur to current layer
 *      - remove even row and col of current layer   r/2 * c/2
 * DOG (difference of gaussian)
 * */

const char input_image[] = "/Users/annanshu/Documents/picture/03.jpg";
const char input_image2[] = "/Users/annanshu/Documents/picture/02.jpg";
const char input_win[] = "Input picture";
const char output_win[] = "DOG";


void test01()
{
    Mat src, dst, gray_src, g1, g2;
    src = imread(input_image);
    if (src.empty()){
        cout << "Couldn't load the image: " << input_image << endl;
        return;
    }
    namedWindow(input_win, WINDOW_AUTOSIZE);
    namedWindow(output_win, WINDOW_AUTOSIZE);

    // down-sampling image then use dog to extract feature
    pyrDown(src, src, Size(src.cols/2, src.rows/2));
    imshow(input_win, src);
//    imshow(output_win, dst);
//    pyrUp(src, dst, Size(src.cols*2, src.rows*2));
//    imshow(output_win, dst);

    // difference of gaussian
    cvtColor(src, gray_src, COLOR_BGR2GRAY);
    GaussianBlur(gray_src, g1, Size(3, 3), 0, 0);
    GaussianBlur(g1, g2, Size(3, 3), 0, 0);
    subtract(g1, g2, dst, Mat());
    normalize(dst, dst, 255, 0, NORM_MINMAX);
    imshow(output_win, dst);
    waitKey(0);
}

