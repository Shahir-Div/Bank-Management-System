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
#include"ScreensLib.h"


using namespace std;

const string UsersFile = "Users.txt";



namespace UserLib {
	

	string ChackUserID();

	struct stUserInfo {
		string UserID = "";
		string UserName = "";
		string Password = "";
		int Permission = 0;
		bool M = false;
	};

	//extern stUserInfo CurrentUser;

	vector<stUserInfo> GetUsers();

	enum enPermissions
	{
		pAll = -1,
		pListClients = 1,
		pAddClient = 2,
		pDeleteClient = 4,
		pUpdateClient = 8,
		pFindClient = 16,
		pTransactions = 32,
		pManageUsers = 64
	};

	string ReadUserID() {
		string ID = "";
		cout << "\t\t Enter User ID: ";
		getline(cin >> ws, ID);

		return ID;
	}

	int ReadPermissions() {

		int Permission = 0;
		char Answer = 'n';
		cout << "\t\t Do You Want To Get Full Access To This User? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {
			return Permission = -1;
		}
		else {

			cout << "\t\t Add New Client?";
			cin >> Answer;
			if (Answer == 'Y' || Answer == 'y')
				Permission += pAddClient;

			cout << "\t\t UpDate Client?";
			cin >> Answer;
			if (Answer == 'Y' || Answer == 'y')
				Permission += pUpdateClient;

			cout << "\t\t Delete Client?";
			cin >> Answer;
			if (Answer == 'Y' || Answer == 'y')
				Permission += pDeleteClient;

			cout << "\t\t Find Client?";
			cin >> Answer;
			if (Answer == 'Y' || Answer == 'y')
				Permission += pFindClient;

			cout << "\t\t List Clients?";
			cin >> Answer;
			if (Answer == 'Y' || Answer == 'y')
				Permission += pListClients;

			cout << "\t\t Transaction?";
			cin >> Answer;
			if (Answer == 'Y' || Answer == 'y')
				Permission += pTransactions;

			cout << "\t\t Mange Users?";
			cin >> Answer;
			if (Answer == 'Y' || Answer == 'y')
				Permission += pManageUsers;

		}

