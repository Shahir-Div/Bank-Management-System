#pragma once

#include<iostream>
#include<cstdlib>
#include<vector>
#include<ctime>
#include<cmath>
#include<string>
#include<iomanip>
#include<cctype>
#include<fstream>
#include"ClientLib.h"
#include"ScreensLib.h"

using namespace std;

namespace TransLib {

	const string TransactionFile = "Transaction.txt";

	enum enTransactions {
		Deposit = 1, Withdraw = 2, Transfer = 3
	};

	struct sData
	{
		short Day = 0;
		short Month = 0;
		short Year = 0;
	};

	string DataType(enTransactions Choose) {


		switch (Choose) {
		case enTransactions::Deposit:return "Deposit";break;
		case enTransactions::Transfer:return "Transfer";break;
		case enTransactions::Withdraw:return "Withdraw";break;
		}
	}

	sData GetSystemData()
	{
		sData Data;

		time_t T = time(0);

		tm LocalTime;
		localtime_s(&LocalTime, &T);

		Data.Year = LocalTime.tm_year + 1900;
		Data.Month = LocalTime.tm_mon + 1;
		Data.Day = LocalTime.tm_mday;

		return Data;
	}

	string DataToString(sData Data, string Delim = "/") {

		string Data1 = "";

		Data1 = to_string(Data.Day) + Delim + to_string(Data.Month) + Delim + to_string(Data.Year);

		return Data1;

	}

	string DataToLine(enTransactions Choose,double Amont, string AccountNumber, string Delim = "/--/") {

		sData Data = GetSystemData();


		string Line = "";
		Line = DataType(Choose) + Delim;
		Line += AccountNumber + Delim;
		Line += to_string(Amont) + Delim;
		Line += DataToString(Data) + Delim;

		return Line;
	}

	void SaveDataToFile(enTransactions Choose,double Amont, string AccountNumber ="") {


		string Line = DataToLine(Choose,Amont, AccountNumber);
		fstream Transfer;

		Transfer.open(TransactionFile, ios::out | ios::app);

		if (Transfer.is_open()) {

			Transfer << Line << endl;

		}
		Transfer.close();
	}

	vector<ClientLib::stClientData> GetvClients() {

		return ClientLib::LoadClientDataFromFile(FileName);

	}

	string ReadAccountNumber() {

		string AccountNumber = "";
		AccountNumber = ClientLib::ReadAccountNumber();

		return AccountNumber;

	}

	bool DepositTransaction(vector<ClientLib::stClientData> &vClients, string AccountNumber) {

		double Deposit = 0;
		char Answer = 'n';

		cout << "\t\t Are You Sure Do You Want To Deposit To This Client?";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {

			for (ClientLib::stClientData& C : vClients) {
				if (C.AccountNumber == AccountNumber) {

					cout << "\t\t How Much To Deposit? ";
					cin >> Deposit;
					C.AccountBalance += Deposit;
					ClientLib::SaveClientDataToFile(FileName, vClients);
					cout << "\t\t Deposit Transaction Done!" << endl;
					SaveDataToFile(enTransactions::Deposit,Deposit, AccountNumber);

					return true;



				}
			}
		}

		return false;
	}

	void DepositScreen() {

		vector<ClientLib::stClientData >vClients = GetvClients();
		ClientLib::stClientData Client;
		string AccountNumber = ReadAccountNumber();

		if (ClientLib::FindClientByAccountNumber(Client,AccountNumber)) {

			ClientLib::PrintClientCard(Client);

			DepositTransaction(vClients, AccountNumber);
		}
		else {
			ClientLib::ClientNotFound();
		}

	}

	bool WithdrawTransaction(vector<ClientLib::stClientData>& vClients, string AccountNumber) {

		double Withdraw = 0;
		char Answer = 'n';

		cout << "\t\t Are You Sure Do You Want To Deposit To This Client?";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {

			for (ClientLib::stClientData& C : vClients) {
				if (C.AccountNumber == AccountNumber) {

					cout << "\t\t How Much To Withdraw? ";
					cin >> Withdraw;

					if (Withdraw > C.AccountBalance)
					{
						cout << "Insufficient Balance!\n";
						return false;
					}


					C.AccountBalance -= Withdraw;
					ClientLib::SaveClientDataToFile(FileName, vClients);
					cout << "\t\t Withdraw Transaction Done!" << endl;
					SaveDataToFile(enTransactions::Withdraw,Withdraw, AccountNumber);

					return true;



				}
			}
		}

		return false;
	}

