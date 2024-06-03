#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <dos.h>

int main()
{
    int i, gd = DETECT, gm;
    int x1, y1, x2, y2, xmin, xmax, ymin, ymax, xx1, xx2, yy1, yy2, dx, dy;
    float t1, t2, p[4], q[4], temp;

    xmin = 100;
    ymin = 100;
    xmax = 250;
    ymax = 250;
    initgraph(&gd, &gm, (char*)"");
    setcolor(GREEN);
    rectangle(xmin, ymin, xmax, ymax);
    printf("Enter (x1,y1) and (x2,y2)");
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    line(x1, y1, x2, y2);
    setcolor(WHITE);
     dx = x2 - x1;
    dy = y2 - y1;
    p[0] = -dx;
    p[1] = dx;
    p[2] = -dy;
    p[3] = dy;
    q[0] = x1 - xmin;
    q[1] = xmax - x1;
    q[2] = y1 - ymin;
    q[3] = ymax - y1;

    t1 = 0;
    t2 = 1;
    for (i = 0; i < 4; i++)
    {
        if (p[i] == 0)
        {
            if (q[i] < 0)
            {
                printf("Line is outside the clipping window.\n");
                getch();
                closegraph();
                return 0;
            }
        }
        else
        {
            temp = q[i] / p[i];
            if (p[i] < 0)
            {
                if (t1 < temp)
                    t1 = temp;
            }
            else
            {
                if (t2 > temp)
                    t2 = temp;
            }
        }
    }
    if (t1 > t2)
    {
        printf("Line is outside the clipping window.\n");
        getch();
        closegraph();
        return 0;
    }

    xx1 = x1 + t1 * dx;
    xx2 = x1 + t2 * dx;
    yy1 = y1 + t1 * dy;
    yy2 = y1 + t2 * dy;
    setcolor(RED);
    line(xx1, yy1, xx2, yy2);

    getch();
    closegraph();
    return 0;
}
