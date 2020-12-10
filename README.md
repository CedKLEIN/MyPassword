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
### General view
#### Tab menu
#### Filter
#### List accounts
#### Account view
##### Close account
##### Change Login, Details
The account window will close after changing Login or Details.
Some character as Apostrophe are forbidden, you will have an issue if you try to commit it.

##### Change Password
The account window will close after changing password.
All character are allowed.
*Possibility to view the new password you are writing using the view icon*
*You can also find the security level you are writing*

##### Check your password
As the current password is saved in database encrypted via MD5, you cannot decrypt it.
However you have the possibility to test password that will be encrypted to check if it match with the one in database.
*It is will be green if it matched*
*It is will be red if not*
*Possibility to view the new password you are writing using the view icon*
*You can also find the security level you are writing*

##### Delete account
Will delete the account from the list accounts. No possibility to have it back expect if you did a save in text file (see generate file).

