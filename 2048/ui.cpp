#include "ai.h"
#include "opencv2/opencv.hpp"

using namespace cv;

#define SIDE 512
#define SQUARE_SIZE (SIDE / 4.0)
typedef cv::Point3_<uint8_t> Pixel;

// Color Set
#define BLACK Vec3b(0, 0, 0)

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
            ptr->x = color[0];
            ptr->y = color[1];
            ptr->z = color[2];
        }
    }
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
                fillSquare(j * SQUARE_SIZE, i * SQUARE_SIZE, SQUARE_SIZE, BLACK);

                char n[6];
                sprintf(n, "%d", ai.g.grid[i][j]);
                int size = strlen(n);
                char toShow[6];
                int index = 0;
                for (; index < (5 - size) / 2; index++)
                    toShow[index] = ' ';
                for (int k = 0; k < size; index++, k++)
                    toShow[index] = n[k];
                for (; index < 6; index++)
                    toShow[index] = ' ';

                if (ai.g.grid[i][j] != 0)
                    putText(img, String(n), Point(j * SQUARE_SIZE + (SQUARE_SIZE / 2) - 7, i * SQUARE_SIZE + (SQUARE_SIZE / 2) + 7), FONT_HERSHEY_COMPLEX, 0.5, Scalar(255, 255, 255));
                forDrawing[i][j] = ai.g.grid[i][j];
            }
        }
    }
}

int main(int argc, char **argv)
{
    char keyPress;
    bool AIPlay = argc == 2 && strcmp(argv[1], "-a") == 0 ? true : false;

    render();
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