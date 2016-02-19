/// Check if inverted (horizontally, vertically, diagonally: 8 combinations)
/// mazes are solvable. Use path construction method. Use exhaustion method.

#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define W (6)
#define H (6)
#define S (W * H)

typedef struct Track
{
    int x, y;
    bool tried_r, tried_l, tried_u, tried_d;
} Track;

void gen_maze(int w, int h, int *maze);
bool chk_maze(int w, int h, const int *maze, bool *visited);
bool can_go_r(int w, int x, int n); /* right */
bool can_go_l(int x, int n); /* left  */
bool can_go_u(int y, int n); /* up */
bool can_go_d(int h, int y, int n); /* down */
bool solve_maze(int w, int h, const int *maze, bool *visited, Track *tracks);
void put_maze(int w, int h, const int *maze);
void put_solution(int s, const Track *tracks);

int main(void) /* My programs don't fail. They crash. */
{
    int maze[S] = {0};
    bool visited[S] = {false};
    Track tracks[S] = {{0, 0, false, false, false, false}};
    srand(time(NULL));
    do
    {
        gen_maze(W, H, maze);
    } while (!(chk_maze(W, H, maze, visited) && solve_maze(W, H, maze, visited, tracks)));

    put_maze(W, H, maze);
    put_solution(S, tracks);
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
        for (int y = 0; y < h / 2; ++y) maze[y * w + x] = rand() % (h - 1 - y ) + 1;
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

bool solve_maze(int w, int h, const int *maze, bool *visited, Track *tracks)
{
    assert(w > 1);
    assert(h > 1);
    assert(maze != NULL);
    assert(visited != NULL);
    assert(tracks != NULL);

    for (int i = 0; i < w * h; ++i)
    {
        visited[i] = false;
        tracks[i] = (Track) {0, 0, false, false, false, false};
    }
    visited[0] = true;

    for (int depth = 0; depth < w * h - 1;)
    {
        int x = tracks[depth].x, y = tracks[depth].y, n = maze[y * w + x];
        if (tracks[depth].tried_r == false)
        {
            tracks[depth].tried_r = true;
            if (can_go_r(w, x, n) && !visited[y * w + (x + n)])
            {
                depth += 1;
                tracks[depth].x = x + n;
                tracks[depth].y = y;
                visited[y * w + (x + n)] = true;
            }
        }
        else if (tracks[depth].tried_l == false)
        {
            tracks[depth].tried_l = true;
            if (can_go_l(x, n) && !visited[y * w + (x - n)])
            {
                depth += 1;
                tracks[depth].x = x - n;
                tracks[depth].y = y;
                visited[y * w + (x - n)] = true;
            }
        }
        else if (tracks[depth].tried_u == false)
        {
            tracks[depth].tried_u = true;
            if (can_go_u(y, n) && !visited[(y - n) * w + x])
            {
                depth += 1;
                tracks[depth].x = x;
                tracks[depth].y = y - n;
                visited[(y - n) * w + x] = true;
            }
        }
        else if (tracks[depth].tried_d == false)
        {
            tracks[depth].tried_d = true;
            if (can_go_d(h, y, n) && !visited[(y + n) * w + x])
            {
                depth += 1;
                tracks[depth].x = x;
                tracks[depth].y = y + n;
                visited[(y + n) * w + x] = true;
            }
        }
        else if (depth > 0)
        {
            visited[y * w + x] = false;
            tracks[depth] = (Track) {0, 0, false, false, false, false};
            depth -= 1;
        }
        else return false;
    }

    for (int i = 0; i < w * h; ++i)
    {
        assert(visited[i]);
        assert(tracks[i].x >= 0);
        assert(tracks[i].x < w);
        assert(tracks[i].y >= 0);
        assert(tracks[i].y < h);
    }

    return true;
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

void put_solution(int s, const Track *tracks)
{
    assert(s >= 4);
    assert(tracks != NULL);

    for (int i = 1; i < s; ++i)
    {
        if (tracks[i].x > tracks[i-1].x) putchar('R'); else
        if (tracks[i].x < tracks[i-1].x) putchar('L'); else
        if (tracks[i].y < tracks[i-1].y) putchar('U'); else
        if (tracks[i].y > tracks[i-1].y) putchar('D'); else abort();
    }
    putchar('\n');
}
