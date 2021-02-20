#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

const char image_path[] = "/Users/annanshu/Documents/picture/01.jpg";
const char image_path2[] = "/Users/annanshu/Documents/picture/02.jpg";

Mat src1, src2, src2_resized, dst;
const int alpha_slider_max = 300;
int alpha_slider;
double alpha, beta;
void on_trackbar(char* window_name, int, void*);

void test01()
{
    // Mat is an data structure of image
    src1 = imread(image_path);
    src2 = imread(image_path2);
    if (!src1.data) {cout << "Couldn't load the image 1, please check the path you typed." << endl;return;}
    if (!src2.data) {cout << "Couldn't load the image 2, please check the path you typed." << endl;return;}

    resize(src2, src2_resized, src1.size());
//    imshow("input show 2", src2);
//    imshow("input show 2 after resized", src2_resized);

    char trackbar_name[] = "This is the blended track bar";
    char window_name[] = "Linear Blended";

    namedWindow(window_name, WINDOW_AUTOSIZE);
    createTrackbar(trackbar_name, window_name, &alpha_slider, alpha_slider_max,
                   reinterpret_cast<TrackbarCallback>(on_trackbar));
    on_trackbar(window_name, alpha_slider, nullptr);
    waitKey(0);
}

void on_trackbar(char* window_name, int, void*)
{
    alpha = (double) alpha_slider / alpha_slider_max;
    beta = 1 - alpha;
    addWeighted(src1, alpha, src2_resized, beta, 0.0, dst);
    imshow(window_name, dst);
}


int main()
{
    test01();
    return 0;
}