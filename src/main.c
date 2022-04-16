#include<ncurses.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"states.h"
#include"move.h"
#include"map.h"
#include"view.h"

int OBJECTS = 0;
//敵の数
int ENEMYS = 0;
int mapHeight = 0;
int mapWidth = 0;
//プレイヤーの座標
int X_Player = 0;
int Y_Player = 0;
int hierarchy = 1;
state* charcter[5];
state Player_state,slime,demon,org,god;

int main(){
	int flag;
    char q;
	char name[32];
	char* MAP = NULL;

	system("clear");
	initscr();
	start_color();
    init_pair(1,COLOR_YELLOW,COLOR_BLACK);//プレーヤ,階段 "@","K"
	init_pair(2,COLOR_WHITE,COLOR_BLACK);
	init_pair(3,COLOR_BLUE,COLOR_BLACK);
	init_pair(4,COLOR_MAGENTA,COLOR_BLACK);
	init_pair(5,COLOR_RED,COLOR_BLACK);
	init_pair(6,COLOR_BLACK,COLOR_BLACK);
	init_pair(7,COLOR_BLACK,COLOR_RED);

	bkgd(COLOR_PAIR(2));
	cbreak();
	attrset(COLOR_PAIR(3));

	printw("Mystery Dungeon\n");
	printw("New game or Continue game?(n/c)");
	attrset(COLOR_PAIR(2));
	q = getch();
	attrset(COLOR_PAIR(3));
    //続きから:c 初めから:それ以外
	switch (q){
	case 'c':
		printw("\nCONTINUE GAME\n");
		Dataload();
		printw("~loding Now~\n");
		printw("Welcome back,%s",getName(getStates(0)));
		q = getch();
        MAP = map();
		break;
	default:
		printw("\nNEW GAME\n");
		hierarchy = 1;
        Initstates();
		printw("Enter a name (up to 8 characters)>>");
		attrset(COLOR_PAIR(2));
		scanw("%s",name);
		attrset(COLOR_PAIR(3));
		setName(getStates(0),name);
		printw("~loding Now~\n");
        MAP = map();
		break;
	}
	attrset(COLOR_PAIR(2));
	//100階層登ったらクリア
    while(hierarchy < 100){
        flag = P_move(MAP);
        //階段
		erase();
		if(flag == 2){
			printw("GAME OVER\n");
			printw("continue the game?(y/n)");
			q = getch();
			if(q == 'y'){
				free(MAP);
				main();
			}
			//セーブデータを消去 やり直しはだめ
			remove("savedata.txt");
			break;
		}
		else if(flag == 3){//次の階層
			printw("----%dF -> %dF----\n",hierarchy,hierarchy+1);
			hierarchy++;
			printw("continue the game?(y/n)");
			q = getch();
			if(q == 'y'){
				if(MAP != NULL) free(MAP);
				MAP = map();
			}
			else {
				//セーブしてやめる
				Datasave();
				break;
			}
		}else printw("error");
    }
	erase();
	if(MAP != NULL){
		printw("Bye\n");
		free(MAP);
		q = getch();
	}
	endwin();
    return 0;
}
//flag:1
