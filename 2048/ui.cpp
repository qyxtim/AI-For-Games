#include "ai.h"
#include "opencv2/opencv.hpp"

using namespace cv;

#define SIDE 512
#define SQUARE_SIZE (SIDE / 4.0)
typedef cv::Point3_<uint8_t> Pixel;

// Color Set
#define BACKGROUND Vec3b(238, 228, 218)
#define BLOCK_2048 Vec3b(237,194,46)
#define BLOCK_1024 Vec3b(237,197,63)
#define BLOCK_512 Vec3b(237,201,80)
#define BLOCK_256 Vec3b(237,204,98)
#define BLOCK_128 Vec3b(237,208,115)
#define BLOCK_64 Vec3b(247,95,59)
#define BLOCK_32 Vec3b(247,124,95)
#define BLOCK_16 Vec3b(246,150,100)
#define BLOCK_8 Vec3b(243,178,122)
#define BLOCK_4 Vec3b(238,225,201)
#define BLOCK_2 Vec3b(238,228,218)

Mat img(SIDE, SIDE, CV_8UC3);
AI ai;

void fillSquare(int x, int y, int length, Vec3b color)
{
    for (int r = y; r < y + length; ++r)
    {
        Pixel *ptr = img.ptr<Pixel>(r, x);
        const Pixel *ptr_end = ptr + length;
        for (; ptr != ptr_end; ++ptr)
        {
            ptr->x = color[2];
            ptr->y = color[1];
            ptr->z = color[0];
        }
    }
}

Vec3b findColor(int value){
    Vec3b color;
    switch (value){
        case 2:
            color = BLOCK_2;
            break;
        case 4:
            color = BLOCK_4;
            break;
        case 8:
            color = BLOCK_8;
            break;
        case 16:
            color = BLOCK_16;
            break;
        case 32:
            color = BLOCK_32;
            break;
        case 64:
            color = BLOCK_64;
            break;
        case 128:
            color = BLOCK_128;
            break;
        case 256:
            color = BLOCK_256;
            break;
        case 512:
            color = BLOCK_512;
            break;
        case 1024:
            color = BLOCK_1024;
            break;
        case 2048:
            color = BLOCK_2048;
            break;
        default:
            color = BACKGROUND;
    }
    return color;
}

void render()
{
    static int forDrawing[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (forDrawing[i][j] != ai.g.grid[i][j])
            {
                fillSquare(j * SQUARE_SIZE, i * SQUARE_SIZE, SQUARE_SIZE, findColor(ai.g.grid[i][j]));

                char n[6];
                sprintf(n, "%d", ai.g.grid[i][j]);

                if (ai.g.grid[i][j] != 0)
                    putText(img, String(n), Point(j * SQUARE_SIZE + (SQUARE_SIZE / 2) - 10 * strlen(n), i * SQUARE_SIZE + (SQUARE_SIZE / 2) + 7), FONT_HERSHEY_TRIPLEX, 1, Scalar(117, 110, 102), 1);
                forDrawing[i][j] = ai.g.grid[i][j];
            }
        }
    }
}

void init(){
    fillSquare(0, 0, SIDE, BACKGROUND);
    render();
}

int main(int argc, char **argv)
{
    char keyPress;
    bool AIPlay = argc == 2 && strcmp(argv[1], "-a") == 0 ? true : false;

    init();
    namedWindow("2048");

    while (true)
    {
        imshow("2048", img);

        keyPress = waitKey(20) & 0xFF;

        bool success = false;

        if (keyPress == 'q' || keyPress == 27)
            break;

        if (!AIPlay)
        {
            if (keyPress == 'w')
                success = ai.g.up();
            else if (keyPress == 'a')
                success = ai.g.left();
            else if (keyPress == 's')
                success = ai.g.down();
            else if (keyPress == 'd')
                success = ai.g.right();
        }else{
            success = ai.makeMove();
            if(!success){
                waitKey(0);
                break;
            }
        }

        if (success){
            ai.g.generateAPlace();
            render();
        }
    }

    destroyAllWindows();

    return 0;
}