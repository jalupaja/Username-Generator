#include <stdio.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>

using namespace std;

void startLoop();
string newUName();
void helpOutput(bool error = false);

#define MAXLENGTH 30

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
        if (newInput == "help")
        {
            helpOutput();
        }
        else if (newInput == "new")
        {
            cout << newUName() << endl;
        }
        else if (newInput == "newLower")
        {
            cout << newUName() << endl; //!!!
        }

        else if (newInput == "exit")
        {
            break;
        }
        else
        {
            helpOutput(true);
        }
        cout << "" << endl;
    }
}

string newUName()
{
    string username = "", one = "", two = "";
    //srand(time(NULL));
    //short ran = rand() % 3 + 1;
    //cout << "ran: " << ran << endl;
    switch (1)
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
        }
        break;

    }

    username = one + two;

    return username;
}



void helpOutput(bool error)
{
    if (error)
    {
        cout << "This is not a known command!" << endl;
    }
    cout << "\n" << "Known commands:" << endl;
    cout << "help : Show this output" << endl;
    cout << "new : Create new random username" << endl;
    cout << "newLower : Create new lowercase Username" << endl;
    cout << "exit : Exit the program" << endl;
}

