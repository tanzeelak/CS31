//
//  main.cpp
//  Project 5
//
//  Created by Tanzeela Khan on 11/9/15.
//  Copyright © 2015 Tanzeela Khan. All rights reserved.
//
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include "utilities.h"
#include <cctype>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <cassert>
using namespace std;

int manageOneRound(const char words[][7], int nWords, int wordnum);

int main()
{
    
    char words[10000][MAXWORDLEN+1];
    int nWords = loadWords(words, 10000); //stores number of words in the file
    
    if (nWords < 1)
    {
        cout << "No words were loaded, so I can't play the game." << endl;
        return 0;
    }
    
    int rounds = 0;
    cout << "How many rounds do you want to play? ";
    cin >> rounds;
    
    if (rounds <= 0) //if rounds is not greater than 0, end program
    {
        cout << "The number of rounds must be positive." << endl;
        return 0;
    }
    
    int min = INT_MAX;
    int max = 0;
    double avg = 0;
    cout.setf(ios::fixed);
    cout.precision(2);
    double y = 0.0;

    for (int j = 1; j < (rounds+1); j++)
    {
        if (j == 1)
            cin.ignore(10000, '\n');
        
        int wordnum = randInt(0, nWords-1); //int wordnum = 0;
        
        cout << endl;
        cout << "Round " << j << endl;
        cout << "The secret word is " << strlen(words[wordnum]) << " letters long." << endl;
        
        
        int attempts = manageOneRound(words, nWords, wordnum); //catch attempts for round
        y+= attempts; //updates total attempts of all rounds
        
        //at this point: GOT THE WORD
        if (attempts ==1)
            cout << "You got it in 1 try." << endl;
        else
            cout << "You got it in " << attempts << " tries." << endl;
        
        
        
        //after one round, need to sort out averages
        avg = (y)/(j); //TOTAL ATTEMPTS DIVIDE BY CURRENT ROUND
        if (min > attempts)
        {
            min = attempts;
        }
        
        
        if (attempts > max) //if new minimum is greater than old maximum
        {
            max = attempts;
        }
        
        //at this point: have determined minimum, maximum, and average
        cout << "Average: " << avg << ", minimum: " << min << ", maximum: " << max << endl;

    }
}


int manageOneRound(const char words[][7], int nWords, int wordnum)
{

    
    
    int attempts = 0; //keeping track of attempts per rounds
    char probeWord[100]; //new array for probeWord characters. intitialzing first probe word
    
    do //keep doing this loop until the user guesses the word
    {
        cout << "Probe word: ";
        cin.getline(probeWord, 101); //taking first probe word
        
        //NEED TO CHECK IS PROBE WORD IS BETWEEEN 4-6 LOWER CASE LETTERS
        if (strlen(probeWord) > MAXWORDLEN || strlen(probeWord) < MINWORDLEN)
        {
            cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        }
        
        
        bool equal2 = false;
        for (int k = 0; probeWord[k] != '\0' && k < strlen(probeWord); k++)//MADE CHANGE
        {
            if (islower(probeWord[k]) == 0)
            {
                equal2 = true; //will change if letter in probeword is not lower
                break;
            }
        }
        
        if (equal2 == true) //while running through characters in probeword, there was something not lower
        {
            cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        }
        //covers both cases of 4-6 lower case letters
        
        
        int rocks = 0;
        int pebbles = 0;
        bool equal = false;
        for (int j = 0; words[j][0] != '\0' && j < nWords ; j++) //checking if the probe word is within the text file
        {
            if (strcmp(probeWord, words[j]) == 0) {
                equal = true;//will change if found word in list
                break;
            }
        }
        
        if (equal == false) //while running through entire text file, still did not find word
        {
            cout << "I don't know that word." << endl;
            continue;//starts entire while loop over
        }
        //at this point: probeWord is in the text file
        
        char magicWord[7];
        strcpy(magicWord, words[wordnum]); //creating new array to manipulate
        char tempProbeWord[7];
        strcpy(tempProbeWord, probeWord);
        
        for (int i = 0; tempProbeWord[i] != '\0' && magicWord[i] != '\0'; i++) //running through probe word and wordnum until one ends
        {
            if (tempProbeWord[i] == magicWord[i]) //checking if each character in probword equals an element aligning in actualword of the text file
            {
                rocks++; //covers ROCKS
                magicWord[i] = '\n';
                tempProbeWord[i] = '\n'; //blacking out current rock letter
            }
        }
 
        
        for (int j = 0; tempProbeWord[j] != '\0'; j++) //running through probeword
        {
            if (tempProbeWord[j] == '\n')
                continue;
            
            for (int m = 0; magicWord[m] != '\0'; m++) //run through wordnum
            {
                if (tempProbeWord[j] == magicWord[m] && j != m) //check if current probeword elmeent is equal to curent wordnum elment & that current positions don't equal each other
                {
                    pebbles++; //covers PEBBLES
                    magicWord[m] = '\n';
                    tempProbeWord[j] = '\n'; //blacking out current pebble letter
                    break;
                }
            }
        }
        //at this point: counted all rocks and pebbles

        attempts++; //COUNTING ATTEMPTS AFTER A POSSIBLE WORD
        
        
        
        if (strcmp(probeWord, words[wordnum]) != 0)
        {
            cout << "Rocks: " << rocks << ", Pebbles: " << pebbles << endl; //output each rocks and pebbles after each round
            
            //PROMPT for NEW probeword
            continue;
        }
        //else you found the  word and you'll exit out anywya
        
        
      
    }while (strcmp(probeWord, words[wordnum]) != 0);
    
    //at this point: GOT THE WORD

    return attempts;
}