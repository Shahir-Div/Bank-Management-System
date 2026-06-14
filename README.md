# Bank Management System

A console-based Bank Management System developed in C++ that simulates core banking operations and user management functionalities.

## Overview

This project was built to practice software development fundamentals using C++. It demonstrates authentication, authorization, file handling, data management, and modular programming concepts.

The system allows administrators and authorized users to manage clients, perform banking transactions, and control user access through a permission-based system.

---

## Features

### Authentication System
- Secure user login using username and password.
- User session management.

### Authorization System
- Role-based access control.
- Custom permissions for each user.
- Full-access administrator support.

### Client Management
- Add new clients.
- Update client information.
- Delete clients.
- Search for clients.
- Display all clients.

### Banking Transactions
- Deposit money.
- Withdraw money.
- Transfer funds between accounts.
- View total balances.

### User Management
- Add new users.
- Update user information.
- Delete users.
- Search for users.
- Display all users.

### Data Persistence
- Store clients and users in text files.
- Load data automatically when the application starts.
- Save updates immediately after operations.

---

## Technologies Used

- C++
- STL Vector
- Structs
- Enums
- File Handling
- Modular Programming
- Bitwise Permission Management

---

## Project Structure

```text
BankProject
│
├── ClientLib.h
├── Users.h
├── Login.h
├── ScreensLib.h
├── Transfer.h
├── BankProject.cpp
│
├── Clients.txt
├── Users.txt
└── Transaction.txt
```

---

## Permission System

The application uses a bitwise permission model:

| Permission | Value |
|------------|--------|
| List Clients | 1 |
| Add Client | 2 |
| Delete Client | 4 |
| Update Client | 8 |
| Find Client | 16 |
| Transactions | 32 |
| Manage Users | 64 |
| Full Access | -1 |

This allows combining multiple permissions efficiently in a single integer value.

---

## What I Learned

Through this project I practiced:

- Object organization using namespaces
- File management
- Data persistence
- User authentication
- User authorization
- Permission systems
- Console application design
- Modular software architecture
- Banking transaction logic

---

## Future Improvements

- Refactor the project using Object-Oriented Programming (OOP)
- Replace text files with a database
- Add password encryption
- Add transaction history reports
- Create a graphical user interface (GUI)
- Develop a web-based version

---

## Author

Developed by Shahir as part of a continuous software development learning journey focused on C++ and backend programming.
