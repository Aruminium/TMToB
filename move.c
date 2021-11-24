#include<ncurses.h>
#include<stdlib.h>
#include<unistd.h>
#include"states.h"
#include"move.h"
#include"view.h"
#include"map.h"
#include"battle.h"

extern state* getStates(int);
extern int X_Player;
extern int Y_Player;
extern int mapHeight;
extern int mapWidth;

//プレイヤーの移動、敵の移動,その他コマンドの設定
int P_move(char* MAP){
    int x,y,flag,battleflag;//flag:0>移動 1> 未定 2>死 3>次の階層へ 4>ゲーム中断
    char P_FLAG;
    state* tmp = getStates(0);
    //現在地を保存

    while(1){
        view(MAP);
        mvprintw(0,2,"  coordinates (%d,%d)",X_Player,Y_Player);
        mvprintw(10,0,"Action possible>>");
        P_FLAG = getch();
        x=X_Player;
        y=Y_Player;
        if(P_FLAG=='q'){//左上に移動
            flag=0;
            X_Player-=1;
            Y_Player-=1;
        }
        else if(P_FLAG=='w'){//上に移動
            flag=0;
            Y_Player-=1;
        }
        else if(P_FLAG=='e'){//右上に移動
            flag=0;
            X_Player+=1;
            Y_Player-=1;
        }
        else if(P_FLAG=='a'){//左に移動
            flag=0;
            X_Player-=1;
        }
        else if(P_FLAG=='d'){//右に移動
            flag=0;
            X_Player+=1;
        }
        else if(P_FLAG=='z'){//左下に移動
            flag=0;
            X_Player-=1;
            Y_Player+=1;
        }
        else if(P_FLAG=='x'){//下に移動
            flag=0;
            Y_Player+=1;
        }
        else if(P_FLAG=='c'){//右下に移動
            flag=0;
            X_Player+=1;
            Y_Player+=1;
        }
        else if(P_FLAG=='k'){//自殺（詰み防止） *すなわちGAMEOVER
            mvprintw(12,0,"The player has lost his way.");
            P_FLAG = getch();
            flag = 2;
            break;
        }

        if(flag==0 && *(MAP + Y_Player*mapWidth*sizeof(char) + X_Player*sizeof(char))=='.'){
            *(MAP + Y_Player*mapWidth*sizeof(char) + X_Player*sizeof(char)) = '@';
            *(MAP + y*mapWidth*sizeof(char) + x*sizeof(char))= '.';
            setMot(tmp,getMot(tmp)-1);
            if(getMot(tmp)< 0){
                setHP(getStates(0),getHP(getStates(0))-1);
                break;
            }
        }
        else if(flag==0 && *(MAP + Y_Player*mapWidth*sizeof(char) + X_Player*sizeof(char))=='S'){
            mvprintw(12,0,"----Start of battle----");
            P_FLAG = getch();
            battleflag = battle(tmp,getStates(1));
            //battle_flag 勝敗：0>勝ち　敵の位置に移動、1>負け　ゲームオーバー
            erase();
            if(battleflag==0){
                *(MAP + Y_Player*mapWidth*sizeof(char) + X_Player*sizeof(char)) = '@';
                *(MAP + y*mapWidth*sizeof(char) + x*sizeof(char)) = '.';
            }
            else if(battleflag == 1){
                mvprintw(0,0,"The player was too impotent.\n");
                P_FLAG = getch();
                flag = 2;
                break;
            }
            else mvprintw(0,0,"error\n");
        }
        else if(flag==0 && *(MAP + Y_Player*mapWidth*sizeof(char) + X_Player*sizeof(char))=='G'){
            mvprintw(12,0,"----Start of battle----");
            P_FLAG = getch();
            battleflag = battle(tmp,getStates(4));
            //battle_flag 勝敗：0>勝ち　敵の位置に移動、1>負け　ゲームオーバー　
            erase();
            if(battleflag==0){
                *(MAP + Y_Player*mapWidth*sizeof(char) + X_Player*sizeof(char)) = '@';
                *(MAP + y*mapWidth*sizeof(char) + x*sizeof(char)) = '.';
            }
            else if(battleflag == 1){
                mvprintw(0,0,"The player was too impotent.");
                P_FLAG = getch();
                flag = 2;
                break;
            }
            else mvprintw(0,0,"error\n");
        }
        else if(flag==0 && *(MAP + Y_Player*mapWidth*sizeof(char) + X_Player*sizeof(char))=='D'){
            mvprintw(12,0,"----Start of battle----");
            P_FLAG = getch();
            battleflag = battle(tmp,getStates(2));
            //battle_flag 勝敗：0>勝ち　敵の位置に移動、1>負け　ゲームオーバー　
            erase();
            if(battleflag==0){
                *(MAP + Y_Player*mapWidth*sizeof(char) + X_Player*sizeof(char)) = '@';
                *(MAP + y*mapWidth*sizeof(char) + x*sizeof(char)) = '.';
            }
            else if(battleflag == 1){
                mvprintw(0,0,"The player was too impotent.");
                P_FLAG = getch();
                flag = 2;
                break;
            }
            else mvprintw(0,0,"error\n");
        }
        else if(flag==0 && *(MAP + Y_Player*mapWidth*sizeof(char) + X_Player*sizeof(char))=='O')
        {
            mvprintw(12,0,"----Start of battle----\n");
            P_FLAG = getch();
            battleflag = battle(tmp,getStates(3));
            //battle_flag 勝敗：0>勝ち　敵の位置に移動、1>負け　ゲームオーバー　
            erase();
            if(battleflag==0){
                *(MAP + Y_Player*mapWidth*sizeof(char) + X_Player*sizeof(char)) = '@';
                *(MAP + y*mapWidth*sizeof(char) + x*sizeof(char)) = '.';
            }
            else if(battleflag == 1){
                mvprintw(0,0,"The player was too impotent.");
                P_FLAG = getch();
                flag = 2;
                break;
            }
            else mvprintw(0,0,"error\n");
        }

        else if(flag==0 && *(MAP + Y_Player*mapWidth*sizeof(char) + X_Player*sizeof(char))=='#'){
            setHP(tmp,getHP(tmp)-1);
            mvprintw(12,0,"Cannot proceed. Player has taken 1 damage.");
            P_FLAG = getch();
            X_Player = x;
            Y_Player = y;
            if(getHP(tmp)<=0){
                mvprintw(mapHeight+7,0,"The player has made friends with the wall.");
                P_FLAG = getch();
                flag = 2;
                break;
            }
        }
        else if(flag==0 && *(MAP + Y_Player*mapWidth*sizeof(char) + X_Player*sizeof(char))=='K'){
            mvprintw(12,0,"Yes!");
            P_FLAG = getch();
            flag=3;
            break;
        }
        else mvprintw(12,0,"You cannot proceed.");
    }
    return flag;
}
