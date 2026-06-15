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
#include "Users.h"
using namespace std;

namespace LoginLib {


	string ReadUserName() {
	
		string UserName = "";
		getline(cin >> ws, UserName);
		return UserName;
	}

	string ReadPassWord() {
		string PassWord;
		getline(cin >> ws, PassWord);
		return PassWord;
	}

	bool FindUserByUserNameAndPassword(string UserName,string Password,UserLib::stUserInfo& User){

		vector<UserLib::stUserInfo> vUsers =UserLib::LoadUsersFromFile(UsersFile);

		for (UserLib::stUserInfo U : vUsers)
		{
			if (U.UserName == UserName &&
				U.Password == Password)
			{
				User = U;
				return true;
			}
		}

		return false;
	}

	bool Login(){


		cout << "User Name: ";
		string UserName = ReadUserName();

		cout << "Password: ";
		string PassWord = ReadPassWord();

		UserLib::stUserInfo User;

		if (FindUserByUserNameAndPassword(UserName,PassWord,User)){

			UserLib::CurrentUser() = User;

			return true;
		}

		return false;
	}


}
