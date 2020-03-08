#include <iostream>
#include <fstream>
#include <cmath>
#include <set>
#include <list>
#include "class.h"

using namespace std;

Shape *shapeList[500000];

class Solve {
public:
    int num;
    int cnt;
    set<pair<double, double>> interSet;
    
    Solve(int num);
    int getSolve();
    void addShape(Shape *s);
    void getIntersect(Shape* s1, Shape* s2, set<pair<double, double>>* interSet);
    void LLintersect(Line* l1, Line* l2, set<pair<double, double>>* interSet);
    void CCintersect(Circle* c1, Circle* c2, set<pair<double, double>>* interSet);
    void CLintersect(Circle* c1, Line* l2, set<pair<double, double>>* interSet);
};

Solve::Solve(int num) {
    this->num = num;
    cnt = 0;
}

int Solve::getSolve() {
    for (int i = 0; i < num; i++) {
        for (int j = i + 1; j < num; j++) {
            getIntersect(shapeList[i], shapeList[j], &interSet);
        }
    }
    return (int)interSet.size();
}

void Solve::addShape(Shape *s) {
    shapeList[cnt++] = s;
}

void Solve::getIntersect(Shape* s1, Shape* s2, set<pair<double, double>>* interSet) {   //计算两条图形的交点
    char t1, t2;
    t1 = s1->type;
    t2 = s2->type;
    if (t1 == 'L' && t2 == 'L') {   //求两直线的交点
        LLintersect((Line*)s1, (Line*)s2, interSet);
    }
    else if (t1 == 'C' && t2 == 'C') {  //求两圆的交点
        CCintersect((Circle*)s1, (Circle*)s2, interSet);
    }
    else {  //求直线与圆的交点
        if (s1->type == 'L' && s2->type == 'C') {
            CLintersect((Circle*)s2, (Line*)s1, interSet);
        }
        else if (s1->type == 'C' && s2->type == 'L') {
            CLintersect((Circle*)s1, (Line*)s2, interSet);
        }
        else {
            cout << "something goes wrong!" << endl;
        }
    }
}

void Solve::LLintersect(Line* l1, Line* l2, set<pair<double, double>>* interSet) {
    double a1 = (double)l1->y1 - l1->y2;
    double b1 = (double)l1->x2 - l1->x1;
    double c1 = (double)l1->x1 * l1->y2 - (double)l1->x2 * l1->y1;  //l1: a1x + b1y + c1 = 0
    double a2 = (double)l2->y1 - l2->y2;
    double b2 = (double)l2->x2 - l2->x1;
    double c2 = (double)l2->x1 * l2->y2 - (double)l2->x2 * l2->y1;  //l2: a2x + b2y + c2 = 0
    double d = a1 * b2 - a2 * b1;
    if (d == 0) {   //d == 0时两直线平行
        return;
    }
    else {
        double x = (b1 * c2 - b2 * c1) / d;
        double y = (a2 * c1 - a1 * c2) / d;
        (*interSet).insert(pair<double, double>(x, y));
        return;
    }
}

void Solve::CCintersect(Circle* c1, Circle* c2, set<pair<double, double>>* interSet) {
    double a1 = c1->x;
    double b1 = c1->y;
    double r1 = c1->r;
    double a2 = c2->x;
    double b2 = c2->y;
    double r2 = c2->r;
    if ((pow((a1 - a2), 2) + pow((b1 - b2), 2)) > pow(r1 + r2, 2)) {
        return; //两圆不相交
    }
    else {
        double value1 = a1 * a1 - 2 * a1 * a2 + a2 * a2 + b1 * b1 - 2 * b1 * b2 + b2 * b2;
        double value2 = -r1 * r1 * a1 + r1 * r1 * a2 + r2 * r2 * a1 - r2 * r2 * a2 + a1 * a1 * a1 - a1 * a1 * a2 - a1 * a2 * a2 + a1 * b1 * b1 - 2 * a1 * b1 * b2 + a1 * b2 * b2 + a2 * a2 * a2 + a2 * b1 * b1 - 2 * a2 * b1 * b2 + a2 * b2 * b2;
        double value3 = -r1 * r1 * b1 + r1 * r1 * b2 + r2 * r2 * b1 - r2 * r2 * b2 + a1 * a1 * b1 + a1 * a1 * b2 - 2 * a1 * a2 * b1 - 2 * a1 * a2 * b2 + a2 * a2 * b1 + a2 * a2 * b2 + b1 * b1 * b1 - b1 * b1 * b2 - b1 * b2 * b2 + b2 * b2 * b2;
        double sigma = sqrt((r1 * r1 + 2 * r1 * r2 + r2 * r2 - a1 * a1 + 2 * a1 * a2 - a2 * a2 - b1 * b1 + 2 * b1 * b2 - b2 * b2) * (-r1 * r1 + 2 * r1 * r2 - r2 * r2 + value1));

        double p1_x = (value2 - sigma * b1 + sigma * b2) / (2 * value1);
        double p2_x = (value2 + sigma * b1 - sigma * b2) / (2 * value1);
        double p1_y = (value3 + sigma * a1 - sigma * a2) / (2 * value1);
        double p2_y = (value3 - sigma * a1 + sigma * a2) / (2 * value1);

        (*interSet).insert(pair<double, double>(p1_x, p1_y));
        (*interSet).insert(pair<double, double>(p2_x, p2_y));
        return;
    }
}

