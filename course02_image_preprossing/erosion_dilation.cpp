//
// Created by Annan Shu on 2021/2/20.
//
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const char image_path[] = "/Users/annanshu/Documents/picture/01.jpg";
const char image_path2[] = "/Users/annanshu/Documents/picture/02.jpg";
const char window_name[] = "output show";
Mat src, dst;
int max_size = 21;
int kernel_size = 3;
void Callback_demo(int, void*);

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
//    imshow("input show", src);

    namedWindow(window_name, WINDOW_AUTOSIZE);
    createTrackbar("Element Size: ", window_name, &kernel_size, max_size, Callback_demo);
    Callback_demo(0, nullptr);

    waitKey(0);
}

void Callback_demo(int, void*)
{
    int x = kernel_size * 2 + 1;
    Mat structureElement = getStructuringElement(MORPH_RECT, Size(x, x), Point(-1, -1));
    erode(src, dst, structureElement, Point(-1, -1), 1);
//    dilate(src, dst, structureElement, Point(-1, -1), 1);
    imshow(window_name, dst);
}


