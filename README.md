# Bank Teller

This program was created to represent the transaction that a bank teller may encounter. This program has only been tested in the google cloud shell editor so please use that. The user is required to login to the program first with a password before anything can be done. Default password is password.

Q: What's the password?<br />
A: **password**

Q: How do I get started?<br />
A:<br />    1. Head over to https://shell.cloud.google.com/ <br />   2. Sign in with a Google Account. 

 The user uses a menu (see image below) to do certain transactions or by using command-line arguments. Available command-line arguments include: 
*  **./a.out create** - to create a new bank account
* 	**./a.out show** - to show all the bank accounts
* 	**./a.out deposit** - for a deposit
* 	**./a.out withdraw** - for a withdraw
* 	**./a.out fee** - to apply a fee
* 	**./a.out balance** - for a balance inquiry
* 	**./a.out menu** - to access the menu
* 	**./a.out** – to see all available command-line arguments

When using the menu, the program will prompt the user to enter a number 1 -7 to access the contents of the menu. For the deposit, withdraw, apply fee and check balance functions, the user is required to enter a valid bank account number else they will be returned to the main menu. To view an account the user can enter 2 to show all the accounts and right-click and copy/paste to make it easier. 

![image](https://user-images.githubusercontent.com/75858369/166078505-9e03889a-2e56-42ad-a78a-6aca03e4f77d.png)

## Create Account
*	User enters 1 on the menu
*	Program checks if accounts.txt and accounts.csv exist
*	accounts.txt is read by the program and stores existing created accounts in a vector and adds new ones if they are created.
*	accounts.csv stores information associated with the account like the first name, last name, house number and street address, state, zip code which can be opened in Excel or other software for more convenient viewing
*	If accounts.txt and account.csv are not created the program automatically creates them 

## Show Accounts
* User enters 2 on the menu
* Displays all the current accounts from accounts.txt in the terminal 

![image](https://user-images.githubusercontent.com/75858369/166078663-30635084-abf7-4656-ad17-b777bf603625.png)

## Deposits
*	Allows the user to enter deposits for a valid bank account
*	User must enter a bank account before entering details of the deposit
* A deposits directory will be automatically created if there is not one already
*	A text file associated with that account will be created in that directory with a name like  EEGEFLIHJDDeposit.txt if the file does not already exist. If it exists then the new information will be appended.

## Withdraw
*	Allows the user to enter withdraws for a valid bank account
*	User must enter a bank account before entering details of the withdraw
*	A withdraws directory will be automatically created if there is not one already
*	A text file associated with that account will be created in that directory with a name like  EEGEFLIHJDWithdraw.txt if the file does not already exist. If it exists then the new information will be appended.

## Apply Fee
*	Allows the user to apply fees for a valid bank account
*	User must enter a bank account before entering details of the fee
*	A fees directory will be automatically created if there is not one already
* A text file associated with that account will be created in that directory with a name like  EEGEFLIHJDFees.txt if the file does not already exist. If it exists then the new information will be appended.

## Check Balance
* Allows the user to check the balance for a valid bank account
*	Check balance uses the text files from withdraws, deposits, and fees to calculate the balance of a bank account
*	Positive balances are green and negative balances are red
*	Balance = deposits – withdraws - fees

![image](https://user-images.githubusercontent.com/75858369/166078847-b3514949-95f9-4ace-8359-40fa7179acf4.png)

## Exit
* User can enter 7 to exit the program
