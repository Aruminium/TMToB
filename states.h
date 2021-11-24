#ifndef STATES_H
#define STATES_H
#include<string.h>
#include"defState.h"

typedef struct STATE state;

extern state Player_state,slime,demon,org,god;
extern state* charcter[5];

extern void monsterLvSetting(state* const,state* const,float);
extern void monsterLVUP();
extern void States_construct(state*,char,char*,int,int,int,int,int,int,int,int);

extern void Initstates();
extern void setStates(state* const,int);
extern state* getStates(const int);

extern void setImage(state* const,char);
extern char getImage(const state* const);

extern void setName(state* const,char*);
extern char* getName(state* const);

extern void setLV(state* const,int);
extern int getLV(const state* const);

extern void setHP(state* const,int);
extern int getHP(const state* const);

extern void setMaxHP(state* const,int);
extern int getMaxHP(const state* const);

extern void setATK(state* const,int);
extern int getATK(const state* const);

extern void setDEF(state* const,int);
extern int getDEF(const state* const);

extern void setNextLV(state* const,int);
extern int getNextLV(const state* const);

extern void setExpP(state* const,int);
extern int getExpP(const state* const);

extern void setMot(state* const, int);
extern int getMot(const state* const);

extern void Datasave();
extern void Dataload();

#endif