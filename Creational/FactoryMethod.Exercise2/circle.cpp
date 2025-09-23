#include "circle.hpp"

using namespace std;
using namespace Drawing;

Circle::Circle(int x, int y, uint32_t radius) : radius_(radius)
{
    set_coord({x,y});
}

uint32_t Circle::radius() const
{
    return radius_;
}

void Circle::set_radius(uint32_t size)
{
    radius_ = size;
}

void Circle::draw() const
{
    std::cout << "Drawing circle at " << coord() << " with radius: " << radius_ << std::endl;
}
