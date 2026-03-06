#include <opencv2/opencv.hpp>
#include <iostream>

// valores iniciales
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

    // ventana para sliders
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

        // espejo
        cv::flip(frame, frame, 1);

        // convertir a HSV
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        // rango dinámico
        cv::Scalar lower(Hmin, Smin, Vmin);
        cv::Scalar upper(Hmax, Smax, Vmax);

        // máscara
        cv::inRange(hsv, lower, upper, mask);

        // mostrar resultados
        cv::imshow("Camara", frame);
        cv::imshow("Mascara", mask);

        if (cv::waitKey(1) == 27) break;
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}