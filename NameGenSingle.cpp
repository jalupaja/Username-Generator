#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <thread>

using namespace std;

void inputLoop();
string newUName(short);
string newPass(int);
void helpOutput();
int setupFiles();
int string2Num(string);

#define MAXLENGTH 20

vector<string> adjs, advs, nouns, verbs;

static const string FOLDER = "Resources/";

int main(int argc, char *argv[])
{
    srand((uintmax_t)std::hash<std::thread::id>()(std::this_thread::get_id()));
    srand(unsigned(time(0)));
    int repeatCounter = 1;
    if (argc == 1)
    {
        helpOutput();
    }
    else if (!strcmp(argv[1], "new"))
    {
        if (setupFiles() == EXIT_FAILURE)
            return EXIT_FAILURE;
        if (argc > 2)
            repeatCounter = string2Num(argv[2]);
        if (repeatCounter < 1) repeatCounter = 1;
        for (int i = 0; i < repeatCounter; i++)
            cout << newUName(0) << "\n";
    }
    else if (!strcmp(argv[1], "newLower") || !strcmp(argv[1], "newlower"))
    {
        if (setupFiles() == EXIT_FAILURE)
            return EXIT_FAILURE;
        if (argc > 2)
            repeatCounter = string2Num(argv[2]);
        if (repeatCounter < 1) repeatCounter = 1;
        for (int i = 0; i < repeatCounter; i++)
            cout << newUName(1) << "\n";
    }
    else if (!strcmp(argv[1], "newUpper") || !strcmp(argv[1], "newupper"))
    {
        if (setupFiles() == EXIT_FAILURE)
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
                one = advs[(rand() % (advs.size() - 1))];
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
    cout << "adj:" << adjs[(adjs.size() - 1)] << "\nadv:" << advs[(advs.size() - 1)] << "\nverbs:" << verbs[(verbs.size() - 1)] << "\nnouns:" << nouns[(nouns.size() - 1)] << "\n";
    return "1" + one + "2" + two;
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

int setupFiles()
{ 
    #pragma region load adjectives.txt
    fstream adjFile;
    adjFile.open(FOLDER + "adjectives.txt",ios::in);
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
    nounFile.open(FOLDER + "nouns.txt",ios::in);
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
    verbFile.open(FOLDER + "verbs.txt",ios::in);
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
    adverFile.open(FOLDER + "adverbs.txt",ios::in);
    if (adverFile.is_open() )
    {
        string line;
        while(getline(adverFile, line))
        {
            advs.push_back(line);
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