		return Permission;


	}

	bool CheckPermission(stUserInfo User, int Permission)
	{
		if (User.Permission == -1)
			return true;

		return (User.Permission & Permission);
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

	stUserInfo ReadUserInfo() {

		stUserInfo User;
		system("color 4f");


		User.UserID = ChackUserID();
		cout << "\t\tEnter User Name? ";
		getline(cin, User.UserName);
		cout << "\t\tEnter Password? ";
		getline(cin, User.Password);
		cout << "\t\tEnter Permissions? ";
		User.Permission = ReadPermissions();

		return User;
	}

	stUserInfo LineToInfo(string Line) {

		stUserInfo User;
		vector<string> vWords;

		vWords = SplitString(Line, "||");

		if (vWords.size() < 4)
			return User;

		User.UserID = vWords[0];
		User.UserName = vWords[1];
		User.Password = vWords[2];
		User.Permission = stoi(vWords[3]);

		return User;
	}

	string InfoToLine(stUserInfo User, string Delim = "||") {

		string Line = "";

		Line = User.UserID + Delim;
		Line += User.UserName + Delim;
		Line += User.Password + Delim;
		Line += to_string(User.Permission) + Delim;

		return Line;
	}

	vector<stUserInfo> LoadUsersFromFile(string UserFile) {

		vector<stUserInfo> vUsers;
		string Line = "";
		fstream UsersFile;
		stUserInfo User;

		UsersFile.open(UserFile, ios::in);

		if (UsersFile.is_open()) {
			while (getline(UsersFile, Line)) {

				User = LineToInfo(Line);
				vUsers.push_back(User);

			}

			UsersFile.close();
		}

		return vUsers;

	}

	bool FindUserUsingID(stUserInfo& User, string ID) {

		vector<stUserInfo> vUsers = LoadUsersFromFile(UsersFile);

		for (stUserInfo& U : vUsers) {
			if (U.UserID == ID) {
				User = U;
				return true;
			}
		}

		return false;
	}

	void SaveUserInfoInFile(string Line, string UserFile) {

		fstream UsersFile;

		UsersFile.open(UserFile, ios::out | ios::app);
		if (UsersFile.is_open()) {

			UsersFile << Line << endl;

			UsersFile.close();
		}


	}

	void AddUserToFile() {

		string Line = "";
		stUserInfo User = ReadUserInfo();
		Line = InfoToLine(User);
		SaveUserInfoInFile(Line, UsersFile);

	}

	void AddUsersToFile() {

		char Answer = 'n';

		do {

			AddUserToFile();
			cout << "\t\t Users Adding Successfully, Do You Want To Add More Users? ";
			cin >> Answer;


		} while (Answer == 'Y' || Answer == 'y');





	}

	string ChackUserID() {

		stUserInfo User;
		User.UserID = ReadUserID();
		string ID = User.UserID;

		while (FindUserUsingID(User, ID)) {
			system("cls");

			cout << "\t\t User Already Exists, Please Enter Another ID." << endl;
			User.UserID = ReadUserID();
			ID = User.UserID;

		}

		return ID;

	}

	//Find
	void PrintUserCard(stUserInfo User) {

		cout << "\t\t+++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "\t\t\t    User Card " << endl;
		cout << "\t\t+++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "\t\t ID: " << User.UserID << endl;
		cout << "\t\t Name: " << User.UserName << endl;
		cout << "\t\t Password: " << User.Password << endl;
		cout << "\t\t Permissions: " << User.Permission << endl;
		cout << "\t\t+++++++++++++++++++++++++++++++++++++++" << endl;

	}

	bool SearchUsers() {

		stUserInfo User;
		string ID = ReadUserID();

		if (FindUserUsingID(User, ID)) {
			PrintUserCard(User);
			return true;
		}
		return false;
	}

	void UserNotFound() {
		char Answer = 'y';
		cout << "\t\t Client Is Not Found,Do You Want To Add Client ? y/n ?";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			AddUsersToFile();
		}
	}

	void FindUser() {

		if (!SearchUsers()) {
			UserNotFound();
		}

	}
	//show
	void PrintUserRecord(stUserInfo User) {

		cout << "\t|" << setw(15) << left << User.UserID;
		cout << "|" << setw(25) << left << User.UserName;
		cout << "|" << setw(15) << left << User.Password;
		cout << "|" << setw(30) << left << User.Permission << endl;

	}

	void ShowUsersList() {

		int i = 1;
		vector<stUserInfo> vUsers = LoadUsersFromFile(UsersFile);
		stUserInfo User;


		cout << "\t==============================================================================================================" << endl;
		cout << setw(55) << right << "Show All (" << vUsers.size() << ") Users Info" << endl;
		cout << "\t==============================================================================================================" << endl;

		if (vUsers.size() == 0) {
			cout << setw(60) << right << "\tNo Clients Found..." << endl;
		}
		else {

			cout << "\t|" << setw(15) << left << "ID ";
			cout << "|" << setw(25) << left << "User Name ";
			cout << "|" << setw(15) << left << "Password ";
			cout << "|" << setw(30) << left << "Permissions " << endl;
		}
		cout << "\t==============================================================================================================" << endl;






		for (stUserInfo& U : vUsers) {
			User = U;
			PrintUserRecord(User);
		}

		cout << "\t==============================================================================================================" << endl;

		cout << "\t\t Press Any Key To Back..." << endl;
		system("pause>0");

	}

	//update
	vector<stUserInfo> SaveUsersInfoToTheFile(string UsersFile, vector<stUserInfo>& vUsers) {

		//vUsers = LoadUsersFromFile(UsersFile);
		string Line = "";
		//stUserInfo User;

		fstream UserFile;
		UserFile.open(UsersFile, ios::out);
		if (UserFile.is_open()) {

			for (stUserInfo& U : vUsers) {

				if (U.M == false) {

					Line = InfoToLine(U);

					UserFile << Line << endl;
				}

			}

			UserFile.close();
		}

		return vUsers;
	}

	stUserInfo UpdateUserByIDNumber(string ID) {

		stUserInfo User;

		cout << "\t\t Please Enter The New Info:" << endl;
		User.UserID = ID;
		cout << "\t\t Enter User Name:";getline(cin >> ws, User.UserName);
		cout << "\t\t Enter Password:";getline(cin, User.Password);
		cout << "\t\t Enter Premissions:";
		User.Permission = ReadPermissions();


		return User;
	}

	void UpdateUsersData() {
		stUserInfo User;
		string ID = ReadUserID();
		char Answer = 'n';
		vector<stUserInfo> vUsers = LoadUsersFromFile(UsersFile);

		if (!FindUserUsingID(User, ID)) {

			UserNotFound();
		}
		else {
			PrintUserCard(User);
			cout << "\n Are You Sure Do You Want To Update This User Data ? y/n? ";
			cin >> Answer;
			if (Answer == 'Y' || Answer == 'y') {

				for (stUserInfo& U : vUsers) {

					if (U.UserID == ID) {

						U = UpdateUserByIDNumber(ID);
						break;
					}
				}
				SaveUsersInfoToTheFile(UsersFile, vUsers);

				cout << "\n Client Update Successfully.." << endl;
				//return true;
			}
		}
	}

	//Delete
	bool MarkForDeleting(vector<stUserInfo>& vUsers) {


		stUserInfo User;
		string ID = ReadUserID();

		if (FindUserUsingID(User, ID)) {

			for (stUserInfo& U : vUsers) {
				if (U.UserID == ID) {
					U.M = true;
					User = U;
					return true;
				}
			}
		}

		return false;
	}

	void DeleteUserByIDNumber() {

		vector<stUserInfo> vUsers = GetUsers();
		char Answer = 'n';
		stUserInfo User;

		if (MarkForDeleting(vUsers)) {


			for (stUserInfo& U : vUsers) {
				if (U.M == true) {
					PrintUserCard(U);

				}
			}

			cout << "\t\t Ary You Sure Do You Want To Delete This User? y/n?" << endl;
			cin >> Answer;

			if (Answer == 'Y' || Answer == 'y') {

				SaveUsersInfoToTheFile(UsersFile, vUsers);
				cout << "\t\t User Deleting Succeed..." << endl;
			}

		}
		else {
			UserNotFound();
		}


	}

	vector<stUserInfo> GetUsers() {
		return LoadUsersFromFile(UsersFile);
	}

	//chack

	stUserInfo& CurrentUser()
	{
		static stUserInfo User;
		return User;
	}

	bool CheckPermission(int Permission)
	{
		if (CurrentUser().Permission == pAll)
			return true;

		return (CurrentUser().Permission & Permission);
	}


}
