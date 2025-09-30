#include "my_camera.hpp"  
#include "hikrobot/include/MvCameraControl.h"
#include <opencv2/opencv.hpp>

// 转换函数保持不变
cv::Mat transfer(MV_FRAME_OUT& raw)
{
    MV_CC_PIXEL_CONVERT_PARAM cvt_param;
    cv::Mat img(cv::Size(raw.stFrameInfo.nWidth, raw.stFrameInfo.nHeight), CV_8U, raw.pBufAddr);

    cvt_param.nWidth = raw.stFrameInfo.nWidth;
    cvt_param.nHeight = raw.stFrameInfo.nHeight;

    cvt_param.pSrcData = raw.pBufAddr;
    cvt_param.nSrcDataLen = raw.stFrameInfo.nFrameLen;
    cvt_param.enSrcPixelType = raw.stFrameInfo.enPixelType;

    cvt_param.pDstBuffer = img.data;
    cvt_param.nDstBufferSize = img.total() * img.elemSize();
    cvt_param.enDstPixelType = PixelType_Gvsp_BGR8_Packed;

    auto pixel_type = raw.stFrameInfo.enPixelType;
    const static std::unordered_map<MvGvspPixelType, cv::ColorConversionCodes> type_map = {
      {PixelType_Gvsp_BayerGR8, cv::COLOR_BayerGR2RGB},
      {PixelType_Gvsp_BayerRG8, cv::COLOR_BayerRG2RGB},
      {PixelType_Gvsp_BayerGB8, cv::COLOR_BayerGB2RGB},
      {PixelType_Gvsp_BayerBG8, cv::COLOR_BayerBG2RGB}};
    cv::cvtColor(img, img, type_map.at(pixel_type));
    
    return img;
}

myCamera::myCamera(void *handle)
{
    int ret;
    // 打开相机
    MV_CC_DEVICE_INFO_LIST device_list;
    ret = MV_CC_EnumDevices(MV_USB_DEVICE, &device_list);
    if (ret != MV_OK) {
      throw std::runtime_error("开启相机时出现异常了");        
    }
  
    if (device_list.nDeviceNum == 0) {
      throw std::runtime_error("开启相机时出现异常了");        
    }
  
    ret = MV_CC_CreateHandle(&handle_, device_list.pDeviceInfo[0]);
    if (ret != MV_OK) {
      throw std::runtime_error("开启相机时出现异常了");        
    }
  
    ret = MV_CC_OpenDevice(handle_);
    if (ret != MV_OK) {
      throw std::runtime_error("开启相机时出现异常了");        
    }
  
    MV_CC_SetEnumValue(handle_, "BalanceWhiteAuto", MV_BALANCEWHITE_AUTO_CONTINUOUS);
    MV_CC_SetEnumValue(handle_, "ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);
    MV_CC_SetEnumValue(handle_, "GainAuto", MV_GAIN_MODE_OFF);
    MV_CC_SetFloatValue(handle_, "ExposureTime", 8000);
    MV_CC_SetFloatValue(handle_, "Gain", 16.9);
    MV_CC_SetFrameRate(handle_, 60);

    ret = MV_CC_StartGrabbing(handle_);
    if (ret != MV_OK) {
      throw std::runtime_error("开启相机时出现异常了");        
    }
}

cv::Mat myCamera::read()
{
    int ret;
    // 读取一帧图像
  
    MV_FRAME_OUT raw;
    unsigned int nMsec = 100;

    ret = MV_CC_GetImageBuffer(handle_, &raw, nMsec);
    if (ret != MV_OK) {
      throw std::runtime_error("读取图像时出现异常了");
    }

    cv::Mat img = transfer(raw);

    ret = MV_CC_FreeImageBuffer(handle_, &raw);
    if (ret != MV_OK) {
      throw std::runtime_error("读取图像时出现异常了");
    }

    return img;
}

myCamera::~myCamera()
{
    int ret;
    // 关闭相机
    ret = MV_CC_StopGrabbing(handle_);
    if (ret != MV_OK) {
      std::cout<<"关闭相机时出现异常了";
    }

    ret = MV_CC_CloseDevice(handle_);
    if (ret != MV_OK) {
      std::cout<<"关闭相机时出现异常了";
    }

    ret = MV_CC_DestroyHandle(handle_);
    if (ret != MV_OK) {
      std::cout<<"关闭相机时出现异常了";
    }
}