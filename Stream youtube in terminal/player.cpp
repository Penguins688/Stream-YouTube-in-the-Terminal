#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    string filePath;
    double scalePercent = 50;

    std::ifstream file("info.txt");
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    if (std::getline(file, line)) {
        filePath = line;
    } else {
        std::cerr << "info.txt is empty" << std::endl;
    }

    file.close();

    cv::VideoCapture cap(filePath);
    if (!cap.isOpened()) {
        cerr << "Error: no video file found" << std::endl;
        return -1;
    }

    cv::Mat frame, grayFrame;
    while (true) {
        cap >> frame;
        system("clear");
        if (frame.empty()) {
            break;
        }

        cv::resize(frame, frame, cv::Size(), scalePercent / 100, scalePercent / 100);
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

        for (int y = 0; y < grayFrame.rows; y++) {
            for (int x = 0; x < grayFrame.cols; x++) {
                uchar intensity = grayFrame.at<uchar>(y, x);
                if (intensity < 24) {
                    cout << "@";
                } else if (intensity < 48) {
                    cout << "%";
                } else if (intensity < 72) {
                    cout << "#";
                } else if (intensity < 96) {
                    cout << "*";
                } else if (intensity < 120) {
                    cout << "+";
                } else if (intensity < 144) {
                    cout << "=";
                } else if (intensity < 168) {
                    cout << "-";
                } else if (intensity < 192) {
                    cout << ":";
                } else if (intensity < 216) {
                    cout << ".";
                } else {
                    cout << " ";
                }
            }
            cout << "\n";
        }

        cout.flush();

        cv::waitKey(100);
    }

    cap.release();
    return 0;
}