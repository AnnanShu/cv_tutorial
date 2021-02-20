//
// Created by Annan Shu on 2021/2/20.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const char image_path[] = "/Users/annanshu/Documents/picture/01.jpg";
const char image_path2[] = "/Users/annanshu/Documents/picture/02.jpg";

Mat src, dst;


void test01()
{
    // Mat is an data structure of image
    src = imread(image_path);
    if (!src.data)
    {
        cout << "Couldn't load the image, please check the path you typed." << endl;
        return;
    }
    cout << src.size() << " " << src.type() << " " << src.channels() << endl;
    imshow("input show", src);
    const char window_name[] = "Morphology demo";

    Mat kernel = getStructuringElement(MORPH_RECT, Size(11, 11), Point(-1, -1));
    // open operator: erosion then dilation
//    morphologyEx(src, dst, MORPH_OPEN, kernel);
    // close operator: dilation then erosion
//    morphologyEx(src, dst, MORPH_CLOSE, kernel);
    // gradient operator: dilation minus erosion
//    morphologyEx(src, dst, MORPH_GRADIENT, kernel);
    // top hat: original - open
//    morphologyEx(src, dst, MORPH_TOPHAT, kernel);
    // black hat: close - original
    morphologyEx(src, dst, MORPH_BLACKHAT, kernel);

    namedWindow(window_name, WINDOW_AUTOSIZE);
    imshow(window_name, dst);

    waitKey(0);
}



int main()
{
    test01();
    return 0;
}