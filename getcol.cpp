#include</usr/include/opencv2/opencv.hpp>
#include <ctype.h>
#include "iostream"
#include <stdio.h>

using namespace std;
using namespace cv;

void on_mouse(int EVENT, int x, int y, int flags, void* userdata);


int main(int argc, char** argv)
{

	Mat src, hsv ;

        //载入，OPENCV2.0写法
    	if (argc < 2)
    	{
		//此处更改图片地址
		src = imread("mycat.png");
    	}
	else
	{
    		string InputPictureName = argv[1];
		src =  imread( InputPictureName );
	}

	namedWindow("【display】");
	setMouseCallback("【display】", on_mouse, &src);
	while (1)
	{
		imshow("【display】", src);
		waitKey(40);
	}
}


void on_mouse(int EVENT, int x, int y, int flags, void* userdata)
{
	Mat rgb,hsv;
	rgb = *(Mat*)userdata;
	Mat temp;
	cvtColor(*(Mat*)userdata, hsv, CV_RGB2HSV);
	Point p(x, y);
	switch (EVENT)
	{
		case EVENT_LBUTTONDOWN:
		{
		
			printf("b=%d\t", rgb.at<Vec3b>(p)[0]);
			printf("g=%d\t", rgb.at<Vec3b>(p)[1]);
			printf("r=%d\n", rgb.at<Vec3b>(p)[2]);
			
			printf("H=%d\t", hsv.at<Vec3b>(p)[0]);
			printf("S=%d\t", hsv.at<Vec3b>(p)[1]);
			printf("V=%d\n", hsv.at<Vec3b>(p)[2]);

			circle(rgb, p, 2, Scalar(255), 3);
		}
		break;

	}
} 
