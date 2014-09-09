#define _WIN32_WINNT 0x0500     //MOUSE POS
#include <iostream>             //COUT AND CIN
#include<windows.h>             //COLOURS AND VARIOUS BELLS AND WHISTLES
#include<time.h>                //SEDDING RANDOM VALUES
#include <limits.h>             //FOR MOUSEPOS
#include<conio.h>               //KBHIT() AND GETCH()
#include<fstream>             //FOR HIGHSCORE FILE
#include<stdio.h>

using namespace std;

int main();                     //TO CALL MAIN ;)


//GLOBAL VARIABLES
char ch;int num;int turn=29,t=29;int uc;int a;int mx,my;int xpre,ypre;
char title[124] = "DRENCH - the world's simplest flash game";



//CLASS AND OBJECTS
class board
{
public:
    bool state;
    char sym;
};
board coin[10][15];

class score
{
public:
    char name[30];
    int mark;
};

//SYSTEM CONTROL FUNCTIONS
void gotoxy (int x, int y)                  //CURSOR COORDINATES
{
    COORD coord;
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setcursor(bool visible,DWORD size)     //REMOVE BLINKING CURSOR
{
        HANDLE console=GetStdHandle(STD_OUTPUT_HANDLE);
        if(size==0)
        {
                size=20;
        }
        CONSOLE_CURSOR_INFO lpCursor;
        lpCursor.bVisible=visible;
        lpCursor.dwSize=size;
        SetConsoleCursorInfo(console,&lpCursor);
}



//USER DEFINED FUNCTIONS
void highscore()
{
    score sc,ss;
    char x;char name[20];
    fstream file;
    file.open("Score",ios::app|ios::in|ios::out|ios::binary);
    cout<<"Want to Save Your Score?.....(y)";
    cin>>x;
    if(x=='y'||x=='Y')
    {
        cin.clear();
        cout<<"Enter Name...";cin.ignore();
        cin.getline(sc.name,30);
        sc.mark=t-turn*10;
        file.write((char *)&sc,sizeof(sc));

        file.seekg(ios::beg);
        file.read((char *)&ss,sizeof(ss));
        cout<<ss.name<<"\t"<<ss.mark;

        x='n';
    }

    file.close();
}

void border()                               //CUSTOM BORDER
{
    int c,r;
    for(c=0;c<80;c++)                       //HORIZONTAL
    {
        gotoxy(c,0);
        cout<<'%';
        gotoxy(c,24);
        cout<<'%';
    }
    for(r=0;r<24;r++)                       //VERTICAL
    {
        gotoxy(0,r);
        cout<<'%';
        gotoxy(79,r);
        cout<<'%';
    }
}

void clear()                                //CLEAR DRENCH BOARD
{
    for(int i=3;i<33;++i)
        for(int k=2;k<22;++k)
        {
            gotoxy(i,k);
            cout<<" ";
        }
}

void mousepos()                             //MOUSE CHARACTER COORDINATES
{
    // Get screen frame rate, as there's no point going any faster
    DWORD frameRate = 0;

    DEVMODEA devMode = {0};
    devMode.dmSize = sizeof(DEVMODE);
    if(EnumDisplaySettingsA(NULL, ENUM_CURRENT_SETTINGS, &devMode))
        frameRate = devMode.dmDisplayFrequency;
    else
        frameRate = 60; // default value if fail to get actual value

    // get our window
    HWND hWnd = GetConsoleWindow();

    // to remember where we were last time
    POINT posLast = {LONG_MIN, LONG_MIN};

    while(1)
    {
        // get current mouse position in screen coords
        POINT pos = {0, 0};
        if (GetCursorPos(&pos))
        {
            // convert position to client window coords
            if (ScreenToClient(hWnd, &pos))
            {
                // get window's client rect
                RECT rcClient = {0};
                GetClientRect(hWnd, &rcClient);

                // if mouse cursor is inside rect
                if (PtInRect(&rcClient, pos))
                {
                    // and if we've moved since last time
                    if ((posLast.x != pos.x) || (posLast.y != pos.y))
                    {
                        // get size and position of console window/buffer in rows and columns
                        CONSOLE_SCREEN_BUFFER_INFO info = {0};
                        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
                        const SMALL_RECT& smRect = info.srWindow;

                        // calculate row and column corresponding to mouse position
                        // (note this takes accounts of console buffer scrolling)
                        mx = smRect.Left + (pos.x * (smRect.Right  - smRect.Left))
                                / (rcClient.right  - rcClient.left);
                        my = smRect.Top  + (pos.y * (smRect.Bottom - smRect.Top ))
                                / (rcClient.bottom - rcClient.top );

                        // and last position
                        posLast = pos;
                    }
                }
                else
                {
                    //Do nothing
                }
                Sleep(10000 / frameRate);
                break;
            }
        }
    }
}

void disp(void)                             //DISPLAY FUNCTION
{
    //CONVERTING SYMBOLS IN EACH ARRAY ELEMENT TO COLOURED SQUARE
    cout<<"\n\n";
    for(int i=0;i<20;++i)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//COLOUR
        cout<<"%  ";
        for(int j=0;j<30;++j)
        {
            switch(coin[i/2][j/2].sym)
            {
            case '!':
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                cout<<char(219);
                break;

            case '@':
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout<<char(219);
                break;

            case '#':
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
                cout<<char(219);
                break;

            case '$':
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                cout<<char(219);
                break;

            case '%':
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                cout<<char(219);
                break;

            case '*':
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                cout<<char(219);
                break;
            }
        }
        cout<<endl;
    }

    //DRENCH BOARD BORDER
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    for(int i=0;i<30;++i)
    {
        gotoxy(3+i,1);
        cout<<char(209);
        gotoxy(3+i,22);
        cout<<char(207);
    }
    for(int i=0;i<20;++i)
    {
        gotoxy(2,i+2);
        cout<<char(186);
        gotoxy(33,i+2);
        cout<<char(186);
    }
    gotoxy(2,1);cout<<char(201);
    gotoxy(33,1);cout<<char(187);
    gotoxy(33,22);cout<<char(188);
    gotoxy(2,22);cout<<char(200);
    gotoxy(40,17);

    cout<<"YOU HAVE "<<turn<<" MOVES TO DRENCH THE BOARD";
    gotoxy(65,21);
    cout<<"'H' FOR HELP";
    gotoxy(63,22);
    cout<<"'ESC' FOR EXIT";
}

