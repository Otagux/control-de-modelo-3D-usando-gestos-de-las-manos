#include "camera.h"

Camera::Camera(int index) {
    cap.open(index);
}

bool Camera::open() {
    return cap.isOpened();
}

cv::Mat Camera::getFrame() {
    cv::Mat frame;
    cap >> frame;
    return frame;
}
