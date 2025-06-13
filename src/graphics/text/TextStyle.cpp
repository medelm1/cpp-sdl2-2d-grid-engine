#include "graphics/text/TextStyle.hpp"

TextStyle::TextStyle()
    :
    m_fontSize(11),
    m_textColor({0xFF, 0xFF, 0xFF, 0xFF}),
    m_shadowColor({0xFF, 0xFF, 0xFF, 0xFF})
{

}

TextStyle::TextStyle(int fontSize, SDL_Color textColor, SDL_Color shadowColor)
    :
    m_fontSize(fontSize),
    m_textColor(textColor),
    m_shadowColor(shadowColor)
{

}

TextStyle::~TextStyle()
{

}

int TextStyle::getFontsize() const
{
    return m_fontSize;
}

void TextStyle::setFontSize(int fontSize)
{
    m_fontSize = fontSize;
}

SDL_Color TextStyle::getTextColor() const
{
    return m_textColor;
}

SDL_Color TextStyle::getShadowColor() const
{
    return m_shadowColor;
}

void TextStyle::setTextColor(SDL_Color textColor)
{
    m_textColor = textColor;
}

void TextStyle::setShadowColor(SDL_Color shadowColor)
{
    m_shadowColor = shadowColor;
}