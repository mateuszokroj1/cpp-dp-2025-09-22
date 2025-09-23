#include "text.hpp"
#include "shape_factories.hpp"

using namespace Drawing;

namespace
{
    bool is_registered = SingletonShapeFactory::instance()
        .register_creator(Text::id, [] { return std::make_unique<Text>(); });
} 
