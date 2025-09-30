#ifndef LESSON_2_TOOLS_HPP
#define LESSON_2_TOOLS_HPP

#include <opencv2/opencv.hpp>
#include <iostream>

class myCamera
{
private:
    void *handle_;
public:
    myCamera(void *handle);
    cv::Mat read();
    ~myCamera();
};
#endif // LESSON_2_TOOLS_HPP