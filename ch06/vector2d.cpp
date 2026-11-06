#include<cassert>
class Vector2D
{
    double x_;
    double y_;
public:
    explicit Vector2D(double x, double y = 0) : x_{x}, y_{y}
    {}
    double x() const
    {
        return x_;
    }
    double y() const{
        return y_;
    }
    Vector2D& operator+=(const Vector2D& other)
    {
        x_ += other.x_;
        y_ += other.y_;
        return *this;
    }
    bool operator==(const Vector2D&) const = default;


};

Vector2D operator+(Vector2D a, const Vector2D& b)
{
    a+=b;
    return a;
}



int main()
{
    // Construction
    Vector2D a{1, 2};
    Vector2D b{3, 4};

    assert(a.x() == 1);
    assert(a.y() == 2);

    // Addition
    Vector2D c = a + b;

    assert(c == Vector2D(4, 6));
    assert(a == Vector2D(1, 2));
    assert(b == Vector2D(3, 4));

    // Compound addition
    a += b;

    assert(a == Vector2D(4, 6));

    // Equality
    Vector2D d{3, 4};

    assert(b == d);
    assert(!(a == b));

    return 0;
}