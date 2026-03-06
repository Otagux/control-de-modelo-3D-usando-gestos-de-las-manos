#include <opencv2/opencv.hpp>
#include <iostream>

int main() {

    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cout << "Error abriendo camara\n";
        return -1;
    }

    cv::Mat frame;
    cv::Mat hsv;
    cv::Mat mask;

    while (true) {

        cap >> frame;

        if (frame.empty()) break;

        // modo espejo
        cv::flip(frame, frame, 1);

        // convertir a HSV
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        // rango de piel
        cv::Scalar lower(0, 30, 60);
        cv::Scalar upper(20, 150, 255);

        // crear mascara
        cv::inRange(hsv, lower, upper, mask);

        // mostrar ventanas
        cv::imshow("Camara", frame);
        cv::imshow("HSV", hsv);
        cv::imshow("Mascara de piel", mask);

        if (cv::waitKey(1) == 27) break;
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}