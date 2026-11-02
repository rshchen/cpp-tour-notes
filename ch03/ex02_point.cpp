#include <utility>
#include <cassert>
#include <iostream>
struct Point
{
    int x;
    int y;
};

auto translate(Point& point, int dx, int dy) -> void
{
    point.x += dx;
    point.y += dy;
}

auto translated(Point point, int dx, int dy) -> Point
{
    translate(point, dx, dy);
    return point;
}

auto add(Point a, Point b)
{
    return Point{a.x+b.x, a.y+b.y};
}

auto coordinates(const Point& point) -> std::pair<int, int>
{
    return {point.x, point.y};
}

int main()
{
    Point p{2,3};
    translate(p, 4, -1);
    assert(p.x==6 && p.y==2);
    
    Point original{2,3};
    auto moved = translated(original, 4,-1);
    assert(original.x==2 && original.y==3);
    assert(moved.x==6 && moved.y==2);

    Point p1{1,2};
    Point p2{3,4};
    auto [x1, y1] = add(p1, p2);
    assert(x1==4 && y1==6);

    Point p3{5,-2};
    auto [x2, y2] = coordinates(p3);
    assert(x2==5 && y2==-2);

    Point p4{1,2};
    auto& [x3,y3] = p4;
    x3=10;
    assert(p4.x==10 && p4.y==2);

    std::cout<< "All tests passed.\n";
    return 0;
}