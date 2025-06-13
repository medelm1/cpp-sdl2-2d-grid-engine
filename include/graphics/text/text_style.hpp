#ifndef TEXT_STYLE_H
#define TEXT_STYLE_H

#include <SDL.h>

class TextStyle
{
private:
    int m_fontSize;
    SDL_Color m_textColor;
    SDL_Color m_shadowColor;

public:
    TextStyle();
    TextStyle(int fontSize, SDL_Color textColor, SDL_Color shadowColor);
    ~TextStyle();

    int getFontsize() const;
    SDL_Color getTextColor() const;
    SDL_Color getShadowColor() const;

    void setFontSize(int fontSize);
    void setTextColor(SDL_Color textColor);
    void setShadowColor(SDL_Color shadowColor);
};

#endif