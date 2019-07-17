#ifndef GAME_H
#define GAME_H

#include "project.h"
#include "Menu.h"

class Game : public sf::Drawable, public sf::Transformable
{
    public:
        Game(sf::Font& font);
        bool is_first_turn;
        char isWin();
        void init(char type);
        bool turn(sf::Vector2i& mouseLocalPosition, bool mouseIsLeftButtnPressed);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual ~Game();

    protected:

    private:
        char type;
        char map[9];

        int number_turn;

        Menu user_interface;
        sf::Font font;

        bool isCorrectlyTurn(char number_cell);
        char checkCollision(sf::Vector2i& mouseLocalPosition, bool mouseIsLeftButtnPressed);

        void turn_type_players(char number_cell);
        void turn_type_ai(char number_cell);
        void setLabelText();
};

#endif // GAME_H
