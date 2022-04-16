#include<stdlib.h>
#include<time.h>
#include<ncurses.h>
#include"states.h"
#include"battle.h"

int battle(state* a,state* b){
    /*攻撃について
    与えるダメージは「攻撃力　×　1~3の乱数」で決まる
    ただし「防御力」の値分ダメージが軽減される
    */
    int hand,Enemy_hand,getMOT,getExp,Damage;
    char Player_hand;
    int battle_flag = -1;
    monsterLVUP();
    srand((unsigned int)time(NULL));
    //終わる条件は『プレイヤーが勝つ　または　敵が勝つ』
    while(!(battle_flag == 0 || battle_flag == 1)){
        int z;
        do{
            erase();
            mvprintw(0,0,"%s HP:%d",getName(a),getHP(a));
            mvprintw(1,0,"%sLV%d HP:%d",getName(b),getLV(b),getHP(b));
            mvprintw(2,0,"Decide.(Rock:r,Paper:p,Scissors:s)>>");
            Player_hand = getch();
        } while (Player_hand != 'r' && Player_hand != 'p' && Player_hand != 's');
        erase();
        mvprintw(0,0,"%s HP:%d",getName(a),getHP(a));
        mvprintw(1,0,"%sLV%d HP:%d",getName(b),getLV(b),getHP(b));
        if(Player_hand=='r'){
            mvprintw(3,0,"You : Rock");
            hand = 0;
        }
        else if(Player_hand=='p'){
            mvprintw(3,0,"You : Paper");
            hand = 1;
        }
        else{
            mvprintw(3,0,"You : Scissors");
            hand = 2;
        }
        Enemy_hand=rand()%3;
        if(Enemy_hand==0)mvprintw(4,0,"Enemy : Rock");
        else if(Enemy_hand==1)mvprintw(4,0,"Enemy : Paper");
        else mvprintw(4,0,"Enemy : Scissors");
        z=(hand-Enemy_hand+3)%3;
        //勝敗条件
        if(z==1){//じゃんけん勝ち
            //ダメージ処理
            Damage=getATK(a) * ((rand()%3)+1) - getDEF(b);
            if(Damage < 0) Damage = 0;
            mvprintw(5,0,"%s attack! %d damage.",getName(a),Damage);
            //HP判定
            if(getHP(b)>Damage) setHP(b,getHP(b)-Damage);
            else{
                attrset(COLOR_PAIR(7));
                mvprintw(6,0,"YOU WIN!!");
                attrset(COLOR_PAIR(2));
                Player_hand = getch();
                erase();
                getExp=getLV(b) * getExpP(b);
                getMOT=getMot(b);
                battle_flag=0;
                mvprintw(1,0,"You got %d EXP and %d Mot.",getExp,getMOT);
                setNextLV(a,getNextLV(a)-getExp);
                (getMot(a) + getMOT > 100)? setMot(a,100):setMot(a,getMot(a) + getMOT);

                //レベルアップ関係
                if(getNextLV(a) > 0) mvprintw(4,0,"NextLv %d EXP\n",getNextLV(a));
                else
                {
                    int x;
                    setLV(a,getLV(a)+1);
                    mvprintw(2,0,"Level UP! %dLV -> %dLV",getLV(a)-1,getLV(a));
                    setNextLV(a,getLV(a) * 5);
                    //HP最大値上昇
                    x = (rand()%3+1) * 3;
                    mvprintw(4,0,"MaxHP : %d -> %d (+%d)",getMaxHP(a),getMaxHP(a) + x,x);
                    setMaxHP(a,getMaxHP(a) + x);
                    //ATK上昇
                    x = (rand()%3+1) * 3;
                    mvprintw(5,0,"ATK : %d -> %d (+%d)",getATK(a),getATK(a) + x,x);
                    setATK(a,getATK(a) + x);
                    //DEF上昇
                    x = (rand()%3+1) * 3;
                    mvprintw(6,0,"ATK : %d -> %d (+%d)",getDEF(a),getDEF(a) + x,x);
                    setDEF(a,getDEF(a) + x);
                    setHP(a,getMaxHP(a));
                }
                battle_flag = 0;
            }
        }
        else if(z == 2)//ジャン負け
        {
            Damage = getATK(b) * ((rand()%3)+ 1) - getDEF(a);
            if(Damage < 0)  Damage = 0;
            mvprintw(5,0,"%sLV%d Attack! %d damage",getName(b),getLV(b),Damage);
            setHP(a,getHP(a)-Damage);
            if(getHP(a) <= 0){
                attrset(COLOR_PAIR(7));
                mvprintw(6,0,"You Lose");
                attrset(COLOR_PAIR(2));
                battle_flag = 1;
                Player_hand = getch();
                break;
            }
        }
        Player_hand = getch();
        refresh();
    }
    return battle_flag;
}
