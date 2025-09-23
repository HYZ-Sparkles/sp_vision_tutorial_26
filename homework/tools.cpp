#include "tools.hpp"
#include <fmt/core.h>

cv::Mat scaleToCenter(const cv::Mat& srcImage, int targetSize) {
    if (srcImage.empty()) {
        return cv::Mat();
    }

    int srcWidth = srcImage.cols;
    int srcHeight = srcImage.rows;

    double scaleFactor = std::min(
        static_cast<double>(targetSize) / srcWidth,
        static_cast<double>(targetSize) / srcHeight
    );

    int scaledWidth = static_cast<int>(srcWidth * scaleFactor);
    int scaledHeight = static_cast<int>(srcHeight * scaleFactor);

    cv::Mat scaledImage;
    cv::resize(
        srcImage,
        scaledImage,
        cv::Size(scaledWidth, scaledHeight),
        0, 0,  // 缩放因子由Size参数决定，这里设为0
        cv::INTER_LINEAR  // 双线性插值算法
    );

    cv::Mat canvas(
        targetSize,
        targetSize,
        srcImage.type(),
        cv::Scalar::all(0)  // 全0表示黑色（自动适配单通道/多通道）
    );

    int offsetX = (targetSize - scaledWidth) / 2;
    int offsetY = (targetSize - scaledHeight) / 2;

    cv::Rect roi(
        offsetX,       // 左上角X坐标
        offsetY,       // 左上角Y坐标
        scaledWidth,   // 区域宽度
        scaledHeight   // 区域高度
    );

    scaledImage.copyTo(canvas(roi));

    //用fmt输出放缩用到的参数
    fmt::print("放缩比例为{}\n",scaleFactor);
    fmt::print("横向偏移距离为{}\n",(srcWidth-scaledWidth)/2.0);
    fmt::print("竖向偏移距离为{}\n",(srcHeight-scaledHeight)/2.0);

    return canvas;
}
