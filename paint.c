#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "paint.h"
#include "stack.h"

void setCordinates(struct Point *p, int x, int y)
{
    p->x = x;
    p->y = y;
}

void initPoint(struct Point *p, int x, int y)
{
    p->setCordinates = setCordinates;
    p->x = x;
    p->y = y;
}

void screen_init(struct Screen *screen, unsigned int weight, unsigned int height)
{
    screen->_height = height;
    screen->_weight = weight;
    screen->_screen = calloc(height * weight, sizeof(int));
    screen->setPixel = setPixel;
    screen->getPixel = getPixel;
    screen->line = line;
    screen->screenClear = screenClear;
    screen->screenPrint = screenPrint;
    screen->triangle = triangle;
    screen->floodFill4 = floodFill4;
    screen->floodFill8 = floodFill8;
}

void setPixel(struct Screen *screen, struct Point *p, int color)
{
    screen->_screen[screen->_weight * p->y + p->x] = color;
}

int getPixel(struct Screen *screen, struct Point *p)
{
    return screen->_screen[screen->_weight * p->y + p->x];
}

void line(struct Screen *screen, struct Point *p1, struct Point *p2, int color)
{
    int dx = abs(p1->x - p2->x);
    int dy = abs(p1->y - p2->y);
    int sx = (p1->x < p2->x) ? 1 : -1;
    int sy = (p1->y < p2->y) ? 1 : -1;
    int err = dx - dy;
    struct Point p;
    initPoint(&p, p1->x, p1->y);
    screen->setPixel(screen, &p, color);
    while (p.x != p2->x || p.y != p2->y)
    {
        int err2 = 2 * err;
        if (err2 >= -dy)
        {
            err -= dy;
            p.x += sx;
        }
        if (err2 <= dx)
        {
            err += dx;
            p.y += sy;
        }
        screen->setPixel(screen, &p, color);
    }
}

void screenPrint(struct Screen *screen)
{
    struct Point p;
    for (int i = 0; i < screen->_height; i++)
    {
        for (int j = 0; j < screen->_weight; j++)
        {
            initPoint(&p, j, i);
            if (screen->getPixel(screen, &p) != 0)
                printf("%d", screen->getPixel(screen, &p));
            else
                printf(" ");
        }
        printf("\n");
    }
}

void screenClear(struct Screen *screen)
{
    struct Point p;
    for (int i = 0; i < screen->_height; i++)
    {
        for (int j = 0; j < screen->_weight; j++)
        {
            initPoint(&p, j, i);
            screen->setPixel(screen, &p, 0);
        }
    }
}

void triangle(struct Screen *screen, struct Point *p1, struct Point *p2, struct Point *p3, int color)
{
    screen->line(screen, p1, p2, color);
    screen->line(screen, p1, p3, color);
    screen->line(screen, p2, p3, color);
}

void floodFill4(struct Screen *screen, struct Point *start, int color)
{
    int curcolor = screen->getPixel(screen, start);
    if (curcolor == color)
        return;

    struct Stack st;
    init(&st, sizeof(struct Point));
    st.push(&st, start);

    struct Point cnt;
    while (!st.empty(&st))
    {
        st.pop(&st, &cnt);

        if (screen->getPixel(screen, &cnt) != curcolor)
            continue;

        screen->setPixel(screen, &cnt, color);

        if (cnt.x + 1 < screen->_weight)
        {
            struct Point nb;
            initPoint(&nb, cnt.x + 1, cnt.y);
            st.push(&st, &nb);
        }
        if (cnt.x >= 0)
        {
            struct Point nb;
            initPoint(&nb, cnt.x - 1, cnt.y);
            st.push(&st, &nb);
        }
        if (cnt.y + 1 < screen->_height)
        {
            struct Point nb;
            initPoint(&nb, cnt.x, cnt.y + 1);
            st.push(&st, &nb);
        }
        if (cnt.y >= 0)
        {
            struct Point nb;
            initPoint(&nb, cnt.x, cnt.y - 1);
            st.push(&st, &nb);
        }
    }

    st.clear(&st);
}

void floodFill8(struct Screen *screen, struct Point *start, int color)
{
    int curcolor = screen->getPixel(screen, start);
    if (curcolor == color)
        return;

    struct Stack st;
    init(&st, sizeof(struct Point));
    st.push(&st, start);

    struct Point cnt;
    while (!st.empty(&st))
    {
        st.pop(&st, &cnt);

        if (screen->getPixel(screen, &cnt) != curcolor)
            continue;

        screen->setPixel(screen, &cnt, color);

        if (cnt.x + 1 < screen->_weight)
        {
            struct Point nb;
            initPoint(&nb, cnt.x + 1, cnt.y);
            st.push(&st, &nb);
        }
        if (cnt.x > 0)
        {
            struct Point nb;
            initPoint(&nb, cnt.x - 1, cnt.y);
            st.push(&st, &nb);
        }
        if (cnt.y + 1 < screen->_height)
        {
            struct Point nb;
            initPoint(&nb, cnt.x, cnt.y + 1);
            st.push(&st, &nb);
        }
        if (cnt.y > 0)
        {
            struct Point nb;
            initPoint(&nb, cnt.x, cnt.y - 1);
            st.push(&st, &nb);
        }

        if (cnt.x + 1 < screen->_weight && cnt.y + 1 < screen->_height)
        {
            struct Point nb;
            initPoint(&nb, cnt.x + 1, cnt.y + 1);
            st.push(&st, &nb);
        }
        if (cnt.x > 0 && cnt.y + 1 < screen->_height)
        {
            struct Point nb;
            initPoint(&nb, cnt.x - 1, cnt.y + 1);
            st.push(&st, &nb);
        }
        if (cnt.x + 1 < screen->_weight && cnt.y > 0)
        {
            struct Point nb;
            initPoint(&nb, cnt.x + 1, cnt.y - 1);
            st.push(&st, &nb);
        }
        if (cnt.x > 0 && cnt.y > 0)
        {
            struct Point nb;
            initPoint(&nb, cnt.x - 1, cnt.y - 1);
            st.push(&st, &nb);
        }
    }

    st.clear(&st);
}