void iface()                                //MOUSE AND KEYBOARD INPUT
{
    uc=0;
    while(uc!=1 && uc!=2 && uc!=3 && uc!=4 && uc!=5 && uc!=6)
    {
        //DISPLAY OPTIONS
        gotoxy(40,10);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout<<"   |1|";//<<char(2);
        gotoxy(52,10);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout<<"   |2|";//<<char(2);
        gotoxy(64,10);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
        cout<<"   |3|";//<<char(2);
        gotoxy(40,5);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout<<"   |4|";//<<char(2);
        gotoxy(52,5);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cout<<"   |5|";//<<char(2);
        gotoxy(64,5);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout<<"   |6|";//<<char(2);

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        help:
        if(kbhit())                         //KEYBOARD INPUT
        {
            char f=getch();
            if(f=='h')                      //HELP SECTION IF 'H'
            {
                gotoxy(3,4+40);cout<<"How to Play...";
                gotoxy(3,7+40);cout<<"1. Drench the board from ";
                gotoxy(3,8+40);cout<<"   top left in one colour";
                gotoxy(3,10+40);cout<<"2. Click on a colour";
                gotoxy(3,12+40);cout<<"3. Enter a corresponding number";
                gotoxy(3,15+40);cout<<"Enjoy!!!";
                gotoxy(3,15+46);
                Sleep(3210);
                gotoxy(0,0);
                goto help;
            }
            else                            //ELSE INPUT NUMBER
               uc=f-48;

        }

        if((GetKeyState(0x1B)<-100))        //ESCAPE KEY PRESS
        {
            gotoxy(0,100);
            exit(0);
        }

        if ((GetKeyState(VK_LBUTTON) & 0x80) != 0)  //MOUSE INPUT
        {
            mousepos();                     //GET MOUSE COORDINATES

            //CHECK MOUSE POSITION TO DETERMINE COLOUR
            if(mx>=42 && mx<=45 && my>=9 && my<=11)
                uc=1;
            else if(mx>=54 && mx<=57 && my>=9 && my<=11)
                uc=2;
            else if(mx>=66 && mx<=69 && my>=9 && my<=11)
                uc=3;
            else if(mx>=42 && mx<=45 && my>=4 && my<=6)
                uc=4;
            else if(mx>=54 && mx<=57 && my>=4 && my<=6)
                uc=5;
            else if(mx>=66 && mx<=69 && my>=4 && my<=6)
                uc=6;
        }
    }
    //ASSIGN APPROPRIATE SYMBOL
    switch(uc)
    {
    case 1:ch='!';    break;
    case 2:ch='@';    break;
    case 3:ch='#';    break;
    case 4:ch='$';    break;
    case 5:ch='%';    break;
    case 6:ch='*';    break;
    }
    gotoxy(0,0);

}

