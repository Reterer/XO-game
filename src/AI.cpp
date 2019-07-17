#include "AI.h"

char isWin(char* map)
{
    char isWin = -2;

    //Проверка прямых линий
    for(int i = 0; i < 3; i++)
    {
        if(map[i*3] != -1 && map[i*3] == map[i*3+1] && map[i*3+1] == map[i*3+2])
        {
            isWin = map[i*3];
        }
        if(map[i] != -1 && map[i] == map[i+3] && map[i+3] == map[i+6])
        {
            isWin = map[i];
        }
    }

    //Диагонали
    if(map[0] != -1 && map[0] == map[4] && map[4] == map[8])
    {
        isWin = map[0];
    }
    if(map[2] != -1 && map[2] == map[4] && map[4] == map[6])
    {
        isWin = map[2];
    }

    if(isWin == -2)
    {
        bool isEmpty = false;
        for(int i = 0; i < 9; ++i)
        {
            if(map[i] == -1) isEmpty = true;
        }
        if(!isEmpty) isWin = -1; //Ничья
    }
    return isWin;
}


char miniMax(char* map, bool is_turn_AI, int n)
{
    if     (isWin(map) == -1) return 0;
    else if(isWin(map) == 0) return 1;
    else if(isWin(map) == 1) return -1;

    if(is_turn_AI)
    {
        char max = -1;
        for(int i = 0; i < 9; i++)
        {
            if(map[i] == -1)
            {
                map[i] = 0;
                char res = miniMax(map,0,n+1);
                if(res > max)
                {
                    max = res;
                    if(max == 1)
                    {
                        map[i] = -1;
                        break;
                    }
                }
                map[i] = -1;
            }
        }
        return max;
    }
    else
    {
        char min = 1;
        for(int i = 0; i < 9; i++)
        {
            if(map[i] == -1)
            {
                map[i] = 1;
                char res = miniMax(map,1,n+1);
                if(res < min)
                {
                    min = res;
                    if(min == -1)
                    {
                        map[i] = -1;
                        break;
                    }
                }
                map[i] = -1;
            }
        }
        return min;
    }
}

char turnAI(char* map,char type)
{
    char my_char = (type==2?'X':'0');
    char player_char = (type==1?'X':'0');

    char new_map[9];
    for(int i = 0; i < 9; i++)
    {
        if(map[i] == ' ') new_map[i] = -1;
        else if(map[i] == 'X') new_map[i] = type == 1;
        else if(map[i] == '0') new_map[i] = type == 2;
    }
    char number_sell = 0;
    char max = -1;
    for(int i = 0; i < 9; i++)
    {
        if(new_map[i] == -1)
        {
            new_map[i] = 0;
            char res = miniMax(new_map,0,1);
            if(res > max)
            {
                max = res;
                number_sell = i;
                if(max == 1)
                {
                    new_map[i] = -1;
                    break;
                }
            }
            new_map[i] = -1;
        }
    }

    return number_sell;
}
