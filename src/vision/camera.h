#pragma once
#include <opencv2/opencv.hpp>

class Camera {

private:
    cv::VideoCapture cap;

public:
    Camera(int index);

    bool open();

    cv::Mat getFrame();
};