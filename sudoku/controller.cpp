#include "controller.h"

bool isDigit(const char c)
{
    return (c >= '1' && c <= '9');
}

void Controller::fillSquare(int x, int y, int length)
{
    for (int r = y; r < y+length; ++r)
    {
        Pixel *ptr = img.ptr<Pixel>(r, x);
        const Pixel *ptr_end = ptr + length;
        for (; ptr != ptr_end; ++ptr)
        {
            ptr->x = 0;
            ptr->y = 0;
            ptr->z = 0;
        }
    }
}

void Controller::generate(){
    do
    {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                ai.b(i, j) = 0;
        ai.build();
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                original(i, j) = ai.b(i, j);
    } while (!ai.solve());

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            ai.b(i, j) = original(i, j);
}

void Controller::init()
{
    for (int i = 0; i < 10; i++)
    {
        line(img, Point(i * SQUARE_SIZE, 0), Point(i * SQUARE_SIZE, SIDE), Scalar(255, 255, 255), 3);
        line(img, Point(0, i * SQUARE_SIZE), Point(SIDE, i * SQUARE_SIZE), Scalar(255, 255, 255), 3);
    }

    putText(img, "Current Number", Point(SIDE + 30, 30), FONT_HERSHEY_COMPLEX, 0.5, Scalar(255, 255, 255));
    rectangle(img, Point(SIDE + (OFFSET / 2) - 20, 50), Point(SIDE + (OFFSET / 2) + 20, 90), Scalar(255, 255, 255), 3);

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(ai.b.grid[i][j] != 0){
                char n[2] = {char(ai.b.grid[i][j] + '0')};
                putText(img, String(n), Point(i * SQUARE_SIZE + (SQUARE_SIZE / 2) - 7, j * SQUARE_SIZE + (SQUARE_SIZE / 2) + 7), FONT_HERSHEY_COMPLEX, 0.5, Scalar(255, 255, 255));
            }
        }
    }

    // Render Solve Button
    rectangle(img, Point(SIDE + (OFFSET / 2) - 80, 250), Point(SIDE + (OFFSET / 2) + 80, 300), Scalar(255, 255, 255), 3);
    putText(img, "Solve", Point(SIDE + (OFFSET / 2) - 20, 280), FONT_HERSHEY_COMPLEX, 0.5, Scalar(255, 255, 255));

    // Render Current Number
    renderCurrentNumber();
}

void Controller::renderCurrentNumber(){
    static int currentNumberForDrawing = -1;
    if (currentNumberForDrawing != curNum)
    {
        // Refill the square of the current number
        fillSquare(SIDE + (OFFSET / 2) - 10, 60, 20);
        char n[2] = {char(curNum + '0')};
        putText(img, String(n), Point(SIDE + (OFFSET / 2) - 7, 75), FONT_HERSHEY_COMPLEX, 0.5, Scalar(255, 255, 255));
        currentNumberForDrawing = curNum;
    }
}

void Controller::render(int x, int y)
{
    // Refill the square of the grid
    fillSquare(x * SQUARE_SIZE + 5, y * SQUARE_SIZE + 5, SQUARE_SIZE - 10);
    char n[2] = {char(ai.b.grid[x][y] + '0')};
    putText(img, String(n), Point(x * SQUARE_SIZE + (SQUARE_SIZE / 2) - 7, y * SQUARE_SIZE + (SQUARE_SIZE / 2) + 7), FONT_HERSHEY_COMPLEX, 0.5, Scalar(255, 255, 255));
}

void Controller::solve(){
    fillSquare(SIDE + (OFFSET / 2) - 50, 350, 100);

    Board backup;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            backup(i, j) = ai.b(i, j);

    bool b = ai.solve();

    if(!b){
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                ai.b(i, j) = backup(i, j);
        // Render Unsolvable
        putText(img, "Unsolvable", Point(SIDE + (OFFSET / 2) - 50, 400), FONT_HERSHEY_COMPLEX, 0.5, Scalar(255, 255, 255));
    }else{
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                render(i, j);
        freeze = true;
    }
}

bool clickSolve(int x, int y){
    return x >= SIDE + (OFFSET / 2) - 80 && x <= SIDE + (OFFSET / 2) + 80 && y >= 250 && y <= 300;
}

void onClick(int evt, int x, int y, int flags, void *param){
    Controller* cptr = (Controller*)param;
    if(!cptr->freeze && evt == EVENT_LBUTTONDOWN){
        if(x > SIDE || y > SIDE){
            if(clickSolve(x, y))
                cptr->solve();
            return;
        }

        x = x / SQUARE_SIZE;
        y = y / SQUARE_SIZE;
        if(cptr->original(x, y) == 0){
            cptr->ai.b(x, y) = cptr->curNum;
            cptr->render(x, y);
        }
    }
}

// Press the number and click the square to place the chosen number
void Controller::show()
{
    generate();
    init();

    namedWindow("sudoku");
    setMouseCallback("sudoku", onClick, this);

    char c;
    while (1)
    {
        imshow("sudoku", img);
        if(isDigit((c = (waitKey(20) & 0xFF)))){
            curNum = c - '0';
            renderCurrentNumber();
        }

        if (c == 27 || c == 'q')
            break;
    }

    destroyAllWindows();
}