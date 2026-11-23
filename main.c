#include <stdio.h>
#include "paint.h"

void make_screen(struct Screen *screen)
{
    int w, h;
    printf("Input screen weight: ");
    scanf("%d", &w);
    printf("Input screen height: ");
    scanf("%d", &h);
    screen_init(screen, w, h);
}

void commands_list()
{
    printf("1 - clear \n");
    printf("2 x1 y1 x2 y2 color - make line with color \n");
    printf("3 x1 y1 x2 y2 x3 y3 color - make triangle circuit with color \n");
    printf("4 x y color - fill with color. 4-Flood fill algorithm. \n");
    printf("5 x y color - fill with color. 8-Flood fill algorithm. \n");
    printf("6 - print screen \n");
    printf("7 - exit \n");
    printf("* zeros are not shown \n");
}

int main()
{
    struct Screen screen;
    int op;
    int x1, y1, x2, y2, x3, y3, color;
    make_screen(&screen);
    commands_list();
    while (1)
    {
        scanf("%d", &op);
        if (op == 1)
        {
            screen.screenClear(&screen);
        }
        if (op == 2)
        {
            scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &color);
            struct Point p1;
            struct Point p2;
            initPoint(&p1, x1, y1);
            initPoint(&p2, x2, y2);
            screen.line(&screen, &p1, &p2, color);
        }
        if (op == 3)
        {
            scanf("%d %d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3, &color);
            struct Point p1;
            struct Point p2;
            struct Point p3;
            initPoint(&p1, x1, y1);
            initPoint(&p2, x2, y2);
            initPoint(&p3, x3, y3);
            screen.triangle(&screen, &p1, &p2, &p3, color);
        }
        if (op == 4)
        {
            scanf("%d %d %d", &x1, &y1, &color);
            struct Point p1;
            initPoint(&p1, x1, y1);
            screen.floodFill4(&screen, &p1, color);
        }
        if (op == 5)
        {
            scanf("%d %d %d", &x1, &y1, &color);
            struct Point p1;
            initPoint(&p1, x1, y1);
            screen.floodFill8(&screen, &p1, color);
        }
        if (op == 6)
        {
            screen.screenPrint(&screen);
        }
        if (op == 7)
        {
            break;
        }
    }
    return 0;
}