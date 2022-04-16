## COMPILE and RUN

1. https://www.docker.com/pricing/ からDocker for (windos or mac)をダウンロード
2. 任意のディレクトリ上で git cloneする
3. cd TMToB
4. docker-compose build (docker compose build)
5. docker-compose up -d (docker compose up -d)
6. docker exec-it cdev bash
7. make
8. ./game

⚠️docker for ...が起動している状態であることを確認してください

## FEATURES

1. roguelike
2. CUI
3. Saveable
4. "Motivation" instead of "stomach"
5. May cause bugs!

## PUROISE
Climb 100 floors of the Tower of Babel

## GAMEOVER
1. Player's HP is 0
2. Motivation(Mot) is 0

## SPECIFICATIONS
Defeating enemies will give you experience and Mot
For every step you take, you lose 1Mot
K (stairs) is surrounded by a wall,
and the worst that can happen is that you cannot finish


## OPERATION METHOD
move : q,w,e,a,d,z,x,c
Magic command : k
save : you can only do it when I'm going up the stairs
