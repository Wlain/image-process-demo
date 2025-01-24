//
// Created by william on 2025/1/25.
//

#include <opencv2/opencv.hpp>

cv::Mat grayTest(const cv::Mat& img)
{
    const int width = img.cols;
    const int height = img.rows;
    // prepare output
    cv::Mat out = cv::Mat::zeros(height, width, CV_8UC3);
    // each y, x
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            cv::Vec3f weight{ 0.2125, 0.7154, 0.0721 };
            cv::Vec3f color{ (float)img.at<cv::Vec3b>(y, x)[0], (float)img.at<cv::Vec3b>(y, x)[1], (float)img.at<cv::Vec3b>(y, x)[2] };
            auto gray = weight.dot(color);
            out.at<cv::Vec3b>(y, x)[0] = (int)gray;
            out.at<cv::Vec3b>(y, x)[2] = (int)gray;
            out.at<cv::Vec3b>(y, x)[1] = (int)gray;
        }
    }
    return out;
}
