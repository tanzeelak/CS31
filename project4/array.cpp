//
//  array.cpp
//  project4
//
//  Created by Tanzeela Khan on 11/2/15.
//  Copyright © 2015 Tanzeela Khan. All rights reserved.
//

#include <iostream>
#include <cctype>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>

using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int rotateRight(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int split(string a[], int n, string splitter);

int main()
{
    string h[7] = { "bernie", "hillary", "donald", "jeb", "", "carly", "ben" };
    assert(lookup(h, 7, "carly") == 5);
    assert(lookup(h, 7, "donald") == 2);
    assert(lookup(h, 2, "donald") == -1);
    assert(positionOfMax(h, 7) == 3);
    
    string g[4] = { "bernie", "hillary", "jeb", "carly" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "bernie?" && g[3] == "carly?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "jeb?" && g[3] == "hillary?");
    
    string e[4] = { "donald", "jeb", "", "carly" };
    assert(subsequence(h, 7, e, 4) == 2);
    
    string d[5] = { "hillary", "hillary", "hillary", "ben", "ben" };
    assert(countRuns(d, 5) == 2);
    
    string f[3] = { "jeb", "donald", "marco" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "marco" && f[2] == "jeb");
    
    assert(split(h, 7, "carly") == 3);
    
    cout << "All tests succeeded" << endl;


}

int appendToAll(string a[], int n, string value)
{
    if (n<0)
        return n;
    for (int i = 0; i < n; i++) //running through the array
    {
        a[i] = a[i] + value; //adding the value to each element of the array
    }
    return n;
}


int lookup(const string a[], int n, string target)
{
    if (n<0)
        return n;
    for (int i = 0; i < n; i++) //run through each element in array
    {
        if (a[i] == target) //if an element at position n = string target, good
            return i;
    }
    return -1; //never found it
         
}

int positionOfMax(const string a[], int n)
{
    int movingValue = 0;
    if(n <= 0) //if empty string
        return -1;
    if (n == 1) //if only one value in string
        return 0;
    else //if more than one value in string
    {
        for(int j =1; j < n; j++) //run through rest of array after first element
        {
            if (a[movingValue] > a[j]) //if the first element is greater than the current element
                continue;
            //else if (a[j+1] == "") //if reaching out of array/empty string. do NOT want to go forward with movingValue
              //  break;
            else //if the first element is not greater than the current element
                movingValue = j; //set moving value to new max
        }
    }
    return movingValue;
}

int rotateLeft(string a[], int n, int pos)
{
    if (n < 0 || pos < 0 || pos >= n)
        return -1;
    string origElement = a[pos]; //do not want to erase element position
    int origPos = pos; //do not want to erase orignal position
    
    int j; //protect value of i
    for (j = pos+1; j < n; j++) //next moving point will run through rest of origiginal array
    {
        a[pos] = a[j]; //copy one value over to original array
        pos++;
    }
    //leaves for loop when reaches n bound
    a[n-1] = origElement; //copy element of inputted position to last position in array
    //(n-1) bc out of bounds
    return origPos;
}

int rotateRight(string a[], int n, int pos)
{
    if (n < 0 || pos < 0 || pos >= n)
        return -1;
    string origElement = a[pos]; //do not want to erase element position
    int origPos = pos; //do not want to erase orignal position
    
    int j; //protect value of i
    for (j = pos-1; j >= 0; j--) //next moving point will run through rest of origiginal array
    {
        a[pos] = a[j]; //copy one value over to original array
        pos--;
    }
    //leaves for loop when reaches n bound
    a[0] = origElement; //copy element of inputted position to last position in array
    //(n-1) bc out of bounds
    return origPos;
}

int countRuns(const string a[], int n)
{
    if (n < 0)
        return -1;
    int counter = 0;
    for (int i = 0; i < n; i++) //run through the whole array
    {
        //if (a[i+1] == "") //if reaching out of array/empty string. do NOT want to go forward with counter
            //break;
        counter++;
        for (int j = i +1; j < n; j++) //run through next part of string till not equal prior element
        {
            if (a[j] == a[i]) //check if element at j = element at i
            {
                i++;
            }
            else // element at j does not equal i
                break;
        }
    }
    return counter;
}

int flip(string a[], int n)
{
    if (n < 0)
        return -1;
    for (int i = 0; i < n/2; i++) //n/2 bc of integer divsion will lead to the middle
    {
        string storing = a[i]; //saves first value
        a[i] = a[-i + n - 1]; //moves last value to first value
        a[-i + n - 1] = storing; // move first value to last value
    }
    return n;
}


int differ(const string a1[], int n1, const string a2[], int n2)
{
    //a1[n1];
    //a2[n2];
    if (n1 <= 0 || n2 <= 0)
        return -1;
    int k;
    for (k =0; (a1[k] == a2[k]) && (k < n1) && (k < n2); k++) //will run through both arrays until one element does not equal another element at the same position k
        {}
    //when leaving loop, k = unequal element position
    if (k == (n1) || k == (n2)) // if either element after running through loop is empty, that means one of them ended
    {
        if (n1 < n2) //check if the first array is bigger than the second darray
            return n1; //return the smaller array
        return n2;
    }
    else //left the for loop when element was not equal, not because string ended
        return k; //different position
}

int subsequence(const string a1[], int n1, const string a2[], int n2) //fix
{
    //a1[n1]; //set boundaries
    //a2[n2]; //always start from beginning value of a2
    if (n1 <0 || n2 < 0 || n2 > n1)
        return -1;
    for (int j = 0; j < n1; j++)
    {
        if (a1[j] != a2[0])
            continue;
        else //(a1[k]  == a2[0])
        {
            int m;
            for (m = 0; (m < n1 && m < n2); m++)
            {
                if (a1[m+j] != a2[m])
                    break;
            }
            if (m == n2)
                return j;
        }
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    //a1[n1-1]; //defining boundaries in arrays
    //a2[n2-1];
    if (n1 <= 0 || n2 <= 0)
        return -1;
    for(int k = 0; k < n1; k++)//run through a1
    {
        for (int j = 0; j < n2; j++) //run through a2
        {
            if (a1[k] == a2[j]) //check if current a1 elmeent is NOT equal to curent a2 elment
                return k;
            //else // one element is equal
                //return k; //return current element of a1
        }
    }
    return -1; //no element is equal
}

int split(string a[], int n, string splitter)
{
    //first rerrange array
    if (n <= 0)
        return -1;
    int i;
    int counterMoved = 0; //how many elements have been moved to the beginning
    for (i = 0; i < n; i++) //run through array
    {
        if (a[i] < splitter)
        {
            rotateRight(a, n, i);
            counterMoved++;
        }
        else if (a[i] == splitter) //problem is in this loop
        {
            rotateRight(a, (counterMoved), i); //rotateRight(a, (counterMoved+1), i);
            continue;
            
        }
    }
    int j;
    for (j= 0; j < n; j++) //run through rearranged array
    {
        if ((a[j] < splitter))
            continue;
        else
            break;
    }
    return j;
}