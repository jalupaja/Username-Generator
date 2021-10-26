#include <stdio.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <stdlib.h>

using namespace std;

void startLoop();
string newUName();
void helpOutput(bool error = false);

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
            adjs.push_back(line);
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
            adjs.push_back(line);
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
            adjs.push_back(line);
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
    while (true)
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
            cout << newUName() << endl;
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
    //switch (rand() % 3 + 1)
    string username = "";
    switch (1)
    {
        case 1:
        //Adjetive + Noun
        //if the username is too small or too long, well keep going.
        while (username.length() < 3 || username.length() > 15 )
        {
            string one = adjs[rand() % (adjs.size() - 1)];
            cout << "one: " << one << endl;
            //while (one == "" || one == " ") one = adjs[rand() % (adjs.size() - 1)];
            string two = nouns[rand() % (nouns.size() - 1)];
            cout << "two: " << two << endl;
            //while (two == "" || two == " ") two = nouns[rand() % (nouns.size() - 1)];
            
            username = one + two;
            cout << one << " | " << two << " | " << username << endl; //!!!
        }
        break;
        /*case 2:
        {
            //Verbs + Noun
            //if the username is too small or too long, well keep going.
            while (username == "" || username.Length < 3  || username.Length > 10 )
            {
                string one = verbs[ran.Next(0, verbs.Length - 1)];
                while (one == "" || one == " ") one = verbs[ran.Next(0, verbs.Length - 1)];
                string two = nouns[ran.Next(0, nouns.Length - 1)];
                while (two == "" || two == " ") two = nouns[ran.Next(0, nouns.Length - 1)];
                //Pretty self-explanatory <3
                one = one.ToLower();
                two = two.ToLower();
                if (upperCase)
                {
                    char o = one.Substring(0, 1).ToCharArray()[0];
                    char t = two.Substring(0, 1).ToCharArray()[0];
                    one = one.Remove(0, 1);
                    one = o.ToString().ToUpper() + one;
                    two = two.Remove(0, 1);
                    two = t.ToString().ToUpper() + two;
                }
                if (!allinOne)
                {
                    username = one + " " + two;
                }
                else
                {
                    username = one + two;
                }
            }
            //we found it! lets get out of this mess.
            break;
        }
        case 3:
        {
            //Adverb + Noun
            //if the username is too small or too long, well keep going.
            while (username == "" || username.Length < 3 || username.Length > 10)
            {
                string one = adverbs[ran.Next(0, adverbs.Length - 1)];
                while (one == "" || one == " ") one = adverbs[ran.Next(0, adverbs.Length - 1)];
                string two = nouns[ran.Next(0, nouns.Length - 1)];
                while (two == "" || two == " ") two = nouns[ran.Next(0, nouns.Length - 1)];
                //Pretty self-explanatory <3
                one = one.ToLower();
                two = two.ToLower();
                if (upperCase)
                {
                    char o = one.Substring(0, 1).ToCharArray()[0];
                    char t = two.Substring(0, 1).ToCharArray()[0];
                    one = one.Remove(0, 1);
                    one = o.ToString().ToUpper() + one;
                    two = two.Remove(0, 1);
                    two = t.ToString().ToUpper() + two;
                }
                if (!allinOne)
                {
                    username = one + " " + two;
                }
                else
                {
                    username = one + two;
                }
            }
            
            //we found it! lets get out of this mess.
            break;
        }*/
            

    }

    return "username";
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

