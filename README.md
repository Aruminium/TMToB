## COMPILE and RUN

1. からDocker for (windos or mac)をダウンロード windows(https://docs.docker.com/desktop/windows/install/) mac(https://docs.docker.com/desktop/mac/install/)
2. 任意のディレクトリ上で git cloneする
3. ``` cd TMToB ```
4. ``` docker-compose build ``` or  ``` docker compose build ``` ❗結構時間がかかります
5. ``` docker-compose up -d ``` or ``` docker compose up -d ```
6. ``` docker exec -it cdev bash ```
7. ``` make ``` 
8. ``` ./game ```

⚠️docker for ... が起動状態であることを確認してください
### 遊び終わったら
``` 
exit ([root@... src]状態から抜けます)
docker-compose down(docker compose down) 
```

### 再び遊ぶ時は
上記のCOMPILE and RUNより、5番目以降(docker-compose up -d (docker compose up -d))をそれぞれ実行

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
