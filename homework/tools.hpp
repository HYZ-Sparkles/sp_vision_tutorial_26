#ifndef LESSON_2_TOOLS_HPP
#define LESSON_2_TOOLS_HPP

#include <opencv2/opencv.hpp>
#include <iostream>

// ====== 函数声明 ======
cv::Mat scaleToCenter(const cv::Mat& srcImage, int targetSize);

#endif // LESSON_2_TOOLS_HPP