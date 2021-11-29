#include <stdio.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <cctype>
#include <time.h>
#include <algorithm>
#include <thread>

using namespace std;

void inputLoop();
string newUName();
string newPass();
int setupName();
int string2Num(string);
void helpOutput();

int maxLength = 20;
int minLength = 3;

bool passLower, passUpper, passNum, passSpec;

enum Modes{
    None,
    Name,
    NameLower,
    NameUpper,
    Pass
};
Modes mode;

vector<string> firstWord;
vector<string> secondWord;

const string LISTPATH = "Resources/";

int main (int argc, const char *argv[])
{
    srand((uintmax_t)std::hash<std::thread::id>()(std::this_thread::get_id()));
    mode = None;
    int repeatCounter = 1;
    maxLength = 20;
    minLength = 3;
    passLower = true;
    passUpper = true;
    passNum = true;
    passSpec = true;

    if (argc == 1)
    {
        helpOutput();
        return EXIT_FAILURE;
    }
    else if (!strcmp(argv[1], "name"))
    {
        mode = Name;
        if (argc > 1) repeatCounter = string2Num(argv[2]);
    }
    else if (!strcmp(argv[1], "nameLower") || !strcmp(argv[1], "namelower"))
    {
        mode = NameLower;
        if (argc > 1) repeatCounter = string2Num(argv[2]);
    }
    else if (!strcmp(argv[1], "nameUpper") || !strcmp(argv[1], "nameupper"))
    {
        mode = NameUpper;
        if (argc > 1) repeatCounter = string2Num(argv[2]);
    }
    else if (!strcmp(argv[1], "pass"))
    {
        mode = Pass;
        if (argc > 1) maxLength = string2Num(argv[2]);
        if (argc > 2) repeatCounter = string2Num(argv[3]);
    }
    else 
    {
        for(int i = 1; i < argc; i++)
        {
            if (mode == None)
            {
                if (!strcmp(argv[i], "-n") || !strcmp(argv[i], "--name") || !strcmp(argv[i], "--Name"))
                {
                    mode = Name;
                    continue;
                }
                else if (!strcmp(argv[i], "-nL") || !strcmp(argv[i], "-nl") || !strcmp(argv[i], "--namelower") || !strcmp(argv[i], "--nameLower"))
                {
                    mode = NameLower;
                    continue;
                }
                else if (!strcmp(argv[i], "-nU") || !strcmp(argv[i], "-nu") || !strcmp(argv[i], "--nameupper") || !strcmp(argv[i], "--nameUpper"))
                {
                    mode = NameUpper;
                    continue;
                } 
                else if (!strcmp(argv[i], "-p") || !strcmp(argv[i], "--pass") || !strcmp(argv[i], "--Pass"))
                {
                    mode = Pass;
                    continue;
                }
            }
            if (!strcmp(argv[i], "-r") || !strcmp(argv[i], "--repeat"))
            {
                repeatCounter = string2Num(argv[++i]);
            }
            else if (!strcmp(argv[i], "-l") || !strcmp(argv[i], "--length") || !strcmp(argv[i], "--maxLength") || !strcmp(argv[i], "--maxlength"))
            {
                maxLength = string2Num(argv[++i]);
            }
            else if (!strcmp(argv[i], "-lM") || !strcmp(argv[i], "-lm") || !strcmp(argv[i], "--minLength") || !strcmp(argv[i], "--minlength"))
            {
                minLength = string2Num(argv[++i]);
            }
            else if (!strcmp(argv[i], "-pO") || !strcmp(argv[i], "-po") || !strcmp(argv[i], "--passOptions") || !strcmp(argv[i], "--passoptions"))
            {
                i++;
                int j = 0;
                passLower = false;
                passUpper = false;
                passNum = false;
                passSpec = false;

                while(argv[i][j] != '\0')
                {
                    if (argv[i][j] == 'a')
                        passLower = true;
                    else if (argv[i][j] == 'A')
                        passUpper = true;
                    else if (argv[i][j] == '1')
                        passNum = true;
                    else if (argv[i][j] == '+')
                        passSpec = true;
                    else
                    {
                        cout << "\"" << argv[i-1] << " " << argv[i][j] << "\"" << " is not a valid option!\n";
                        helpOutput();
                        return EXIT_FAILURE;
                    }
                    j++;
                }
            }
            else
            {
                cout << "\"" << argv[i] << "\"" << " is not a valid option!\n";
                helpOutput();
                return EXIT_FAILURE;
            }
        }
    }

    if (mode == None)
    {
        cout << "You are missing an option!\n";
        helpOutput();
        return EXIT_FAILURE;
    }

    if (mode == Name || mode == NameLower || mode == NameUpper)
    {
        if (setupName() == EXIT_FAILURE)
            return EXIT_FAILURE;
        if (repeatCounter < 0) repeatCounter = 1;
        for (int i = 0; i < repeatCounter; i++)
            cout << newUName() << "\n";
    }
    else if (mode == Pass)
    {
        if (repeatCounter < 1) repeatCounter = 1;
        for (int i = 0; i < repeatCounter; i++)
            cout << newPass() << "\n";
    }
    else
    {
        cout << "Something went horribly wrong!\n";
        helpOutput();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int setupName()
{
    #pragma region load firstList.txt
    fstream firstFile;
        firstFile.open(LISTPATH + "firstList.txt",ios::in);
    if (firstFile.is_open() )
    {
        string line;
        while(getline(firstFile, line))
        {
            firstWord.push_back(line);
        }
    }
    firstFile.close();
    #pragma endregion

    #pragma region load secondList.txt
    fstream secondFile;
    secondFile.open(LISTPATH + "secondList.txt",ios::in);
    if (secondFile.is_open())
    {
        string line;
        while(getline(secondFile, line))
        {
            secondWord.push_back(line);
        }
    }
    secondFile.close();
    #pragma endregion

    if (firstWord.size() < 1 || secondWord.size() < 1)
    {
        cout << "You need a longer list in order to continue\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

string newUName()
{
    string username = "", one = "", two = "";

    while (username.length() < minLength || username.length() > maxLength )
    {
        one = firstWord[(rand() % (firstWord.size() - 1))];

        two = secondWord[(rand() % (secondWord.size() - 1))];
    
        username = one + two;
    }

    switch (mode)
    {
        case 0:
            break;
        case 1: //first Letters to upper Chars
            one[0] = toupper(one[0]);
            two[0] = toupper(two[0]);
            break;
        case 2: //lower
            one[0] = tolower(one[0]);
            two[0] = tolower(two[0]);
            break;
        case 3: //complete upper Chars
            for (int i = 0; i < one.length(); i++)
                one[i] = toupper(one[i]);
            for (int i = 0; i < two.length(); i++)
                two[i] = toupper(two[i]);
            break;
        default:
            break;
    }

    return one + two;
}

string newPass()
{
    string output;
    string alphabet;
    if (passLower) alphabet += "abcdefghijklmnopqrstuvwxyz";
    if (passUpper) alphabet +="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (passNum) alphabet += "0123456789";
    if (passSpec) alphabet += "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    if (maxLength < 1) maxLength = 20;
    for (int i = 0; i < maxLength; i++)
    {
        output += alphabet[rand() % (alphabet.length())];
    }
    return output;
}

int string2Num(string input)
{
    int ret = 0;
    int multi = 1;
    for (int j = input.length(); j>=0; j--)
    {
        try
        {
            if (isdigit(input[j]))
            {
                ret += (input[j] - '0')*multi;
                multi *= 10;
            }
        }
        catch (exception) {}
    }
    return ret;
}

void helpOutput()
{
    cout << "Known options:\n";
    cout << "-h  | --help\t\tShow this output\n";
    cout << "-n  | --name\t\tCreate new random username\n";
    cout << "-nL | --nameLower\tCreate new lowercase username\n";
    cout << "-nU | --nameUpper\tCreate new uppercase username\n";
    cout << "-p  | --pass\t\tCreate new password\n";
    cout << "-pO | --passOptions\tSet password options\n";
    cout << "-r  | --repeat\tSet how many names/passwords you want\n";
    cout << "-l  | --maxLength\tSet maximum length for username/password\n";
    cout << "-lm | --minLength\tSet minimum length for username\n";
    cout << "\nUsage:\n";
    cout << "youName ( -h | -n | -nL | -nU | -p ) [ -pO [aA1+] -r [x] -l [x] -lM [x] ]\n";
}

