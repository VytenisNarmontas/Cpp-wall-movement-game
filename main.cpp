#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
using namespace std;

string mapName;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); ///spalvu keitimo kodas (taip pat atkomentuoti apacioje kodo dali Draw())
bool gameOver;///susikuriame bool kuris suzinos kada baig zaidima
int playerX, playerY, score=0, mapSizeX, mapSizeY; ///susikuriame pagrindinius intus (universalius)
const int maxMapSizeX=100, maxMapSizeY=100; ///susikutiame constantinius intus, kurie nesikeis
char mapArr[maxMapSizeY][maxMapSizeX]; ///susikuriame pagrindinio zemelapio array
int oCount = 0;
enum eDir {STOP = 0, LEFT, RIGHT, UP, DOWN, RESTART}; ///paskiriame dir reiksmes
eDir dir;

void Setup()///pradiniai zaidimo nustatymai
{
    gameOver = false;
    dir = STOP;
    score=0;
    oCount=0;
}
void Read()///skaitome faila su duomenimis
{
    char a;
    ifstream fd(mapName);
    fd>> mapSizeX >> mapSizeY >> playerX >> playerY;
    if(mapSizeX>maxMapSizeX||mapSizeY>maxMapSizeY||mapSizeX<=0||mapSizeY<=0)
    {
        cout<<"invalid coordinates in the file: "<<mapName<<endl;
        exit(-1);
    }

    for(int y=0; y<mapSizeY; y++)
    {
        for(int x=0; x<mapSizeX; x++)
        {
            fd>>a;
            switch(a)
            {
            case 'o':
                oCount++;
                mapArr[y][x]=a;
                break;
            case '#':
                mapArr[y][x]=(char)219u;
                break;
            case 'E':
                mapArr[y][x]=(char)220u;
                break;
//            case '@':
//                mapArr[y][x]=a;
//                playerX=x;
//                playerY=y;
//                break;
            default:
                mapArr[y][x]=' ';
            }
        }
    }
}
void Draw()///piesiame lenta su playeriu
{
    system("cls");
    for(int i=0; i<mapSizeY; i++)
    {
        for(int j=0; j<mapSizeX; j++)
        {
            if(playerY==i&&playerX==j)
            {
                cout<<(char)2u;
            }
            else if(mapArr[i][j]=='o')
            {
                SetConsoleTextAttribute(hConsole, 12); ///spalvos keitimo kodas
                cout<<mapArr[i][j];
                SetConsoleTextAttribute(hConsole, 15); ///spalvos keitimo kodas
            }
            else
            {
                cout<<mapArr[i][j];
            }
        }
        cout<<endl;
    }
    cout<<"score: "<<score<<endl;
    cout<<"movement: wasd"<<endl;
    cout<<"restart level: r"<<endl;
    cout<<"skip level: x"<<endl<<endl;
    cout<<"player moves until a wall is hit"<<endl<<"Objective: collect all the \"o\"s"<<endl;
}
void Input()///nuskaitome mygtuko paspaudima ir priskiriame jam reiksme
{
    if(_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir=LEFT;
            break;
        case 'd':
            dir=RIGHT;
            break;
        case 'w':
            dir=UP;
            break;
        case 's':
            dir=DOWN;
            break;
        case 'r':
            dir=RESTART;
            break;
        case 'x':
            gameOver=true;
            break;
        }
    }
}
void Checko()
{
    if(mapArr[playerY][playerX]=='o')
            {
                score++;
                mapArr[playerY][playerX]=' ';
//                Draw();
            }
}
//void Logic();
//void DCD()
//{
//
//}
void Logic()///pagrindine zaidimo logika (judejimas ir tasku rinkimas)
{
    switch(dir)
    {
    case LEFT:
        while(mapArr[playerY][playerX-1]!=(char)219u)//||mapArr[playerY][playerX-1]!=(char)220u)
        {
            playerX--;
            Draw();
            Checko();
        }
        dir=STOP;
        Checko();
        Draw();
//        if(mapArr[playerY][playerX-1]==(char)220u)
//            {
//                score=0;
//                oCount=0;
//                dir=STOP;
//                Read();
//                Draw();
//            }
        break;
    case RIGHT:
        while(mapArr[playerY][playerX+1]!=(char)219u)//||mapArr[playerY][playerX+1]!=(char)220u)
        {
            playerX++;
            Draw();
            Checko();
        }
        dir=STOP;
        Checko();
        Draw();
//        if(mapArr[playerY][playerX+1]==(char)220u)
//            {
//                score=0;
//                oCount=0;
//                dir=STOP;
//                Read();
//                Draw();
//            }
        break;
    case UP:
        while(mapArr[playerY-1][playerX]!=(char)219u)//||mapArr[playerY-1][playerX]!=(char)220u)
        {
            playerY--;
            Draw();
            Checko();
        }
        dir=STOP;
        Checko();
        Draw();
//        if(mapArr[playerY-1][playerX]==(char)220u)
//            {
//                score=0;
//                oCount=0;
//                dir=STOP;
//                Read();
//                Draw();
//            }
        break;
    case DOWN:
        while(mapArr[playerY+1][playerX]!=(char)219u)//||mapArr[playerY+1][playerX]!=(char)220u)
        {
            playerY++;
            Draw();
            Checko();
        }
        dir=STOP;
        Checko();
        Draw();
//        if(mapArr[playerY+1][playerX]==(char)220u)
//            {
//                score=0;
//                oCount=0;
//                dir=STOP;
//                Read();
//                Draw();
//            }
        break;
    case RESTART:
        score=0;
        oCount=0;
        Read();
        Draw();
        dir=STOP;
        break;
    }
    if (oCount==score) {
        cout << endl << "You did it!" << endl;
        gameOver=true;
    }
}
void Play()
{
    while(!gameOver)
    {
        Input();
        Logic();
    }
}


int main()///main
{
    ///pirmas zaidimas
    Setup();
    mapName="Map2.txt";
    Read();
    Draw();
    Play();

    ///antras zaidimas
    Setup();
    mapName="Map1.txt";
    Read();
    Draw();
    Play();

    ///trecias zaidimas
    Setup();
    mapName="Map3.txt";
    Read();
    Draw();
    Play();

    ///ketvirtas zaidimas
    Setup();
    mapName="Map4.txt";
    Read();
    Draw();
    Play();

}
