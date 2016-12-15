
// Code for Project 1
// Report survey results

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;   // pp. 38-39 in Savitch 6/e explains this line


int main()
{
    cout << setprecision (2) << fixed; //sets two decimal places to the right of the decimal point
    double unitsSent;
    string title;
    double basePrice;
    string premiumItem;
    double royaltyRate = 0.0;
    double totalPrice = 0.0;
    
    
    cout << "Units sent: ";
    cin >> unitsSent; //looks for the next blank space
    cin.ignore(10000,'\n'); //use when about to use a string
    cout << "Title: ";
    getline(cin, title); //string's cin, looks for '/n'
    cout << "Base price: ";
    cin >> basePrice;
    cin.ignore(10000,'\n');
    cout << "Premium item? (y/n): ";
    cin >> premiumItem;
    cin.ignore(10000,'\n');
    cout << "---"<< endl;
    
    if (unitsSent < 0) {
        cout << "The number of units sent must be nonnegative." << endl;
        return 0;
    }
    if (title == ""){
        cout << "You must enter a title." << endl;
        return 0;
    }
    
    if (basePrice < 0) {
        cout << "The base price must be nonnegative." << endl;
        return 0;
    }
    if (premiumItem != "y" && premiumItem != "n"){ //when i put in yes or no, still computes
        cout << "You must enter y or n." << endl;
        return 0; //ends program without computing false results
    }
    
    if (unitsSent > 1200) {
        int x = unitsSent - 1200; //x is how much above 1200
        royaltyRate = basePrice * .14;
        totalPrice = x * royaltyRate; //computes total price of units above 1200
    }
    int x;
    if (unitsSent > 400){ //computes total price of units between 1200 and 400
        if (unitsSent > 1200) {
            x = 800;
        }
        else {
            x = unitsSent - 400;
        }
        if (premiumItem == "y") {
            royaltyRate = basePrice * .16;
            totalPrice = totalPrice + x * royaltyRate;
        }
        else if (premiumItem == "n") {
            royaltyRate = basePrice * .13;
            totalPrice = totalPrice + x * royaltyRate;
        }
    }
    if (unitsSent > 0) { //computes total price of units between 400 and 0
        if (unitsSent > 400) {
            x = 400;
        }
        else {
            x = unitsSent;
        }
        royaltyRate = basePrice * .09;
        totalPrice = totalPrice + x * royaltyRate;
    }
    
    cout << title << " earned $" << totalPrice << " in royalties." << endl;
}