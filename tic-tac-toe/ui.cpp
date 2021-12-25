#include "ai.h"
#include "opencv2/opencv.hpp"

#define OFFSET_IN_X 20
#define SIDE 512

using namespace cv;

Mat img(SIDE, SIDE, CV_8UC3);
bool isAINow = false;

// The game will be freezed when it is ended
bool freeze = false;

void drawCircle(int x, int y, int radius)
{
    radius *= 0.8;
    circle(img, Point(x, y), radius, Scalar(255, 255, 255), 3);
}

void drawX(Point lt, Point rb)
{
    line(img, Point(lt.x + OFFSET_IN_X, lt.y + OFFSET_IN_X), Point(rb.x - OFFSET_IN_X, rb.y - OFFSET_IN_X), Scalar(255, 255, 255), 3);
    line(img, Point(rb.x - OFFSET_IN_X, lt.y + OFFSET_IN_X), Point(lt.x + OFFSET_IN_X, rb.y - OFFSET_IN_X), Scalar(255, 255, 255), 3);
}

void drawBackground(Mat &img)
{
    line(img, Point(SIDE, 0), Point(SIDE, SIDE), Scalar(255, 255, 255), 3);
    line(img, Point(SIDE / 3.0, 0), Point(SIDE / 3.0, SIDE), Scalar(255, 255, 255), 3);
    line(img, Point(SIDE * 2 / 3.0, 0), Point(SIDE * 2 / 3.0, SIDE), Scalar(255, 255, 255), 3);
    line(img, Point(0, SIDE / 3.0), Point(SIDE, SIDE / 3.0), Scalar(255, 255, 255), 3);
    line(img, Point(0, SIDE * 2 / 3.0), Point(SIDE, SIDE * 2 / 3.0), Scalar(255, 255, 255), 3);
}

void render(Board *bptr)
{
    static Choice forDrawing[3][3] = {{Empty, Empty, Empty}, {Empty, Empty, Empty}, {Empty, Empty, Empty}};
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            if (forDrawing[i][j] != bptr->board[i][j])
            {
                printf("Draw: %x %d\n", i, j);
                if (bptr->board[i][j] == X)
                    drawX(Point(i * (SIDE / 3.0), j * (SIDE / 3.0)), Point((i + 1) * (SIDE / 3.0), (j + 1) * (SIDE / 3.0)));
                else if (bptr->board[i][j] == O)
                    drawCircle((i + 0.5) * (SIDE / 3.0), (j + 0.5) * (SIDE / 3.0), SIDE / 6.0);
                forDrawing[i][j] = bptr->board[i][j];
            }
        }
    }
}

void onMouse(int evt, int x, int y, int flags, void *param)
{
    if (!freeze && evt == EVENT_LBUTTONDOWN)
    {
        if (x > SIDE || y > SIDE)
            return;
        x = x / (float)(SIDE / 3.0);
        y = y / (float)(SIDE / 3.0);

        Board *bptr = (Board *)param;
        if (bptr->move({x, y}))
        {
            render(bptr);
            isAINow = true;
        }
    }
}

int main(void)
{
    //(y+1)ou are alw(y+1)s the first player in the ui
    AI ai('0');
    bool isUserQuit = false;

    drawBackground(img);
    namedWindow("tic-tac-toe");
    setMouseCallback("tic-tac-toe", onMouse, &ai.b);

    while (!isUserQuit && !ai.b.isEnd())
    {
        imshow("tic-tac-toe", img);
        char k = waitKey(20) & 0xFF;

        if (isAINow)
        {
            ai.move();
            render(&ai.b);
            isAINow = false;
        }

        // If press ESC or q, the game is over
        if (k == 'q' || k == 27)
            isUserQuit = true;
    }

    freeze = true;

    if (!isUserQuit)
    {
        int winner = ai.b.winner();
        if (winner == 0)
            putText(img, "Tie!", Point(SIDE/2 - 20, SIDE/2), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0, 215, 255), 2);
        else if (winner == 1)
            putText(img, "You won!", Point(SIDE/2 - 50, SIDE/2), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0, 215, 255), 2);
        else
            putText(img, "You lose!", Point(SIDE/2 - 50, SIDE/2), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0, 215, 255), 2);

        imshow("tic-tac-toe", img);
        waitKey(0);
    }

    destroyAllWindows();

    return 0;
}