#include <iostream>
#include <cmath>
#include <sstream>

class Point {
public:
    double x, y;

    void set(double x, double y) {
        this->x = x;
        this->y = y;
    }

    Point get() {
        return Point(this->x, this->y);
    }

    Point() :x(0), y(0) {}

    Point(double x, double y) : x(x), y(y) {}

    Point(const Point& a) : x(a.x), y(a.y) {}

    ~Point() {}
};

class Segment {
public:
    Point a, b;

    void set(Point a, Point b) {
        this->a = a;
        this->b = b;
    }

    Segment get() {
        return Segment(this->a, this->b);
    }

    void show() {
        std::cout << "A: (" << this->a.x << ", " << this->a.y << ") B: (" << this->b.x << ", " << this->b.y << ")" << std::endl;
    }

    double Length() {
        return sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y),2));
    }

    double Tan() {
        return (b.y - a.y) / (b.x - a.x);
    }

    Point Center() {
        return Point((a.x + b.x) / 2, (a.y + b.y) / 2);
    }

    Segment Orthogonal(double x, double y) {
        return Segment(Point(x, y), Point(x - (this->b.y - this->a.y), y + (this->b.x - this->a.x)));
    }
    
    Segment Orthogonal(Point a) {
        return Segment(Point(a.x, a.y), Point(a.x - (this->b.y - this->a.y), a.y + (this->b.x - this->a.x)));
    }

    //isPoint т.к. имеется класс Point(возникают ошибки)
    int isPoint(double x, double y) {
        return Segment(this->a, Point(x, y)).Length() + Segment(Point(x, y), this->b).Length() == Segment(this->a, this->b).Length() ? 1 : 0;
    }

    int isPoint(Point a) {
        return Segment(this->a, a).Length() + Segment(a, this->b).Length() == Segment(this->a, this->b).Length() ? 1 : 0;
    }

    Segment Turn(double x, double y, double alfa) {
        return Segment(
            Point((this->a.x - x) * cos(alfa) - (this->a.y - y) * sin(alfa) + x,(this->a.x - x) * sin(alfa) + (this->a.y - y) * cos(alfa) + y),
            Point((this->b.x - x) * cos(alfa) - (this->b.y - y) * sin(alfa) + x, (this->b.x - x) * sin(alfa) + (this->b.y - y) * cos(alfa) + y)
            );
    }

    Segment Turn(Point a, double alfa) {
        return Segment(
            Point((this->a.x - a.x) * cos(alfa) - (this->a.y - a.y) * sin(alfa) + a.x, (this->a.x - a.x) * sin(alfa) + (this->a.y - a.y) * cos(alfa) + a.y),
            Point((this->b.x - a.x) * cos(alfa) - (this->b.y - a.y) * sin(alfa) + a.x, (this->b.x - a.x) * sin(alfa) + (this->b.y - a.y) * cos(alfa) + a.y)
        );
    }

    std::string Line() { 
        std::stringstream res;
        res << "(x-" << this->a.x << ")/(" << this->b.x << "-" << this->a.x << ") = (y-" << this->a.y << ")/(" << this->b.y << "-" << this->a.y << ")";
        return res.str();
    }

    double operator +(const Segment& ab) {
        return Segment(this->a, this->b).Length() + Segment(ab.a, ab.b).Length();
    }

    double operator -(const Segment& ab) {
        return abs(Segment(this->a, this->b).Length() - Segment(ab.a, ab.b).Length());
    }

    int operator <(const Segment& ab) {
        return Segment(this->a, this->b).Length() < Segment(ab.a, ab.b).Length() ? 1 : 0;
    }

    int operator >(const Segment& ab) {
        return Segment(this->a, this->b).Length() > Segment(ab.a, ab.b).Length() ? 1 : 0;
    }

    int operator =(const Segment& ab) {
        return Segment(this->a, this->b).Length() == Segment(ab.a, ab.b).Length() ? 1 : 0;
    }
    //параллельный перенос
    Segment operator ||(const Segment& ab) {
        return Segment(Point(this->a.x += ab.b.x - ab.a.x , this->a.y += ab.b.y - ab.a.y),
                       Point(this->b.x += ab.b.x - ab.a.x, this->b.y += ab.b.y - ab.a.y));
        
    }
    //проверка на параллельность(возможно ошибка в условии лабы, нельзя дважды перегрузить один оператор принимающий одинаковые значение справа)
    int operator /(const Segment& ab) {
        return Segment(this->a, this->b).Length() / (this->b.x - this->a.x) == Segment(ab.a, ab.b).Length() / (ab.b.x - ab.a.x);
    }

    int operator |(const Segment& ab) {
        return (this->a.x - this->b.x) * (ab.a.x - ab.b.x) + (this->a.y - this->b.y) * (ab.a.y - ab.b.y) == 0 ? 1 : 0;
    }

    Segment operator *(const int n) {
        Segment me = Segment(this->a, this->b);
        return Segment(Point(me.Center().x - ((me.Center().x - this->a.x) * n), me.Center().y - (me.Center().x - this->a.y ) * n),
        Point(me.Center().x + (this->b.x - me.Center().x) * n, me.Center().y + (this->b.y - me.Center().y) * n)
        );
    }

    Segment() : a(Point()), b(Point()) {}

    Segment(Point a, Point b) : a(a), b(b) {}

    Segment(const Segment& ab) : a(ab.a), b(ab.b) {}

    ~Segment() {}
};

int main()
{
    setlocale(LC_ALL, "RU");

    Segment a = Segment(Point(0, 0), Point(2, 2));
    Segment b = Segment(Point(0, 0), Point(1, 1));

    std::cout << "Длинна отрезка а: " << a.Length() << std::endl;
    std::cout << "Тагненс угла наклона а к положительному направлению оси Ох: " << a.Tan() << std::endl;
    std::cout << "Середина отрезка а: (" << a.Center().x << ", " << a.Center().y << ")" << std::endl;
    std::cout << "Отрезок перпендикулярный а проходящий через (2, 3) мне прямой содержащей отрезок а - ";
    a.Orthogonal(2,3).show();
    std::cout << "Лежит ли точка (1, 1) на отрезке a: " << a.isPoint(Point(1, 1)) << std::endl;
    std::cout << "Лежит ли точка (1,-1) на отрезке a: " << a.isPoint(Point(1, -1)) << std::endl;
    std::cout << "Поворот отрезка а на 90° относительно точки (1, 1) ";
    a.Turn(1,1, 90).show();
    std::cout << "Каноническое уравнение прямой, на которой лежит отрезок а: " << a.Line()  << std::endl;
    std::cout << "Сравнение длин отрезков a и b: a < b ? " << (a < b) << " a > b ? " << (a > b) << std::endl;
    std::cout << "a = b ? " << (a = b) << std::endl;
    std::cout << "Растяжение на 2 ";
    (a * 2).show();
    std::cout << "параллельный перенос a на вектор b: ";
    (a || b).show();
    std::cout << "Проверка на параллельность отрезков a и b: " << (a / b) << std::endl;
    std::cout << "Проверка на перпендикулярность отрезков a и b: " << (a | b) << std::endl;
    std::cout << "Сумма длин отрезков a и b: " << a + b << std::endl;
    std::cout << "Модуль разности длин отрезков a и b: " << a - b << std::endl;
}
