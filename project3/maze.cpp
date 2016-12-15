#include "grid.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cassert>
using namespace std;

//prototype: telling file what function is

bool isValidDir(char);
bool isInBounds(int size, int offset, int i);
bool isRouteWellFormed(string);
int navigateSegment(int, int, char, int);
int navigateRoute(int, int, int, int, string, int&);
bool positionCheck (int r, int c);

//checking if everything is false before determining true
int main()
{
    setSize(3,4);      // make a 3 by 4 grid
    setWall(1,4);      // put a wall at (1,4)
    setWall(2,2);      // put a wall at (2,2)
    if (!isWall(3,2))  // if there's no wall at (3,2)  [there isn't]
        setWall(3,2);  //    put a wall at (3,2)
    draw(3,1, 3,4);    // draw the grid, showing an S at (3,1)
    //    start position, and an E at (3,4)
}

//declare function and implementation
bool isValidDir(char a)//determines if char is a valid direction
{
    if((a == 'N') || (a == 'n') || (a == 'S') || (a == 's') || (a == 'W') || (a == 'w') || (a == 'E') || (a == 'e'))
    {
        return true;
    }
    else
        return false;
}

bool isInBounds(int size, int offset, int i) //determines if digit at char is within bounds and offset
{
    if ((offset + i) >= size)
        return false;
    if ((offset + i) < 0)
        return false;
    return true;
}

bool isRouteWellFormed(string route) //determines if route is syntactically valid
{
    if (route.size() == 0)//check if there are no chraacters
    {
        return false;
    }
    if (!isValidDir(route[0]))//check if the first character is a valid direction
    {
        return false;
    }
    for (int i = 1; i < route.size(); i++) //after checking first character, run through whole string
        {
            if (!isValidDir(route[i]) && !isdigit(route[i]))
            {
                return false;
            }
            if (isdigit(route[i]))
            {
                if (isInBounds(route.size(), -1, i) && !isdigit(route[i-1]))//check one character behind is a direction
                {
                    continue;
                }
                if (isInBounds(route.size(), -2, i) && !isdigit(route[i-2]))//check if two characters behind is a direction
                {
                    continue;
                }
                return false;
            }
            
        }
    return true;
}

bool positionCheck (int r, int c) //determines if coordinate is within the assigned grid, using libraries
{
    if (c > getCols() || c < 1)
        return false;
    if (r > getRows() || r < 1)
        return false;
    return true;
}

int navigateSegment(int r, int c, char dir, int maxSteps)// determines max steps in ONE direction
{
    int tempc, tempr, counter = 0;
    
    if ( (positionCheck(r, c)==false) || (isWall(r, c)) || (isValidDir(dir)==false) || (maxSteps<0)) //all bad stuff
        return -1;
    if (dir == 'E' || dir == 'e')
    {
        for (tempc = c+1; tempc <= c + maxSteps; tempc++) //offset
        {
            if (positionCheck(r, tempc) && !isWall(r,tempc) ) //checking if position is within grid and no wall
                counter++;
            else
                return counter;
        }
    }
    if (dir == 'W' || dir == 'w')
    {
        for (tempc = c-1; tempc >= c - maxSteps; tempc--)
        {
            if (positionCheck(r, tempc) && !isWall(r,tempc) )
                counter++;
            else
                return counter;
        }
    }
    if (dir == 'N' || dir == 'n')
    {
        for (tempr = r-1; tempr >= r - maxSteps; tempr--)
        {
            if (positionCheck(tempr, c) && !isWall(tempr, c) )
                counter++;
            else
                return counter;
        }
    }
    if (dir == 'S' || dir == 's')
    {
        for (tempr = r+1; tempr <= r + maxSteps; tempr++)
        {
            if (positionCheck(tempr, c) && !isWall(tempr, c) )
                counter++;
            else
                return counter;
        }
    }
    return counter;
}

void updateStartingPosition(int& sr, int& sc, char dir, int nsteps) //moves starting position for each step depending on direction
{
    int ur, uc;
    if (dir == 'N'  || dir == 'n')
    {
        ur = -1;
        uc = 0;
        sr += nsteps * ur;
    }
    else if (dir == 'S' || dir == 's')
    {
        ur = 1;
        uc = 0;
        sr += nsteps * ur;
    }
    else if (dir == 'W' || dir == 'w')
    {
        ur = 0;
        uc = -1;
        sc += nsteps * uc;
    }
    else if (dir == 'E' || dir == 'e')
    {
        ur = 0;
        uc = 1;
        sc += nsteps * uc;
    }
}

int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps)//sets nsteps = max # of steps robot at (sr,sc) takes when following ROUTE to (er,ec)
{
    if (positionCheck(sr, sc) == false || isWall(sr,sc) == true || positionCheck(er, ec) == false || isWall(er,ec) == true || isRouteWellFormed(route) == false)
    {
        return 2;
    }
    
    int tempr = sr, tempc = sc;
    nsteps = 0;
    int attemptedSteps = 0, actualSteps = 0, steps = 0, stepCount = 0;

    for (int i =0; i < route.size(); i++)//go through all characters in ROUTE
    {
        if (isValidDir(route[i]) == true) //starts each SEGMENT at direction char
        {
            int j = i;
            j++;
            
            if (isdigit(route[j]) == false) //if character after dir is not a number
            {                               //then must be a character. so first dir is incremented by 1
                attemptedSteps += 1;
                steps = navigateSegment(tempr, tempc, route[i], 1); //actual steps for segment
                actualSteps += steps; //overall counter for whole path
                updateStartingPosition(tempr, tempc, route[i], steps);//update starting position each ONE time segment's step is increased
                if (steps != 1)
                {
                    nsteps = actualSteps;
                    return 3;
                }
                continue;
            }
            else if (isdigit(route[j])) //if character after dir is a number
            {

                if ( j+1 < route.size() && isdigit(route[j+1]) == true) //if two characters after dir is a number (two consecutive numbers)
                {
                    stepCount = ((route[j] - '0')*10 + route[j+1] - '0');//ASCII conversion from characters to one double-digit number
                    attemptedSteps += stepCount;
                    
                }
                else //if only one number after dir
                {
                    stepCount = (route[j]-'0');
                    attemptedSteps += stepCount;
                }
                steps = navigateSegment( tempr, tempc, route[i], stepCount); //actual steps for one segment
                actualSteps += steps;
                updateStartingPosition(tempr, tempc, route[i], steps);
                if (steps != stepCount) //compares if actual steps in segment does not equal
                {
                    nsteps = actualSteps;
                    return 3;
                }

            }
            //if route sub i is NOT a digit, but also a direction
            //compare actualstepsand attemptedSteps
            //if actual steps is less than attempted steps
            //hit a wall, return 3
        }
    }
    nsteps = actualSteps;
    if (actualSteps < attemptedSteps)
    {
        return 3;
    }
    
    if (tempr == er &&  tempc == ec)
        return 0;
    else
        return 1;
}