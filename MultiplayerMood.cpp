#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

class chor_police
{
    int i, j, face, data[100], d, c = 0, p, e, q, l, m, sum[100], f, number, n, ab, bc, choose, ed, geb, pel, pela, mui, muia, x[100], y[100][100], z[100], jack, sum1 = 0, xy[100];
    int temp, yj[100], maximum, jet, minimum, med, r, a1, az, ap, ac, ad;
    int zeno, zemo, letto, loitta, maximum2, maximum3, ash[100], goku = 0;
    int toriama = 0, toriama1 = 0, toriama2 = 0, donald, micky, mona, gohan = 0, easy = -1, doggy = 0;
    char pikacchu;
    int easy1 = -1;
    int f1, f2, f3, f4, so1, accah = 0, mj1, mj2, mj3, mj4;

public:
    int find_chor_police(string s[], int saitama)
    {
        srand(time(0));
        easy1 = -1;
        for (i = 1; i <= saitama; i++)
        {
            mj1 = 0;
            mj2 = 0;
            mj3 = 0;
            mj4 = 0;
            easy++;
            cout << endl
                 << "Round no: " << i << endl << endl;
            cout << "Do you wish to continue with the game???" << endl;
            cout << "Press any key to continue and press 1 to quit and press 0 to restart the game again:";
            cin >> pikacchu;
            if (doggy > 0)
            {
                easy1++;
                if (pikacchu == '1')
                {
                    doggy = 0;
                    return easy;
                }
                else if (pikacchu == '0')
                {
                    goku = 0;
                    doggy = 0;
                    easy = -1;
                    return 0;
                }
                else
                {
                    cout << endl
                         << "Continue the game at your will" << endl << endl;
                    system("pause");
                    system("cls");
                }
            }
            else if (pikacchu == '1' && i == 1)
            {
                return 100;
            }
            else if (pikacchu == '1')
            {
                cout << endl << endl;
                system("pause");
                system("cls");
                return easy;
            }
            else if (pikacchu == '0')
            {
                doggy++;
                goku = 0;
                return 0;
            }
            else
            {
                cout << endl
                     << "Continue the game at your will" << endl << endl;
                system("pause");
                system("cls");
            }
            jack = 0;
            c = 1;
            e = 0;
            for (j = 1; j <= 6000000; j++)
            {
                face = 1 + rand() % 4;
                if (e == 4)
                {
                    break;
                }
                if (c == 1)
                {
                    data[face] = 100;
                    p = face;
                    c++;
                    e++;
                }
                else if (c == 2 && face != p)
                {
                    data[face] = 160;
                    q = face;
                    c++;
                    e++;
                }
                else if (c == 3 && face != p && face != q)
                {
                    data[face] = 60;
                    l = face;
                    c++;
                    e++;
                }
                else if (face != p && face != q && face != l)
                {
                    data[face] = 50;
                    e++;
                }
            }
            cout << endl << endl;
            cout << "                  --------         --------" << endl;
            cout << "                  |   1  |         |   2  |" << endl;
            cout << "                  --------         --------" << endl << endl;
            cout << "                  --------         --------" << endl;
            cout << "                  |   3  |         |   4  |" << endl;
            cout << "                  --------         --------" << endl << endl;
            cout << "You can choose any number from the range of 1 to 4: " << endl;
            int leka = 0;
            int doll = 0;
            accah = 0;
            f1 = 0;
            f2 = 0;
            f3 = 0;
            f4 = 0;
            for (int k = 1; k <= 4; k++)
            {
                if (accah == 1)
                {
                    accah = 0;
                    cout << endl << endl << endl << endl;
                    system("pause");
                    system("cls");
                }
                if (k == 2)
                {
                    f1 = number;
                    so1 = number;
                }
                if (k == 3)
                {
                    f2 = number;
                }
                if (k == 4)
                {
                    f3 = number;
                }
                cout << s[k] << " please choose:";
                while (1)
                {
                    cin >> number;
                    if (number == 1 && mj1 == 0)
                    {
                        mj1++;
                        break;
                    }
                    else if (number == 2 && mj2 == 0)
                    {
                        mj2++;
                        break;
                    }
                    else if (number == 3 && mj3 == 0)
                    {
                        mj3++;
                        break;
                    }
                    else if (number == 4 && mj4 == 0)
                    {
                        mj4++;
                        break;
                    }
                    else
                    {
                        cout << endl;
                        cout << s[k] << " please choose again:";
                        continue;
                    }
                }
                if (data[number] == 100)
                {
                    z[k] = data[number];
                    geb = k;
                }
                else if (data[number] == 160)
                {
                    cout << s[k] << " got Police=" << data[number] << endl;
                    cout << "Now you have to find who is Chor OR who is Dakat" << endl;
                    z[k] = data[number];
                    n = number;
                    ed = k;
                }
                else if (data[number] == 60)
                {
                    pel = number;
                    z[k] = data[number];
                    pela = k;
                }
                else if (data[number] == 50)
                {
                    mui = number;
                    z[k] = data[number];
                    muia = k;
                }
                accah++;
            }
            cout << endl << endl << endl << endl;
            system("pause");
            system("cls");
            cout << "Revealed!! " << s[ed] << " got Police" << endl << endl << endl << endl;

            if (i % 2 == 1)
            {
                cout << s[ed] << " Now you have to choose between the remaining three players to find the thief:" << endl;
                for (int k = 1; k <= 4; k++)
                {
                    if (k != ed)
                    {
                        cout << k << ". " << s[k] << endl;
                    }
                }

                cin >> choose;
                while (1)
                {
                    if (choose == ed || choose < 1 || choose > 4)
                    {
                        cout << endl
                             << "You have chosen Invalid. Please guess again:" << endl;
                        cin >> choose;
                    }
                    else
                    {
                        break;
                    }
                }

                if (data[choose] == 50)
                { 
                    cout << "You have caught the Chor. Congratulations" << endl;
                    data[mui] = 0; 
                    jack += 2;
                }
                else if (data[choose] == 100)
                { 
                    cout << "You have chosen the Babu. This is an invalid guess!" << endl;
                    data[ed] = 0; 
                    jack++;
                }
                else
                {
                    cout << "You have chosen the wrong guy" << endl;
                    data[ed] = 0; 
                    jack++;
                }
            }
            else
            {
                cout << s[ed] << " Now you have to choose between the remaining three players to find the Dakat:" << endl;
                for (int k = 1; k <= 4; k++)
                {
                    if (k != ed)
                    { 
                        cout << k << ". " << s[k] << endl;
                    }
                }

                cin >> choose;
                while (1)
                {
                    if (choose == ed || choose < 1 || choose > 4)
                    {
                        cout << endl
                             << "You have chosen Invalid. Please guess again:" << endl;
                        cin >> choose;
                    }
                    else
                    {
                        break;
                    }
                }

                if (data[choose] == 60)
                { 
                    cout << "You have caught the Dakat. Congratulations" << endl;
                    data[pel] = 0; 
                    jack += 2;
                }
                else if (data[choose] == 100)
                { 
                    cout << "You have chosen the Babu. This is an invalid guess!" << endl;
                    data[ed] = 0; 
                    jack++;
                }
                else if (data[choose] == 50)
                { 
                    cout << "You have chosen the Chor. This is not the Dakat!" << endl;
                    data[ed] = 0; 
                    jack++;
                }
                else
                {
                    cout << "You have chosen the wrong guy" << endl;
                    data[ed] = 0; 
                    jack++;
                }
                if (data[mui] == 50)
                {
                    cout << s[muia] << " retains their 50 points as the thief was not caught in this round." << endl;
                }

                if (data[pel] == 0)
                {
                    data[ed] = 160;
                }
                else
                {
                    data[pel] = 60;
                    data[ed] = 0;
                }
            }

            if (jack == 1)
            {
                z[ed] = data[n];
            }
            else if (jack == 2)
            {
                z[pela] = data[pel];
                z[muia] = data[mui];
            }
            for (int deq = 1; deq <= 4; deq++)
            {
                y[i][deq] = z[deq];
            }
            goku++;
            cout << endl << endl << endl << endl;
            for (int duck = 1; duck <= 4; duck++)
            {
                cout << setw(15) << s[duck] << setw(10);
            }
            cout << endl;
            for (donald = 1; donald <= goku; donald++)
            {
                for (micky = 1; micky <= 4; micky++)
                {
                    cout << setw(15) << y[donald][micky] << setw(13);
                }
                cout << endl;
            }
            cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
            system("pause");
            system("cls");
        }
        cout << endl << endl << endl << "The game is over. So the final result is shown below" << endl << endl << endl << endl;
        cout << " Revealed!! " << s[geb] << " got Babu" << endl << endl << endl << endl;
        for (i = 1; i <= 4; i++)
        {
            cout << setw(15) << s[i] << setw(10);
        }
        cout << endl;
        for (i = 1; i <= saitama; i++)
        {
            for (j = 1; j <= 4; j++)
            {
                cout << setw(15) << y[i][j] << setw(13);
            }
            cout << endl;
        }
        for (i = 1; i <= 4; i++)
        {
            sum1 = 0;
            for (j = 1; j <= saitama; j++)
            {
                sum1 = sum1 + y[j][i];
            }
            xy[i] = sum1;
        }
        cout << "--------------------------------------------------------------" << endl;
        for (i = 1; i <= 4; i++)
        {
            cout << setw(15) << xy[i] << setw(13);
        }
        maximum = xy[1];
        minimum = xy[1];
        int pq, gq;
        for (int i = 1; i <= 4; i++)
        {
            if (xy[i] > maximum)
            {
                maximum = xy[i];
                pq = i;
            }
        }
        for (int i = 1; i <= 4; i++)
        {
            if (xy[i] < minimum)
            {
                minimum = xy[i];
                gq = i;
            }
        }
        return -13;
    }

