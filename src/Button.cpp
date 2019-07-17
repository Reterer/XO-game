#include "Button.h"

Button::Button(int x, int y, int size_x, int size_y,sf::String text, sf::Font& font, sf::Color color)
{
    this->x = x;
    this->y = y;
    this->size_x = size_x;
    this->size_y = size_y;

    this->text.setPosition(sf::Vector2f(x + size_x/2 - 9*text.getSize() + 10,y + size_y/4));
    this->text.setCharacterSize(size_y/3);
    this->text.setFont(font);
    this->text.setString(text);
    this->text.setFillColor(color);

    isPressed = false;
}

Button::~Button()
{

}
