#include "graphics/text/text_object.hpp"

TextObject::TextObject()
    :
    m_text("")
{

}

TextObject::TextObject(const std::string& text, TextStyle style)
    :
    m_text(text),
    m_style(style)
{

}

TextObject::~TextObject()
{

}

std::string TextObject::getText() const
{
    return m_text;
}

void TextObject::setText(const std::string& text)
{
    m_text = text;
}

TextStyle TextObject::getStyle() const
{
    return m_style;
}

void TextObject::setStyle(TextStyle style)
{
    m_style = style;
}