void init()                                 //INITIALISE BOARD
{
    for(int i=0;i<10;++i)
    {
        for(int j=0;j<15;++j)
        {
            coin[i][j].state=false;
            num=rand()%6;                   //RANDOM NUMBER SELECTION
            switch(num)                     //ASSIGN COLOURS
            {
            case 0:coin[i][j].sym='@';
            break;
            case 1:coin[i][j].sym='#';
            break;
            case 2:coin[i][j].sym='$';
            break;
            case 3:coin[i][j].sym='%';
            break;
            case 4:coin[i][j].sym='*';
            break;
            case 5:coin[i][j].sym='!';
            break;
            }
        }
    }
}

bool test()                                 //CHECK FOR WIN CONDITION
{
    int a=1;
    char ch=coin[0][0].sym;                 //COLOUR OF TOP LEFT ELEMENT
    for(int i=0;i<10;++i)
    {
        for(int j=0;j<15;++j)
        {
            if(coin[i][j].sym==ch)
                continue;
            else                            //RETURN FALSE IF DIFFERENT COLOUR 'CH'
            {
                a=0;
                return false;
            }
        }
    }
    if(a==1)                                //RETURN TRUE IF ALL SAME COLOUR
        return true;
    return 0;
}

void game(void)                             //GAME FUNCTION
{
    coin[0][0].state=true;                  //MAKE TOP LEFT ELEMENT TRUE
    while(turn>=0)
    {
        iface();                            //CALLING INTERFACE
        for(int i=0;i<10;++i)
        {
            for(int j=0;j<15;++j)
            {
                if(coin[i][j].state==true)  //IF ELEMENT IS TRUE
                    {   //MAKE ADJACENT ELEMENTS OF SAME COLOUR TRUE
                        coin[i][j].sym=ch;
                        if(coin[i+1][j].sym==ch && i<10)
                            coin[i+1][j].state=true;
                        if(coin[i][j+1].sym==ch && j<15)
                            coin[i][j+1].state=true;
                        if(coin[i-1][j].sym==ch && i>0)
                            coin[i-1][j].state=true;
                        if(coin[i][j-1].sym==ch && j>0)
                            coin[i][j-1].state=true;
                    }
            }
        }
        clear();                            //CALLING CLEAR BOARD
        gotoxy(0,0);
        disp();                             //CALLING DISPLAY

        if(test())                          //WIN CONDITION
        {
            system("cls");
            gotoxy(26,11);cout<<"YOU HAVE DONE IT......!!!";
            gotoxy(28,13);cout<<"NEXT LEVEL?...(Y)";
            char xx;
            cin>>xx;
            if(xx=='y' || xx=='Y')
            {
                t--;                        //DECREASE NUMBER OF TURNS
                turn=t;
                main();                     //REPLAY
            }
            Sleep(101);
            exit(0);
        }

        if(turn==0 && test()==false)        //LOSE OR TURNS OVER CONDITION
        {
            system("cls");
            gotoxy(29,11);cout<<"REFRESH?......(Y)!!!";
            char xx;
            cin>>xx;
            if(xx=='y' || xx=='Y')
            {
                turn=t;
                main();                     //REPLAY
            }
            Sleep(101);
            exit(0);
        }

        turn--;
    }
}



//MAIN FUNCTION
int main()                                  //MAIN FUNCTION
{
    highscore();
    /*
    system("cls");
    cout<<"Hello World!"<<endl;
    Sleep(666);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //COLOUR
    SetConsoleTitleA(title);
    Sleep(101);
    srand(time(NULL));
    setcursor(0,0);

    border();
    gotoxy(0,0);
    init();
    disp();
    gotoxy(40,17);

    cout<<"YOU HAVE "<<turn+1<<" MOVES TO DRENCH THE BOARD";

    game();
    getch();
    */
    return 0;
}


//************************************CREDITS******************************************
//  FLASHBYNIGHT (THE ORIGINAL GAME ... http://www.flashbynight.com/drench/  )
//  cplusplus.com ,FOR THE HELP AND SUPPORT (AND THE MOUSEPOS FUNCTION)
//  VEDANT, RAVIKIRAN AND SUSHIL FOR IDEAS, TROUBLESHOOTING AND SUPPORT
