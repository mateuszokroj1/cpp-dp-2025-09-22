#include "rectangle_reader_writer.hpp"
#include "../rectangle.hpp"
#include "../shape_factories.hpp"

namespace
{
    using namespace Drawing;
    using namespace Drawing::IO;

    bool is_registered = 
        SingletonShapeRWFactory::instance() 
            .register_creator(make_type_index<Rectangle>(), [] { return std::make_unique<RectangleReaderWriter>();});
}


void Drawing::IO::RectangleReaderWriter::read(Drawing::Shape& shp, std::istream& in)
{
    Rectangle& rect = static_cast<Rectangle&>(shp);

    Point pt;
    int w, h;

    in >> pt >> w >> h;

    rect.set_coord(pt);
    rect.set_height(h);
    rect.set_width(w);
}

void Drawing::IO::RectangleReaderWriter::write(const Drawing::Shape& shp, std::ostream& out)
{
    const Rectangle& rect = static_cast<const Rectangle&>(shp);

    out << Rectangle::id << " " << rect.coord() << " " << rect.width() << " " << rect.height() << std::endl;
}
