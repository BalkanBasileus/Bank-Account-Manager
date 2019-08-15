#include <iostream>
#include <string>
#include <fstream>
#include "bankBranch.h"
using namespace std;


int main(int argc, char const *argv[])
{
	bankBranch accounts; //Declare class 'accounts'

	//File input variables
	ifstream inFile;
	ofstream outFile;
	string fileName;
	
	//Input variables to pass into class functions
	string f, l;
	long acctNo;
	short pin;
	double amt;

	//Variable used establish # of lines in file
	int numOfAccounts=0;

	//Input variables for control stuctures in main().
	long searchAcctNo;
	short searchPin;
	int i;

	//Menu-driven input varialbes //Most of code in main wrapped in do-while.
	char willTheyContinue, withdrawl_Or_Deposit;
	bool doWhile = false;	//So long as 'false', do-while will loop.

	double withdrawlAmount, depositAmount;


	do{//open file
    cout << "Enter the input file: "; 
    cin >> fileName;
    inFile.open(fileName.c_str());
  } while(!inFile.is_open());

  	//While loop reads file line by line and assigns values accordingly,
  	//calls addAccount function from Class, and assigns values in re-arranged
  	//order.
  	while(inFile >> f >> l >> acctNo >> pin >> amt)
  	{
  		accounts.addAccount(f,l,amt,pin,acctNo);

  		numOfAccounts+=1;
  	}
  	inFile.close(); //Close file.

  	do{//Menu driven do-while loop wrapped around code.

	  	cout << "Enter Account Number: " << endl;
	  	cin >> searchAcctNo;

	  	i = accounts.searchAccount(searchAcctNo);

	  	if(i == -1) //If account not found, re-prompt.
	  	{
	  		cin.clear();
			cin.ignore(100,'\n');

			cout << "Account not found! :(" << endl;
			cout << "Do you wish to continue? [Y/N]" << endl;
			cin >> willTheyContinue;
			
			willTheyContinue=toupper(willTheyContinue);
			//Error check.
					while(willTheyContinue != 'Y' && willTheyContinue != 'N')
					{
						cin.clear();
						cin.ignore(100, '\n');
								
						cout << "Do you wish to continue? [Y/N]" << endl;
						cin >> willTheyContinue;

						willTheyContinue=toupper(willTheyContinue);

					}
				if(willTheyContinue == 'Y')
				{
					doWhile = false;	//Keeps looping do-while
				}
				else if(willTheyContinue == 'N')
				{
					return 0;	//terminates program.
				}
	  	}
		
		/*
		  If pin matches account, outputUserInfo func called. Then prompts for either
		  withdrawl or deposit, quantity, and whether to continue or terminate.
		  Error check while loops included.
		  Wish to continue prompts included. If 'yes', reloops do-while. 'No' terminates.
		*/
		
		else
		{
			cout << "Enter account Pin: " << endl;
			cin >> searchPin;

			if(accounts.verifyAccount(i,searchPin))
			{
				//Output account profile.
				accounts.outputUserInfo(i);

				cout << "Would you like to make a withdrawl or deposit? [W/D]: " << endl;
				cin >> withdrawl_Or_Deposit;

				withdrawl_Or_Deposit = toupper(withdrawl_Or_Deposit);

					//Error check.
					while(withdrawl_Or_Deposit != 'W' && withdrawl_Or_Deposit != 'D')
					{
						cin.clear();
						cin.ignore(100,'\n');

						cout << "Would you like to make a withdrawl or deposit? [W/D]: " << endl;
						cin >> withdrawl_Or_Deposit;

						withdrawl_Or_Deposit = toupper(withdrawl_Or_Deposit);
					}

						if(withdrawl_Or_Deposit == 'W')
						{
							cout << "Enter amount you want to withdrawl: " << endl;
							cin >> withdrawlAmount;

							if(withdrawlAmount > 0)
							{
								withdrawlAmount = withdrawlAmount * -1;
							}

							//Update account balance.
							// accounts.updateAccount(i,withdrawlAmount);


							if(accounts.updateAccount(i,withdrawlAmount) == false)
							{
								cout << "Cannot process transaction...O.o" << endl;
							}

						}//If they deposit
						else if(withdrawl_Or_Deposit == 'D')
						{
							cout << "Enter amount you want to deposit: " << endl;
							cin >> depositAmount;


							accounts.updateAccount(i,depositAmount);
						}


						cout << "Do you wish to continue? [Y/N]: " << endl;
						cin >> willTheyContinue;

						willTheyContinue = toupper(willTheyContinue);

						while(willTheyContinue != 'Y' && willTheyContinue != 'N')
								{
									cin.clear();
									cin.ignore(100,'\n');

									cout << "Do you wish to continue? [Y/N]:" << endl;
									cin >> willTheyContinue;

									willTheyContinue=toupper(willTheyContinue);

								}

							if(willTheyContinue == 'Y')
							{
								doWhile = false;  //Keeps looping do-while
							}
							else if(willTheyContinue == 'N')
							{
								return 0;  //terminates program.
							}

			/*
			If pin is incorrect or if pin input attempts exceeds 3, prompts whether they wish to continue.
			If 'yes', reloops do-while. 'No' terminates.
			*/

			}
			else if(accounts.verifyAccount(i,searchPin) == false)
			{	

				cout << "Either Invalid pin, or Account Frozen! GoodBye! " << endl;

				cin.clear();
				cin.ignore(100,'\n');

				cout << "Do you wish to continue? [Y/N]:" << endl;
				cin >> willTheyContinue;

				willTheyContinue=toupper(willTheyContinue);

					//Error check.
					while(willTheyContinue != 'Y' && willTheyContinue != 'N')
					{
						cin.clear();
						cin.ignore(100,'\n');

						cout << "Do you wish to continue? [Y/N]:" << endl;
						cin >> willTheyContinue;

						willTheyContinue=toupper(willTheyContinue);

					}
				if(willTheyContinue == 'Y')
				{
					doWhile = false;  //Keeps looping do-while
				}
				else if(willTheyContinue == 'N')
				{
					return 0;  //terminates program.
				}
			}

		}


  	}while(doWhile == false); //So long as do-while loop is false, continues looping.
  							  //"Do you wish to continue [Y/N]" --> " Y " --> "Enter account number: "
	return 0;
}
