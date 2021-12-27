#include "ai.h"
#include "opencv2/opencv.hpp"

using namespace cv;

#define OFFSET 200
#define SIDE 512
#define SQUARE_SIZE (SIDE / (float)size)
typedef cv::Point3_<uint8_t> Pixel;

Mat img(SIDE, SIDE + OFFSET, CV_8UC3);
int size = 9;
AI ai(size);
bool freeze = false;

// color is provided as RGB but opencv renders it as BGR
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

// When the level is reset, this function is called
void refresh()
{
    static int s = 9;
    if (s != size)
    {
        ai = AI(size);
        s = size;

        fillSquare(0, 0, SIDE, Vec3b(0, 0, 0));
    }
}

void background()
{
    for (int i = 0; i <= size; ++i)
    {
        line(img, Point(i * SQUARE_SIZE, 0), Point(i * SQUARE_SIZE, SIDE), Scalar(255, 255, 255), 3);
        line(img, Point(0, i * SQUARE_SIZE), Point(SIDE, i * SQUARE_SIZE), Scalar(255, 255, 255), 3);
    }
}

void render(int x, int y, bool untag)
{
    fillSquare(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, Vec3b(0, 0, 0));

    if (ai.b.grid[x][y] == -1)
    {
        fillSquare(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, Vec3b(255, 0, 0));
        putText(img, "O", Point(x * SQUARE_SIZE + (SQUARE_SIZE / 2) - 10, y * SQUARE_SIZE + (SQUARE_SIZE / 2) + 10), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 0));
    }
    else if (ai.b.taggedLocations.find({x, y}) != ai.b.taggedLocations.end())
    {
        putText(img, "^", Point(x * SQUARE_SIZE + (SQUARE_SIZE / 2) - 10, y * SQUARE_SIZE + (SQUARE_SIZE / 2) + 10), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
    }
    else if (!untag)
    {
        char text[2] = {(char)(ai.b.grid[x][y] + '0'), '\0'};
        putText(img, text, Point(x * SQUARE_SIZE + (SQUARE_SIZE / 2) - 10, y * SQUARE_SIZE + (SQUARE_SIZE / 2) + 10), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
    }

    background();
}

void init()
{
    background();

    // Render Number of Mines
    putText(img, "Mines", Point(SIDE + (OFFSET / 2) - 50, 30), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
    char text[4];
    sprintf(text, "%d", (int)(ai.b.factor * size * size));
    putText(img, text, Point(SIDE + (OFFSET / 2) - 10 * strlen(text), 70), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));

    // Render 9*9 Button
    rectangle(img, Point(SIDE + (OFFSET / 2) - 40, SIDE / 2), Point(SIDE + (OFFSET / 2) + 40, SIDE / 2 + 40), Scalar(255, 255, 255), 3);
    putText(img, "9", Point(SIDE + (OFFSET / 2) - 10, SIDE / 2 + 30), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));

    // Renderr 16*16 Button
    rectangle(img, Point(SIDE + (OFFSET / 2) - 40, SIDE / 2 + 80), Point(SIDE + (OFFSET / 2) + 40, SIDE / 2 + 120), Scalar(255, 255, 255), 3);
    putText(img, "16", Point(SIDE + (OFFSET / 2) - 20, SIDE / 2 + 110), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
}

// Function to check if 9 is clicked
bool click9(int x, int y)
{
    return x >= SIDE + (OFFSET / 2) - 40 && x <= SIDE + (OFFSET / 2) + 40 && y >= SIDE / 2 && y <= SIDE / 2 + 40;
}

bool click16(int x, int y)
{
    return x >= SIDE + (OFFSET / 2) - 40 && x <= SIDE + (OFFSET / 2) + 40 && y >= SIDE / 2 + 80 && y <= SIDE / 2 + 120;
}

void onClick(int evt, int x, int y, int flags, void *param)
{
    if (freeze)
        return;

    if (evt == EVENT_LBUTTONDOWN)
    {
        if (x > SIDE || y > SIDE)
        {
            if (click9(x, y))
            {
                size = 9;
                refresh();
            }
            else if (click16(x, y))
            {
                size = 16;
                refresh();
            }
        }
        else
        {
            x = x / SQUARE_SIZE;
            y = y / SQUARE_SIZE;

            ai.b.click({x, y});

            render(x, y, false);
        }
    }
    else if (evt == EVENT_RBUTTONDOWN)
    {
        if (x > SIDE || y > SIDE)
            return;

        x = x / SQUARE_SIZE;
        y = y / SQUARE_SIZE;

        // If already clicked, don't do anything
        if(ai.b.clickedLocations.find({x, y}) != ai.b.clickedLocations.end())
            return;

        bool untag = false;
        if (ai.b.taggedLocations.find({x, y}) != ai.b.taggedLocations.end())
        {
            ai.b.reset({x, y});
            untag = true;
        }
        else
            ai.b.tag({x, y});

        render(x, y, untag);
    }

    background();
}

int main(void)
{
    srand((unsigned int)time(NULL));

    char keyPress;

    init();
    namedWindow("demining");
    setMouseCallback("demining", onClick, nullptr);

    while (!ai.b.isEnd())
    {
        imshow("demining", img);
        if ((keyPress = (waitKey(20) & 0xFF)) == 'q' || keyPress == 27)
        {
            destroyAllWindows();
            return 0;
        }
    }
    freeze = true;

    if (ai.b.clickMine())
    {
        putText(img, "You lose", Point(SIDE + OFFSET / 2 - 80, 450), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
    }
    else
    {
        putText(img, "You win", Point(SIDE + OFFSET / 2 - 70, 450), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
    }
    imshow("demining", img);
    waitKey(0);

    destroyAllWindows();

    return 0;
}