#include "tools.hpp"

int main() {
    cv::Mat sourceImage = cv::imread("homework/mine.png", cv::IMREAD_UNCHANGED);
    
    if (sourceImage.empty()) {
        std::cerr << "找不到对应的图片" << std::endl;
        return -1;
    }

    // 执行缩放居中处理
    cv::Mat resultImage = scaleToCenter(sourceImage,640);

    // 检查处理结果
    if (resultImage.empty()) {
        std::cerr << "错误：图片处理失败！" << std::endl;
        return -1;
    }

    cv::imshow("放缩后的结果",resultImage);
    cv::waitKey(0);

    return 0;
}