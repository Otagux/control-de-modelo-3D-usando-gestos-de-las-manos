#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main() {

    VideoCapture cap(0);

    if (!cap.isOpened()) {
        cout << "Error al abrir la camara\n";
        return -1;
    }

    Mat frame, hsv, mask;

    while (true) {

        cap >> frame;

        if (frame.empty()) break;

        // convertir a HSV
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        // rango de piel
        Scalar lower(0, 30, 60);
        Scalar upper(20, 150, 255);

        // mascara
        inRange(hsv, lower, upper, mask);

        // limpiar ruido
        erode(mask, mask, Mat(), Point(-1,-1), 2);
        dilate(mask, mask, Mat(), Point(-1,-1), 2);

        // encontrar contornos
        vector<vector<Point>> contours;
        findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        int largestContour = -1;
        double maxArea = 0;

        for(int i = 0; i < contours.size(); i++) {

            double area = contourArea(contours[i]);

            if(area > maxArea) {
                maxArea = area;
                largestContour = i;
            }
        }

        int fingerCount = 0;

        if(largestContour != -1 && maxArea > 5000) {

            drawContours(frame, contours, largestContour, Scalar(0,255,0), 2);

            // convex hull
            vector<int> hull;
            convexHull(contours[largestContour], hull, false, false);

            // convexity defects
            vector<Vec4i> defects;

            if(hull.size() > 3) {

                convexityDefects(contours[largestContour], hull, defects);

                for(int i = 0; i < defects.size(); i++) {

                    int startIdx = defects[i][0];
                    int endIdx = defects[i][1];
                    int farIdx = defects[i][2];

                    Point start = contours[largestContour][startIdx];
                    Point end = contours[largestContour][endIdx];
                    Point far = contours[largestContour][farIdx];

                    float depth = defects[i][3] / 256.0;

                    if(depth > 10) {

                        circle(frame, far, 5, Scalar(0,0,255), -1);
                        fingerCount++;

                    }

                    line(frame, start, end, Scalar(255,0,0), 2);
                }
            }
        }

        // mostrar numero de dedos
        putText(frame,
                "Dedos: " + to_string(fingerCount),
                Point(50,50),
                FONT_HERSHEY_SIMPLEX,
                1.5,
                Scalar(255,0,0),
                3);

        imshow("Camara", frame);
        imshow("Mascara", mask);

        if(waitKey(1) == 27) break;
    }

    cap.release();
    destroyAllWindows();

    return 0;
}