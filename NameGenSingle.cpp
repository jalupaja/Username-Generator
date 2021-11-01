#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <cctype>
#include <time.h>
#include <algorithm>
#include <thread>

using namespace std;

void inputLoop();
string newUName(short);
string newPass(int);
void helpOutput();
int string2Num(string);


#define MAXLENGTH 20

#pragma region vectors
vector<string> adjs;
vector<string> nouns;
vector<string> adverbs;
vector<string> verbs;
#pragma endregion

int main(int argc, char *argv[])
{
    srand((long long)std::hash<std::thread::id>()(std::this_thread::get_id()));

    int repeatCounter = 1;
    if (argc == 1)
    {
        helpOutput();
    }
    else if (!strcmp(argv[1], "new"))
    {
        if (argc > 2)
            repeatCounter = string2Num(argv[2]);
        if (repeatCounter < 1) repeatCounter = 1;
        for (int i = 0; i < repeatCounter; i++)
            cout << newUName(0) << "\n";
    }
    else if (!strcmp(argv[1], "newLower") || !strcmp(argv[1], "newlower"))
    {
        if (argc > 2)
            repeatCounter = string2Num(argv[2]);
        if (repeatCounter < 1) repeatCounter = 1;
        for (int i = 0; i < repeatCounter; i++)
            cout << newUName(1) << "\n";
    }
    else if (!strcmp(argv[1], "newUpper") || !strcmp(argv[1], "newupper"))
    {
        if (argc > 2)
            repeatCounter = string2Num(argv[2]);
        if (repeatCounter < 1) repeatCounter = 1;
        for (int i = 0; i < repeatCounter; i++)
            cout << newUName(2) << "\n";
    }
    else if (!strcmp(argv[1], "pass"))
    {
        int length = 20;
        if (argc > 2)
            length = string2Num(argv[2]);
        if (length < 1) length = 1;
        if (argc > 3)
            repeatCounter = string2Num(argv[3]);
        if (repeatCounter < 1) repeatCounter = 1;
        for (int i = 0; i < repeatCounter; i++)
            cout << newPass(length) << "\n";
    }
    else
    {
        helpOutput();
    }

    return EXIT_SUCCESS;
}

string newUName(short nameState)
{
    string username = "", one = "", two = "";
    switch (rand() % 3 + 1)
    {
        case 1:
        //Adjetive + Noun
        //if the username is too small or too long, well keep going.
        while (username.length() < 3 || username.length() > MAXLENGTH )
        {
            do
            {
                one = adjs[(rand() % (adjs.size() - 1))];
            }
            while (one.length() < 3);

            do
            {
                two = nouns[(rand() % (nouns.size() - 1))];
            }
            while (two.length() < 3);
            
            username = one + two;
        }
        break;

        case 2:
        //Verbs + Noun
        //if the username is too small or too long, well keep going.
        while (username.length() < 3  || username.length() > MAXLENGTH )
        {
            do
            {
                one = verbs[(rand() % (verbs.size() - 1))];
            }
            while (one.length() < 3);

            do
            {
                two = nouns[(rand() % (nouns.size() - 1))];
            }
            while (two.length() < 3);
            
            username = one + two;
        }
        break;

        case 3:
        //Adverb + Noun
        //if the username is too small or too long, well keep going.
        while (username.length() < 3 || username.length() > MAXLENGTH)
        {
            do
            {
                one = adverbs[(rand() % (adverbs.size() - 1))];
            }
            while (one.length() < 3);

            do
            {
                two = nouns[(rand() % (nouns.size() - 1))];
            }
            while (two.length() < 3);

            username = one + two;
        }
        break;

    }

    switch (nameState)
    {
        case 0: //first Letters to upper Chars
            one[0] = toupper(one[0]);
            two[0] = toupper(two[0]);
            break;
        case 1: //lower
            one[0] = tolower(one[0]);
            two[0] = tolower(two[0]);
            break;
        case 2: //complete upper Chars
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

string newPass(int len)
{
    const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    string output;
    if (len == 1) len = 20;
    for (int i = 0; i < len; i++)
    {
        output += alphabet[rand() % (alphabet.length())];
    }
    return output;
}

void helpOutput()
{
    cout << "Known commands:\n";
    cout << "help \t\tShow this output\n";
    cout << "new \t\tCreate new random username\n";
    cout << "newLower \tCreate new lowercase Username\n";
    cout << "newUpper \tCreate new uppercase Username\n";
    cout << "pass20 \t\tCreate new password with length 20\n";
    cout << "exit \t\tExit the program\n";
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
