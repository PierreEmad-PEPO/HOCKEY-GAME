#include<bits/stdc++.h>
#include<conio.h>
using namespace std;

const int ScreenX = 23 , ScreenY = 30;


class Player
{
protected:
    int posx=0,posy=0;
    int score=0;

public:
    void input(char ch);

    pair<int,int> getPos()
    {
        return {posx,posy};
    }

    void respawn();

    int getScore()
    {
        return score;
    }

    void Goal()
    {
        score++;
    }
};

class Player1 : public Player
{
public:
    Player1()
    {
        posx=ScreenX/4-2;
        posy=ScreenY/2-3;
    }
    void respawn()
    {
        posx=ScreenX/4-2;
        posy=ScreenY/2-3;
    }
    void print()
    {
        cout<<posx<<" "<<posy<<"\n";
    }

    void input(char ch)
    {
        if(ch=='4' && posy>0)
            posy--;
        else if(ch=='6' && posy<ScreenY-4)
            posy++;
        else if(ch=='5' && posx+1<ScreenX/2)
            posx++;
        else if(ch=='8' && posx>0)
            posx--;
    }
};


class Player2 : public Player
{
public:
    Player2()
    {
        posx=ScreenX/2 + ScreenX/4 + 2;
        posy=ScreenY/2-3;
    }
    void respawn()
    {
        posx=ScreenX/2 + ScreenX/4 + 2;;
        posy=ScreenY/2-3;
    }

    void input(char ch)
    {
        if(ch=='a' && posy>0)
            posy--;
        else if(ch=='d' && posy<ScreenY-4)
            posy++;
        else if(ch=='s' && posx<ScreenX-1)
            posx++;
        else if(ch=='w' && posx-1>ScreenX/2)
            posx--;
    }
};

class Ball
{
private:
    int posx = ScreenX/2 + ScreenX/4 - 2, posy = ScreenX/2;
    int vectorx=0,vectory=0;
public:
    void collision()
    {
        if(posy>=11 && posy<=18)
            return;
        if(posx+vectorx >= ScreenX || posx+vectorx < 0)
            vectorx*=-1;
        if(posy+vectory >= ScreenY || posy+vectory < 0)
            vectory*=-1;
    }
    void direct(Player1& p1,Player2& p2)
    {
        if(posx<0 && posy>=11 && posy<=18)
            p2.Goal(),p1.respawn(),p2.respawn(),posx=p1.getPos().first+2,posy=p1.getPos().second+1,vectorx=0,vectory=0;

        else if(posx>ScreenX && posy>=11 && posy<=18)
            p1.Goal(),p1.respawn(),p2.respawn(),posx=p2.getPos().first-2,posy=p2.getPos().second+1,vectorx=0,vectory=0;

        if(posx+vectorx == p1.getPos().first && posy+vectory == p1.getPos().second+1)
            vectory=0,vectorx==0?vectorx=1:vectorx*=-1;
        else if(posx+vectorx == p1.getPos().first && posy+vectory == p1.getPos().second+2)
            vectory=0,vectorx==0?vectorx=1:vectorx*=-1;
        else if(posx+vectorx == p1.getPos().first && posy+vectory == p1.getPos().second)
            vectory=-1,vectorx==0?vectorx=1:vectorx*=-1;
        else if(posx+vectorx == p1.getPos().first && posy+vectory == p1.getPos().second+3)
            vectory=1,vectorx==0?vectorx=1:vectorx*=-1;

        if(posx+vectorx == p2.getPos().first && posy+vectory == p2.getPos().second+1)
            vectory=0,vectorx==0?vectorx=-1:vectorx*=-1;
        else if(posx+vectorx == p2.getPos().first && posy+vectory == p2.getPos().second+2)
            vectory=0,vectorx==0?vectorx=-1:vectorx*=-1;
        else if(posx+vectorx == p2.getPos().first && posy+vectory == p2.getPos().second)
            vectory=-1,vectorx==0?vectorx=-1:vectorx*=-1;
        else if(posx+vectorx == p2.getPos().first && posy+vectory == p2.getPos().second+3)
            vectory=1,vectorx==0?vectorx=-1:vectorx*=-1;
    }
    void update()
    {
        posx+=vectorx;
        posy+=vectory;
    }
    pair<int,int> getPos()
    {
        return {posx,posy};
    }
    void out_of_grid_respawn()
    {
        if(posx<0 || posx>ScreenX || posy<0 || posy>ScreenY)
            posx = ScreenX/2 + ScreenX/4 - 2, posy = ScreenX/2;
    }
};

void Draw(Player1& p1,Player2& p2,Ball& b)
{
    cout<<"\n";
    for(int i=0;i<ScreenY/2-3;i++)
        cout<<'#';
    for(int i=0;i<7;i++)
        cout<<' ';
    for(int i=0;i<ScreenY/2-2;i++)
        cout<<'#';
    cout<<"\n";
    for(int i=0;i<ScreenX;i++)
    {
        cout<<'#';
        for(int j=0;j<ScreenY;j++)
        {
            if(i==p1.getPos().first && j>=p1.getPos().second && j<=p1.getPos().second+3)
                cout<<'*';
            else if(i==p2.getPos().first && j>=p2.getPos().second && j<=p2.getPos().second+3)
                cout<<'*';
            else if(i==b.getPos().first && j==b.getPos().second)
                cout<<'O';
            else
                cout<<' ';
        }
        cout<<"#";
        if(i==9) cout<<"\tPLAYER 1: "<<p1.getScore();
        else if(i==13) cout<<"\tPLAYER 2: "<<p2.getScore();
        cout<<"\n";
    }
    for(int i=0;i<ScreenY/2-3;i++)
        cout<<'#';
    for(int i=0;i<7;i++)
        cout<<' ';
    for(int i=0;i<ScreenY/2-2;i++)
        cout<<'#';
    cout<<"\n";
}

int main()
{
    Player1 player1;
    Player2 player2;
    Ball ball;
    while(1)
    {
        if(kbhit())
        {
            char ch = getch();
            player1.input(ch);
            player2.input(ch);
        }
        ball.direct(player1,player2);
        ball.update();
        ball.collision();
        system("cls");
        Draw(player1,player2,ball);
    }

    return 0;
}
