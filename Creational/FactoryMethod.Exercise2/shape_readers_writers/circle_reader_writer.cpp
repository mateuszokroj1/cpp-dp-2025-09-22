#include "circle_reader_writer.hpp"
#include "../circle.hpp"
#include <cstdint>

using namespace std;
using namespace Drawing;
using namespace Drawing::IO;

namespace
{
    Circle *getCircle(Shape &shape)
    {
        return dynamic_cast<Circle *>(&shape);
    }

    const Circle *getCircle(const Shape &shape)
    {
        return dynamic_cast<const Circle *>(&shape);
    }
}

void CircleReaderWriter::read(Shape &shp, std::istream &in)
{
    Point p;
    uint32_t radius;
    in >> p >> radius;
    auto circle = getCircle(shp);
    if (!circle)
        throw std::invalid_argument("is not circle");

    circle->set_coord(p);
    circle->set_radius(radius);
}

void CircleReaderWriter::write(const Shape &shp, std::ostream &out)
{
    auto circle = getCircle(shp);
    out << Circle::id << " " << circle->coord() << " " << circle->radius() << std::endl;
}