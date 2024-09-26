#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 读取图像
    cv::Mat src = cv::imread("../resources/1.png");
    if (src.empty()) {
        std::cerr << "Error: Image cannot be loaded." << std::endl;
        return -1;
    }
       cv::imshow("Original Image", src);

    // 创建一个掩膜，选择红色区域
    cv::Mat mask;
    cv::inRange(src, cv::Scalar(0, 43, 46), cv::Scalar(10, 255, 255), mask); // 红色区域

    // 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 绘制红色 bounding box
    cv::Mat src4=src.clone();
    for (const auto& contour : contours) {
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
        cv::line(src4, cv::Point2i(100,100), cv::Point2i(150,150), cv::Scalar(0, 0, 255), 200); // 红色线
        cv::line(src4, points2[1], points2[2], cv::Scalar(0, 0, 255), 2); // 红色线
        cv::line(src4, points2[2], points2[3], cv::Scalar(0, 0, 255), 2); // 红色线
        cv::line(src4, points2[3], points2[0], cv::Scalar(0, 0, 255), 2); // 红色线
    }

    // 显示结果
    cv::imshow("Original Image with Red Bounding Boxes", src4);
    cv::waitKey(0);

    return 0;
}
