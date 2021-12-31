#include<bits/stdc++.h>
using namespace std;

struct Point{
    int x, y;
    Point(){
        x = 0;
        y = 0;
    }

    Point(int x1, int y1){
        x = x1;
        y = y1;
    }
};

struct Line{

    int a, b, c; //ax + by + c = 0

    Line(){
        a = 0;
        b = 0;
        c = 0;
    }

    Line(Point p1, Point p2){
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = - a * p1.x - b * p1.y;

        int g = __gcd(__gcd(a, b), c);
        a /= g;
        b /= g;
        c /= g;
        if(a < 0 || (a == 0 && b < 0)){
            a *= -1;
            b *= -1;
            c *= -1;
        }
        
    }

    bool passesThru(Point p1){
        return a * p1.x + b * p1.y + c == 0;
    }
};
