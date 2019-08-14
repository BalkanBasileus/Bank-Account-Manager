#include <iostream>
#include <iomanip>
#include "bankBranch.h"
using namespace std;

bankBranch::bankBranch()
{
	//default constructor. Sets empty strings for each element of the string arrays and sets zeros for all numeric types
	
	amountOfAccounts=0;

	for(int i=0; i < 20;i++)
	{
		first[i] = "";
		last[i] = "";
		amount[i] = 0;
		acctNo[i] = 0;
		pin[i] = 0;
		attempts[i] = 0;
	}
	
}
void bankBranch::addAccount(std::string f, std::string l, double amt, short _pin, long _acctNo )
{
	//Set all values read in from file to private variables in Class.
	//Increments amountOfAccounts.

	first[amountOfAccounts] = f;
	last[amountOfAccounts] = l;
	amount[amountOfAccounts] = amt;
	acctNo[amountOfAccounts] = _acctNo;
	pin[amountOfAccounts] = _pin;

	amountOfAccounts++;
}

int bankBranch::searchAccount(long _acctNo) const
{
	//Searches parallel arrays for the account number that is input and passed from main().
	//If account not found, 'position' value left to it's initial '-1'. Hence 'not found'.
	//Otherwise returns line of account with matching account number.
	int position=-1;

	for(int i=0;i<amountOfAccounts;i++)
	{
		if(_acctNo == acctNo[i])
		{
			position = i;
		}
	}
	return position;
}

bool bankBranch::verifyAccount(int searchedAcctPosition, short _pin)
{
	/*
	 Checks to see if pin entered in main() matches with pin in desired account.
	 If verification attempts exceed 3, keeps 'correct' variable as false, and
	 returns false. Otherwise if pin matches, return correct as true.
	 */
	
	bool correct = false;

	if(attempts[searchedAcctPosition] < 3)
	{
		if(pin[searchedAcctPosition] == _pin)
		{
			correct = true;
		}
		else
		{
			attempts[searchedAcctPosition]+=1;
		}
	}

	return correct;	
}

bool bankBranch::updateAccount(int i, double amt)
{
	/*
	this function updates the amount for a bank account at the position given 
	by the first argument (i.e. it will update amount[index] with amt), if the 
	account at the index given by the first argument is negative, the function 
	returns false and does not do anything else, otherwise it updates the 
	account and returns true.
	*/
	bool correct = false;

	if(amount[i] >= 0 || amt > 0)
	{	
		amount[i] += amt;

		correct = true;
	}

	return correct;
}

void bankBranch::outputUserInfo(int index) const
{
	cout << fixed << showpoint << setprecision(2) << endl;
	cout << right << endl;

	//Concatenated so as to stay 'right' aligned
	cout <<  "Name:  " << setw(20) << first[index] + ", " + last[index] << endl;

	cout << "AcctNo:" << setw(20) << acctNo[index] << endl;
	cout << "Balance" << setw(20) << setfill('.') << amount[index]<< endl;
  }
