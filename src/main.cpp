#include <opencv2/opencv.hpp>
#include <iostream>

int main(){

    cv::VideoCapture cap(0);

    if(!cap.isOpened()){
        std::cout<<"No se pudo abrir la camara\n";
        return -1;
    }

    cv::Mat frame;

    while(true){

        cap >> frame;

        if(frame.empty())
            break;

        cv::imshow("Camara", frame);

        if(cv::waitKey(30) == 27)
            break;
    }

    return 0;
}