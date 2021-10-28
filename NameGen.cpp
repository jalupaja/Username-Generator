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

using namespace std;

void inputLoop();
string newUName(short);
string newPass(int);
void helpOutput();

#define MAXLENGTH 20

vector<string> adjs;
vector<string> nouns;
vector<string> verbs;
vector<string> adverbs;

int main ()
{
    #pragma region load adjectives.txt
    fstream adjFile;
    adjFile.open("Resources/adjectives.txt",ios::in);
    if (adjFile.is_open() )
    {
        string line;
        while(getline(adjFile, line))
        {
            adjs.push_back(line);
        }
    }
    else
    {
        cout << "You are missing the adjectives.txt file";
        return EXIT_FAILURE;
    }
    adjFile.close();
    #pragma endregion

    #pragma region load nouns.txt
    fstream nounFile;
    nounFile.open("Resources/nouns.txt",ios::in);
    if (nounFile.is_open())
    {
        string line;
        while(getline(nounFile, line))
        {
            nouns.push_back(line);
        }
    }
    else
    {
        cout << "You are missing the nouns.txt file";
        return EXIT_FAILURE;
    }
    nounFile.close();
    #pragma endregion

    #pragma region load verbs.txt
    fstream verbFile;
    verbFile.open("Resources/verbs.txt",ios::in);
    if (verbFile.is_open() )
    {
        string line;
        while(getline(verbFile, line))
        {
            verbs.push_back(line);
        }
    }
    else
    {
        cout << "You are missing the verbs.txt file";
        return EXIT_FAILURE;
    }
    verbFile.close();
    #pragma endregion

    #pragma region load adverbs.txt
    fstream adverFile;
    adverFile.open("Resources/adverbs.txt",ios::in);
    if (adverFile.is_open() )
    {
        string line;
        while(getline(adverFile, line))
        {
            adverbs.push_back(line);
        }
    }
    else
    {
        cout << "You are missing the adverbs.txt file";
        return EXIT_FAILURE;
    }
    adverFile.close();
    #pragma endregion

    srand((unsigned)time(NULL));

    inputLoop();

    return EXIT_SUCCESS;
}

void inputLoop()
{
    string newInput;
    while (1)
    {
        cout << "NameGen: ";
        cin >> newInput;

        int repeatCount = 1;

        for (int i = 0; i < newInput.length(); i++)
        {
            if (isdigit(newInput[i]))
            {
                repeatCount = 0;
                int multi = 1;
                for (int j = newInput.length(); j>=i; j--)
                {
                    try
                    {
                        if (isdigit(newInput[j]))
                        {
                            repeatCount += (newInput[j] - '0')*multi;
                            multi *= 10;
                        }
                    }
                    catch (exception) {}
                }
                if (repeatCount < 1)
                {
                    cout << repeatCount << " is not a valid number!\n";
                    repeatCount = 1;
                }
                newInput.erase(i);
            }
        }

        if (newInput == "help")
        {
            helpOutput();
        }
        else if (newInput == "new")
        {
            for (int i = 0; i < repeatCount; i++)
                cout << newUName(0) << "\n";
        }
        else if (newInput == "newLower" || newInput == "newlower")
        {
            for (int i = 0; i < repeatCount; i++)
                cout << newUName(1) << "\n";
        }
        else if (newInput == "newUpper" || newInput == "newupper")
        {
            for (int i = 0; i < repeatCount; i++)
                cout << newUName(2) << "\n";
        }
        else if (newInput == "pass")
        {
            cout << newPass(repeatCount) << "\n";
        }
        else if (newInput == "exit")
        {
            break;
        }
        else
        {
            cout << "This is not a known command!\n";
            helpOutput();
        }
        cout << "\n";
    }
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
    cout << "\n" << "Known commands:\n";
    cout << "help \t\tShow this output\n";
    cout << "new \t\tCreate new random username\n";
    cout << "newLower \tCreate new lowercase Username\n";
    cout << "newUpper \tCreate new uppercase Username\n";
    cout << "pass20 \t\tCreate new password with length 20\n";
    cout << "exit \t\tExit the program\n";
}

