//fyi this is like my first time making a desktop application n usin c++ for softwaredev stuff so idrk what im doing lmao
#include <iostream>
#include<opencv2/opencv.hpp>
#include "opencv2/core.hpp"
...
cv::Mat H = cv::findHomography(points1, points2, cv::RANSAC, 5);
...

struct Image {
    size_t size = 0;
    uint8_t* data = NULL;
    int width;
    int height;
}

int main() {
    Mat img;
    namedWindow("Video");
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cout << "no video stream detected" << std::endl;
        return -1;
    }
}
while (true) {
    cap >> img;
    if (img.empty()) {
        std::cout << "no video stream detected" << std::endl;
        break;
    }
    imshow("Video", img);
    if (waitKey(30) >= 0) {
        break;
    }
    cap.release();
    return 0;
}