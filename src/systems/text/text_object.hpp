#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "text_style.hpp"

class TextObject
{
private:
    std::string m_text;
    TextStyle m_style;

public:
    TextObject();
    TextObject(const std::string& text, TextStyle style);
    ~TextObject();

    std::string getText() const;
    TextStyle getStyle() const;

    void setText(const std::string& text);
    void setStyle(TextStyle style);
};

#endif