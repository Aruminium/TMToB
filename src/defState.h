#ifndef DEFSTATE_H
#define DEFSTATE_H

typedef struct STATE{
    char image;
    char name[8];
    int LV;
    int HP;
    int MaxHP;
    int ATK;
    int DEF;
    int nextLV;
    int ExpPoint;
    int Motivation;
}state;

#endif