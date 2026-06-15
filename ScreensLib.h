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
#include"Transfer.h"
#include"Users.h"
#include"Login.h"

using namespace std;

namespace ScreenLib {

	void BackToMainScreen();
	void ClientsScreen();
	void TransactionsScreen();
	void UsersScreen();
	void LogInScreen();

	void BackScreensFun(string M) {
		cout << "Press Any Key To Back " << M << " Screen...";
		system("pause>0");
	}

	// enums
	enum enMienMenuChoose {
		Clients = 1, Transactions = 2, Users = 3, Exti = 4
	};

	enum enClientMenuChoose {
		Add = 1, Delete = 2, UpDate = 3, Find = 4, List = 5, Back = 6
	};

	enum enTransactionsChoose {
		Deposit = 1, Withdraw = 2, Transfer = 3, Total = 4, Main = 5
	};

	enum enUsersChoose {
		U_List = 1, U_Add = 2, U_Delete = 3, U_UpDate = 4, U_Find = 5, Bask = 6
	};
	//Read Chooses Functions...
	enMienMenuChoose ReadMienMenuChoose() {
		short Choose = 0;
		cout << "\n Please Enter Your Choose? ";
		cin >> Choose;

		return enMienMenuChoose(Choose);
	}

	enClientMenuChoose ReadClientMenuChoose() {
		short Choose = 0;
		cout << "\n Please Enter Your Choose? ";
		cin >> Choose;
		return enClientMenuChoose(Choose);
	}

	enTransactionsChoose ReadTransactionChoose() {
		short Choose = 0;
		cout << "\n Please Enter Your Choose? ";
		cin >> Choose;
		return enTransactionsChoose(Choose);
	}

	enUsersChoose ReadUsersChoose() {
		short Choose = 0;
		cout << "\t\t Please Enter Your Choose? ";
		cin >> Choose;
		return enUsersChoose(Choose);
	}
	//
	bool AccessDenied(int Permission)
	{
		system("cls");
		if (!UserLib::CheckPermission(Permission))
		{
			cout << "\n=================================\n";
			cout << " Access Denied!\n";
			cout << "=================================\n";

			return true;
		}

		return false;
	}

	//Clients Screen

	void AddClientScreen() {


		if (AccessDenied(UserLib::pAddClient)) {
		
			BackScreensFun("Client");
			ClientsScreen();
			
			return;
		}

		 ClientLib::AddClientsToFile();
		 BackScreensFun("Client");
		 ClientsScreen();
	

	/*	ClientLib::AddClientsToFile();*/

	}

	void DeleteClientScreen() {

		if (AccessDenied(UserLib::pDeleteClient)) {

			BackScreensFun("Client");
			ClientsScreen();

			return;
		}

		vector<ClientLib::stClientData> vClients =
			ClientLib::LoadClientDataFromFile(FileName);
		ClientLib::DeleteClientByAcountNumber(vClients);
		BackScreensFun("Client");
		ClientsScreen();

	}

	void UpDateClientScreen() {

		if (AccessDenied(UserLib::pUpdateClient)) {

			BackScreensFun("Client");
			ClientsScreen();

			return;
		}

		ClientLib::UpdateClientData();
		BackScreensFun("Client");
		ClientsScreen();

	}

	void FindClientScreen() {

		if (AccessDenied(UserLib::pFindClient)) {

			BackScreensFun("Client");
			ClientsScreen();

			return;
		}

		ClientLib::FindClient();
		BackScreensFun("Client");
		ClientsScreen();
	}

	void ClientListScreen() {

		if (AccessDenied(UserLib::pListClients)) {

			BackScreensFun("Client");
			ClientsScreen();

			return;
		}

		ClientLib::ShowClientsList();
		BackScreensFun("Client");
		ClientsScreen();
	}

	//Transactions Screen

	void DepositScreen() {

		if (AccessDenied(UserLib::pTransactions)) {

			BackScreensFun("Transaction");
			TransactionsScreen();

			return;
		}

		TransLib::DepositScreen();
		BackScreensFun("Transaction");
		TransactionsScreen();

	}

