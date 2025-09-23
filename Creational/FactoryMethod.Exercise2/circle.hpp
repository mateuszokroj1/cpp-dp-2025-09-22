#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.hpp"
#include <cstdint>

namespace Drawing
{
    class Circle : public ShapeBase
    {
        uint32_t radius_;

    public:
        static constexpr const char *id = "Circle";

        Circle(int x, int y, uint32_t radius);
        uint32_t radius() const;
        void set_radius(uint32_t size);

        void draw() const override;
    };
}

#endif // CIRCLE_H
