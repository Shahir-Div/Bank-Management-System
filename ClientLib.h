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
//#include"Users.h"

using namespace std;

const string FileName = "Client.txt";

namespace ClientLib {

	string ChackClientAccount();

	struct stClientData {
		string ClientFullName = "";
		string Phone = "";
		string PinCode = "";
		string Email = "";
		string AccountNumber = "";
		double AccountBalance = 0;
		bool Mark = false;
	};

	string ReadAccountNumber() {

		stClientData Client;
		cout << "\t\t Enter Account Number:";
		getline(cin >> ws, Client.AccountNumber);

		return Client.AccountNumber;
	}

	stClientData ReadClientData() {

		stClientData Client;

		Client.AccountNumber = ChackClientAccount();
		cout << "\t\t Please Enter Full Name:";
		getline(cin, Client.ClientFullName);
		cout << "\t\t Please Enter PinCode:";
		getline(cin, Client.PinCode);
		cout << "\t\t Enter Phone Number:";
		getline(cin, Client.Phone);
		cout << "\t\t Enter Email:";
		getline(cin, Client.Email);
		cout << "\t\t Enter Account Balance:";
		cin >> Client.AccountBalance;

		return Client;
	}

	vector<string> SplitString(string S, string Delim = "/--/") {

		short Pos = 0;
		vector<string> Words;
		string sWord = "";

		while ((Pos = S.find(Delim)) != std::string::npos) {

			sWord = S.substr(0, Pos);

			if (sWord != "") {
				Words.push_back(sWord);
			}

			S = S.erase(0, Pos + Delim.length());

		}

		if (S != "") {
			Words.push_back(S);
		}

		return Words;

	}

	string ClientDataToLine(stClientData Data, string Delim = "/--/") {

		string Line = "";

		Line = Data.AccountNumber + Delim;
		Line += Data.ClientFullName + Delim;
		Line += Data.PinCode + Delim;
		Line += Data.Phone + Delim;
		Line += Data.Email + Delim;
		Line += to_string(Data.AccountBalance) + Delim;

		return Line;

	}

	stClientData LineToRecord(string Line, string Delim = "/--/") {

		stClientData Client;
		vector<string> Words = SplitString(Line, Delim);

		Client.AccountNumber = Words[0];
		Client.ClientFullName = Words[1];
		Client.PinCode = Words[2];
		Client.Phone = Words[3];
		Client.Email = Words[4];
		Client.AccountBalance = stod(Words[5]);

		return Client;

	}
	//Add
	void AddDataToFile(string Line, string Delim = "/--/") {

		fstream ClientFile;

		ClientFile.open(FileName, ios::out | ios::app);

		if (ClientFile.is_open()) {

			ClientFile << Line << endl;

			ClientFile.close();
		}


	}

	void AddClientToFile() {

		stClientData Client;
		string Line = "";

		Client = ReadClientData();
		Line = ClientDataToLine(Client);
		AddDataToFile(Line);
	}

	void AddClientsToFile() {

		char Answer = 'y';

		do {
			AddClientToFile();
			//system("color 8A");
			cout << "\t\t Adding Client Succeed, Do You Want To Add More Clients ?";
			cin >> Answer;
			//system("cls");

		} while (Answer == 'y' || Answer == 'Y');

	}

	vector<stClientData> LoadClientDataFromFile(string FileName) {

		vector<stClientData> vClients;
		string Line = "";
		fstream ClientFile;
		stClientData Client;

		ClientFile.open(FileName, ios::in);

		if (ClientFile.is_open()) {
			while (getline(ClientFile, Line)) {

				Client = LineToRecord(Line);
				vClients.push_back(Client);

			}

			ClientFile.close();
		}

		return vClients;

	}

	vector<stClientData> vClients = LoadClientDataFromFile(FileName);

	bool FindClientByAccountNumber(stClientData& Client, string AccountNumber) {

		vector<stClientData> vClients;
		vClients = LoadClientDataFromFile(FileName);

		for (stClientData C : vClients) {

			if (C.AccountNumber == AccountNumber) {
				Client = C;
				return true;

			}
		}
		return false;
	}

	string ChackClientAccount() {

		stClientData Client;
		Client.AccountNumber = ReadAccountNumber();
		string AccountNumber = Client.AccountNumber;

		while (FindClientByAccountNumber(Client, AccountNumber)) {
			system("cls");

			cout << "\t\t Client Already Exists, Please Enter Another Account Number." << endl;
			Client.AccountNumber = ReadAccountNumber();
			AccountNumber = Client.AccountNumber;

		}

		return AccountNumber;

	}
	//Find
	void PrintClientCard(stClientData Client) {

		cout << "\t\t+++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "\t\t\t    Client Card " << endl;
		cout << "\t\t+++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "\t\t Account Number: " << Client.AccountNumber << endl;
		cout << "\t\t Name: " << Client.ClientFullName << endl;
		cout << "\t\t PinCode: " << Client.PinCode << endl;
		cout << "\t\t Phone: " << Client.Phone << endl;
		cout << "\t\t Email: " << Client.Email << endl;
		cout << "\t\t Account Balance: " << Client.AccountBalance << endl;
		cout << "\t\t+++++++++++++++++++++++++++++++++++++++" << endl;

	}