void Solve::CLintersect(Circle* circle1, Line* line2, set<pair<double, double>>* interSet) {
    double a = circle1->x;
    double b = circle1->y;
    double r = circle1->r;
    double a1 = (double)line2->y1 - line2->y2;
    double b1 = (double)line2->x2 - line2->x1;
    double c1 = (double)line2->x1 * line2->y2 - (double)line2->x2 * line2->y1;  //l2: a1x + b1y + c1 = 0

    double d = abs((a1 * a + b1 * b + c1) / sqrt(a1 * a1 + b1 * b1));
    if (d > r) {    //圆与直线不相交
        return;
    }
    else {
        if (a1 == 0) {
            double y = -c1 / b1;
            double p1_x = sqrt(r * r + (y - b) * (y - b)) + a;
            double p2_x = -sqrt(r * r + (y - b) * (y - b)) + a;
            (*interSet).insert(pair<double, double>(p1_x, y));
            (*interSet).insert(pair<double, double>(p2_x, y));
        }
        else {
            double p1_x = -(c1 - (b1 * (b1 * c1 + a1 * sqrt(-a * a * a1 * a1 - 2 * a * a1 * b * b1 - 2 * a * a1 * c1 + a1 * a1 * r * r - b * b * b1 * b1 - 2 * b * b1 * c1 + b1 * b1 * r * r - c1 * c1) - a1 * a1 * b + a * a1 * b1)) / (a1 * a1 + b1 * b1)) / a1;
            double p2_x = -(c1 - (b1 * (b1 * c1 - a1 * sqrt(-a * a * a1 * a1 - 2 * a * a1 * b * b1 - 2 * a * a1 * c1 + a1 * a1 * r * r - b * b * b1 * b1 - 2 * b * b1 * c1 + b1 * b1 * r * r - c1 * c1) - a1 * a1 * b + a * a1 * b1)) / (a1 * a1 + b1 * b1)) / a1;
            double p1_y = -(b1 * c1 + a1 * sqrt(-a * a * a1 * a1 - 2 * a * a1 * b * b1 - 2 * a * a1 * c1 + a1 * a1 * r * r - b * b * b1 * b1 - 2 * b * b1 * c1 + b1 * b1 * r * r - c1 * c1) - a1 * a1 * b + a * a1 * b1) / (a1 * a1 + b1 * b1);
            double p2_y = -(b1 * c1 - a1 * sqrt(-a * a * a1 * a1 - 2 * a * a1 * b * b1 - 2 * a * a1 * c1 + a1 * a1 * r * r - b * b * b1 * b1 - 2 * b * b1 * c1 + b1 * b1 * r * r - c1 * c1) - a1 * a1 * b + a * a1 * b1) / (a1 * a1 + b1 * b1);
            (*interSet).insert(pair<double, double>(p1_x, p1_y));
            (*interSet).insert(pair<double, double>(p2_x, p2_y));
        }
        return;
    }

}

int main(int argc, const char* argv[]) {
    ifstream fin(argv[2], ios::in);
    ofstream fout(argv[4], ios::out);
    int num = 0;
    cin >> num;
    Solve *sol = new Solve(num);
    for (int i = 0; i < num; i++) {
        char type;
        cin >> type;
        if (type == 'L') {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            Line* newline = new Line(x1, y1, x2, y2);
            sol->addShape(newline);
        }
        else {
            int x, y, r;
            cin >> x >> y >> r;
            Circle* newcircle = new Circle(x, y, r);
            sol->addShape(newcircle);
        }
    }

    cout << sol->getSolve() << endl;

    fin.close();
    fout.close();
    return 0;
}