    void final_result(string s[], int saitama)
    {
        for (i = 1; i <= 4; i++)
        {
            sum1 = 0;
            for (j = 1; j <= saitama; j++)
            {
                sum1 += y[j][i];
            }
            xy[i] = sum1;
        }
        maximum = xy[1];
        int winnerIndex = 1;

        for (int i = 2; i <= 4; i++)
        {
            if (xy[i] > maximum || (xy[i] == maximum && s[i] < s[winnerIndex]))
            {
                maximum = xy[i];
                winnerIndex = i;
            }
        }

        cout << "\nCongratulations!!! " << s[winnerIndex] << " is the winner with " << maximum << " points!" << endl;
    }
};

int main()
{
    chor_police c;
    string a[10], b[10];
    int n, number;
    cout << endl
         << "                  Welcome to the world of Chor Dakat Police Babu Game " << endl
         << endl;
    cout << "Rules:" << endl
         << endl;
    cout << "1. First of all,4 player is needed to play this game" << endl;
    cout << "2. Each player has to choose a number from the range of 1 to 4 to see whether the player is babu or police or chor or dakat" << endl;
    cout << "3. The player who finds babu will be remained safe and get 100 points" << endl;
    cout << "4. But the rest of the players are not safe" << endl;
    cout << "5. The player who gets the police will have to choose between the chor and dakat" << endl;
    cout << "6. If the police is able to catch the chor the police will get 80 points otherwise chor and dakat will get 40 and 60 points respectively" << endl;
    cout << "7. The game will continue to be like this and all the points achieved by the players will be added to their previous points respectively" << endl;
    cout << "8. At the end whoever has the maximum point will be declared as the first winner and others will be declared as second,third and imposter according to their points" << endl;
    cout << "9. Therefore the game will be completed and will be completely shut down" << endl
         << endl;
    system("pause");
    system("cls");
    cout << endl << endl;
    char choose;
    cout << setw(70) << "<New Game(Press any key for a New game)" << endl;
    cout << setw(63) << "<Quit Game(Press 1 to quit game)" << endl;
    cout << setw(38) << "Press:";
    cin >> choose;
    cout << endl;
    system("pause");
    system("cls");
    if (choose == '1')
    {
        cout << "The game has been shut down" << endl;
        return 0;
    }
    else
    {
        cout << "Continue the game at your own will" << endl
             << endl;
        system("pause");
        system("cls");
    }
    cout << endl
         << "Enter 4 player names:" << endl
         << endl;
    for (int i = 1; i <= 4; i++)
    {
        cout << "Player no. " << i << ":";
        if (i == 1)
        {
            cin.ignore();
        }
        getline(cin, a[i]);
    }
    cout << endl
         << "So how many times do you guys want to play: 8, 16 or 20?";
    cin >> number;
    system("cls");
    int ans = c.find_chor_police(a, number);
    if (ans == 0)
    {
        while (1)
        {
            cout << endl
                 << endl
                 << "The game has been restarted" << endl
                 << endl;
            system("pause");
            system("cls");
            cout << endl
                 << "Enter 4 player names:" << endl;
            for (int i = 1; i <= 4; i++)
            {
                cout << "Player no. " << i << ":";
                if (i == 1)
                {
                    cin.ignore();
                }
                getline(cin, b[i]);
            }
            cout << endl
                 << "So how many times do you guys want to play:";
            cin >> number;
            system("cls");
            int ans = c.find_chor_police(b, number);
            if (ans == 0)
            {
                continue;
            }
            else if (ans == 1000)
            {
                c.final_result(b, number);
                cout << "The game has been shut down completely" << endl;
                break;
            }
            else if (ans == -13)
            {
                cout << endl
                     << endl
                     << endl;
                system("pause");
                system("cls");
                c.final_result(b, number);
                cout << "The game has been shut down completely" << endl;
                break;
            }
            else
            {
                c.final_result(b, ans);
                cout << endl;
                system("pause");
                system("cls");
                cout << "The game has been completely shut down" << endl;
                break;
            }
        }
    }
    else if (ans == 100)
    {
        c.final_result(a, number);
        cout << "The game has been shut down completely" << endl;
    }
    else if (ans == -13)
    {
        c.final_result(a, number);
        cout << "The game has been shut down completely" << endl;
    }
    else
    {
        c.final_result(a, ans);
        cout << endl;
        system("pause");
        system("cls");
        cout << "The game has been shut down completely" << endl;
    }
    return 0;
}
