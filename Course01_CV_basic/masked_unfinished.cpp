//
// Created by Annan Shu on 2021/2/17.
//

#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

const char image_path[] = "/Users/annanshu/Documents/picture/box_ball.jpg";

void test01()
{
    Mat src, dest;
    src = imread(image_path);
    if (!src.data)
    {
        cout << "Couldn't load the image, please check the path you typed." << endl;
        return;
    }
//    imshow("Input Image", src);
    int column = src.cols, rows = src.rows, channels = src.channels();
    cout << "0" << endl;
    waitKey(0);
}

int main()
{
    test01();
    return 0;
}