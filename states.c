#include<string.h>
#include<stdio.h>
#include"states.h"
#include"defState.h"

extern int hierarchy;

//デフォルト設定(初めからを選択した場合の初期設定)
void Initstates(){
    //強さ slime < demon < org < god

    //プレイヤー
    // Player_state.image = '@';
    // strcpy(Player_state.name,"alice");
    // Player_state.LV=1;
    // Player_state.HP=10;
    // Player_state.ATK=5;
    // Player_state.DEF=5;
    // Player_state.nextLV = Player_state.LV*5;
    // Player_state.ExpPoint = 0;
    // Player_state.Motivation = 100;
    // Player_state.MaxHP = 10;
    States_construct(&Player_state,'@',"Alice",1,10,5,5,5,0,100,10);

    //slime
    // slime.image = 'S';
    // strcpy(demon.name,"slime");
    // slime.LV = 1;
    // slime.HP = 2;
    // slime.ATK = 2;
    // slime.DEF = 2;
    // slime.nextLV = 1;
    // slime.ExpPoint = 2;
    // slime.Motivation = 2;
    // slime.MaxHP = 2;
    States_construct(&slime,'S',"slime",1,2,2,2,2,2,2,2);


    //demon
    // demon.image = 'D';
    // strcpy(demon.name,"demon");
    // demon.LV = 1;
    // demon.HP = 3;
    // demon.ATK = 3;
    // demon.DEF = 3;
    // demon.nextLV = 1;
    // demon.ExpPoint = 3;
    // demon.Motivation = 3;
    // demon.MaxHP = 3;
    States_construct(&demon,'D',"demon",1,3,3,3,3,3,3,3);

    //org
    // org.image = 'O';
    // strcpy(demon.name,"org");
    // org.LV = 1;
    // org.HP = 10;
    // org.ATK = 5;
    // org.DEF = 5;
    // org.nextLV = 1;
    // org.ExpPoint = 5;
    // org.Motivation = 5;
    // org.MaxHP = 5;
    States_construct(&org,'O',"org",1,10,5,5,5,5,5,5);

    // //god
    // god.image = 'G';
    // strcpy(demon.name,"org");
    // god.LV = 1;
    // god.HP = 10;
    // god.ATK = 10;
    // god.DEF = 10;
    // god.nextLV = 1;
    // god.ExpPoint = 10;
    // god.Motivation = 10;
    // god.MaxHP = 10;
    States_construct(&god,'G',"god",1,10,10,10,10,10,10,10);

    setStates(&Player_state,0);
    setStates(&slime,1);
    setStates(&demon,2);
    setStates(&org,3);
    setStates(&god,4);
}

//補正プレイヤー依存
//slime 0.7 , demon 1.0 , org 1.1 god 1.2
void monsterLvSetting(state* const player,state* const monster,float correctionFactor){
    setLV(monster,player->LV);
    setHP(monster,(int)((float)player->MaxHP * correctionFactor));
    setATK(monster,(int)((float)player->ATK * correctionFactor));
    setDEF(monster,(int)((float)player->DEF * correctionFactor));
}

void monsterLVUP(){
    monsterLvSetting(getStates(0),getStates(1),0.7);
    monsterLvSetting(getStates(0),getStates(2),1.0);
    monsterLvSetting(getStates(0),getStates(3),1.1);
    monsterLvSetting(getStates(0),getStates(4),1.2);
}

void States_construct(state* const p_this,char image,char* name,int lv,int hp, int atk, int def, int nextlv, int expp,int mot,int maxhp){
    p_this->image = image;
    strcpy(p_this->name,name);
    p_this->LV = lv;
    p_this->HP = hp;
    p_this->ATK = atk;
    p_this->DEF = def;
    p_this->nextLV = nextlv;
    p_this->ExpPoint = expp;
    p_this->Motivation = mot;
    p_this->MaxHP = maxhp;
}

void setStates(state* const a,int i){
    charcter[i] = a;
}

state* getStates(const int i){
    return charcter[i];
}

void setImage(state* const a,char image){
    a->image = image;
}
char getImage(const state* const a){
    return a->image;
}

//setter getterの定義
void setName(state* const a,char* name){
    if(strlen(name) == 0 || strlen(name) >= 9) strcpy(a->name,"Alice");
    else strcpy(a->name,name);
}
char* getName(state* const a){
    return a->name;
}

void setLV(state* const a,int x){
    a->LV = x;
}
int getLV(const state* const a){
    return a->LV;
}

void setHP(state* const a, int x){
    a->HP = x;
}
int getHP(const state* const a){
    return a->HP;
}

void setMaxHP(state* const a,int x){
    a->MaxHP = x;
}
int getMaxHP(const state* const a){
    return a->MaxHP;
}

void setATK(state* const a, int x){
    a->ATK = x;
}
int getATK(const state* const a){
    return a->ATK;
}

void setDEF(state* const a, int x){
    a->DEF = x;
}
int getDEF(const state* const a){
    return a->DEF;
}

void setNextLV(state* const a,int x){
    a->nextLV = x;
}
int getNextLV(const state* const a){
    return a->nextLV;
}

void setExpP(state* const a,int x){
    a->ExpPoint = x;
}
int getExpP(const state* const a){
    return a->ExpPoint;
}

void setMot(state* const a,int x){
    a->Motivation = x;
}
int getMot(const state* const a){
    return a->Motivation;
}

void Datasave(){
	FILE* fp;
    state* tmp = getStates(0);
	fp = fopen("savedata.txt","w");
    fprintf(fp,"%s\n%d,%d,%d,%d,%d,%d,%d,%d,%d",getName(tmp),getLV(tmp),getHP(tmp),getMaxHP(tmp),getATK(tmp),getDEF(tmp),getNextLV(tmp),getExpP(tmp),getMot(tmp),hierarchy);
	fclose(fp);
}

void Dataload(){
	FILE* fp;
    char name[8];
    int LV,HP,MaxHP,ATK,DEF,nextLV,ExpPoint,Motivation;
    int hie;
    Initstates();
	fp = fopen("savedata.txt","r");
	if(fp != NULL){
        fscanf(fp,"%s",name);
        fscanf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d",&LV,&HP,&MaxHP,&ATK,&DEF,&nextLV,&ExpPoint,&Motivation,&hie);
        hierarchy = hie;
        setName(getStates(0),name);
        setLV(getStates(0),LV);
        setHP(getStates(0),HP);
        setMaxHP(getStates(0),MaxHP);
        setATK(getStates(0),ATK);
        setDEF(getStates(0),DEF);
        setNextLV(getStates(0),nextLV);
        setExpP(getStates(0),ExpPoint);
        setMot(getStates(0),Motivation);
    }
    fclose(fp);
}