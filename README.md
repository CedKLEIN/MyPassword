# MyPassword

## About the app:
The goal of MyPassword is to provide a service to handle all accounts of a user.
Indeed you have the possibility to store all data about accounts as login, email etc
You can provide the password, which will be encrypted.
No possibility to get the password back but MyPassword provide a feature to try password and check if it matchs.
#### First deploy 01/12/2020

## Features:
- Store data from account: Name, Login, password encrypted, other details and password security level.
- Try password and check if it matchs
- Generate a data text file with all your accounts
- Import a text file with the good format to bring accounts
- Checker of security level of password (VERY HIGH, HIGH, MEDIUM, LOW, VERY_LOW)

## Technically:
- QT version: 
- Compiler: 
- Language: C++
- Encryption: MD5

## Version:
### 1.1 - 10/12/2020 - New features:
- Import data accounts from text file
- Fix issue with filter
- Add attribution in info tab
- Generate password and severity in text file

### Guide:

## Tab view accounts
This is the main tab, where you have the list of your accounts.
It can also select each of them to display another view to display account data or to make modification. 

### Tab menu
### Filter
### List accounts
### Account view
#### Close account
#### Change Login, Details
The account window will close after changing Login or Details.
Some character as Apostrophe are forbidden.

#### Change Password
The account window will close after changing password.
All character are allowed.
*Possibility to view the new password you are writing using the view icon*
*You can also find the security level you are writing*

#### Check your password
As the current password is saved in database encrypted via MD5, you cannot decrypt it.
However you have the possibility to test password that will be encrypted to check if it match with the one in database.

*It is will be green if it matched*

*It is will be red if not*

*Possibility to view the new password you are writing using the view icon*

*You can also find the security level you are writing*

#### Delete account
Will delete the account from the list accounts. No possibility to have it back expect if you did a save in text file (see generate file).

## Tab create account
This tab allow to create new account.

### Name
This is the name that will be display in main tab list. This name has to be unique. 
For instance if you have several Outlook account, you can put as name "Outlook1" and "Outlook2", or "Outlook" and "Outlook for job" etc
Whatever you want to be the eiser to get it from the list.
Some character as Apostrophe are forbidden.

### Login
The login you use to connect to the account.
Some character as Apostrophe are forbidden.

### Password
You canwrite the password here, it will be then encrypted and you won't be able to get it back.
But you will have the possibity to try password and check if it matchs
All character are allowed.
*Possibility to have the password in clear when you are writing using the view icon*
*You can also find the security level you are writing*

### Details
Any details you want to add, as clue for your password. Other account details etc.
Of course the goal is to avoid to write the password in clear, but if needed you can put it here.
Some character as Apostrophe are forbidden.

### Validate the password
Will create the password, and clear the tab. If no issue came out, you will find your password in the main tab view list.
