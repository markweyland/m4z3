#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define W (5)
#define H (6)
#define S (W * H)

void gen_maze(int w, int h, int *maze);
void put_maze(int w, int h, int *maze);

int main(void) /* My programs don't fail. They crash. */
{
    int maze[S] = {0};
    gen_maze(W, H, maze);
    put_maze(W, H, maze);
    return EXIT_SUCCESS;
}

void gen_maze(int w, int h, int *maze)
{
    assert(maze != NULL);
    assert(w > 0);
    assert(h > 0);
    if (w > h) for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w / 2; ++j) maze[i * w + j] = w - 1 - j;
        for (int j = w / 2; j < w; ++j) maze[i * w + j] = j;
    }
    else for (int i = 0; i < w; ++i)
    {
        for (int j = 0; j < h / 2; ++j) maze[j * w + i] = h - 1 - j;
        for (int j = h / 2; j < h; ++j) maze[j * w + i] = j;
    }
}

void put_maze(int w, int h, int *maze)
{
    assert(maze != NULL);
    assert(w > 0);
    assert(h > 0);
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j) printf("%2d ", maze[i * w + j]);
        putchar('\n');
    }
}
