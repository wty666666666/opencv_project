#include <opencv2/opencv.hpp>
#include <vector>

int main() {
    // 读取图像
    cv::Mat src = cv::imread("../resources/1.png");
    if (src.empty()) {
        std::cerr << "Error: Image cannot be loaded." << std::endl;
        return -1;
    }
    imshow("原图",src);





    // 转换为 HSV 颜色空间
    cv::Mat hsv;
    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
    // 定义红色的 HSV 范围
    cv::Scalar lower_red = cv::Scalar(150, 43, 46);
    cv::Scalar upper_red = cv::Scalar(180, 255, 255);
    cv::Scalar lower_red2 = cv::Scalar(170, 100, 100);
    cv::Scalar upper_red2 = cv::Scalar(180, 255, 255);
    // 创建掩膜
    cv::Mat mask, mask2, mask_red;
    cv::inRange(hsv, lower_red, upper_red, mask);
    cv::inRange(hsv, lower_red2, upper_red2, mask2);
    cv::bitwise_or(mask, mask2, mask_red);
    // 形态学操作，去噪点
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(mask_red, mask_red, cv::MORPH_CLOSE, kernel);
    cv::morphologyEx(mask_red, mask_red, cv::MORPH_OPEN, kernel);
    // 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask_red, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);//（输入二值图，输出参数存储数据，模式（cv::RETR_EXTERNAL，这意味着只检测最外层的轮廓。），方式（cv::CHAIN_APPROX_SIMPLE，这意味着仅保留每个轮廓的最外层点，从而简化了轮廓。））
    // 计算每个轮廓的面积和总面积
    std::vector<double> areas;
    for (const auto& contour : contours) {
        double area = cv::contourArea(contour);
        areas.push_back(area);
    }
        double sum;
    for (size_t i = 0; i < contours.size(); i++) {
        std::cout << "Contour " << i << " area: " << areas[i] << std::endl;
        sum+=areas[i];
    }
    std::cout<<"SUM = "<<sum<<std::endl;
    // 绘制轮廓
    cv::Mat drawing = cv::Mat::zeros(mask_red.size(), CV_8UC3);
    cv::Mat dst=src.clone();
     for (size_t i = 0; i < contours.size(); i++) {
        cv::Scalar color = cv::Scalar(0, 0, 255); // 红色
        cv::drawContours(dst, contours, (int)i, color, 2, cv::LINE_8, std::vector<cv::Point>(), 0, cv::Point());//在原图上绘制
    }

    for (size_t i = 0; i < contours.size(); i++) {
        cv::Scalar color = cv::Scalar(0, 0, 255); // 红色
        cv::drawContours(drawing, contours, (int)i, color, 2, cv::LINE_8, std::vector<cv::Point>(), 0, cv::Point());//单独绘制
    }
    // 显示结果
    cv::imshow("Contours", drawing);//单独绘制的红色轮廓
    cv::imshow("dst",dst);//原图上绘制的红色轮廓
       
       
    
    
    
    //克隆原图
    cv::Mat src1=src.clone();
    //确认红色是啥   
    cv::Scalar red(0, 0, 255);
    // 绘制红色圆形 
    cv::circle(src1, cv::Point(50, 50), 20, red, -1);//参数分别是（图片，左上角坐标，半径，颜色向量，布尔值（只有ture与false的区别））
    // 绘制红色方形
    cv::rectangle(src1, cv::Point(1000, 1000), cv::Point(1050, 1050), red, -1);//参数分别是（图片，顶角坐标1，顶角坐标2，颜色向量，布尔值（只有ture与false的区别））
    cv::rectangle(src1, cv::Point(100, 100), cv::Point(150, 150), red, -1);//参数分别是（图片，顶角坐标1，顶角坐标2，颜色向量，布尔值（只有ture与false的区别））
    // 绘制红色文字
    cv::putText(src1, "I am gold", cv::Point(200, 200), cv::FONT_HERSHEY_PLAIN, 1, red, 2);//参数分别是（图片，打出的内容，左上角坐标，字体类型，字体大小，颜色向量，布尔值（只有ture与false的区别））
    // 显示结果
    cv::imshow("Image", src1);//原图上绘制红色圆圈，红色方块，红色文字

    
    






    // 创建一个掩膜，选择红色区域
    cv::Mat mask9;
    cv::inRange(src, cv::Scalar(150, 43, 46), cv::Scalar(180, 255, 255), mask); // 红色区域

    // 查找轮廓
    std::vector<std::vector<cv::Point>> contour2s;
    cv::findContours(mask, contour2s, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    // 绘制红色 bounding box
    cv::Mat src4=src.clone();
    for (const auto& contour : contour2s) {
        cv::RotatedRect rect = cv::minAreaRect(contour);
        cv::Point2f  points[4];
        rect.points(points); // 这里使用 cv::Point 类型的数组
        cv::Point2i points2[4];
        for(int i=1;i<=4;i++)
        {
            cv::Point2f x;
            cv::Point2i y;
            x=points[i-1];
            y=cv::Point2i(x);
            points2[i-1]=y;
        }
        cv::line(src4, points2[0], points2[1], cv::Scalar(0, 0, 255), 2); // 红色线
        cv::line(src4, points2[1], points2[2], cv::Scalar(0, 0, 255), 2); // 红色线
        cv::line(src4, points2[2], points2[3], cv::Scalar(0, 0, 255), 2); // 红色线
        cv::line(src4, points2[0], points2[3], cv::Scalar(0, 0, 255), 2); // 红色线
    }
    // 显示结果
    cv::imshow("Original Image with Red Bounding Boxes", src4);

     cv::waitKey(0);
    return 0;   
}
