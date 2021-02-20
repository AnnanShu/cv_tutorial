#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

void test01()
{
    Mat img = imread("/Users/annanshu/Documents/picture/box_ball.jpg");
    if(!img.data)
    {
        std::cout << "This image is not existed" << std::endl;
        return ;
    }
    int im_row = img.rows;
    unsigned int im_col = img.cols;
    std::cout <<"The image height is: " << im_row << " and the witdh is " << im_col << std::endl;
//    namedWindow("input image", WINDOW_AUTOSIZE);
    imshow("[img]", img);
//    namedWindow("output window", WINDOW_AUTOSIZE);
    Mat output_image;
    cvtColor(img, output_image, COLOR_BGR2GRAY);
    imshow("output_window", output_image);

    waitKey(0);
}

int main()
{
    test01();
    return 0;
}