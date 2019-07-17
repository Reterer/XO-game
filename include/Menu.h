#ifndef MENU_H
#define MENU_H

#include <vector>
#include "project.h"
#include "Button.h"

class Menu : public sf::Drawable, public sf::Transformable
{
    public:
        Menu(int x,int y, int size_x, int size_y, sf::Font& font, sf::Color color);
        virtual ~Menu();

        void createBtn(int x,int y, int size_x, int size_y, sf::String text, sf::Color color);
        void createBtn(int x,int y, int size_x, int size_y, int size_text, sf::String text, sf::Color color);
        void createLabel(int x,int y, int size_text, sf::String text, sf::Color color);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        bool active;

        std::vector <Button> buttons;
        std::vector <sf::Text> texts;
    private:
        int size_x,size_y;
        int x,y;

        sf::Font font;
        sf::RectangleShape main_rect;
};

#endif // MENU_H
