#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

struct Landmark{

    float x;
    float y;
    float z;

};

struct HandData{

    std::vector<Landmark> landmarks;

    bool detected=false;

};

class HandTracker{

public:

    HandData detect(cv::Mat &frame);

};