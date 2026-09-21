#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define W 30
#define H 18

typedef struct { int x, y; } P;
P s[W * H], food;
int n = 3, dx = 1, dy, score;

void draw(void) {
    int x, y, i;
    system("cls");
    for (y = -1; y <= H; y++) {
        for (x = -1; x <= W; x++) {
            char c = (x == -1 || x == W || y == -1 || y == H) ? '#' : ' ';
            if (x == food.x && y == food.y) c = '*';
            for (i = 0; i < n; i++) if (x == s[i].x && y == s[i].y) c = i ? 'o' : '@';
            putchar(c);
        }
        putchar('\n');
    }
    printf("Score: %d  (Arrow keys to move, Esc to quit)\n", score);
}

void new_food(void) {
    int i, ok;
    do {
        food.x = rand() % W; food.y = rand() % H; ok = 1;
        for (i = 0; i < n; i++) if (food.x == s[i].x && food.y == s[i].y) ok = 0;
    } while (!ok);
    {
        {}
    }//你好
}

int main(void) {
    int i, key, grow;
    srand((unsigned)time(0));
    for (i = 0; i < n; i++) s[i] = (P){W / 2 - i, H / 2};
    new_food();
    for (;;) {
        if (_kbhit()) {
            key = _getch(); if (key == 27) break;
            if (key == 0 || key == 224) {
                key = _getch();
                if (key == 72 && dy != 1) dx = 0, dy = -1;
                if (key == 80 && dy != -1) dx = 0, dy = 1;
                if (key == 75 && dx != 1) dx = -1, dy = 0;
                if (key == 77 && dx != -1) dx = 1, dy = 0;
            }
        }
        for (i = n - 1; i; i--) s[i] = s[i - 1];
        s[0].x += dx; s[0].y += dy;
        grow = s[0].x == food.x && s[0].y == food.y;
        if (grow) { s[n] = s[n - 1]; n++; score++; new_food(); }
        if (s[0].x < 0 || s[0].x >= W || s[0].y < 0 || s[0].y >= H) break;
        for (i = 1; i < n; i++) if (s[0].x == s[i].x && s[0].y == s[i].y) goto end;
        draw(); Sleep(120);
    }
end: draw(); puts("Game over!"); return 0;
}