	void WithdrawScreen() {

		if (AccessDenied(UserLib::pTransactions)) {

			BackScreensFun("Transaction");
			TransactionsScreen();

			return;
		}

		TransLib::WithdrawScreen();
		BackScreensFun("Transaction");
		TransactionsScreen();


	}

	void TransferScreen() {

		if (AccessDenied(UserLib::pTransactions)) {

			BackScreensFun("Transaction");
			TransactionsScreen();

			return;
		}

		TransLib::TransferScreen();
		BackScreensFun("Transaction");
		TransactionsScreen();


	}

	void TotalBalanceScreen() {
	
		if (AccessDenied(UserLib::pTransactions)) {

			BackScreensFun("Transaction");
			TransactionsScreen();

			return;
		}

		TransLib::TotalBalancesScreen();
		BackScreensFun("Transaction");
		TransactionsScreen();
	
	}

	//Users Screen

	void AddUserScreen() {

		if (AccessDenied(UserLib::pManageUsers)) {

			BackScreensFun("Users");
			UsersScreen();

			return;
		}

		UserLib::AddUsersToFile();
		BackScreensFun("Users");
		UsersScreen();
	}

	void UpDateUserScreen() {

		if (AccessDenied(UserLib::pManageUsers)) {

			BackScreensFun("Users");
			UsersScreen();

			return;
		}

		UserLib::UpdateUsersData();
		BackScreensFun("Users");
		UsersScreen();

	}

	void DeleteUserScreen() {

		if (AccessDenied(UserLib::pManageUsers)) {

			BackScreensFun("Users");
			UsersScreen();

			return;
		}

		UserLib::DeleteUserByIDNumber();
		BackScreensFun("Users");
		UsersScreen();

	}

	void UserListScreen() {

		if (AccessDenied(UserLib::pManageUsers)) {

			BackScreensFun("Users");
			UsersScreen();

			return;
		}

		UserLib::ShowUsersList();
		BackScreensFun("Users");
		UsersScreen();

	}

	void FindUserScreen() {

		if (AccessDenied(UserLib::pManageUsers)) {

			BackScreensFun("Users");
			UsersScreen();

			return;
		}

		UserLib::FindUser();
		BackScreensFun("Users");
		UsersScreen();
	}

	//Set Chooses Screens
	void SetChooseScreen(enMienMenuChoose Choose) {

		switch (Choose) {
		case enMienMenuChoose::Clients: {
			system("cls");
			ClientsScreen();
			//BackToMainScreen();
			break;
		}
		case enMienMenuChoose::Transactions: {
			system("cls");
			TransactionsScreen();
			//BackToMainScreen();
			break;

		}
		case enMienMenuChoose::Users: {
			system("cls");
			UsersScreen();
			break;
		}
		case enMienMenuChoose::Exti: {
			system("cls");
			LogInScreen();
			break;
		}
		}

	}

	void SetClientChooses(enClientMenuChoose Choose) {

		switch (Choose) {

		case enClientMenuChoose::Add: {
			system("cls");
			AddClientScreen();

			break;


		}
		case enClientMenuChoose::Delete: {
			system("cls");
			DeleteClientScreen();

			break;

		}
		case enClientMenuChoose::Find: {
			system("cls");
			FindClientScreen();

			break;

		}
		case enClientMenuChoose::UpDate: {
			system("cls");
			UpDateClientScreen();

			break;

		}
		case enClientMenuChoose::List: {
			system("cls");
			ClientListScreen();

			break;

		}
		case enClientMenuChoose::Back: {
			BackToMainScreen();
			break;
		}
		}

	}

