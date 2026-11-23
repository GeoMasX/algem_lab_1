#ifndef PAINT_H
#define PAINT_H

struct Point
{
    int x, y;
    void (*setCordinates)(struct Point *, int, int);
};

struct Screen
{
    int _height, _weight;
    int *_screen;
    void (*setPixel)(struct Screen *, struct Point *, int);
    int (*getPixel)(struct Screen *, struct Point *);
    void (*line)(struct Screen *, struct Point *, struct Point *, int);
    void (*screenPrint)(struct Screen *);
    void (*screenClear)(struct Screen *);
    void (*triangle)(struct Screen *, struct Point *, struct Point *, struct Point *, int);
    void (*floodFill4)(struct Screen *, struct Point *, int);
    void (*floodFill8)(struct Screen *, struct Point *, int);
};

void setCordinates(struct Point *p, int x, int y);
void setPixel(struct Screen *screen, struct Point *p, int color);
int getPixel(struct Screen *screen, struct Point *p);
void line(struct Screen *screen, struct Point *p1, struct Point *p2, int color);
void screen_init(struct Screen *screen, int weight, int height);
void screenPrint(struct Screen *screen);
void screenClear(struct Screen *screen);
void triangle(struct Screen *screen, struct Point *p1, struct Point *p2, struct Point *p3, int color);
void floodFill4(struct Screen *screen, struct Point *p, int color);
void floodFill8(struct Screen *screen, struct Point *p, int color);
void initPoint(struct Point *p, int x, int y);

#endif