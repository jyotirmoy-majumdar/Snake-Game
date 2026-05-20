#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
using namespace std;

int main()
{
    char World_Grid[10][10];
    char control = 'D';
    char lastMove = 'D';
    char key;
    int body = 3;
    int snakex[100];
    int snakey[100];
    snakex[0] = 5;
    snakey[0] = 5;
    snakex[1] = 5;
    snakey[1] = 4;
    snakex[2] = 5;
    snakey[2] = 3;
    bool pause = false;
    int foodx, foody;
    int i, j;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            World_Grid[i][j] = '.';
        }
    }
    World_Grid[snakex[0]][snakey[0]] = 'O';
    cout << "-------------GAME START--------------- " << endl;
    Sleep(500);

    // Print grid
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            cout << World_Grid[i][j] << " ";
        }
        cout << endl;
    }

    // FOOD GENERATION
    foodx = rand() % 10;
    foody = rand() % 10;

    cout << "Enter how to move the snake (W A S D): " << endl;
    cout << "Enter SPACEBAR to pause the game " << endl;
    cout << "Enter '/' to exit the game " << endl;
    cout << "Press any key to start";
    getch();
    system("cls");

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = false;

    SetConsoleCursorInfo(console, &cursorInfo);

    while (true)
    {
        // DYNAMIC INPUT LOGIC
        if (kbhit())
        {
            key = getch();
            if (key == ' ')
            {
                pause = !pause;
            }
            if (key == '/')
            {
                return 0;
            }
        }

        // KEY CHECKING
        if (key == 'W' || key == 'w' || key == 'A' || key == 'a' || key == 'S' || key == 's' || key == 'D' || key == 'd')
        {
            control = key;
        }

        // OPPOSITE MOVEMENT CHECKING
        if (toupper(control) == 'A' && lastMove == 'D')
            control = 'D';

        if (toupper(control) == 'D' && lastMove == 'A')
            control = 'A';

        if (toupper(control) == 'W' && lastMove == 'S')
            control = 'S';

        if (toupper(control) == 'S' && lastMove == 'W')
            control = 'W';

        // PAUSE CHECKING
        if (pause == false)
        {
            // SNAKE MOVEMENT
            for (i = body - 1; i > 0; i--)
            {
                snakex[i] = snakex[i - 1];
                snakey[i] = snakey[i - 1];
            }

            // Movement
            if (control == 'W' || control == 'w') // UP
                snakex[0]--;

            else if (control == 'S' || control == 's') // DOWN
                snakex[0]++;

            else if (control == 'A' || control == 'a') // LEFT
                snakey[0]--;

            else if (control == 'D' || control == 'd') // RIGHT
                snakey[0]++;

            if (snakey[0] < 0) // LEFT TO RIGHT TELEPORT
                snakey[0] = 9;

            if (snakey[0] > 9) // RIGHT TO LEFT TELEPORT
                snakey[0] = 0;

            if (snakex[0] < 0) // DOWN TO UP TELEPORT
                snakex[0] = 9;

            if (snakex[0] > 9) // UP TO DOWN TELEPORT
                snakex[0] = 0;

            lastMove = toupper(control);

            // HEAD TOUCHING
            for (i = 1; i < body; i++)
            {
                if (snakex[0] == snakex[i] && snakey[0] == snakey[i])
                {
                    Beep(660, 100);
                    Beep(660, 100);
                    Sleep(50);

                    Beep(660, 100);
                    Sleep(150);

                    Beep(510, 100);
                    Beep(660, 100);
                    Sleep(150);

                    Beep(770, 100);
                    Sleep(300);

                    Beep(380, 100);
                    cout << "---------------GAME OVER---------------" << endl;
                    cout << "------------- YOUR SCORE : " << body - 3 << " -------------" << endl;
                    return 0;
                }
            }

            // GRID Removing
            for (i = 0; i < 10; i++)
            {
                for (j = 0; j < 10; j++)
                {
                    World_Grid[i][j] = '.';
                }
            }

            // FOOD DRAWING
            World_Grid[foodx][foody] = '$';

            // FOOD EATING
            if (snakex[0] == foodx && snakey[0] == foody)
            {
                Beep(700, 150);
                Sleep(5);
                body++;
                snakex[body - 1] = snakex[body - 2];
                snakey[body - 1] = snakey[body - 2];
                foodx = rand() % 10;
                foody = rand() % 10;
            }

            // SNKAE DRAWING
            for (i = 0; i < body; i++)
            {
                if (i == 0)
                {
                    World_Grid[snakex[i]][snakey[i]] = 'O';
                }
                else
                {
                    World_Grid[snakex[i]][snakey[i]] = 'o';
                }
            }
        }

        COORD cursorPosition;
        cursorPosition.X = 0;
        cursorPosition.Y = 0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

        // Print grid
        for (i = 0; i < 10; i++)
        {
            for (j = 0; j < 10; j++)
            {
                cout << World_Grid[i][j] << " ";
            }
            cout << endl;
        }
        Sleep(150);
    }
}