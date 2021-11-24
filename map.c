
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"states.h"
#include"map.h"

extern int mapHeight,mapWidth,OBJECTS,ENEMYS,X_Player,Y_Player;

char* map(){
    int x,y,z,count = 0;
    char* MAP = NULL;
    srand((unsigned int)time(NULL));
	mapHeight = (rand() % (MAX_MAP_HEIGHT-MIN_MAP_HEIGHT)) + MIN_MAP_HEIGHT;
    mapWidth = (rand() % (MAX_MAP_WIDTH-MIN_MAP_WIDTH)) + MIN_MAP_WIDTH;
    MAP = (char*)malloc(mapHeight*mapWidth *sizeof(char));
    if(MAP == NULL) exit(1);
    OBJECTS = ((mapHeight*mapWidth) / 7);
    ENEMYS = ((mapHeight*mapWidth) / 10);
    //基本マップ生成 壁>"-","|"
    //MAP[i][j] を *(MAP + i*mapwidth + j)　で表す
    for(int i=0;i<mapHeight;i++){
        for(int j=0;j<mapWidth;j++){
            if(i<=1||i>=mapHeight-2||j<=1||j>=mapWidth-2) *(MAP + i*mapWidth*sizeof(char) + j*sizeof(char)) = '#';
            else *(MAP + i*mapWidth*sizeof(char) + j*sizeof(char)) = '.';
        }
    }
    // //障害物生成 障害物>"#"
    for(int i=0;i < OBJECTS;i++){
        while(1){
            x=(rand()%(mapWidth-4)) + 2;
            y=(rand()%(mapHeight-4)) + 2;
            if(*(MAP + y*mapWidth*sizeof(char) + x*sizeof(char)) == '.'){
                *(MAP + y*mapWidth*sizeof(char) + x*sizeof(char)) = '#';
                break;
            }
        }
    }

    // //プレイヤの位置決定　プレイヤー>"@"
    while(1){
        x=(rand()%(mapWidth-4)) + 2;
        y=(rand()%(mapHeight-4)) + 2;
        if(*(MAP + y*mapWidth*sizeof(char) + x*sizeof(char))=='.'){
            *(MAP + y*mapWidth*sizeof(char) + x*sizeof(char))=getImage(getStates(0));
            X_Player=x;
            Y_Player=y;
            break;
        }
    }
    count = 0;
    // //敵の位置決定　敵>"E"
    while (count < ENEMYS){
        x=(rand()%(mapWidth-4)) + 2;
        y=(rand()%(mapHeight-4)) + 2;
        if(*(MAP + y*mapWidth*sizeof(char) + x*sizeof(char))=='.'){
            z = 1+(rand() % 4);//1~4
            *(MAP + y*mapWidth*sizeof(char) + x*sizeof(char)) = getImage(getStates(z));
            count++;
        }
    }
    // //ゴール（階段） ゴール>"K"
    while(1){
        x=(rand()%(mapWidth-4)) + 2;
        y=(rand()%(mapHeight-4)) + 2;
        if(*(MAP + y*mapWidth*sizeof(char) + x*sizeof(char))=='.'){
            *(MAP + y*mapWidth*sizeof(char) + x*sizeof(char))='K';
            break;
        }
    }
    return MAP;
}