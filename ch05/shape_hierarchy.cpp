#include <stdexcept>
#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>
constexpr double pi = 3.141592653589793;

class Shape
{
public:
    virtual auto area() const -> double = 0;
    virtual ~Shape() = default;
};

class Rectangle : public Shape
{
    double h_;
    double w_;
public:
    Rectangle(double h, double w) : h_{h}, w_{w}
    {
        if (h <=0 || w <= 0) throw std::invalid_argument{"Invalid rectangle."};
    }
    auto area() const -> double override
    {
        return h_ * w_;
    }
};

class Circle : public Shape
{
    double r_;
public:
    Circle(double r) : r_{r}
    {
        if (r <= 0) throw std::invalid_argument{"Invalid circle."};
    }
    auto area() const -> double override
    {
        return (r_ * r_ * pi);
    }
};

auto total_area(const std::vector<Shape*>& shapes) -> double
{
    double total = 0.0;
    for (const Shape* shape : shapes)
    {
        total += shape->area();
    }
    return total;
}

int main()
{
    constexpr double error = 1e-9;  
    Rectangle rect{3,4};
    assert(std::abs(rect.area() - 12.0) <= error);
    
    Circle circ{2};
    assert(std::abs(circ.area() - 12.566370614359172) <= error);
    
    std::vector<Shape*> shapes={&rect, &circ};
    assert(std::abs(total_area(shapes) - 24.566370614359172) <= error);

    std::vector<Shape*> empty;
    assert(total_area(empty) == 0.0);

    try
    {
        Rectangle{-5, 6};
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        Circle{0};
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    return 0;
}