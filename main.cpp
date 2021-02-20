#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const char image_path[] = "/Users/annanshu/Documents/picture/01.jpg";
const char image_path2[] = "/Users/annanshu/Documents/picture/02.jpg";

void test01()
{
    // Mat is an data structure of image
    Mat src, dst;
    src = imread(image_path);
    if (!src.data)
    {
        cout << "Couldn't load the image, please check the path you typed." << endl;
        return;
    }
    cout << src.size() << " " << src.type() << " " << src.channels() << endl;
    imshow("opencv show", src);
    
    waitKey(0);
}

int main()
{
    test01();
    return 0;
}