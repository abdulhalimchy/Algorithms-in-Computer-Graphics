/*
    Abdul Halim Chowdhury
    ID: 161-115-044
    CSE 38th B
*/
#include <windows.h>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#define pb push_back
#define mp make_pair
using namespace std;

double xmin, xmax, ymin, ymax;
vector<pair<double, double>> lines;     ///(x, y)
int n;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);

    //Drawing Window
    glBegin(GL_LINE_LOOP);
    glVertex2d(xmin, ymin);
    glVertex2d(xmax, ymin);
    glVertex2d(xmax, ymax);
    glVertex2d(xmin, ymax);
    glVertex2d(xmin, ymin);
    glEnd();

    glBegin(GL_LINES);
    for(int i=0; i<lines.size(); i+=2)
    {
        glColor3f(0.35,0.35,0.35);
        //Drawing Input Lines
        glVertex2d(lines[i].first, lines[i].second);
        glVertex2d(lines[i+1].first, lines[i+1].second);

        double p[4], q[4];
        p[1]=lines[i+1].first-lines[i].first;
        p[0]=-p[1];
        p[3]=lines[i+1].second-lines[i].second;
        p[2]=-p[3];

        q[0]=lines[i].first-xmin;
        q[1]=xmax-lines[i].first;
        q[2]=lines[i].second-ymin;
        q[3]=ymax-lines[i].second;

        bool flag=false;
        for(int j=0; j<4; j++)
        {
            if(p[j]==0 && q[j]<0)
            {
                flag=true;
                break;
            }
        }

        if(flag==true)
            continue;

        double u1=0, u2=1;
        for(int j=0; j<4; j++)
        {
            if(p[j]<0)
                u1=max(u1,q[j]/p[j]);
            else if(p[j]>0)
                u2=min(u2,q[j]/p[j]);
        }

        if(u1>u2)
            continue;

        glColor3f(0,1,0);
        //Drawing Clipped lines
        glVertex2d(lines[i].first+p[1]*u1, lines[i].second+p[3]*u1);
        glVertex2d(lines[i].first+p[1]*u2, lines[i].second+p[3]*u2);
    }
    glEnd();
    glFlush();
}
int main(int argc, char** argv)
{
    cout << "Window Bottom Left(x, y): ";
    cin >> xmin >> ymin;
    cout << "Window Top Right(x, y): ";
    cin >> xmax >> ymax;

    cout << "Number of lines: ";
    cin >> n;
    for(int i=0; i<n; i++)
    {
        double a, b;
        cin >> a >> b;
        lines.pb(mp(a, b));
        cin >> a >> b;
        lines.pb(mp(a, b));
    }

    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Liang Barsky Line Clipping");
    glClearColor(1,1,1,1);
    glOrtho(-100, 400, -150, 350, -1, 1);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
/*
0 0
300 200
22
70 249
-20 101
-50 219
40 66
-40 -66
40 66
80 280
45 -70
65 270
97 -50
62 100
82 100
104 230
104 -25
104 0
144 0
156 227
156 -20
150 230
176 100
176 100
202 230
196 238
196 -50
236 280
200 -80
218 100
238 100
222 260
257 -90
260 250
260 -37
255 228
305 -58
295 237
295 -50
310 -15
320 209
-50 -50
250 -80
-70 -27
-77 218
-22 257
295 287
*/
