/**
 * @file mine.cpp
 * @author Chen Zhaoyv
 * @brief   This is a code for the Minesweeper game, I connect this game with the account system
 *          by input the difficult level and return the players' grade.
 *          IN this code, I set all the variables as global variable or macro definition, so that 
 *          I don't need to input the variables in the functions everytime. What's more, I use some
 *          extracurricular functions likes color() and rand(),and also gto(),which i think is very 
 *          more brief than using circulation.
 * @version 0.1
 * @date 2023-05-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
//commentator: Chen Zhaoyv

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<conio.h>
#include<windows.h>
#include<cstdlib>
#include<ctime>
#include"head.h"
#include"Timer.hpp"
using namespace std;
 
#define MAXN 35
#define MIDX 10
#define MIDY 40
#define CG 25
#define CK 80
 
int H,M,Mnum,Fnum;//H is the height of map,M is map,Mnum is the num of mine,Fnum is the num of the rest of flags.
int nx,ny;//The position of cursor
bool Lose=0,is_flag_true[MAXN][MAXN];//Lose is judge for lose,
char map[MAXN][MAXN],tmap[MAXN][MAXN];//map is only about mines，tmap is the player interface map
int map1[MAXN][MAXN],mapc[MAXN][MAXN];//map1 is about numbers, 0 for blank,-1 for mines，1-8 for the nums of the mines arounded
//mapc is about the color
int col[10]={240,249,242,252,241,244,243,240,248};//col[i] represents the color of i in windows , col[0] is the color of space
int d[10][4]={{0},{0,1},{1,0},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};//The surrounding aquares
bool if_Perspective;//open the perspective model
int grade;//The grade that you gain.
//int Dif;//the difficulty of the game.
 

void color(int);//Setting the color
void gto(int,int);//go to the position
void generate();//generate a random map
void print();//print the interface of the begining
bool check(int,int);//check if the map make senses
bool is_win();//judge for win
bool is_lose();//judge for lose
void ras(int,int);//reveal its adjacent squares
void test(int,int);//test the adjacent squares
void flag(int,int);//flag it as flag
void fq(int,int);//flag it as question mark
void again();//paly again
void Perspective();//open perspective model
int mine();//the main function of mine.cpp
int print_real_map();//print the final map
int calculate_grade(int w,double t);//calculate players grade in my way
void begin();//all kinds of operations
 
void color(int a){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);}
void gto(int x,int y)
{
    COORD pos;pos.X=y;pos.Y=x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
 
void generate()
{
    for(int i=1;i<=H;i++)
        for(int j=1;j<=M;j++)
            map[i][j]='#';//initialization
    for(int i=1;i<=Mnum;i++)
    {
        int x=rand()%H+1,y=rand()%M+1;
        while(map[x][y]=='O')
            x=rand()%H+1,y=rand()%M+1;
        map[x][y]='O';
    }//random mines' position
    for(int i=1;i<=H;i++)
        for(int j=1;j<=M;j++)
        {
            if(map[i][j]=='O')map1[i][j]=-1,mapc[i][j]=240;//if it is mine
            else
            {
                for(int k=1;k<=8;k++)
                    if(map[i+d[k][0]][j+d[k][1]]=='O')
                        map1[i][j]++;//calculate the number of the adjacent aquares
                mapc[i][j]=col[map1[i][j]];//set the colors
            }
        }
    for(int i=1;i<=H;i++)
        for(int j=1;j<=M;j++)
            if(mapc[i][j]==0)//blank
                mapc[i][j]=240;
}
void print()
{
    system("cls");

    gto(0,MIDY-4); color(233); printf("Minesweeper");
    color(240);
    gto(1,MIDY);
    for(int i=2;i<=H+1;i++)
    {
        gto(i,0);
        for(int j=1;j<=M;j++)
            printf("#"),tmap[i-1][j]='#';
    }
 
    gto(2,0);
    nx=2,ny=0;
    color(15);
    printf("@");
 
    color(15);
    gto(3,2*M+5);cout<<"-----rule-----";
    gto(4,2*M+5);cout<<"wasd:choose the position";
    gto(5,2*M+5);cout<<"space:reveal";
    gto(6,2*M+5);cout<<"1:reveal its adjacent squares.";
    gto(7,2*M+5);cout<<"2:flag it as mine.";
    gto(8,2*M+5);cout<<"3:flag it as unknown.";
    gto(9,2*M+5);cout<<"4:show all.";
    gto(10,2*M+5);cout<<"0:restart.";

 
    gto(H+4,0);printf("-----operation tips-----\n");
    printf("please choose the block to opeerate");
 
    gto(1,2*M+10);color(12);printf("remain flags:%d",Fnum=Mnum);
}
 
bool check(int x,int y){return y>=0&&y<M&&x>=2&&x<H+2;}
bool is_win()
{
    int cnt=0;
    for(int i=1;i<=H;i++)
        for(int j=1;j<=M;j++)
            if(map[i][j]=='#'&&map1[i][j]==-1)
                cnt++;
    if(cnt==Mnum) return 1;
    for(int i=1;i<=H;i++)
        for(int j=1;j<=M;j++)
            if((tmap[i][j]!='F'&&map1[i][j]==-1)||(tmap[i][j]=='F'&&map1[i][j]!=-1))
                return 0;
    return 1;
}
bool is_lose(){return Lose;}
 
void ras(int x,int y)
{
    if(map1[x-1][y+1]>0)//surrounding by nums
    {
        gto(x,y),color(mapc[x-1][y+1]),printf("%d",map1[x-1][y+1]);
        tmap[x-1][y+1]=map1[x-1][y+1]+'0';
        return;
    }
    gto(x,y);color(255);
    tmap[x-1][y+1]=' ';
    printf(" ");
    for(int i=1;i<=8;i++)
    {
        int xx=x+d[i][0]-1,yy=y+d[i][1]+1;
        if(check(xx+1,yy-1)&&tmap[xx][yy]=='#'&&map1[xx][yy]!=-1)
            ras(xx+1,yy-1);
    }
}
void test(int x,int y)
{
    for(int i=1;i<=8;i++)
    {
        int xx=x+d[i][0],yy=y+d[i][1];
        if(check(xx,yy))
        {
            gto(xx,yy);
            if(tmap[xx-1][yy+1]!='#')
                color(mapc[xx-1][yy+1]-128);//The background color changes to gray
            else
                color(112);
            printf("%c",tmap[xx-1][yy+1]);
        }
    }
    gto(H+5,0),color(15),cout<<"press again to confirm                                      ";
    char c=getch();
    if(c=='1')
    {
        for(int i=1;i<=8;i++)
        {
            int xx=x+d[i][0],yy=y+d[i][1];
            if(check(xx,yy))
                if(tmap[xx-1][yy+1]=='F'&&map1[xx-1][yy+1]!=-1)
                {
                    Lose=1;
                    return;
                }
        }
        for(int i=1;i<=8;i++)
        {
            int xx=x+d[i][0],yy=y+d[i][1];
            if(check(xx,yy))
                if(map1[xx-1][yy+1]==-1&&tmap[xx-1][yy+1]!='F')//cancel  reveal
                    return;
        }
        for(int i=1;i<=8;i++)
        {
            int xx=x+d[i][0],yy=y+d[i][1];
            if(check(xx,yy)&&tmap[xx-1][yy+1]=='#')//open the surrounding aquares
                ras(xx,yy);
        }
    }
}
void flag(int x,int y)
{
    x-=1,y+=1;
    if(tmap[x][y]=='F')
    {
        tmap[x][y]='#';mapc[x][y]=240;
        gto(x+1,y-1),color(240),printf("#");
        Fnum++;
    }
    else
    {
        is_flag_true[x][y]=map1[x][y]==-1;//judge if the flag is correct
        tmap[x][y]='F';mapc[x][y]=253;
        gto(x+1,y-1),color(253),printf("F");
        Fnum--;
    }
    gto(1,2*M+10);color(12);cout<<"The rest of flags is:       ";
    gto(1,2*M+32);cout<<Fnum;
}
void fq(int x,int y)
{
    x-=1,y+=1;
    if(tmap[x][y]=='?')
    {
        gto(x+1,y-1),color(240),printf("#");
        tmap[x][y]='#';mapc[x][y]=240;
    }
    else
    {
        if(tmap[x][y]=='F')//update the num of flags
        {
            Fnum++;
            gto(1,2*M+10);color(12);cout<<"The rest of flags is:       ";
            gto(1,2*M+32);cout<<Fnum;
        }
        gto(x+1,y-1),color(240),printf("?");
        tmap[x][y]='?';mapc[x][y]=240;
    }
}
void Perspective()
{
    if(if_Perspective)
    {
        for(int i=1;i<=H;i++)
        {
            gto(i+1,M+2);
            for(int j=1;j<=M;j++)
                color(15),printf(" ");
        }
        if_Perspective=0;
    }
    else
    {
        for(int i=1;i<=H;i++)
        {
            gto(i+1,M+2);
            for(int j=1;j<=M;j++)
            {
                color(mapc[i][j]);
                if(map1[i][j]==-1) printf("O");
                else if(map1[i][j]>0) printf("%d",map1[i][j]);
                else printf(" ");
            }
        }
        if_Perspective=1;
    }
}
void again()
{
    H=M=Mnum=nx=ny=Lose=if_Perspective=0;
    memset(is_flag_true,0,sizeof(is_flag_true));//clear the pointor
    memset(map,0,sizeof(map));
    memset(tmap,0,sizeof(tmap));
    memset(map1,0,sizeof(map1));
    memset(mapc,0,sizeof(mapc));
    color(15);
    system("cls");
    mine();
}
 
void begin()
{
    char c=getch(); 
    gto(H+5,0),color(15),cout<<"Please choose the square to operate.";
    color(240);
    if(c=='w'&&check(nx-1,ny))//move
    {
        gto(nx,ny);
        if(tmap[nx-1][ny+1]!='#'||tmap[nx-1][ny+1]==' ')
            color(mapc[nx-1][ny+1]);
        printf("%c",tmap[nx-1][ny+1]);
        gto(nx-=1,ny);color(15);printf("@");
    }
    else if(c=='s'&&check(nx+1,ny))
    {
        gto(nx,ny);if(tmap[nx-1][ny+1]!='#'||tmap[nx-1][ny+1]==' ')color(mapc[nx-1][ny+1]);printf("%c",tmap[nx-1][ny+1]);
        gto(nx+=1,ny);color(15);printf("@");
    }
    else if(c=='a'&&check(nx,ny-1))
    {
        gto(nx,ny);if(tmap[nx-1][ny+1]!='#'||tmap[nx-1][ny+1]==' ')color(mapc[nx-1][ny+1]);printf("%c",tmap[nx-1][ny+1]);
        gto(nx,ny-=1);color(15);printf("@");
    }
    else if(c=='d'&&check(nx,ny+1))
    {
        gto(nx,ny);if(tmap[nx-1][ny+1]!='#'||tmap[nx-1][ny+1]==' ')color(mapc[nx-1][ny+1]);printf("%c",tmap[nx-1][ny+1]);
        gto(nx,ny+=1);color(15);printf("@");
    }
    else
    {
        if(c==' '&&(!(tmap[nx-1][ny+1]<='9'&&tmap[nx-1][ny+1]>='0'))&&tmap[nx-1][ny+1]!='F')
        {
            mapc[nx-1][ny+1]=col[map1[nx-1][ny+1]];
                if(map1[nx-1][ny+1]==-1) {Lose=1;return;}
                ras(nx,ny);
        }
        else if(c=='1')
        {
            test(nx,ny);
            for(int i=1;i<=8;i++)
            {
                int xx=nx+d[i][0],yy=ny+d[i][1];
                if(check(xx,yy))
                {
                    gto(xx,yy);
                    if(tmap[xx-1][yy+1]!='#') color(mapc[xx-1][yy+1]);
                    else color(240);
                    printf("%c",tmap[xx-1][yy+1]);
                }
            }
        }
        else if(c=='2'&&(tmap[nx-1][ny+1]>'9'||tmap[nx-1][ny+1]<'1'))
        {
            flag(nx,ny);
        }
        else if(c=='3'&&(tmap[nx-1][ny+1]>'9'||tmap[nx-1][ny+1]<'1'))
        {
            fq(nx,ny);
        }
        else if(c=='4')
        {
            Perspective();
        }
        else if(c=='0')
        {
            again();
        }
    }
}
 
int mine()
{
    H=M=Mnum=nx=ny=Lose=if_Perspective=0;
    memset(is_flag_true,0,sizeof(is_flag_true));//clear the pointor
    memset(map,0,sizeof(map));
    memset(tmap,0,sizeof(tmap));
    memset(map1,0,sizeof(map1));
    memset(mapc,0,sizeof(mapc));
    color(15);
    system("cls");
    system("mode con cols=120 lines=35");
    srand((unsigned)time(NULL));
    int mode = Dif;
    if(mode>4) mode=4;
    if(mode==1) H=9,M=9,Mnum=10;
    else if(mode==2) H=16,M=16,Mnum=40;
    else if(mode==3) H=16,M=30,Mnum=99;
    else
    {
        cout<<"Height:";cin>>H;
        cout<<"Width:";cin>>M;
        cout<<"mines:";cin>>Mnum;
        if(H>24) H=24;if(M>30) M=30;
        if(H<9) H=9;if(M<9) M=9;
        if(Mnum<10) Mnum=10;if(Mnum>H*M*9/10) Mnum=H*M*9/10;//compel the parameters correct
    }
    generate();
    print();
    Timer<double,void> T;

    while(1)
    {
        begin();
        if (T.elapsed() >= 1)
        {
            gto(2,2*M+5);
            cout<<T;
        }
        bool f1=is_win(),f2=is_lose();
        if(f1||f2)
        {
            gto(0,0);
            if(f1){
                color(240),gto(0,0),printf("You win!!!");            
                grade = calculate_grade(print_real_map(),T.elapsed());
            }
            if(f2){
                color(15),gto(0,0),printf("You lose!!!");
                print_real_map();
                grade = 0;
            }
                color(15);
                cout<<"your grade is "<<grade<<endl;
                system("pause");
                system("cls");
            return grade;
        }
    }
    return 0;
}
int print_real_map()
{
    int w = 0;
    color(240);
    for(int i=1;i<=H;i++)
    {
        gto(i+1,0);
        for(int j=1;j<=M;j++)
        {
            if(tmap[i][j]=='F'&&is_flag_true[i][j]==0)//wrong flags
            {
                color(252),printf("X");
                w++;
            }
            else if(map1[i][j]==-1)//mine
                color(240),printf("O");
            else if(map1[i][j]==0)//blank
                color(240),printf(" ");
            else//num
                color(mapc[i][j]),printf("%d",map1[i][j]);
        }
    }
    return w;
}

int calculate_grade(int w,double t){
    int g;
    g = 1000 - t - w*100;

    return g;
}