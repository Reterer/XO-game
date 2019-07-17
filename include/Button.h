#ifndef BUTTON_H
#define BUTTON_H

#include "project.h"

class Button
{
    public:
        Button(int x, int y, int size_x, int size_y, sf::String text, sf::Font& font, sf::Color color);
        virtual ~Button();

        sf::Text text;

        int x,y;
        int size_x, size_y;

        bool isPressed;
    protected:

    private:
};

#endif // BUTTON_H
