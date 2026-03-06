#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

int Hmin = 0;
int Hmax = 20;
int Smin = 30;
int Smax = 150;
int Vmin = 60;
int Vmax = 255;

int main() {

    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cout << "No se pudo abrir la camara\n";
        return -1;
    }

    cv::Mat frame;
    cv::Mat hsv;
    cv::Mat mask;
    cv::Mat blur;
    cv::Mat morph;

    cv::namedWindow("Control HSV");

    cv::createTrackbar("H min", "Control HSV", &Hmin, 179);
    cv::createTrackbar("H max", "Control HSV", &Hmax, 179);

    cv::createTrackbar("S min", "Control HSV", &Smin, 255);
    cv::createTrackbar("S max", "Control HSV", &Smax, 255);

    cv::createTrackbar("V min", "Control HSV", &Vmin, 255);
    cv::createTrackbar("V max", "Control HSV", &Vmax, 255);

    while (true) {

        cap >> frame;
        if (frame.empty()) break;

        cv::flip(frame, frame, 1);

        // BGR → HSV
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        cv::Scalar lower(Hmin, Smin, Vmin);
        cv::Scalar upper(Hmax, Smax, Vmax);

        cv::inRange(hsv, lower, upper, mask);

        // suavizar
        cv::GaussianBlur(mask, blur, cv::Size(7,7), 0);

        // operaciones morfologicas
        cv::erode(blur, morph, cv::Mat(), cv::Point(-1,-1), 2);
        cv::dilate(morph, morph, cv::Mat(), cv::Point(-1,-1), 2);

        // encontrar contornos
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(morph, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        if (!contours.empty()) {

            int largestIndex = 0;
            double largestArea = 0;

            for (int i = 0; i < contours.size(); i++) {

                double area = cv::contourArea(contours[i]);

                if (area > largestArea) {
                    largestArea = area;
                    largestIndex = i;
                }
            }

            // dibujar contorno de la mano
            cv::drawContours(frame, contours, largestIndex, cv::Scalar(0,255,0), 3);
        }

        cv::imshow("Camara", frame);
        cv::imshow("Mascara", mask);
        cv::imshow("Morph", morph);

        if (cv::waitKey(1) == 27) break;
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}