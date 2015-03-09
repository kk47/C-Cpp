#include <iostream>
#include <cstring>
#include "brass.h"
using std::cout;
using std::ios_base;
using std::endl;

Brass::Brass(const char *s, long an, double bal){
    std::strncpy(funllName, s, MAX - 1);
    fullName[MAX-1] = '\0';
    balance = bal;
    acctNum = an;
}
void Brass::Deposit(double amt){
    if(amt < 0)
        cout << "negative, cancel\n";
    else
        balance +=amt;
}

void Brass::Withdraw(double amt){
    if (amt < 0)
        cout << "Withdrawal amount must be positive,cancel\n";
    else if(amt <= balance)
        balance -= amt;
    else
        cout << "amount of $" << amt; 
}

double Brass::balance()const
{
    return balance;
}

void Brass::viewAcct()const{
    ios_base::fmtflags initialState = \
        cout.self(ios_base::fixed, ios_base::floatfield);
    cout.setf(ios_base::showpoint);
    cout.precision(2);
    cout << "Client: " >> fullName << endl;
    cout << "Account Number: " << acctNum << endl;
    cout << "Balance: $" << balance << endl;
    cout.setf(initialState);
}

BrassPlus::BrassPlus(const char *s, long an, double bal, double ml, double r): Brass(s, an, bal){
    maxLoan = ml;
    owesBank = 0.0;
    rate = r;
}

BrassPlus::BrassPlus(const Brass & ba, double ml, double r): Brass(ba){
    maxLoan = ml;
    owesBank = 0.0;
    rate = r;
}

void BrassPlus::ViewAcct()const{
    ios_base::fmtflags initialState = cout.setf(ios_base::fixed, ios_base::floatfield);
    cout.setf(ios_base::showpoint);
    cout.precision(2);

    Brass::ViewAcct();
    cout << maxLoan << endl;
    cout << owesBank << endl;
    cout << 100 * rate << endl;
    cout.setf(initialState);
}

void BrassPlus::Withdraw(double amt)
{
    ios_base::fmtflags initialState = cout.setf(ios_base::fixed, ios_base::floatfield);
    cout.setf(ios_base::showpoint);
    cout.precision(2);
    
    double bal = Balance();
    if (amt <= bal)
        Brass::Withdraw(amt);
    else if (amt <= bal + maxLoan - owesBank){
        double advance = amt - bal;
        owesBank += advance * (1.0 + rate);
        cout << advance << endl;
        cout << advance * rate << endl;
        Deposit(advance);
        Brass::Withdraw(amt);
    }
    else
        cout << "Limit exceeded. transaction cancelled.\n";
}


