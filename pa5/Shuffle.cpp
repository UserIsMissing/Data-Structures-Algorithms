/*
Cole Schreiner
caschrei
pa5
Shuffle.cpp
*/


#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>

using namespace std;
#include "List.h"


void shuffle(List &D)
{
    List A;
    int halfDeck = D.length() / 2;
    D.moveFront();
    int inc = 0;
    while (inc < halfDeck)
    {
        A.insertBefore(D.front());
        D.eraseAfter();
        inc++;
    }
    A.moveFront();
    while (A.length() > 0)
    {
        D.moveNext();
        D.insertBefore(A.front());
        A.eraseAfter();
    }
}

int main(int argc, char *argv[])
{
    ifstream in;
    ofstream out;
    stringstream SString;

    //-----------------------------------------------------------------------------
    // Check command line arguments
    //-----------------------------------------------------------------------------
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        exit(1);
    }

    //-----------------------------------------------------------------------------
    // Print output
    //-----------------------------------------------------------------------------
    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;

    int DECK;
    SString << argv[1];
    SString >> DECK;

    for (int i = 1; i <= DECK; i++)
    {
        List deck;
        for (int j = 0; j < i; j++)
        {
            deck.insertBefore(j);
        }
        int count = 0;
        List originalDeck = deck;
        do
        {
            shuffle(deck);
            count++;
        } while (!(deck == originalDeck));
        cout << i << " " << count << endl;
    }

    //-----------------------------------------------------------------------------
    // Close files
    //-----------------------------------------------------------------------------
    in.close();
    out.close();
    return 0;
}
