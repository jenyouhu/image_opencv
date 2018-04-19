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
    //waitKey(0);
    
    //把图片转成三通道图
    //cvtColor(image1, image2, CV_GRAY2BGR);
    //namedWindow("彩色图",0);
    //resizeWindow("彩色图", 400, 400); 
    //imshow("彩色图",image2);
    //printf("\n [彩色图]image2 =【%d】,原图高度=【%d】，原图宽度 = [%d]\n",image2.channels(),image2.rows,image2.cols);
    //waitKey(0);


   //将彩色图转成灰度图片 
   // image2 = image1 ;
   // cvtColor(image2, image3, CV_BGR2GRAY);
   // namedWindow("灰色图",0 );
   // resizeWindow("灰色图", 400, 400); 
   // imshow("灰色图",image3);
   // printf("\n [灰色图]image3 =【%d】,原图高度=【%d】，原图宽度 = [%d]\n",image3.channels(),image3.rows,image3.cols);
   // waitKey(0);


    //二值化
    //threshold(image3, image4, 127, 255, THRESH_BINARY);
    //namedWindow("二值图",0);
    //resizeWindow("二值图", 400, 400); 
    //imshow("二值图",image4);
    //printf("\n [二值图]image4 =【%d】,原图高度=【%d】，原图宽度 = [%d]\n",image4.channels(),image4.rows,image4.cols);
    //waitKey(0);


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
    Scalar scalar1;     //constant parameter
    //Rect ccomp(20,20,20,20);         //constant parameter
    Rect ccomp ;        //constant parameter
    Vec3b temp;
    int rand_b;
    int rand_g;
    int rand_r;
    int flag = 0;

    image5=image1;
    while(1)
    {
	// Scalar(0,0,0)              黑色
        // Scalar(255,255,255)        白色
        // Scalar(255,0,0)            蓝色 
        // Scalar(0,255,0)            绿色 
        // Scalar(0,0,255)            红色 

	temp = image5.at<Vec3b>(y, x);

	//jenyou hu 
	//黑色换棕色 
        if (temp.val[0] <= 80 && temp.val[1] <=80  && temp.val[2] <= 80)   
        {
                	//棕色 
               	temp.val[0] =  28;
               	temp.val[1] =  50 ;
               	temp.val[2] =  118 ;

		scalar1 = Scalar( temp.val[0],temp.val[1],temp.val[2] );
        	floodFill(image5, Point(x, y), scalar1, &ccomp, Scalar(0, 0, 0), Scalar(0, 0, 0),8);  
                flag = 1;
        }
        // 棕色换黑色 
        else if( temp.val[0] <= 30 && temp.val[1] <= 50  && temp.val[2] <= 120 )
        {
                //黑色  
                temp.val[0] =  68 ;
                temp.val[1] =  68 ;
                temp.val[2] =  66 ;
                if ( flag == 0 )
		{
			scalar1 = Scalar( temp.val[0],temp.val[1],temp.val[2] );
        		floodFill(image5, Point(x, y), scalar1, &ccomp, Scalar(0, 0, 0), Scalar(0, 0, 0));  
		}
        }
        //白色不变 
        //else if( temp.val[0] >= 230 && temp.val[1] >= 230  && temp.val[2] >= 230 )
        //{
        //        temp.val[0] =  temp.val[0] ;
        //        temp.val[1] =  temp.val[1] ;
        //        temp.val[2] =  temp.val[2] ;
        //}

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
    namedWindow("填充图",0);
    printf("\n [填充图]image5 =【%d】,原图高度=【%d】，原图宽度 = [%d]\n",image5.channels(),image5.rows,image5.cols);
    resizeWindow("填充图", image5.rows,image5.cols); 
    imshow("填充图",image5);
    waitKey(0);


    //输出 
    printf("\n output jpeg\n ");
    imwrite(InputPictureName + "_output.jpeg", image5);
    return 0;
}