	void SetTransactionsChooses(enTransactionsChoose Choose) {

		switch (Choose) {

		case enTransactionsChoose::Deposit: {
			system("cls");
			DepositScreen();
			break;


		}
		case enTransactionsChoose::Transfer: {
			system("cls");
			TransferScreen();
			break;

		}
		case enTransactionsChoose::Withdraw: {
			system("cls");
			WithdrawScreen();
			break;

		}
		case enTransactionsChoose::Total:{
			system("cls");
			TotalBalanceScreen();
			break;
		}
		case enTransactionsChoose::Main: {
			BackToMainScreen();
		}
		}
	}

	void SetUsersChooses(enUsersChoose Choose) {

		switch (Choose) {

		case enUsersChoose::U_Add: {

			AddUserScreen();
			break;

		}
		case enUsersChoose::U_UpDate: {

			UpDateUserScreen();
			break;

		}
		case enUsersChoose::U_Delete: {

			DeleteUserScreen();
			break;

		}
		case enUsersChoose::U_Find: {

			FindUserScreen();
			break;

		}
		case enUsersChoose::U_List: {

			UserListScreen();
			break;

		}
		case enUsersChoose::Bask: {
			BackToMainScreen();
			break;
		}


		}

	}

	//Screen Functions...
	void ClientsScreen() {

		system("cls");
		system("color 04");
		cout << "\t----------------------------------------\n";
		cout << "\n\t\t Client Screen\n";
		cout << "\t----------------------------------------\n";
		cout << "\t [1]_ Add." << endl;
		cout << "\t [2]_ Delete." << endl;
		cout << "\t [3]_ UpDate." << endl;
		cout << "\t [4]_ Find." << endl;
		cout << "\t [5]_ Clients List." << endl;
		cout << "\t [6]_ Main Menu." << endl;
		cout << "\t----------------------------------------\n";
		SetClientChooses(ReadClientMenuChoose());

	}

	void TransactionsScreen() {
		system("cls");
		system("color 06");
		cout << "\t----------------------------------------\n";
		cout << "\n\t\t Transactions Screen\n";
		cout << "\t----------------------------------------\n";
		cout << "\t [1]_ Deposit." << endl;
		cout << "\t [2]_ Withdraw." << endl;
		cout << "\t [3]_ Transfer." << endl;
		cout << "\t [4]_ Total Balances." << endl;
		cout << "\t [5]_ Main Menu." << endl;
		cout << "\t----------------------------------------\n";
		SetTransactionsChooses(ReadTransactionChoose());
	}

	void UsersScreen() {

		system("cls");
		system("color 02");
		cout << "\t----------------------------------------\n";
		cout << "\t\t Users Screen " << endl;
		cout << "\t----------------------------------------\n";
		cout << "\t  [1] List Users." << endl;
		cout << "\t  [2] Add New User." << endl;
		cout << "\t  [3] Delete User." << endl;
		cout << "\t  [4] UpDate User." << endl;
		cout << "\t  [5] Find User." << endl;
		cout << "\t  [6] Main Menu." << endl;
		cout << "\t----------------------------------------\n";
		SetUsersChooses(ReadUsersChoose());
	}

	void ShowMainMenuScreen() {
		//system("color 08");
		cout << "====================================================" << endl;
		cout << "\t\t Main Menu Screen" << endl;
		cout << "====================================================" << endl;
		cout << "\n[1]_ Clients." << endl;
		cout << "\n[2]_ Transactions." << endl;
		cout << "\n[3]_ Users." << endl;
		cout << "\n[4]_ LogOut." << endl;
		cout << "====================================================" << endl;
		SetChooseScreen(ReadMienMenuChoose());
	}

	void BackToMainScreen() {
		system("cls");
		ShowMainMenuScreen();
	}

	void LoginScreen()
	{
		while (!LoginLib::Login())
		{
			system("cls");

			cout << "\nInvalid Username/Password\n";
		}

		ShowMainMenuScreen();
	}

	void LogInScreen() {
		cout << "\t\t==============================" << endl;
		cout << "\t\t\t LogIn" << endl;
		cout << "\t\t==============================" << endl;
		LoginScreen();
	}







}