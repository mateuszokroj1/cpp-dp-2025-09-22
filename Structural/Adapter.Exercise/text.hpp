#ifndef TEXT_HPP
#define TEXT_HPP

#include "paragraph.hpp"
#include "shape.hpp"
#include <string>

namespace Drawing
{
    class Text : public ShapeBase, private LegacyCode::Paragraph
    {
    public:
        constexpr static const char* id = "Text";

        Text(int x = 0, int y = 0, const std::string& text = "")
            : ShapeBase{x, y}, LegacyCode::Paragraph(text.c_str())
        {}

        void draw() const
        {
            render_at(coord().x, coord().y);
        }

        std::string text() const
        {
            return get_paragraph();
        } 

        void set_text(const std::string& text)
        {
            set_paragraph(text.c_str());
        }
    };
}

#endif