	void WithdrawScreen() {

		vector<ClientLib::stClientData >vClients = GetvClients();
		ClientLib::stClientData Client;
		string AccountNumber = ReadAccountNumber();

		if (ClientLib::FindClientByAccountNumber(Client, AccountNumber)) {

			ClientLib::PrintClientCard(Client);

			WithdrawTransaction(vClients, AccountNumber);


		}
		else {
			ClientLib::ClientNotFound();
		}

	}

	bool TransferTransaction(string Number1, string Number2, vector<ClientLib::stClientData> &vClients,double Transfer) {


		for (ClientLib::stClientData& C1 : vClients) {

			if (C1.AccountNumber == Number1) {

				if (C1.AccountBalance >= Transfer) {

					C1.AccountBalance -= Transfer;
				}else {
					cout << "Insufficient Balance";
					return false;
				}
			}

		}

		for (ClientLib::stClientData& C2 : vClients) {

			if (C2.AccountNumber == Number2) {

				C2.AccountBalance += Transfer;
			}
		}

		ClientLib::SaveClientDataToFile(FileName, vClients);
		return true;

	}

	void TransferScreen() {

		vector<ClientLib::stClientData >vClients = GetvClients();

		cout << "\t\t Please Enter Accounts Numbers To Do Transfer Action." << endl;
		cout << "\t\t From: ";
		string Number1 = ReadAccountNumber();
		cout << "\t\t To: ";
		string Number2 = ReadAccountNumber();
		ClientLib::stClientData Client1, Client2;
		char Answer = 'n';
		double Transfer = 0;
		

		if (ClientLib::FindClientByAccountNumber(Client1, Number1) && ClientLib::FindClientByAccountNumber(Client2, Number2)) {



			cout << "\t\t Are You Sure You Want To Do Transfer Transaction Between "
				<< Client1.ClientFullName << " And " << Client2.ClientFullName << "? y/n ?" << endl;
			cin >> Answer;

			if (Answer == 'y' || Answer == 'Y') {
				cout << "\t\tPlease Enter How Much To Transfer? ";
				cin >> Transfer;
				TransferTransaction(Number1, Number2, vClients, Transfer);
				cout << "\t\t Transfer Transaction Done Successfully." << endl;
				SaveDataToFile(enTransactions::Transfer,Transfer, Number1 + " -> " + Number2);

				system("pause>0");
			}
		}
		else {
			ClientLib::ClientNotFound();
		}



	}
	
	double CountTotalBalances(vector<ClientLib::stClientData> vClients) {

		double Total = 0;

		for (ClientLib::stClientData C : vClients) {

			Total += C.AccountBalance;

		}
		return Total;
	}

	void ClientBalance(ClientLib::stClientData Client) {
		cout << "|" << setw(20) << left << Client.AccountNumber;
		cout << "|" << setw(40) << left << Client.ClientFullName;
		cout << "|" << setw(25) << left << Client.AccountBalance << endl;

	}

	void TotalBalancesScreen() {

		vector<ClientLib::stClientData> vClients = GetvClients();

		cout << setw(40) << right << "Balancec Lis (" << vClients.size() << ") Clients." << endl;
		cout << "_________________________________________________________________________________________________" << endl;
		cout << "|" << setw(20) << left << "Account Number ";
		cout << "|" << setw(40) << left << "Full Name ";
		cout << "|" << setw(20) << left << "Account Balance " << endl;
		cout << "_________________________________________________________________________________________________" << endl;

		for (ClientLib::stClientData C : vClients) {

			ClientBalance(C);

		}

		cout << "_________________________________________________________________________________________________" << endl;

		cout << setw(70) << right << "Total Balances = " << CountTotalBalances(vClients) << endl;



	}


}

