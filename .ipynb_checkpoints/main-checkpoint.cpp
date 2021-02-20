#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const char image_path[] = "/Users/annanshu/Documents/picture/01.jpg";
const char image_path2[] = "/Users/annanshu/Documents/picture/02.jpg";
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
    imshow("input show", src);

    Callback_demo(0, nullptr);

    waitKey(0);
}

void Callback_demo(int, void*)
{
    int x = kernel_size * 2 + 1;
    Mat structureElement = getStructuringElement(MORPH_RECT, Size(x, x), Point(-1, -1));
    dilate(src, dst, structureElement, Point(-1, -1), 1);
    imshow("output show", dst);
}

int main()
{
    test01();
    return 0;
}