#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 30
#define HEIGHT 15
#define MAX_TAIL 200

int gameOver;
int x, y;
int fruitX, fruitY;
int score;
int tailX[MAX_TAIL], tailY[MAX_TAIL];
int nTail = 0;
int dir;

void Setup() {
    gameOver = 0;
    dir = 1;
    x = WIDTH / 2;
    y = HEIGHT / 2;

    srand(time(NULL));
    fruitX = rand() % (WIDTH - 2) + 1;
    fruitY = rand() % (HEIGHT - 2) + 1;
    score = 0;
}

void Draw() {
    system("cls");

    for (int i = 0; i < WIDTH; i++) printf("-");
    printf("\n");

    for (int i = 1; i < HEIGHT - 1; i++) {
        for (int j = 0; j < WIDTH; j++) {

            if (j == 0 || j == WIDTH - 1)
                printf("|");
            else if (i == y && j == x)
                printf("O");
            else if (i == fruitY && j == fruitX)
                printf("*");
            else {
                int printed = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printed = 1;
                        printf("o");
                        break;
                    }
                }
                if (!printed) printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH; i++) printf("-");
    printf("\n");

    printf("Score: %d\n", score);
}

void Input() {
    if (kbhit()) {
        int c = getch();

        if (c == 224) {
            int arrow = getch();
            if (arrow == 75) dir = 1;  // ←
            else if (arrow == 77) dir = 2; // →
            else if (arrow == 72) dir = 3; // ↑
            else if (arrow == 80) dir = 4; // ↓
        }

        if (c == 'q') gameOver = 1;
    }
}

void Logic() {
    int prevX = x;
    int prevY = y;
    int prev2X, prev2Y;

    for (int i = 0; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case 1: x--; break;
        case 2: x++; break;
        case 3: y--; break;
        case 4: y++; break;
    }

    if (x <= 0 || x >= WIDTH - 1 || y <= 0 || y >= HEIGHT - 1)
        gameOver = 1;

    if (x == fruitX && y == fruitY) {
        score += 1
        ;
        nTail++;

        fruitX = rand() % (WIDTH - 2) + 10;
        fruitY = rand() % (HEIGHT - 2) + 5;
    }

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;
    }
}

int main() {
    Setup();

    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(200);
    }

    printf("Game Over! Score: %d\n", score);
    return 0;
}
