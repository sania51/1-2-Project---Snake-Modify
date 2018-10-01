#include <dos.h>
#include <conio.h>
#include <windows.h>
#include <graphics.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
void help();
void game();
void check();
void dead();
void level();
void high();
void over();
int snake_x[500],snake_y[500],snake_size = 5,score,highscore,foodnumber=0,spd = 100,l,p,q,i;
bool checkdied = false,BONUS = false;
main()
{

    int gdirect = DETECT,gmode;
    initgraph(&gdirect,&gmode,"");

    char ch;
    setcolor(CYAN);
    settextstyle(4,0,4);
    outtextxy(80,20,"Project-1: Snake");
    settextstyle(10,0,3);
    setcolor(LIGHTGRAY);
    outtextxy(150,100,"Presented By:");
    outtextxy(190,130,"Syeda Sania Rahman");
    outtextxy(190,160,"Reg No: 2017831051");
    outtextxy(150,230,"Presented To: ");
    outtextxy(190,260,"Asif Mohammed Samir");
    outtextxy(190,290,"Assistant Professor,");
    outtextxy(190,320,"IICT,SUST");
    ch=getch();
    cleardevice();

    int cursor_y = 160;
    while(1)
    {
        for(i=0; i<=70; i++){
        p=rand()%getmaxx();
        q=rand()%getmaxy();
        putpixel(p,q,15);
    }
        setcolor(BLUE);
        settextstyle(6,0,6);
        outtextxy(160,60,"SNAKE");
        setcolor(LIGHTBLUE);
        settextstyle(3,0,3);
        outtextxy(200,160,"New Game");
        outtextxy(200,190,"Help");
        outtextxy(200,220,"Select Level");
        outtextxy(200,250,"HighScore");
        outtextxy(200,280,"Exit");
        outtextxy(180,cursor_y,">");

        if(kbhit){
        ch = getch();
        setcolor(BLACK);
        outtextxy(180,cursor_y,">");
        if(ch == 13) {
            if(cursor_y==280) exit(0);
            else if(cursor_y==190) help();
            else if(cursor_y==160) game();
            else if(cursor_y==220) level();
            else if(cursor_y==250) high();
        }
        }
        setcolor(WHITE);
        if(ch==80) {cursor_y+=30;
        if(cursor_y > 280) {cursor_y=160;}
        }
        if(ch==72) {cursor_y-=30;
        if(cursor_y < 160) {cursor_y=280;}
        }
        outtextxy(180,cursor_y,">");
    }

    return 0;
}
void help()
{
    clearviewport();
    setcolor(WHITE);
    outtextxy(100,150,"Move the snake using the Arrow keys");
    outtextxy(100,230,"Press 'Alt' to Pause");
    outtextxy(100,310,"Press any Key to go Back");
    char ch = getch();
    clearviewport();
    return;
}
void over()
{
    clearviewport();
    for(i=0; i<=500; i++){
        p=rand()%getmaxx();
        q=rand()%getmaxy();
        putpixel(p,q,15);
    }
    setcolor(RED);
    settextstyle(6,0,6);
    outtextxy(125,120,"Game Over");
    setcolor(CYAN);
    settextstyle(0,0,3);
    if(score < highscore){
    char ara[100];
        settextstyle(10,0,3);
        outtextxy(80,200,"You Couldn't Beat The Highscore :/");
        sprintf(ara,"Your Score Is %d",score);
        setcolor(YELLOW);
        outtextxy(80,240,ara);
    }
    if(score > highscore){
        char ara[100];
        settextstyle(10,0,3);
        outtextxy(80,200,"Congo!! You Just Made A New Highscore!");
        sprintf(ara,"Now The Highscore Is %d!",score);
        setcolor(YELLOW);
        outtextxy(80,240,ara);
    }
}
void game()
{
    clearviewport();
    freopen("GameData.dat","r",stdin);
    cin >> highscore;

    cleardevice();
    char ch;
    string key = "right";
    int maxx = getmaxx();
    int maxy = getmaxy()-50;
    int x = 13,y = 13;

    int food_x = rand()%maxx,food_y = rand()%maxy;
    int temp;
    temp = food_x%13;
    food_x-=temp;
    temp = food_y%13;
    food_y-=temp;
    int i = 0;
    int bonus = 500;
    foodnumber = 0;
    while(true)
        {
         clearviewport();
        if(score >0 && score%5==4) BONUS = true;
        else{ bonus = 500;
        BONUS = false;
        }
        if(!BONUS || bonus == 0){
        setcolor(BLACK);
        outtextxy(250,10,"Hurry!! 888");
        setcolor(LIGHTMAGENTA);
        setfillstyle(SOLID_FILL,LIGHTMAGENTA);
        circle(food_x,food_y,7);
        floodfill(food_x,food_y,LIGHTMAGENTA);
        }
        else
        {
        setcolor(BLUE);
        setfillstyle(SOLID_FILL,BLUE);
        circle(food_x,food_y,10);
        floodfill(food_x,food_y,BLUE);

        char spp[1000];
        setcolor(BLACK);
        sprintf(spp,"Hurry!! %d",bonus);
        outtextxy(250,10,"Hurry!! 888");
        setcolor(YELLOW);
        outtextxy(250,10,spp);
        }
        maxx = getmaxx();
        maxy = getmaxy()-50;
        setcolor(WHITE);
        line(0,maxy+8,maxx,maxy+8);
        if(kbhit())
        {
            ch = getch(); if(ch == 0) ch = getch();
            if(ch == 72 && key != "down" ) key = "up";
            if(ch == 80 && key != "up") key = "down";
            if(ch == 75 && key != "right") key = "left";
            if(ch == 77 && key != "left") key = "right";
            if(ch == 27) {
            cleardevice();
            return;
        }

        }
        if(foodnumber >= 5){
            rectangle(13,13,maxx-13,maxy-13);
            rectangle(2,2,maxx,maxy);
            setfillstyle(HATCH_FILL, CYAN);
            floodfill(9,9,WHITE);
            if((snake_y[0]>=390)||(snake_y[0]<=30)||(snake_x[0]>=600)||(snake_x[0]<=30))
            {
            delay(500);
            over();
            while(1){
            if(kbhit()){
            char ch = getch();
            if(ch == 13){
            checkdied = true;
            clearviewport();
            return;
            }
            }
            }
            }
        }
        if(foodnumber >= 10){

            bar(250,180,380,230);

            if(x >= 250 && x <= 380 && y >= 180 && y <= 230)
            {
            delay(500);
            over();
            while(1){
            if(kbhit()){
            char ch = getch();
            if(ch == 13){
            checkdied = true;
            clearviewport();
            return;
            }
            }
            }
            }
        }
        if(foodnumber >= 15){

            bar(60,70,190,120);

            if(x >= 60 && x <= 190 && y >= 70 && y <= 120)
            {
            delay(500);
            over();
            while(1){
            if(kbhit()){
            char ch = getch();
            if(ch == 13){
            checkdied = true;
            clearviewport();
            return;
            }
            }
            }
            }
        }
        if(foodnumber >= 20){

            bar(60,300,190,350);

            if(x >= 60 && x <= 190 && y >= 300 && y <= 350)
            {
            delay(500);
            over();
            while(1){
            if(kbhit()){
            char ch = getch();
            if(ch == 13){
            checkdied = true;
            clearviewport();
            return;
            }
            }
            }
            }
        }
        if(foodnumber >= 25){

            bar(440,70,570,120);

            if(x >= 440 && x <= 570 && y >= 70 && y <= 120)
            {
            delay(500);
            over();
            while(1){
            if(kbhit()){
            char ch = getch();
            if(ch == 13){
            checkdied = true;
            clearviewport();
            return;
            }
            }
            }
            }
        }
        if(foodnumber >= 30){

            bar(440,300,570,350);

            if(x >= 440 && x <= 570 && y >= 300 && y <= 350)
            {
            delay(500);
            over();
            while(1){
            if(kbhit()){
            char ch = getch();
            if(ch == 13){
            checkdied = true;
            clearviewport();
            return;
            }
            }
            }
            }
        }

        if(i < 5)
        {
            snake_x[i] = x-240;
            snake_y[i] = y-285;
            i++;
        }
        else {
        for(int _size = snake_size-2;_size >= 0;_size--) {
        snake_x[_size+1] = snake_x[_size];
        snake_y[_size+1] = snake_y[_size];
        }
        snake_x[0] = x;
        snake_y[0] = y;

        setcolor(RED);
        circle(snake_x[0],snake_y[0],8);
        setfillstyle(SOLID_FILL,WHITE);
        floodfill(snake_x[0],snake_y[0],RED);

        setcolor(WHITE);
        for(int _size = 1; _size < snake_size;_size++)
        {
        circle(snake_x[_size],snake_y[_size],5);
        setfillstyle(SOLID_FILL,WHITE);
        floodfill(snake_x[_size],snake_y[_size],WHITE);
        }

        char ara[100];
        sprintf(ara,"Score: %d",score);
        setcolor(YELLOW);
        outtextxy(00,maxy+10,ara);
        delay(spd);

        }
        if(x == food_x && y== food_y)
        {
        snake_size++;score++;foodnumber++;

        if(score%5==0 && score>0)score+=bonus;

        food_x = rand()%maxx,food_y = rand()%maxy;
        temp = food_x%13;
        food_x-=temp;
        temp = food_y%13;
        food_y-=temp;

        if(food_x < 5 || food_x > maxx - 5 || food_y < 5 || food_y > maxy - 5 || (foodnumber>=4 && food_x>=250 && food_x<=380 && food_y>=180 && food_y<=230) || ((food_y>=360)||(food_y<=30)||(food_x>=600)||(food_x<=30)) || (foodnumber >= 9 && food_x >= 60 && food_x <= 190 && food_y >= 70 && food_y <= 120)||(foodnumber >= 14 && food_x >= 60 && food_x <= 190 && food_y >= 300 && food_y <= 350)||(foodnumber >= 19 && food_x >= 440 && food_x <= 570 && food_y >= 70 && food_y <= 120)||(foodnumber >= 24 && food_x >= 440 && food_x <= 570 && food_y >= 300 && food_y <= 350))
        {
            while(food_x < 5 || food_x > maxx - 5 || food_y < 5 || food_y > maxy - 5 || (foodnumber>=4 && food_x>=250 && food_x<=380 && food_y>=180 && food_y<=230) || ((food_y>=360)||(food_y<=30)||(food_x>=600)||(food_x<=30)) || (foodnumber >= 9 && food_x >= 60 && food_x <= 190 && food_y >= 70 && food_y <= 120) || (foodnumber >= 14 && food_x >= 60 && food_x <= 190 && food_y >= 300 && food_y <= 350)||(foodnumber >= 19 && food_x >= 440 && food_x <= 570 && food_y >= 70 && food_y <= 120)||(foodnumber >= 24 && food_x >= 440 && food_x <= 570 && food_y >= 300 && food_y <= 350)){
            food_x = rand()%600,food_y = rand()%400;
            temp = food_x%13;
            food_x-=temp;
            temp = food_y%13;
            food_y-=temp;
            }
        }

        }
        if(key == "right") x = x+13; if(x > maxx) x =0;
        if(key == "left") x = x-13; if(x < 0) x = maxx-(maxx%13);
        if(key == "up") y = y-13; if(y > maxy) y = 0;
        if(key == "down") y = y+13; if(y < 0) y = maxy-(maxy%13);
        check();
        if(checkdied){
        dead();
        return;
        }

    if(BONUS){
    if(bonus>0)
    bonus-=10;
      }
        setcolor(BLACK);
        circle(snake_x[0],snake_y[0],8);
        setfillstyle(SOLID_FILL,BLACK);
        floodfill(snake_x[0],snake_y[0],BLACK);

        for(int _size = 1; _size < snake_size;_size++)
        {
        circle(snake_x[_size],snake_y[_size],5);
        setfillstyle(SOLID_FILL,BLACK);
        floodfill(snake_x[_size],snake_y[_size],BLACK);
        }

    }
}
void check()
{
    freopen("GameData.dat","w",stdout);
    if(highscore < score)
    cout << score << endl;
    else cout << highscore << endl;

    for(int i = 1;i < snake_size;i++)
    {
        if(snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i])
        {
            delay(600);
            over();
            while(1){
            if(kbhit()){
            char ch = getch();
            if(ch == 13){
            checkdied = true;
            clearviewport();
            return;
            }
            }
            }
        }
    }
}
void dead()
{
    checkdied = false;
    snake_size = 5;
    score = 0;
    foodnumber = 0;
    clearviewport();
}

void level()
{
    clearviewport();
    char ch;
    char ara[100];
    while(true){

    int i = abs(spd/10.-10);
    sprintf(ara,"SELECT LEVEL : %d",i);
    setcolor(WHITE);
    outtextxy(185,190,ara);
    outtextxy(185,250,"Press Enter to go back");

    if(kbhit())
    {
        ch = getch();
        if(ch == 80) {
        spd-=10;
        if(spd < 0) spd = 100;
        }
        else if(ch == 72) {
            spd+=10;
        if(spd > 100) spd = 0;
        }
        else if(ch == 13)
            break;
    sprintf(ara,"SELECT LEVEL : %d",i);
    setcolor(BLACK);
    outtextxy(180,350,ara);
    }
    }

    clearviewport();
}
void high()
{
        clearviewport();
        freopen("GameData.dat","r",stdin);
        cin >> highscore;
        char ara[100];
        sprintf(ara,"Highscore: %d",highscore);
        setcolor(WHITE);
        outtextxy(185,190,ara);
        outtextxy(185,250,"Press any Key to go back");
        char ch = getch();
        clearviewport();
}


