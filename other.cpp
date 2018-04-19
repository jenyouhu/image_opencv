// OpenCV 文件头
// Write By Jenyouhu on 2018.4.11 
// HSV 颜色分量范围 H:0-180 , S:0-255 ,V:0-255 


#include </usr/local/include/opencv2/opencv.hpp>
#include "/usr/local/include/opencv2/imgproc/imgproc.hpp" 
#include "/usr/local/include/opencv/cv.h"                              
#include "/usr/local/include/opencv/highgui.h"  
#include "/usr/local/include/opencv/cvaux.h"  
#include "/usr/local/include/opencv/cxcore.h"  

//C语言系统头文件
#include <cmath>
#include <ctime>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;


int main(int argc, char **argv)

{
    //载入，OPENCV2.0写法
    if (argc < 3)
    {
	printf("\n Please input image name and output Image name \n");
        return 0;
    }
    string InputPictureName = argv[1];
    string OnputPictureName = argv[2];

    //最后一个参数 1=彩色(默认为1,三通道 )，-1=原图读取，0=(单通道，灰色图)
    //Mat 是C++图像类型 
    Mat image1;
    Mat image2;             //灰度化
    Mat image3;             //二值化
    Mat image4;             //彩色图
    Mat image5;             //填充图
    


    //创建窗口
    namedWindow("old_pic",0);
    image1 = imread(InputPictureName,-1);
    resizeWindow("old_pic", image1.rows, image1.cols); 

    //显示图片
    imshow("old_pic", image1);

    printf("\n [原图]image1 =【%d】,原图高度=【%d】，原图宽度 = [%d]\n",image1.channels(),image1.rows,image1.cols);
    //waitKey(0);
    

    //init para
    srand(time(0));

    int x = 0;
    int y = 0;
    int i = 0;
    int j = 0;
    Scalar s_hsv;       //current point's color
    Scalar scalar1;     //constant parameter
    Rect ccomp;         //constant parameter


    Vec3b temp;

    //将RGB转化成 HSV 通道格式 
    image5 = image1 ;

    Mat hsvImage ; 
    //cvtColor(image1, hsvImage, CV_BGR2HSV); 

    int nl=image1.rows;  
    int nc=image1.cols; 

    int H,S,V;
    int colorcount=0 ;
    int colorcount1=0 ;
    int colorcount2=0 ;
    int colorcount3=0 ;
    int colorcount4=0 ;

    int B,G,R ;
    int bcount=0 ;
    int zcount=0 ;
    int wcount=0;
    int scount=0;
    int hcount=0;

    int flagx = 0 ;
    int flagy = 0 ;

    // 第一次循环获取需要替换颜色的像素
    for (int j = 0; j < nl ;j++)
    {
         for (int i = 0; i <nc ;i++)   //遍历图片的每一个像素点
         {
	       
              B=image1.at<Vec3b>(i, j).val[0] ;
              G=image1.at<Vec3b>(i, j).val[1] ;
              R=image1.at<Vec3b>(i, j).val[2] ;

             if( (B >=10 &&B <= 80) && ( G>= 20 && G <= 80) && ( R>=10 && R<=80 ))  //黑色
             {
                     bcount++;
             }
             if( ( B>= 20 && B <= 30)  && ( G>=40 && G <= 50)  && (R>=110 &&  R <= 120 )) //棕色 
             {
		     zcount++ ;
             }
             if ( B >= 230  && G >= 230  && R >= 230  ) //白色
	     {
		     wcount++ ;
             }	
	     if (( B>= 60 && B<=80) && ( G>=60 && G<= 72 ) && ( R>= 90 && R<=98 )) //深紫色 
             {
                     scount++ ;  
             }
             if (( B>=120 && B<=181) && (G>=130 && B<=183) && (R>=140 && R<=191)) //灰色 
             {
                     hcount++ ;
             }    
	    
         }
     }	

     
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    int count4 = 0;
    int count5 = 0;

    if ( bcount > 0) 
    {	
        colorcount = rand() % bcount  ;
	if ( colorcount <=200 )
	{
		colorcount = colorcount + 200  ;
        }
        else if ( colorcount > (bcount - 200 ))
        {
		colorcount = colorcount - 200 ;
        }
    }
    if ( zcount > 0 )
    {	
        colorcount1 = rand() % zcount ;
	if ( colorcount1 <=200 )
	{
		colorcount1 = colorcount1 + 200  ;
        }
        else if ( colorcount1 > (zcount - 200 ))
        {
		colorcount1 = colorcount1 - 400 ;
        }
    }

    if ( scount > 0)
    {
	colorcount2 = rand() % scount ;
    }
    if ( hcount > 0)
    {
	colorcount3 = rand() % hcount ;
    }


    for (int j = 0; j < nl ;j++)
    {
         for (int i = 0; i <nc ;i++)   //遍历图片的每一个像素点
         {
	       
              B=image1.at<Vec3b>(i, j).val[0] ;
              G=image1.at<Vec3b>(i, j).val[1] ;
              R=image1.at<Vec3b>(i, j).val[2] ;

             if( (B >=10 &&B <= 80) && ( G>= 20 && G <= 80) && ( R>=10 && R<=80 ))  //黑色替换成棕色
             {
		     
		     if( count1 <= colorcount )
		     {	
			 // 棕色 
			 image1.at<Vec3b>(i, j).val[0] = 28;
			 image1.at<Vec3b>(i, j).val[1] = 50;
			 image1.at<Vec3b>(i, j).val[2] = 118;
		     }
		     else // 深紫色 
                     {
			 image1.at<Vec3b>(i, j).val[0] = 80;
			 image1.at<Vec3b>(i, j).val[1] = 72;
			 image1.at<Vec3b>(i, j).val[2] = 98;
                     }
		     count1++ ;

             }
             if( ( B>= 20 && B <= 30)  && ( G>=40 && G <= 50)  && (R>=100 &&  R <= 120 )) //棕色替换成黑色 
             {
		     // 黑色 
	 	     if ( count2 <= colorcount1 )
		     {
		 	image1.at<Vec3b>(i, j).val[0] = 68;
		 	image1.at<Vec3b>(i, j).val[1] = 68;
		 	image1.at<Vec3b>(i, j).val[2] = 66;
		     }
                     else
                     {
			 //深紫色 
			 image1.at<Vec3b>(i, j).val[0] = 80;
			 image1.at<Vec3b>(i, j).val[1] = 72;
			 image1.at<Vec3b>(i, j).val[2] = 98;
                     }
                     count2++ ; 
             }
             if (( B>= 60 && B<=80) && ( G>=60 && G<= 72 ) && ( R>= 90 && R<=98 )) //深紫色换棕色
             {
		    if( count3 <= colorcount2 )
                    {
			 //黑色 
		 	 image1.at<Vec3b>(i, j).val[0] = 68;
		 	 image1.at<Vec3b>(i, j).val[1] = 68;
		 	 image1.at<Vec3b>(i, j).val[2] = 66;
		    }
		    else 
                    {
			 //棕色  
			 image1.at<Vec3b>(i, j).val[0] = 28;
			 image1.at<Vec3b>(i, j).val[1] = 50;
			 image1.at<Vec3b>(i, j).val[2] = 118;
                    }
                    count3++ ;
             }
	     if ( B >= 240  && G >= 240  && R >= 240  ) //白色
             {
			image1.at<Vec3b>(i, j).val[0] = 255;
		 	image1.at<Vec3b>(i, j).val[1] = 255;
		 	image1.at<Vec3b>(i, j).val[2] = 255;
             }
	     if ( (B >= 14 && B<= 40)  && ( G>=90 && G<=233)  && ( R>=210 && R<= 243) ) //黄色 
             {
		        //粉红色 
			image1.at<Vec3b>(i, j).val[0] = 150;
		 	image1.at<Vec3b>(i, j).val[1] = 76;
		 	image1.at<Vec3b>(i, j).val[2] = 255;
             }
	     if  ( (B >= 100 && B<= 150)  && ( G>= 70 && G<= 76)   && ( R >= 200 && R<= 225)  )
             {
                        //淡黄色 
		 	image1.at<Vec3b>(i, j).val[0] = 216;
		 	image1.at<Vec3b>(i, j).val[1] = 99;
		 	image1.at<Vec3b>(i, j).val[2] = 14;

             }
             if (( B>=120 && B<=181) && (G>=130 && B<=183) && (R>=140 && R<=191)) //灰色换黑色 
             {
		 	image1.at<Vec3b>(i, j).val[0] = 21;
		 	image1.at<Vec3b>(i, j).val[1] = 24;
		 	image1.at<Vec3b>(i, j).val[2] = 35;
             }
         }
     }	

    printf("\n bcount = %d, zcount= %d, wcount = %d  scount=%d, hcount=%d \n",bcount,zcount,wcount,scount ,hcount ) ;

 
    // 边界填充 
    // borderType = BORDER_CONSTANT(常量填充 ） BORDER_REPLICATE （相近颜色填充 ）
    //copyMakeBorder( image5, finImg, top, bottom, left, right, borderType, value );
    //找轮廓,并填充轮廓 
    // findContours(),drawContours()

    namedWindow("fill_pic",0);
    resizeWindow("fill_pic", image1.rows, image1.cols); 
    imshow("fill_pic",image1);
    
    printf("\n [填充图]image5 =【%d】,原图高度=【%d】，原图宽度 = [%d]\n",image5.channels(),image5.rows,image5.cols);
    waitKey(0);

    //输出 
    imwrite(OnputPictureName , image1);
    return 0;
}
