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
string newUName(short);
string newPass(int);
int setupName();
int string2Num(string);
void helpOutput();

#define MAXLENGTH 20

vector<string> adjs;
vector<string> nouns;
vector<string> verbs;
vector<string> adverbs;

const string LISTPATH = "Resources/";

int main (int argc, char *argv[])
{
    srand((uintmax_t)std::hash<std::thread::id>()(std::this_thread::get_id()));
    int repeatCounter = 1;
    if (argc == 1)
    {
        helpOutput();
    }
    else if (!strcmp(argv[1], "name"))
    {
        if (setupName() == EXIT_FAILURE)
            return EXIT_FAILURE;
        if (argc > 2)
            repeatCounter = string2Num(argv[2]);
        if (repeatCounter < 1) repeatCounter = 1;
        for (int i = 0; i < repeatCounter; i++)
            cout << newUName(0) << "\n";
    }
    else if (!strcmp(argv[1], "nameLower") || !strcmp(argv[1], "namelower"))
    {
        if (setupName() == EXIT_FAILURE)
            return EXIT_FAILURE;
        if (argc > 2)
            repeatCounter = string2Num(argv[2]);
        if (repeatCounter < 1) repeatCounter = 1;
        for (int i = 0; i < repeatCounter; i++)
            cout << newUName(1) << "\n";
    }
    else if (!strcmp(argv[1], "nameUpper") || !strcmp(argv[1], "nameupper"))
    {
        if (setupName() == EXIT_FAILURE)
            return EXIT_FAILURE;
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

int setupName()
{
    #pragma region load adjectives.txt
    fstream adjFile;
    adjFile.open(LISTPATH + "adjectives.txt",ios::in);
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
    nounFile.open(LISTPATH + "nouns.txt",ios::in);
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
    verbFile.open(LISTPATH + "verbs.txt",ios::in);
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
    adverFile.open(LISTPATH + "adverbs.txt",ios::in);
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
    return EXIT_SUCCESS;
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
    cout << "Known commands:\n";
    cout << "help\t\tShow this output\n";
    cout << "name x\t\tCreate new x new random usernames\n";
    cout << "nameLower x\tCreate x new lowercase usernames\n";
    cout << "nameUpper x\tCreate x new uppercase usernames\n";
    cout << "pass l x\t\tCreate x new passwords with the length l\n";
    cout << "exit \t\tExit the program\n";
}

