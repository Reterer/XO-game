#include "project.h"
#include "Menu.h"
#include "Game.h"


//Состояния игры
enum State {MAIN_MENU, SETUP_TWO_PLAYERS, SETTUP_ONE_PLAYERS, EXIT, GAME, GAME_WIN};

bool isPressedOnButton(Button& button, sf::Vector2i& mouseLocalPosition)
{
    return button.x <= mouseLocalPosition.x && button.x + button.size_x >= mouseLocalPosition.x
        && button.y <= mouseLocalPosition.y && button.y + button.size_y >= mouseLocalPosition.y;
}

void updateMainMenu(State& state, Menu& menu, sf::Vector2i& mouseLocalPosition, bool mouseIsLeftButtnPressed)
{
    for(int i = 0; i < 3; i++)
    {
        menu.buttons[i].isPressed = false;
        if(isPressedOnButton(menu.buttons[i], mouseLocalPosition))
        {
            if(mouseIsLeftButtnPressed) state = State(i+1);
            menu.buttons[i].isPressed = true;
        }
    }
}

void updateSetup2PlayersMenu(State& state, Menu& menu, sf::Vector2i& mouseLocalPosition, bool mouseIsLeftButtnPressed)
{
    for(int i = 0; i < 2; i++)
    {
        menu.buttons[i].isPressed = false;
        if(isPressedOnButton(menu.buttons[i], mouseLocalPosition))
        {
            if(mouseIsLeftButtnPressed) state = (i==0?MAIN_MENU:GAME);
            menu.buttons[i].isPressed = true;
        }
    }
}

char updateSetup1PlayersMenu(State& state, Menu& menu, sf::Vector2i& mouseLocalPosition, bool mouseIsLeftButtnPressed)
{
    char type = -1;

    for(int i = 0; i < 3; i++)
    {
        menu.buttons[i].isPressed = false;
        if(isPressedOnButton(menu.buttons[i], mouseLocalPosition))
        {
            if(mouseIsLeftButtnPressed)
            {
                if(i != 2)
                {
                    type = i+1;
                    state = GAME;
                }
                else
                {
                    state = MAIN_MENU;
                }
            }
            menu.buttons[i].isPressed = true;
        }
    }
    return type;
}

void setupGameWinMenu(Menu& menu, char winMode)
{
    switch(winMode)
    {
    case 0:
        menu.texts[0].setString("Player 1 Wins!");
        break;
    case 1:
        menu.texts[0].setString("Player 2 Wins!");
        break;
    case 2:
        menu.texts[0].setString("AI Wins :(");
        break;
    case 3:
        menu.texts[0].setString("Drawn game");
        break;
    default:
        break;
    }
}

void updateGameWinMenu(State& state, Menu& menu,
                       sf::Vector2i& mouseLocalPosition, bool mouseIsLeftButtnPressed)
{
    for(int i = 0; i < 1; i++)
    {
        menu.buttons[i].isPressed = false;
        if(isPressedOnButton(menu.buttons[i], mouseLocalPosition))
        {
            if(mouseIsLeftButtnPressed) state = MAIN_MENU;
            menu.buttons[i].isPressed = true;
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "X0 game!");

    //загрузка
    sf::Font font;
    if(!font.loadFromFile("data\\fonts\\Inconsolata-Regular.ttf"))
    {
        //error load
    }

    //Меню
    Menu main_menu(0,0,WINDOW_WIDTH, WINDOW_HEIGHT, font, sf::Color(212, 182, 117));
        main_menu.createBtn(50,30,400,100,"Start Game 2 players",sf::Color::Black);
        main_menu.createBtn(50,180,400,100,"Start Game 1 players",sf::Color::Black);
        main_menu.createBtn(50,330,400,100,"Exit",sf::Color::Black);

    Menu setup2_players(0,0,WINDOW_WIDTH, WINDOW_HEIGHT, font, sf::Color(212, 182, 1172));
        setup2_players.createLabel(160,30,20,"Mode \"Two Players\"",sf::Color::Black);
        setup2_players.createLabel(80,50,20,"You must have a friend to play it.",sf::Color::Black);
        setup2_players.createLabel(100,360,20,"Hint: The first player goes \"X\".",sf::Color::Black);
        setup2_players.createBtn(50,220,400,100, 26, "Sorry, I don't have friends :(", sf::Color::Black);
        setup2_players.createBtn(50,110,400,100,"Start Game",sf::Color::Black);

    Menu setup1_players(0,0,WINDOW_WIDTH, WINDOW_HEIGHT, font, sf::Color(212, 182, 117));
        setup1_players.createLabel(160,30,20,"Mode \"Player vs AI\"",sf::Color::Black);
        setup1_players.createLabel(167,60,24,"Chose a player",sf::Color::Black);
        setup1_players.createLabel(100,360,20,"Hint: The first player goes \"X\".",sf::Color::Black);
        setup1_players.createBtn(50,110,190,100,"1 Player",sf::Color::Black);
        setup1_players.createBtn(260,110,190,100,"2 Player",sf::Color::Black);
        setup1_players.createBtn(50,220,400,100, "Back to main menu", sf::Color::Black);

    Menu game_win_menu(0,0,WINDOW_WIDTH, WINDOW_HEIGHT, font, sf::Color(212, 182, 117,200));
        game_win_menu.createLabel(140,50,35,"Player1 WIN!!!",sf::Color::Black);
        game_win_menu.createBtn(50,400,400,100,"Back to main menu", sf::Color::Black);
    //Игра
    Game game(font);

    State state = MAIN_MENU;

    sf::Vector2i mouseLocalPosition = sf::Mouse::getPosition(window);
    bool mouseIsLeftButtnPressed = false;

    while (window.isOpen() && state != EXIT)
    {
        mouseIsLeftButtnPressed = false;
        mouseLocalPosition = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                mouseIsLeftButtnPressed = true;
        }

        window.clear();
        switch (state)
        {
        case MAIN_MENU:
        {
            updateMainMenu(state, main_menu, mouseLocalPosition, mouseIsLeftButtnPressed);
            window.draw(main_menu);
            break;
        }
        case SETUP_TWO_PLAYERS:
        {
            updateSetup2PlayersMenu(state, setup2_players, mouseLocalPosition, mouseIsLeftButtnPressed);
            window.draw(setup2_players);
            if(state == GAME) game.init(0);
            break;
        }
        case SETTUP_ONE_PLAYERS:
        {
            char type = updateSetup1PlayersMenu(state, setup1_players, mouseLocalPosition, mouseIsLeftButtnPressed);
            window.draw(setup1_players);
            if(state == GAME) game.init(type);
            break;
        }
        case GAME:
        {
            game.turn(mouseLocalPosition, mouseIsLeftButtnPressed);
            char winMode = game.isWin();
            if(winMode > -1)
            {
                state = GAME_WIN;
                setupGameWinMenu(game_win_menu, winMode);
            }
            window.draw(game);
            break;
        }
        case GAME_WIN:
        {
            updateGameWinMenu(state, game_win_menu, mouseLocalPosition, mouseIsLeftButtnPressed);
            window.draw(game);
            window.draw(game_win_menu);
            break;
        }
        default:
            break;
        }
        window.display();
    }

    return 0;
}
