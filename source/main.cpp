#include <opencv2/opencv.hpp>
#include "commonDefine.h"

extern cv::Mat grayTest(const cv::Mat& img);

int main()
{
    cv::Mat srcImage = cv::imread(getAssetDir("dog.jpg"));
    const auto& out = grayTest(srcImage);
    cv::imwrite(getAssetDir("dog_gray.jpg"), out);
    imshow("result image", out);
    cv::waitKey(0);
    return 0;
}
