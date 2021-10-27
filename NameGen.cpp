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

void startLoop();
string newUName();
void helpOutput(bool = false);

#define MAXLENGTH 20

vector<string> adjs;
vector<string> nouns;
vector<string> verbs;
vector<string> adverbs;

short nameState;

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

    startLoop();

    return EXIT_SUCCESS;
}

void startLoop()
{
    string newInput;
    while (1)
    {
        cout << "NameGen: ";
        cin >> newInput;

        int repeatCount = -1;

        for (int i = 0; i < newInput.length(); i++)
        {
            if (isdigit(newInput[i]))
            {
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
                    cout << "This is not a valid number!\n";
                    newInput.clear();
                    newInput = "help";
                    return;
                }
                newInput.erase(i);
                break;
            }
        }
        cout << "'" << newInput << "'" << endl;
        if (newInput == "help")
        {
            helpOutput();
        }
        else if (newInput == "new")
        {
            nameState = 0;
            cout << newUName() << "\n";
        }
        else if (newInput == "newLower" || newInput == "newlower")
        {
            nameState = 1;
            cout << newUName() << "\n";
        }
        else if (newInput == "newUpper" || newInput == "newupper")
        {
            nameState = 2;
            cout << newUName() << "\n";
        }

        else if (newInput == "exit")
        {
            break;
        }
        else
        {
            helpOutput(true);
        }
        cout << "\n";
    }
}

string newUName()
{
    string username = "", one = "", two = "";
    srand(time(NULL));
    switch (rand() % 3 + 1)
    {
        case 1:
        //Adjetive + Noun
        //if the username is too small or too long, well keep going.
        while (username.length() < 3 || username.length() > MAXLENGTH )
        {
            do
            {
                srand(time(NULL));
                one = adjs[(rand() % (adjs.size() - 1))];
            }
            while (one.length() < 3);

            do
            {
                srand(time(NULL));
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
                srand(time(NULL));
                one = verbs[(rand() % (verbs.size() - 1))];
            }
            while (one.length() < 3);

            do
            {
                srand(time(NULL));
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
                srand(time(NULL));
                one = adverbs[(rand() % (adverbs.size() - 1))];
            }
            while (one.length() < 3);

            do
            {
                srand(time(NULL));
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
            for (int i = 0; i < one.length()-1; i++)
                one[i] = toupper(one[i]);
            for (int i = 0; i < two.length()-1; i++)
                two[i] = toupper(two[i]);
            break;
        default:
            break;
    }

    return one + two;
}


void helpOutput(bool error)
{
    if (error)
    {
        cout << "This is not a known command!\n";
    }
    cout << "\n" << "Known commands:\n";
    cout << "help \t\tShow this output\n";
    cout << "new \t\tCreate new random username\n";
    cout << "newLower \tCreate new lowercase Username\n";
    cout << "newUpper \tCreate new uppercase Username\n";
    cout << "exit \t\tExit the program\n";
}

