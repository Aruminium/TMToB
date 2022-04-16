#include<ncurses.h>
#include"states.h"
#include"view.h"
#include"map.h"
extern int hierarchy;
extern int mapHeight;
extern int mapWidth;

void view(char* MAP){
    int i,j,countY = 2,countX;
    erase();
    attrset(COLOR_PAIR(2));
    printw("%dF",hierarchy);
    for(i = Y_Player-2;i <= Y_Player+2;i++){
        move(countY,1);
        countX = 1;
        for(j = X_Player-2; j <= X_Player+2;j++){
            if(*(MAP + i*mapWidth*sizeof(char) + j*sizeof(char)) == '@' || *(MAP + i*mapWidth*sizeof(char) + j*sizeof(char)) == 'K') attrset(COLOR_PAIR(1));
            else if(*(MAP + i*mapWidth*sizeof(char) + j*sizeof(char)) == '#') attrset(COLOR_PAIR(4));
            else if(*(MAP + i*mapWidth*sizeof(char) + j*sizeof(char)) == '.') attrset(COLOR_PAIR(6));
            else attrset(COLOR_PAIR(5));
            move(countY,countX);
            printw("%c",*(MAP + i*mapWidth*sizeof(char) + j*sizeof(char)));
            countX++;
        }
        countY++;
    }
    attrset(COLOR_PAIR(2));
    mvaddstr(1,0,"+-----+");
    mvaddstr(2,0,"|");
    mvaddstr(2,6,"|");
    mvaddstr(3,0,"|");
    mvaddstr(3,6,"|");
    mvaddstr(4,0,"|");
    mvaddstr(4,6,"|");
    mvaddstr(5,0,"|");
    mvaddstr(5,6,"|");
    mvaddstr(6,0,"|");
    mvaddstr(6,6,"|");
    mvaddstr(7,0,"+-----+");
    statesview();
    refresh();
}

void statesview(){
    attrset(COLOR_PAIR(2));
    mvprintw(1,8,"+--------+");
    mvprintw(2,8,"|%-8s|",getName(getStates(0)));

    attrset(COLOR_PAIR(1));
    mvprintw(2,19,"@ - You");

    attrset(COLOR_PAIR(2));
    mvprintw(3,8,"|LV:%-5d|",getLV(getStates(0)));

    attrset(COLOR_PAIR(1));
    mvprintw(3,19,"K - Stairs");

    attrset(COLOR_PAIR(2));
    mvprintw(4,8,"|HP:%-5d|",getHP(getStates(0)));

    attrset(COLOR_PAIR(4));
    mvprintw(4,19,"# - Wall");

    attrset(COLOR_PAIR(2));
    mvprintw(5,8,"|ATK:%-4d|",getATK(getStates(0)));

    attrset(COLOR_PAIR(5));
    mvprintw(5,19,"S - Slime (Enemy)");

    attrset(COLOR_PAIR(2));
    mvprintw(6,8,"|DEF:%-4d|",getDEF(getStates(0)));

    attrset(COLOR_PAIR(5));
    mvprintw(6,19,"D - Deomn (Enemy)");

    attrset(COLOR_PAIR(2));
    mvprintw(7,8,"|NLv:%-4d|",getNextLV(getStates(0)));
    attrset(COLOR_PAIR(5));
    mvprintw(7,19,"O - Org (Enemy)");

    attrset(COLOR_PAIR(2));
    mvprintw(8,8,"|Mot:%-4d|",getMot(getStates(0)));
    attrset(COLOR_PAIR(5));
    mvprintw(8,19,"G - God (Enemy)");

    attrset(COLOR_PAIR(2));
    mvprintw(9,8,"+--------+");
}