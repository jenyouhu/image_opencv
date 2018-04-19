// OpenCV 文件头

#include </usr/include/opencv2/opencv.hpp>
#include "/usr/include/opencv2/imgproc/imgproc.hpp" 
#include "/usr/include/opencv/cv.h"                              
#include "/usr/include/opencv/highgui.h"  
#include "/usr/include/opencv/cvaux.h"  
#include "/usr/include/opencv/cxcore.h"  

//C语言系统头文件
#include <cmath>
#include <ctime>
#include <string>
#include <stdio.h>

using namespace cv;
using namespace std;

//全局变量
int threshold_value = 0;
int threshold_type = 0;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;

char window_name[] = "Threshold Demo";
char trackbar_type[] = "type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char trackbar_value[] = "Value";

/// 自定义函数声明
void Threshold_Demo( int, void* );



int main(int argc, char **argv)
{
    //载入，OPENCV2.0写法
    if (argc < 2)
    {
	printf("\n Please input one image \n");
        return 0;
    }
    string InputPictureName = argv[1];

    //最后一个参数 1=彩色(默认为1,三通道 )，-1=原图读取，0=(单通道，灰色图)
    Mat image1 = imread(InputPictureName,-1);

    Mat image2;             //灰度化
    Mat image3;             //二值化
    Mat image4;             //彩色图
    Mat image5;             //填充图
    


    printf("\n [原图]image1 =【%d】,原图高度=【%d】，原图宽度 = [%d]\n",image1.channels(),image1.rows,image1.cols);
    //创建窗口
    namedWindow("原图读取",0);
    resizeWindow("原图读取", image1.rows, image1.cols); 
    //显示图片
    imshow("原图读取", image1);
    waitKey(0);
    
    //把图片转成彩色图
    //cvtColor(image1, image2, CV_GRAY2BGR);
    //namedWindow("彩色图",0);
    //resizeWindow("彩色图", 400, 400); 
    //imshow("彩色图",image2);
    //printf("\n [彩色图]image2 =【%d】,原图高度=【%d】，原图宽度 = [%d]\n",image2.channels(),image2.rows,image2.cols);
    //waitKey(0);


   //将彩色图转成灰度图片 
    image2 = image1 ;
    cvtColor(image2, image3, CV_BGR2GRAY);
    namedWindow("灰色图",0 );
    resizeWindow("灰色图", 400, 400); 
    imshow("灰色图",image3);
    printf("\n [灰色图]image3 =【%d】,原图高度=【%d】，原图宽度 = [%d]\n",image3.channels(),image3.rows,image3.cols);
    waitKey(0);


    //二值化
    //threshold(image3, image4, 127, 255, THRESH_BINARY);
    //namedWindow("二值图",0);
    //resizeWindow("二值图", 400, 400); 
    //imshow("二值图",image4);
    //printf("\n [二值图]image4 =【%d】,原图高度=【%d】，原图宽度 = [%d]\n",image4.channels(),image4.rows,image4.cols);
    //waitKey(0);


    /// 创建滑动条来控制阈值
    src_gray = image3 ;
    namedWindow("Threshold Demo", CV_WINDOW_AUTOSIZE);   
    createTrackbar( "type", "Threshold Demo", &threshold_type,  4, Threshold_Demo );
    createTrackbar( "value", "Threshold Demo", &threshold_value, 255, Threshold_Demo );
    Threshold_Demo( 0, 0 );
    waitKey(0) ;


    //恢复彩色图
    //image5 = image4 ;
    //cvtColor(image4, image5, CV_GRAY2BGR);
    //namedWindow("恢复彩色图", 0 );
    //resizeWindow("恢复彩色图", 400, 400); 
    //imshow("恢复彩色图",image5);
    //printf("\n [恢复彩色图]image5 =【%d】,原图高度=【%d】，原图宽度 = [%d]\n",image5.channels(),image5.rows,image5.cols);
    //waitKey(0);


    srand(clock()); //取随机整数 
    
    int x = 0;
    int y = 0;
    //Scalar temp;        //current point's color
    Scalar scalar1;     //constant parameter
    Rect ccomp;         //constant parameter

    Vec3b temp;
    int randcount =0 ;

    image5=image1;
    while(1)
    {
	// Scalar(0,0,0)              黑色
        // Scalar(255,255,255)        白色
        // Scalar(255,0,0)            蓝色 
        // Scalar(0,255,0)            绿色 
        // Scalar(0,0,255)            红色 

	temp = image5.at<Vec3b>(y, x);

        if (temp.val[0] > 220 && temp.val[1] > 220 && temp.val[2] > 220)    //如果不巧碰上非255,255,255的白色
        {
		randcount = rand()%250 ;
		//temp.val[0] = temp.val[0] & randcount ;
                //temp.val[1] = temp.val[1] & randcount ;
                //temp.val[2] = temp.val[2] ;

                temp.val[0] = 100;
                temp.val[1] = 255 ;
                temp.val[2] = 0 ;

		scalar1 = Scalar( temp.val[0],temp.val[1],temp.val[2] );
        	floodFill(image5, Point(x, y), scalar1, &ccomp, Scalar(0, 0, 0), Scalar(0, 0, 0));  
        }
        x += 3;    //步进

        //换行

        if (x >= image5.cols) 
        {
            y += 3;
            x = 0;
        }


        //遍历满后退出填充循环
        if (y >= image5.rows)   
        {
            break;
        }
    }

    //在窗口中显示图像
    //namedWindow("填充图",0);
    //printf("\n [填充图]image5 =【%d】,原图高度=【%d】，原图宽度 = [%d]\n",image5.channels(),image5.rows,image5.cols);
    //resizeWindow("填充图", image5.rows,image5.cols); 
    //imshow("填充图",image5);
    //waitKey(0);


    //输出 
    printf("\n output jpeg\n ");
    imwrite(InputPictureName + "_output.jpeg", image5);
    return 0;
}


void Threshold_Demo( int, void* )
{
  /* 0: 二进制阈值
     1: 反二进制阈值
     2: 截断阈值
     3: 0阈值
     4: 反0阈值
   */

  threshold( src_gray, dst, threshold_value, 255,4  );
  imshow( "Threshold Demo", dst );
}

