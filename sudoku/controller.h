#pragma once

#include "ai.h"
#include "opencv2/opencv.hpp"

#define OFFSET 200
#define SIDE 512
#define SQUARE_SIZE (SIDE / 9.0)
typedef cv::Point3_<uint8_t> Pixel;

using namespace cv;

class Controller
{
private:
    AI ai;
    Board original;
    Mat img = Mat(SIDE, SIDE + OFFSET, CV_8UC3);
    int curNum = 1;
    bool freeze = false;

private:
    // Render UI
    void fillSquare(int, int, int, Vec3b);
    void init();
    void render(int,int,Vec3b);
    void renderCurrentNumber();
    void generate();
    void solve();
    GridLocation check();

public:
    void show();

    // Callback Function
    friend void onClick(int, int, int, int, void *);
};