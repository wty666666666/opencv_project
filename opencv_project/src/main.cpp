#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

Mat redInHSV(Mat img){
  Mat red_image,img1;
  //转换成HSV
  cvtColor(img,img1,COLOR_BGR2HSV);
  //设置颜色预值
  Scalar lower=Scalar(150,43,46);
  Scalar upper=Scalar(180,255,255);//参数没设置对。。。
  //根据预值寻找色块
  Mat mask;
  inRange(img1,lower,upper,mask);
  //通过掩膜提取红色像素
  bitwise_and(img,img1,red_image,mask); 
 waitKey(30);
 return red_image;


}

int main()
{
    string path = "../resources/1.png";
    Mat img = imread(path);  
    
        resize(img, img, Size(0, 0), 0.5, 0.5);
        imshow("Image Origin", img);   
    Mat gray,hsv_image,blur_image,gaoshi_image,red_image ;
    
    cvtColor(img,gray,COLOR_BGR2GRAY);//灰度图
    
    cvtColor(img,hsv_image,COLOR_BGR2HSV);//转换成HSV
    
    blur(img,blur_image,Size(5,5));//均值滤波
    
    GaussianBlur(img,gaoshi_image,Size(25,25),0,0);//高斯滤波

    red_image=redInHSV(img);//红色区域图
	
    
    Mat dst1;
 	threshold(gray, dst1, 127, 255, THRESH_BINARY);//基于灰度图之上的二值化阈值处理

    //膨胀处理
      //获取自定义核
   	  Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
   	  Mat out;
   	  //进行膨胀操作
   	  dilate(img, out, element);
    
    //腐蚀处理

      //获取自定义核
   	  Mat element2 = getStructuringElement(MORPH_RECT, Size(15, 15));
   	  Mat out2;
   	  //进行腐蚀操作
   	  erode(img,out2, element2);
    
    //旋转图
      //旋转中心的选定
     
      Mat xuanzhuan,img_rotated;
      int m=img.cols;//长
      int h=img.rows;//宽
      xuanzhuan=getRotationMatrix2D(Point2f(m/2,h/2),-35,1);//旋转中心
      warpAffine(img,img_rotated,xuanzhuan,Size(),INTER_LINEAR,0);



    //裁剪图
    Rect m_select;
    m_select = Rect(0,0,m/2,h/2);//4个数值分别是（左上角的x值，左上角的y值，矩形column方向上的宽，矩形row方向上的宽） ps：左上角坐标是（0,0）
	Mat ROI = img(m_select);

//展示图片（最大只能展示六个图片）
   
    imshow("Image Gray", gray);//灰度图
    imshow("Image HSV", hsv_image);//转换成HSV
    //imshow("Image Blur",blur_image);//均值滤波
    //imshow("Image Gaoshi",gaoshi_image);//高斯滤波
    //imshow("Image Red",red_image);
    imshow("二值化图片", dst1);//二值化
    imshow("膨胀图片",out);//膨胀图
    imshow("腐蚀图片",out2);//腐蚀图
    //imshow("旋转图片",img_rotated);//旋转35度图
    //imshow("剪裁图", ROI);//裁剪左上角1/4图
    cv::waitKey(0);
    return 0;
}
