#include <iostream>

class Shape {
public:
    char type;
};

class Line: public Shape {    //直线类，使用两点定义
public:
    int x1;
    int y1;   //第一个点的横纵坐标
    int x2;
    int y2;   //第二个点的横纵坐标
    Line(int x1, int y1, int x2, int y2);
    
};

Line::Line(int x1, int y1, int x2, int y2) {
    type = 'L';
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}

class Circle: public Shape {    //圆类，使用圆心-半径定义
public:
    int x;
    int y;
    int r;
    Circle(int x, int y, int r);
};

Circle::Circle(int x, int y, int r) {
    type = 'C';
    this->x = x;
    this->y = y;
    this->r = r;
}