	void ShowClientCardScreen(stClientData Client) {

		system("cls");
		PrintClientCard(Client);
		system("pause>0");
	}

	bool SearchClient() {

		stClientData Client;
		string AccountNumber = ReadAccountNumber();

		if (FindClientByAccountNumber(Client, AccountNumber)) {
			ShowClientCardScreen(Client);
			return true;
		}
		return false;
	}

	void ClientNotFound() {
		char Answer = 'y';
		cout << "\t\t Client Is Not Found,Do You Want To Add Client ? y/n ?";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			AddClientsToFile();
		}
	}

	void FindClient() {

		if (!SearchClient()) {
			ClientNotFound();
		}
	
	}
	//show
	void PrintClientRecord(stClientData Client) {



		cout << "\t|" << setw(15) << left << Client.AccountNumber;
		cout << "|" << setw(25) << left << Client.ClientFullName;
		cout << "|" << setw(15) << left << Client.Phone;
		cout << "|" << setw(30) << left << Client.Email;
		cout << "|" << setw(15) << left << Client.AccountBalance << endl;

	}

	void ShowClientsList() {

		int i = 1;
		vector<stClientData> vClients = LoadClientDataFromFile(FileName);
		stClientData Client;


		cout << "\t==============================================================================================================" << endl;
		cout << setw(55) << right << "Show All (" << vClients.size() << ") Clients Data" << endl;
		cout << "\t==============================================================================================================" << endl;

		if (vClients.size() == 0) {
			cout << setw(60) << right << "\tNo Clients Found..." << endl;
		}
		else {

			cout << "\t|" << setw(15) << left << "Account Number ";
			cout << "|" << setw(25) << left << "Full Name ";
			cout << "|" << setw(15) << left << "Phone ";
			cout << "|" << setw(30) << left << "Email ";
			cout << "|" << setw(15) << left << "Account Balance " << endl;
		}
		cout << "\t==============================================================================================================" << endl;






		for (stClientData& C : vClients) {
			Client = C;
			PrintClientRecord(Client);
		}

		cout << "\t==============================================================================================================" << endl;

		cout << "\t\t Press Any Key To Back..." << endl;
		system("pause>0");

	}

	//update

	vector<stClientData> SaveClientDataToFile(string FileName,vector<stClientData> &vClients) {

		fstream ClientFile;

		string Line = "";

		ClientFile.open(FileName, ios::out);
		if (ClientFile.is_open()) {


			for (stClientData C : vClients) {

				if (C.Mark == false) {

					Line = ClientDataToLine(C);
					ClientFile << Line << endl;

				}
			}

			ClientFile.close();

		}

		return vClients;

	}

	stClientData UpdateClientByAccountNumber(string AccountNumber) {

		stClientData Client;

		cout << "\t\t Please Enter The New Info:" << endl;
		Client.AccountNumber = AccountNumber;
		cout << "\t\t Enter Client Name:";getline(cin >> ws, Client.ClientFullName);
		cout << "\t\t Enter PinCode:";getline(cin, Client.PinCode);
		cout << "\t\t Enter Phone:";getline(cin, Client.Phone);
		cout << "\t\t Enter Email:";getline(cin, Client.Email);
		cout << "\t\t Enter Account Balance:";cin >> Client.AccountBalance;

		return Client;
	}

	void UpdateClientData() {
		stClientData Client;
		string AccountNumber = ReadAccountNumber();
		char Answer = 'n';
		vector<stClientData> vClients = LoadClientDataFromFile(FileName);

		if (!FindClientByAccountNumber(Client, AccountNumber)) {

			ClientNotFound();
			//return false;
		}
		else {
			PrintClientCard(Client);
			cout << "\n Are You Sure Do You Want To Update This Client Data ? y/n? ";
			cin >> Answer;
			if (Answer == 'Y' || Answer == 'y') {

				for (stClientData& C : vClients) {

					if (C.AccountNumber == AccountNumber) {

						C = UpdateClientByAccountNumber(AccountNumber);
						break;
					}
				}
				SaveClientDataToFile(FileName, vClients);

				cout << "\n Client Update Succsfuly.." << endl;
				//return true;
			}
		}
	}
	//Delete

	bool MarkForDeleting(vector<stClientData> &vClients) {

	
		stClientData Client;
		string AccountNumber = ReadAccountNumber();

		if (FindClientByAccountNumber(Client, AccountNumber)) {
			
			for (stClientData &C : vClients) {
				if (C.AccountNumber == AccountNumber) {
					C.Mark = true;
					Client = C;
					return true;
				}
			}
		}

		return false;
	}
	
	void DeleteClientByAcountNumber(vector<stClientData> &vClients) {

		char Answer = 'n';

		stClientData Client;




		if (MarkForDeleting(vClients)) {

			
			for (stClientData& C : vClients) {
				if (C.Mark == true) {
					PrintClientCard(C);

				}
			}

			cout << "\t\t Ary You Sure Do You Want To Delete This Client? y/n?" << endl;
			cin >> Answer;

			if (Answer == 'Y' || Answer == 'y') {

				SaveClientDataToFile(FileName, vClients);
				cout << "\t\t Client Deleting Succeed..." << endl;
			}

		}
		else {
			ClientNotFound();
		}


	}

	


}