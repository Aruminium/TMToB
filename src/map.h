#ifndef MAP_H
#define MAP_H
#define MAX_MAP_HEIGHT 21
#define MAX_MAP_WIDTH 31
#define MIN_MAP_HEIGHT 11
#define MIN_MAP_WIDTH 11
//障害物の数
extern int OBJECTS;
//敵の数
extern int ENEMYS;
extern int mapHeight;
extern int mapWidth;
//プレイヤーの座標
extern int X_Player;
extern int Y_Player;
extern int hierarchy;
extern char* map();
#endif