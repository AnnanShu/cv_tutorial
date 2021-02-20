#include <__bit_reference>
//
// Created by Annan Shu on 2021/2/12.
//

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <string>

using namespace cv;
using namespace std;

const char* filepath = "/Users/annanshu/Documents/picture/box_ball.jpg";

int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;

Mat src; Mat dst;
char window_name[] = "Smoothing demo";

int display_caption(const char* caption);
int display_dst(int delay);

int smooth()
{
    namedWindow(window_name, WINDOW_AUTOSIZE);
    src = imread(samples::findFile(filepath), IMREAD_COLOR);
    if (src.empty())
    {
        cout << "Error opening image" << endl;
        return EXIT_FAILURE;
    }
    return 1;



}

bool isPointInRect(const Point& pt, const Rect& rc)
{
    if (pt.x >= rc.x && pt.x <= (rc.x + rc.width - 1))
        if (pt.y >= rc.y && pt.y <= (rc.y + rc.height - 1))
            return true;

    return false;
}


int display_caption(const char* caption)
{
    dst = Mat::zeros(src.size(), src.type());
    Point a(2, 4);

    return 0;
}
