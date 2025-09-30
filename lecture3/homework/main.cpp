#include "io/my_camera.hpp"
#include "tasks/yolo.hpp"
#include "opencv2/opencv.hpp"
#include "tools/img_tools.hpp"

int main()
{
    // 初始化相机、yolo类
    void *handle;
    myCamera camera(handle);
    auto_aim::YOLO yolo("./configs/yolo.yaml");
    while (1) {
        // 调用相机读取图像
        cv::Mat img=camera.read();

        // 调用yolo识别装甲板
        std::list<auto_aim::Armor> armors=yolo.detect(img);
        for(auto_aim::Armor armor:armors)
        {
            tools::draw_points(img,armor.points);
            cv::Point point = armor.points[0];
            if(point.y>20) point.y-=20;
            else point.y=armor.points[1].y+1;
            std::string text=auto_aim::COLORS[armor.color]+auto_aim::ARMOR_NAMES[armor.name];
            tools::draw_text(img,text,point);
        }
        // 显示图像
        cv::resize(img, img , cv::Size(640, 480));
        cv::imshow("img", img);
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    return 0;
}