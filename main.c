#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define W (7)
#define H (3)
#define S (W * H)

void gen_maze(int w, int h, int *maze);
bool chk_maze(int w, int h, const int *maze, bool *visited);
bool can_go_r(int w, int x, int n); /* right */
bool can_go_l(int x, int n); /* left  */
bool can_go_u(int y, int n); /* up */
bool can_go_d(int h, int y, int n); /* down */
void put_maze(int w, int h, const int *maze);

int main(void) /* My programs don't fail. They crash. */
{
    int maze[S] = {1, 1, 1, 1, 1, 1};
    bool visited[S] = {false};
    srand(time(NULL));
    do gen_maze(W, H, maze); while (chk_maze(W, H, maze, visited) == false);
    put_maze(W, H, maze);
    return EXIT_SUCCESS;
}

void gen_maze(int w, int h, int *maze)
{
    assert(w > 1);
    assert(h > 1);
    assert(maze != NULL);

    if (w > h) for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w / 2; ++x) maze[y * w + x] = rand() % (w - 1 - x) + 1;
        for (int x = w / 2; x < w; ++x) maze[y * w + x] = rand() % x + 1;
    }
    else for (int x = 0; x < w; ++x)
    {
        for (int y = 0; y < h / 2; ++y) maze[y * w + x] = rand() % (h - 1 - y) + 1;
        for (int y = h / 2; y < h; ++y) maze[y * w + x] = rand() % y + 1;
    }
}

bool chk_maze(int w, int h, const int *maze, bool *visited)
{
    assert(w > 1);
    assert(h > 1);
    assert(maze != NULL);
    assert(visited != NULL);

    for (int i = 0; i < w * h; ++i) visited[i] = false;
    visited[0] = true;
    for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x)
    {
        int n = maze[y * w + x];
        if (can_go_r(w, x, n)) visited[y * w + (x + n)] = true;
        if (can_go_l(x, n)) visited[y * w + (x - n)] = true;
        if (can_go_u(y, n)) visited[(y - n) * w + x] = true;
        if (can_go_d(h, y, n)) visited[(y + n) * w + x] = true;
    }
    for (int i = 0; i < w * h; ++i) if (visited[i] == false) return false;
    return true;
}

bool can_go_r(int w, int x, int n)
{
    return x + n < w;
}

bool can_go_l(int x, int n)
{
    return x - n >= 0;
}

bool can_go_u(int y, int n)
{
    return y - n >= 0;
}

bool can_go_d(int h, int y, int n)
{
    return y + n < h;
}

void put_maze(int w, int h, const int *maze)
{
    assert(w > 1);
    assert(h > 1);
    assert(w <= 100);
    assert(h <= 100);
    assert(maze != NULL);

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x) printf("%2d ", maze[y * w + x]);
        putchar('\n');
    }
}
