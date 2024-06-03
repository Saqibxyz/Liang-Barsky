#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <dos.h>

int  main()
{
    int i, gd = DETECT, gm;
    int x1, y1, x2, y2, xmin, xmax, ymin, ymax, xx1, xx2, yy1, yy2, dx, dy;
    float t1, t2, p[4], q[4], temp;

    xmin = 100;
    ymin = 100;
    xmax = 250;
    ymax = 250;
    initgraph(&gd, &gm, "c:\\turboc3\\bgi");
    setcolor(GREEN);
    rectangle(xmin, ymin, xmax, ymax);
    printf("Enter (x1,y1) and (x2,y2)");
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    line(x1, y1, x2, y2);
    setcolor(WHITE);
    dx = x2 - x1;
    dy = y2 - y1;
    // calculate p0 ... p4
    p[0] = -dx;
    p[1] = dx;
    p[2] = -dy;
    p[3] = dy;
    // calculate q0 ... q4
    q[0] = x1 - xmin;
    q[1] = xmax - x1;
    q[2] = y1 - ymin;
    q[3] = ymax - y1;
    // check pi and qi
    for (i = 0; i < 4; i++)
    {
    	// if parallel
        if (p[i] == 0)
        {
            printf("line is parallel to one of the clipping boundary");
            // if inside or on the boundary
            if (q[i] >= 0)
            { 
                // vertical boundaries . left for i=0 or right for i=1
                if (i <= 1)
                {
                    if (y1 < ymin)
                    {
                        y1 = ymin;
                    }
                    if (y2 > ymax)
                    {
                        y2 = ymax;
                    }
                    line(x1, y1, x2, y2);
                }
                // horizantal boundaries bottom for i=2 and top for i=3
                if (i >= 2)
                {
                    if (x1 < xmin)
                    {
                        x1 = xmin;
                    }
                    if (x2 > xmax)
                    {
                        x2 = xmax;
                    }
                    line(x1, y1, x2, y2);
                }
            }
        }
    }
    // if not parallel
    // calculate t1 and t2
    t1 = 0;
    t2 = 1;
    
    for (i = 0; i < 4; i++)
    {
    	// calculate pi/qi
        temp = q[i] / p[i];
        // if pi is negative, take max t1
        if (p[i] < 0)
        {
        	//  takig max t1 among qi/pi
            if (t1 <= temp)
                t1 = temp;
        }
        else
        {
        	// taking min t2 among qi/pi
            if (t2 > temp)
                t2 = temp;
        }
    }
    // check if t1<t2 . this is from algorithm
    if (t1 < t2)
    {
    	// calculate coordinates. 
        xx1 = x1 + t1 * p[1];
        xx2 = x1 + t2 * p[1];
        yy1 = y1 + t1 * p[3];
        yy2 = y1 + t2 * p[3];
        line(xx1, yy1, xx2, yy2);
    }
    while(!kbhit());
    closegraph();
    return 0;
}
