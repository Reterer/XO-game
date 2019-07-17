#include "Menu.h"

Menu::Menu(int x,int y, int size_x, int size_y, sf::Font& font, sf::Color color)
{
    this->font = font;
    this->x = x;
    this->y = y;
    this->size_x = size_x;
    this->size_y = size_y;


    main_rect.setSize(sf::Vector2f(size_x,size_y));
    main_rect.setPosition(sf::Vector2f(x,y));
    main_rect.setFillColor(color);
    active = false;
}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(main_rect, states);

    sf::RectangleShape shape;
    shape.setFillColor(sf::Color(48,186,143,200));

    for(int i = 0; i < buttons.size(); ++i)
    {
        shape.setPosition(sf::Vector2f(buttons[i].x,buttons[i].y));
        shape.setSize(sf::Vector2f(buttons[i].size_x,buttons[i].size_y));

        if(buttons[i].isPressed)
            shape.setFillColor(sf::Color(25, 156, 255));
        else
            shape.setFillColor(sf::Color(48,186,143,200));

        target.draw(shape, states);
        target.draw(buttons[i].text, states);
    }

    for(int i = 0; i < texts.size(); ++i)
    {
        target.draw(texts[i], states);
    }
}

void Menu::createBtn(int x,int y, int size_x, int size_y, sf::String text, sf::Color color)
{
    buttons.push_back(Button(x,y,size_x,size_y,text,font,color));
}

void Menu::createBtn(int x,int y, int size_x, int size_y,int size_text, sf::String text, sf::Color color)
{
    buttons.push_back(Button(x,y,size_x,size_y,text,font,color));
    buttons[buttons.size()-1].text.setCharacterSize(size_text);
    buttons[buttons.size()-1].text.setPosition(sf::Vector2f(x + size_x/2 - 7*text.getSize() + 15,y + size_y/4));
}


void Menu::createLabel(int x,int y, int size_text, sf::String text, sf::Color color)
{
    texts.push_back(sf::Text(text,font));
    texts[texts.size()-1].setPosition(sf::Vector2f(x,y));
    texts[texts.size()-1].setCharacterSize(size_text);
    texts[texts.size()-1].setColor(color);

}
