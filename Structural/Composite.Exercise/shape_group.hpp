#ifndef SHAPEGROUP_HPP
#define SHAPEGROUP_HPP

#include "shape.hpp"

#include <memory>
#include <vector>

namespace Drawing
{
    class ShapeGroup : public CloneableShape<ShapeGroup>
    {
        std::vector<std::unique_ptr<Shape>> shapes_;

    public:
        using iterator = typename std::vector<std::unique_ptr<Shape>>::iterator;
        using const_iterator = typename std::vector<std::unique_ptr<Shape>>::const_iterator;

        constexpr static auto id = "ShapeGroup";

        ShapeGroup() = default;

        ShapeGroup(const ShapeGroup& other)
        {
            shapes_.reserve(other.shapes_.size());
            for (const auto& shape : other.shapes_)
            {
                shapes_.emplace_back(shape->clone());
            }
        }

        ShapeGroup& operator=(const ShapeGroup& other)
        {
            if (this != &other)
            {
                shapes_.clear();
                shapes_.reserve(other.shapes_.size());
                for (const auto& shape : other.shapes_)
                {
                    shapes_.emplace_back(shape->clone());
                }
            }
            return *this;
        }

        ShapeGroup(ShapeGroup&&) = default;
        ShapeGroup& operator=(ShapeGroup&&) = default;

        void add_shape(std::unique_ptr<Shape> shape)
        {
            shapes_.emplace_back(std::move(shape));
        }

        void move(int dx, int dy) override
        {
            for (auto& shape : shapes_)
            {
                shape->move(dx, dy);
            }
        }

        void draw() const override
        {
            for (const auto& shape : shapes_)
            {
                shape->draw();
            }
        }

        size_t size() const
        {
            return shapes_.size();
        }

        iterator begin()
        {
            return shapes_.begin();
        }

        iterator end()
        {
            return shapes_.end();
        }

        const_iterator begin() const
        {
            return shapes_.begin();
        }

        const_iterator end() const
        {
            return shapes_.end();
        }
    };

} // namespace Drawing

#endif // SHAPEGROUP_HPP
