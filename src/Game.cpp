#define SELL_SIZE 160
#include "Game.h"

Game::Game(sf::Font& font) : user_interface(0,WINDOW_HEIGHT-100,WINDOW_WIDTH,100,font,sf::Color(212,182,117))
{
    this->font = font;
    user_interface.createLabel(10,WINDOW_HEIGHT-70,30," ", sf::Color::Black);
}

Game::~Game()
{

}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    //Фон
    sf::RectangleShape shape;
    shape.setPosition(sf::Vector2f(0,0));
    shape.setSize(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT));
    shape.setFillColor(sf::Color(80,145,118));
    target.draw(shape, states);

    //Cells
    sf::Text text;
    text.setFont(font);
    text.setColor(sf::Color::Black);
    text.setCharacterSize(100);

    shape.setSize(sf::Vector2f(SELL_SIZE-4,SELL_SIZE-4));
    shape.setFillColor(sf::Color(212,182,117));
    for(int i = 0; i < 9; i++)
    {
        shape.setPosition(sf::Vector2f(((i%3)*SELL_SIZE)+12,((i/3)*SELL_SIZE)+10));
        text.setPosition(sf::Vector2f(((i%3)*SELL_SIZE)+65,((i/3)*SELL_SIZE)+20));
        text.setString(map[i]);

        target.draw(shape, states);
        target.draw(text, states);
    }

    //UI
    target.draw(user_interface, states);
}

void Game::init(char type)
{
    this->type = type; //Если 0 - 2 игока, если 1 - 2 игрок бот, если 2 - 1 игрок бот

    is_first_turn = true;
    setLabelText();
    is_first_turn = false;


    for(int i = 0; i < 9; ++i)
    {
        map[i] = ' ';
    }
}

char Game::isWin()
{
    bool isWin = false;

    //Проверка прямых линий
    for(int i = 0; i < 3; i++)
    {
        if(map[i*3] != ' ' && map[i*3] == map[i*3+1] && map[i*3+1] == map[i*3+2])
        {
            map[i*3] = '-';
            map[i*3+1] = '-';
            map[i*3+2] = '-';
            isWin = true;
        }
        if(map[i] != ' ' && map[i] == map[i+3] && map[i+3] == map[i+6])
        {
            map[i] = '|';
            map[i+3] ='|';
            map[i+6] = '|';
            isWin = true;
        }
    }

    //Диагонали
    if(map[0] != ' ' && map[0] == map[4] && map[4] == map[8])
    {
        map[0] = '\\';
        map[4] = '\\';
        map[8] = '\\';
        isWin = true;
    }
    if(map[2] != ' ' && map[2] == map[4] && map[4] == map[6])
    {
        map[2] = '/';
        map[4] = '/';
        map[6] = '/';
        isWin = true;
    }
    char res = -1;
    if (isWin)
    {
        switch(type)
        {
        case 0:
            res = !is_first_turn;
            break;
        case 1:
            res = is_first_turn?2:0;
            break;
        case 2:
            res = is_first_turn?0:2;
            break;
        default:
            break;
        }
    }
    else //Проверка на ниьчю
    {
        bool isEmpty = false;
        for(int i = 0; i < 9; ++i)
        {
            if(map[i] == ' ') isEmpty = true;
        }
        if(!isEmpty) res = 3; //Ничья
    }
    return res;
}

bool Game::isCorrectlyTurn(char number_cell)
{
    return number_cell > -1 && number_cell < 9 && map[number_cell] == ' ';
}

void Game::turn_type_players(char number_cell)
{
    map[number_cell] = (is_first_turn==true?'X':'0');
}

void Game::turn_type_ai(char number_cell)
{

}

void Game::setLabelText()
{
    switch(type)
    {
    case 0:
        user_interface.texts[0].setString(is_first_turn==1?"Turn: Player 1":"Turn: Player 2");
        break;
    case 1:
        user_interface.texts[0].setString(is_first_turn==1?"Turn: Player 1":"Turn: AI");
        break;
    case 2:
        user_interface.texts[0].setString(is_first_turn==1?"Turn: AI":"Turn: Player 1");
        break;
    default:
        break;
    }
}

char Game::checkCollision(sf::Vector2i& mouseLocalPosition, bool mouseIsLeftButtnPressed)
{
    char number_cell = -1;
    int x,y;

    for(int i = 0; i < 9; i++)
    {
        x = ((i%3)*SELL_SIZE)+12;
        y = ((i/3)*SELL_SIZE)+10;
        if (x <= mouseLocalPosition.x && x + SELL_SIZE - 4 >= mouseLocalPosition.x
         && y <= mouseLocalPosition.y && y + SELL_SIZE - 4 >= mouseLocalPosition.y)
        {
            if (mouseIsLeftButtnPressed) number_cell = i;
        }
    }

    return number_cell;
}

bool Game::turn(sf::Vector2i& mouseLocalPosition, bool mouseIsLeftButtnPressed)
{
    char number_cell = checkCollision(mouseLocalPosition,mouseIsLeftButtnPressed);

    if(isCorrectlyTurn(number_cell))
    {
        if(type < 3) is_first_turn = !is_first_turn;
        setLabelText();

        if(type == 0)   turn_type_players(number_cell);
        else if (type < 3)  turn_type_ai(number_cell);

        return true;
    }
    else
    {
        return false;
    }

}
