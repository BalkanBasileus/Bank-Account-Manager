class bankBranch
{
public:
	bankBranch();
	void addAccount(std::string, std::string, double, short, long );
	int searchAccount(long) const;
	bool verifyAccount(int, short);
	bool updateAccount(int, double);
	void outputUserInfo(int) const;

private:
	int amountOfAccounts;
	std::string first[20];
	std::string last[20];
	double amount[20];
	long acctNo[20];
	short pin[20];
	short attempts[20];
};
