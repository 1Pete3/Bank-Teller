#include<bits/stdc++.h>
#include <cctype>
#include <cfloat>
#include <cstdio>
#include <cstring>
#include <ios>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <random>
#include <climits>
#include <string>
#include<sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctime>
#include <vector> 
#include <thread>
#include <regex>
#include <unistd.h>
#define EST (-4)
using namespace std;
int NumberofAccounts=1;
int userInput;
int key = 20;
fstream account;
fstream textFile;
fstream depositFile;
fstream errorlog;
void continueExit();
bool isValidString(string text);
int menu();
void checkInputSize(char* input,int size );
vector<int> accountNumbers;
time_t rawtime;
struct tm * ptm;
bool loggedIn = false;

//Person class was used to create bank accounts with personal information
class Person {
  private:
  string houseNumStreetName, town,fName, lName, state, zipcode;
  public:
    unsigned int accountNumber;
  Person() {}

    ~Person() {}

  // Cryptographically random numbers from the inclass example, used to generate account numbers 
  // 7-1 new account numbers are generated everytime an account is created, account numbers are checked so that they are not the same
  unsigned int generateAccountNumber() {
    random_device r;
    seed_seq seed {
      r(), r(), r(), r(), r(), r(), r(), r(), r(), r()
    };
    mt19937 engine {
      seed
    };
    // range is from 1000000000 - INT_MAX
    uniform_int_distribution < > dist(1000000000, INT_MAX);
    accountNumber = dist(engine);
    for (int i = 0; i < accountNumbers.size(); i++) {
      if (accountNumbers[i] == accountNumber) {
        generateAccountNumber();
        //logic used here so that no two accounts share the same account number
        // highly unlikely that the range of all numbers would be full
        cout << "same account num generating new one" << endl;
      } else if (NumberofAccounts == (INT_MAX - 1000000000 + 1)) {
        cout << "Max accounts created" << endl;
        exit(0);
      }
    }
    return accountNumber;
  }
  // Function to get someones first name
  string getFirstName() {
    
    cout << "Enter the customers first name: ";
    cin >> fName;
    //6-1 does not let the user enter a first name over 20 characters and checks if there are any special characters being used
    //using a while loop the program will continue getting input from the user until they enter a valid value
    while (fName.length()>20 ||(isValidString(fName)==false))
    {           
        cin.clear ();    // Restore input stream to working state
        cin.ignore ( 9, '\n' );
        cout << "Invalid Input. Try again: ";
        cin >> fName;
        isValidString(fName);
    }
    return fName;
  }
 // Function to get someones last name 
  string getLastName() {
    cout << "Enter the customers last name: ";
    cin >> lName;
    while (lName.length()>20 ||(isValidString(lName)==false))
    {           
        cin.clear ();    // Restore input stream to working state
        cin.ignore ( 9, '\n' );
        cout << "Invalid Input. Try again: ";
        cin >> lName;
        isValidString(lName);
    }
    return lName;
  }
  // Function to get someones address, getline was used here because of space between house num, street name
  string getHouseNumStreet() {
    cout << "Enter the house number and street name : ";
    // use ignore() so that cin is not skipped
    cin.ignore();
    getline(cin, houseNumStreetName);
    return houseNumStreetName;
  }
  // Function to get the town someone lives in, getline used here incase of space between town name like New Haven, etc.
  string getTown() {
    cout << "Enter the town: ";
    getline(cin, town);
    return town;
  }
  // Function to get the two letter abbrivation for the state that a person lives in
  string getState() {
    cout << "Enter the state (2 letter abbrivation): ";
    cin >> state;
    while (state.length()>2 ||(isValidString(state)==false))
    {           
        cin.clear ();    // Restore input stream to working state
        cin.ignore ( 9, '\n' );
        cout << "Invalid Input. Try again: ";
        cin >> state;
        isValidString(state);
    }
    // Capitalizes the state entered
    for (int i = 0; i < state.length(); i++) {
      state[i] = toupper(state[i]);
    }    
    return state;
  }
  //zipcode.length() != 5
    bool isFiveDigits(string zipcode)
    {
        int count;
    for (int i =0; i < zipcode.length();i++)
        {
            if(isdigit(zipcode[i])==true)
            {
                count++;
            }
        }
        if (count == 5)
        {
            return true; 
        }
        else
        {
            count = 0;
            return false;
        }
    }

  // Function to get someones zipcode
  string getZipcode() {
    int count;
    cout << "Enter the zipcode: ";
    cin >> zipcode;
    while (isFiveDigits(zipcode)==false)
    {           
        cin.clear ();    // Restore input stream to working state
        cin.ignore ( 9, '\n' );
        cout << "Invalid Input. Try again: ";
        cin >> zipcode;
    }
    return zipcode;
  }
};

//5-1 some data sanitization to prevent user from using some special characters when recieving input
bool isValidString(string str)
{
	regex regx("[@,_!#$%^&*()<>?/|}{~:;]");
	if(regex_search(str, regx) == 0)
    {
        return true;
    }
	else
    {
        return false;
    }
}


// Function for logging into the program since this is sensitive information
void login()
{
    char password[9];
    int count = 0;    
    printf("Enter password: ");
//1-1
// Used fgets here so that array bound is checked and so that buffer overflow is prevented     
    fgets(password,9,stdin);
        if(strcmp(password,"password")==0)
        {
            loggedIn = true;
        }
    
}
//7-2 Function for encryting a string, the account numbers are encrypted when writing to a file. The acual account number is not store in files
string encrypt(string encryptedText)
{
    for(int i=0; (i<75 && encryptedText[i]!='\0'); i++)
    {
        encryptedText[i]=encryptedText[i]+key;
    }
    return encryptedText;
}
// Function to decipher encrpyted accounts so they can be stored in vectors and other containers
string decrypt(string decryptedText)
{
    for(int i=0; (i<75 && decryptedText[i]!='\0'); i++)
    {
        decryptedText[i]=decryptedText[i]-key;
    }
    return decryptedText;
}

// Function that returns a float data type and opens/reads every line then takes the string data and converts it
// to float. Files are also checks if files are created and if errors occur they are written to an error log
float readAddFiles(string nameOfFile)
{
  time( & rawtime);
  ptm = gmtime( & rawtime);
  string tmp;
  float temp = 0;
  textFile.open(nameOfFile,ios::in);
  if (!textFile) 
  {
    cout<<nameOfFile<<endl;
    cout << "No such file"<<endl;
    cout<<endl;
    return temp;
  } 
  else 
  {
      while (getline(textFile, tmp, '\n')) {
      // try catch block is used here to try to convert data in a file to float. If an error occurs it's written to a log
      try {        
        float money = stof(tmp);
        temp = money + temp;
        //cout <<"temp is " << temp <<endl;
      } catch (std::exception & e) {
        //6-2 when creating a file, if the file already exists open it in append mode rather than over writting all the contents
        // If the errorlog file doesn't exist then create a file named errorlog.txt that allows output        
        if (errorlog) {
          cout << "\033[93;100mFile errorlog.txt exits, appending to it\033[0m" << endl;
          errorlog.close();          
          errorlog.open("errorlog.txt", std::ios::app);
        } else {
          cout << "Creating file errorlog.txt" << endl;
          errorlog.open("errorlog.txt", std::ios::out);
          if (!errorlog) {
            cout << "Error in creating file!!!";
            return 0;
          }
        }
        //most of the lines below are just to format and display the time and date if an error occurs
        //10-1 error log shows date, time and what caused the error. stoi(EKDEJLDEGDEDEFMMMFEG) can cause an error when converting string to int for example 
        errorlog << setw(2) << setfill('0') << (ptm -> tm_mon + 1) % 12 << "/" << setw(2) << setfill('0') << ptm -> tm_mday << "/" << setw(4) << setfill('0') << ptm -> tm_year + 1900 << " " <<
          setw(2) << setfill('0') << ((ptm -> tm_hour + EST) % 24 + 24) % 24 << ":" << setw(2) << setfill('0') << ptm -> tm_min << ":" << setw(2) << setfill('0') << ptm -> tm_sec << " " <<
          e.what() << "(" << tmp << ")" << " caused this error\n";
      }
    }
  }
    errorlog.close();
    textFile.close();
    return temp;
}
// Function used to create accounts and write info to a csv and txt file
void createAccount()
{
    // Writes account numbers to a txt file so that values can easily be store in a vector without having to do much
    // parsing. This is so that the txt file will be opened at anypoint and store current used account numbers
    textFile.open("accounts.txt");
    if (textFile)
    {
      cout << "File accounts.txt exits, appending to it" << endl;
      textFile.close();
      //Open for appending
      textFile.open("accounts.txt", std::ios::app);
    } 
    else 
    {
      //create a new file if it doesn't exist
      cout << "Creating file accounts.txt" << endl;
      textFile.open("accounts.txt", std::ios::out);
      //if the file fails to be created
      if (!textFile) 
      {
        cout << "Error in creating file!!!";
      }
    }
    //Writes account numbers to a csv file for easier readablity or to open information in excel, account numbers are in encryted though
    account.open("account.csv");
    if (account) {
      cout << "File account.csv exits, appending to it" << endl;
      account.close();
      //Open for appending
      account.open("account.csv", std::ios::app);
    } else {
      //create a new file if it doesn't exist
      cout << "Creating file account.csv" << endl;
      account.open("account.csv", std::ios::out);
      //if the file fails to be created
      if (!account) {
        cout << "Error in creating file!!!";
      } else {
        // Writes the column titles for the csv in the order they are presented in
        account << "Account#,Firstname,Lastname,Address,Town,State,Zipcode,Time(EST),Date" << endl;
      }
    }

    //Creates a new person object and writes the information to a csv and txt file
    Person *person = new Person();
    person -> generateAccountNumber();
    accountNumbers.push_back(person -> accountNumber);
    account << encrypt(to_string(person -> accountNumber));
    textFile << encrypt(to_string(person -> accountNumber))<< endl;
    textFile.close();
    account << ",";
    account << person -> getFirstName();
    account << ",";
    account << person -> getLastName();
    account << ",";
    account << person -> getHouseNumStreet();
    account << ",";
    account << person -> getTown();
    account << ",";
    account << person -> getState();
    account << ",";
    account << person -> getZipcode();
    account << ",";
    //Time formated in HH:MM:SS using setw to set width to 2 and fill 0 where needed
    account << setw(2) << setfill('0') << ((ptm -> tm_hour + EST) % 24 + 24) % 24 << ":" << setw(2) << setfill('0') << ptm -> tm_min << ":" << setw(2) << setfill('0') << ptm -> tm_sec;
    account << ",";
    account << setw(2) << setfill('0') << (ptm -> tm_mon + 1) % 12 << "/" << setw(2) << setfill('0') << ptm -> tm_mday << "/" << setw(4) << setfill('0') << ptm -> tm_year + 1900;
    account << "\n";
    account.close();
    // Green text to let the user know that account was created successfully uses ANSI escape color codes (works in linux)
    cout << "\033[32mAccount created successfully\033[0m" << endl;
    //3-1 the object gets deleted freeing up memory and uses delete rather than useing delete[]    
    delete person;
    
}
// Fuinction to check if the account number exists that way in can be used for different transactions
bool accountChecker(int checkAccountNumber)
{
    //Search through a vector to find the account number
    vector<int>::iterator it;
    it = find(accountNumbers.begin(), accountNumbers.end(), checkAccountNumber);
    
    if (it != accountNumbers.end())
    {
        cout << "\033[32mAccount found\033[0m" << endl;
        return true;
    }
    else
    {
        cout << "\033[31mNo accounts found\033[0m"<< endl;
        cout << "Returning to menu"<< endl;
        sleep(5);
        menu();
        return false;
    }

}
// Function to make a deposit
void deposit()
{
   bool keyExists = false;
   int depositAccountNum;
   float depositAmount; 

   cout << "Enter a bank account number: ";
   cin >> depositAccountNum;
   // Check to see if the bank account that was entered is valid
   if(accountChecker(depositAccountNum)==true)
   {
       //creates a directory called deposits returns message if there is already a directory created
       if (mkdir("deposits", 0777) == -1)
        cerr << "deposits directory already exists"<< endl;

    else
        cout << "Directory created" << endl;
        char yesNo;
        //directory/filename.txt
        string fileName = "deposits/"+encrypt(to_string(depositAccountNum))+"Deposit.txt";
        //Writes deposits to a txt file 
        depositFile.open(fileName);
        if (depositFile)
        {
        // 2-1 format string problems streamed IO is used here
        // If the file already exists  open it for append mode        
        cout << "File "<< fileName << " exits, appending to it" << endl;
        depositFile.close();
        //Open for appending
        depositFile.open(fileName, std::ios::app);
        } 
        else 
        {
            //create a new file if it doesn't exist
            cout << "Creating file " << fileName << endl;
            depositFile.open(fileName, std::ios::out);
            //if the file fails to be created
            if (!depositFile) 
            {
                cout << "Error in creating "<< fileName << endl;
            }
        }
        cout << "Enter the deposit amount: ";
        cin >> depositAmount;
        // If the user enters an ammount outside of this range, the wile loop will keep asking for an input
        while (depositAmount < 0||depositAmount > 100000) 
        {           
            cin.clear ();    // Restore input stream to working state
            cin.ignore ( 9 , '\n' );
            cout << "Invalid input. Try again: ";
            cin >> depositAmount;
        }
        // When writing to the text file, float numbers are written with 2 decimal places
        depositFile << fixed<< setprecision(2)<<depositAmount<<endl;
        cout << "\nEnter an other deposit for this account?"<< endl;
        cout << "Enter y for yes, n for no and return to the menu"<<endl;
        cin >> yesNo;
        while(yesNo == 'y')
        {
            cout << "Enter the deposit amount: ";
            cin >> depositAmount;
            cout << endl;
            while (depositAmount < 0||depositAmount > 100000) 
            {           
                cin.clear ();    // Restore input stream to working state
                cin.ignore ( 9, '\n' );
                cout << "Invalid input. Try again: ";
                cin >> depositAmount;
            }
            depositFile << fixed<< setprecision(2)<<depositAmount<<endl;
            cout << "Enter an other deposit for this account?"<< endl;
            cout << "Enter y for yes, n for no and return to the menu"<<endl;
            cin >> yesNo;
        }
        depositFile.close();
        menu();
    }
}
// Similar to the deposit function
void Withdraw()
{
    bool keyExists;
    int WithdrawAccountNum;
   float WithdrawAmount; 
   string tmp;
   float temp;
   cout << "Enter a bank account number: ";
   cin >> WithdrawAccountNum;
   if(accountChecker(WithdrawAccountNum)==true)
   {
       //Check if that account has deposits before Withdrawing
       textFile.open("deposits/"+encrypt(to_string(WithdrawAccountNum))+"Deposit.txt", ios::in); 
        if (!textFile) 
        {
            cout << "No deposits have been made for that account"<<endl;
            menu();            
        } 
        else 
        {
            while (getline(textFile, tmp, '\n'))
            {
                //4-1 uses a try catch block when creating files, float money trys to convert a string into a float value and if there is an error with this 
                // it will be written in the errorlog.txt 
                try 
                {
                    float money = stof(tmp);
                    temp = money + temp;
                    cout <<"temp is " << temp <<endl;        
                }
                catch (std::exception & e) 
                {
                    if (errorlog) 
                    {
                        cout << "\033[93;100mFile errorlog.txt exits, appending to it\033[0m" << endl;
                        errorlog.close();
                        errorlog.open("errorlog.txt", std::ios::app);
                    }
                    else
                    {
                        cout << "Creating file errorlog.txt" << endl;
                        errorlog.open("errorlog.txt", std::ios::out);
                        if (!errorlog) 
                        {
                            cout << "Error in creating file!!!";
                        }
                    }
                    errorlog << setw(2) << setfill('0') << (ptm -> tm_mon + 1) % 12 << "/" << setw(2) << setfill('0') << ptm -> tm_mday << "/" << setw(4) << setfill('0') << ptm -> tm_year + 1900 << " " <<
                    setw(2) << setfill('0') << ((ptm -> tm_hour + EST) % 24 + 24) % 24 << ":" << setw(2) << setfill('0') << ptm -> tm_min << ":" << setw(2) << setfill('0') << ptm -> tm_sec << " " <<
                    e.what() << "(" << tmp << ")" << " caused this error\n";
                }
            }
        textFile.close();
        errorlog.close();           
        }

       //creates a directory called deposits
       if (mkdir("withdraws", 0777) == -1)
        cout << "withdraws directory already exists"<< endl;

    else
        cout << "Directory created" << endl;
        char yesNo;
        //directory/filename.txt
        string fileName = "withdraws/"+encrypt(to_string(WithdrawAccountNum))+"Withdraw.txt";
        //Writes account numbers to a txt file 
        depositFile.open(fileName);
        if (depositFile)
        {
        cout << "File "<< fileName << " exits, appending to it" << endl;
        depositFile.close();
        //Open for appending
        depositFile.open(fileName, std::ios::app);
        } 
        else 
        {
            //create a new file if it doesn't exist
            cout << "Creating file " << fileName << endl;
            depositFile.open(fileName, std::ios::out);
            //if the file fails to be created
            if (!depositFile) 
            {
                cout << "Error in creating "<< fileName << endl;
            }
        }
        cout << "Enter the Withdraw amount: ";
        cin >> WithdrawAmount;
        while (WithdrawAmount > temp)
        {           
            cin.clear ();    // Restore input stream to working state
            cin.ignore ( 9 , '\n' );
            cout << "Invalid input. Try again: ";
            cin >> WithdrawAmount;
        }
        depositFile << fixed<< setprecision(2)<<WithdrawAmount<<endl;
        depositFile.close();
        menu();
    }
}
void applyFee()
{
   int feeAccountNum;
   float feeAmount; 
   cout << "Enter a bank account number: ";
   cin >> feeAccountNum;
   if(accountChecker(feeAccountNum)==true)
   {
       //creates a directory called fees
       if (mkdir("fees", 0777) == -1)
        cout << "fees directory already exists"<< endl;

    else
        cout << "Directory created" << endl;
        char yesNo;
        //directory/filename.txt
        string fileName = "fees/"+encrypt(to_string(feeAccountNum))+"Fees.txt";
        depositFile.open(fileName);
        if (depositFile)
        {
        cout << "File "<< fileName << " exits, appending to it" << endl;
        depositFile.close();
        //Open for appending
        depositFile.open(fileName, std::ios::app);
        } 
        else 
        {
            //create a new file if it doesn't exist
            cout << "Creating file " << fileName << endl;
            depositFile.open(fileName, std::ios::out);
            //if the file fails to be created
            if (!depositFile) 
            {
                cout << "Error in creating "<< fileName << endl;
            }
        }
        cout << "Enter the fee amount: ";
        cin >> feeAmount;
        while (feeAmount < 0||feeAmount > 100000) 
        {           
            cin.clear ();    // Restore input stream to working state
            cin.ignore ( 9 , '\n' );
            cout << "Invalid input. Try again: ";
            cin >> feeAmount;
        }
        depositFile << fixed<< setprecision(2)<<feeAmount<<endl;
        cout << "Enter an other fee for this account?"<< endl;
        cout << "Enter y for yes, n for no and return to the menu"<<endl;
        cin >> yesNo;
        while(yesNo == 'y')
        {
            cout << "Enter the fee amount: ";
            cin >> feeAmount;
            while (feeAmount < 0||feeAmount > 100000) 
            {           
                cin.clear ();    // Restore input stream to working state
                cin.ignore ( 9, '\n' );
                cout << "Invalid input. Try again: ";
                cin >> feeAmount;
            }
            depositFile << fixed<< setprecision(2)<<feeAmount<<endl;
            cout << "Enter an other fee for this account?"<< endl;
            cout << "Enter y for yes, n for no and return to the menu"<<endl;
            cin >> yesNo;
        }
        depositFile.close();
        //read the values stored in the text file and add them all
        readAddFiles("fees/"+encrypt(to_string(feeAccountNum))+"Fees.txt");
        menu();
    } 
}
//returns a float value because all the deposits, Withdraws and fees are added up and stored in 3 different maps
// The key in each map is an account number and the value is the total deposits in the deposit map, total Withdraws in the 
// Withdraw map and total fees in the fees map. Balance = deposits - Withdraws - fees
void checkBalance()
{
    int accountNumBalance;
    float balance,x,y,z;
    std::map<unsigned int,float>::iterator it;
    cout << "Enter a bank account number: ";
    cin >> accountNumBalance;
    if(accountChecker(accountNumBalance)==true)
    {
        // Uses function readAddFiles to read the file and add the amount in the file
        z = readAddFiles("fees/"+encrypt(to_string(accountNumBalance))+"Fees.txt");
        x = readAddFiles("deposits/"+encrypt(to_string(accountNumBalance))+"Deposit.txt");
        y = readAddFiles("Withdraws/"+encrypt(to_string(accountNumBalance))+"Withdraw.txt");
        // 2-2 format string problems streamed IO is used here
        cout << "Deposits: $" << fixed << setprecision(2) << x << endl;
        cout << "Withdraws: $" << fixed << setprecision(2) << y << endl;
        cout << "Fees: $" << fixed << setprecision(2) << z << endl;
        balance = x - y - z;
        //negative amount = red
        if (balance < 0)
        {
            cout <<"\033[31mBalance: $" << balance << "\033[0m" << endl;
        }
        //positive amout = green
        else if (balance > 0)
        {
            cout <<"\033[32mBalance: $" << balance << "\033[0m" << endl;
        }
        
        menu();
    }
}

// 10-2 function to create the menu so it's easier to understand the functions of this program
int menu() {
  int menuSelection;
  cout << "|=============================|" << endl;
  cout << "|             MENU            |" << endl;
  cout << "|=============================|" << endl;
  cout << "| 1.Create an account" << "         |" << endl;
  cout << "| 2.Show accounts" << "             |" << endl;
  cout << "| 3.Deposit" << "                   |" << endl;
  cout << "| 4.Withdraw" << "                  |" << endl;
  cout << "| 5.Apply fee" << "                 |" << endl;
  cout << "| 6.Check balance" << "             |" << endl;
  cout << "| 7.Exit" << "                      |" << endl;
  cout << "===============================" << endl;

  cout << "Enter a menu item number: ";
  cin >> menuSelection;

// Depending on what number is entered, that is the function that is selected
  if (menuSelection == 1) 
  {
    createAccount();
    continueExit();
  } 
  else if (menuSelection == 2) 
  {
    //10-3 shows the accounts that are created
    for (int i = 0; i < accountNumbers.size(); i++)
    {
        cout << "accountNumbers[" << i << "]" << " " << accountNumbers[i] << endl;
    }
    continueExit();
  }
  else if (menuSelection == 3) 
  {
    deposit();
  } 
  else if (menuSelection == 4) 
  {
    Withdraw();
  } 
  else if (menuSelection == 5) 
  {
    applyFee();
  } 
  else if (menuSelection == 6) 
  {
    checkBalance();
  } 
  else
  {
    exit(0);
  }

  return 0;

}
//Function that gives the user the opporutunity to quit the program or continue and return to the menu to 
//select more functions
void continueExit() {
  int continueSelection;
  cout << "\nPress 1 to return to the menu" << endl;
  cout << "Press 2 to exit" << endl;
  cin >> continueSelection;
  if (continueSelection == 1)
    menu();
  else
    cout << "Goodbye :)\n" << endl;
  exit(0);
}

//command line arguments for bank transactions
int main(int argc, char ** argv) {
    // 13-1 While function is used here so that user needs to enter the correct password or they can't get in
    while(loggedIn==false)
    {
        login();
    }
  time( & rawtime);
  ptm = gmtime( & rawtime);
   string tmp;
  textFile.open("accounts.txt", ios::in );
  if (!textFile) {
    cout << "No such file"<<endl;
  } else {
    while (getline(textFile, tmp, '\n')) {
      //4-2 uses a try catch block when creating files and storing account numbers in vectors/files, int num is using stoi to convert the account num to an int
      // if it fails then it will be written in the errorlog.txt        
      try {
        cout << decrypt(tmp) << endl;         
        int num = stoi(decrypt(tmp));
        if (num >= 1000000000 && num <= INT_MAX) {
          //3-2 using a vector to store account numbers since vectors can store changing data and the size of the vector changes
          accountNumbers.push_back(num);
        }
      } catch (std::exception & e) {
        if (errorlog) {
          cout << "\033[93;100mFile errorlog.txt exits, appending to it\033[0m" << endl;
          errorlog.close();
          errorlog.open("errorlog.txt", std::ios::app);
        } else {
          cout << "Creating file errorlog.txt" << endl;
          errorlog.open("errorlog.txt", std::ios::out);
          if (!errorlog) {
            cout << "Error in creating file!!!";
            return 0;
          }
        }
        errorlog << setw(2) << setfill('0') << (ptm -> tm_mon + 1) % 12 << "/" << setw(2) << setfill('0') << ptm -> tm_mday << "/" << setw(4) << setfill('0') << ptm -> tm_year + 1900 << " " <<
          setw(2) << setfill('0') << ((ptm -> tm_hour + EST) % 24 + 24) % 24 << ":" << setw(2) << setfill('0') << ptm -> tm_min << ":" << setw(2) << setfill('0') << ptm -> tm_sec << " " <<
          e.what() << "(" << tmp << ")" << " caused this error\n";
      }
    }
    textFile.close();
    errorlog.close();
  }
  
  // selects type of transaction using command line arguments
  if (argc == 2 && strcmp(argv[1], "create") == 0) {
    printf("Create account selected\n");
    createAccount();
    continueExit();

  } else if (argc == 2 && strcmp(argv[1], "show") == 0) {
    cout << "Show accounts selected" << endl;
    for (int i = 0; i < accountNumbers.size(); i++)
    {
        cout << "accountNumbers[" << i << "]" << " " << accountNumbers[i] << endl;
    }
    continueExit();

  } else if (argc == 2 && strcmp(argv[1], "deposit") == 0) {
    cout << "Deposit Selected" << endl;
    deposit();

  } else if (argc == 2 && strcmp(argv[1], "Withdraw") == 0) {
    cout << "Withdraw Selected" << endl;
    Withdraw();

  } else if (argc == 2 && strcmp(argv[1], "fee") == 0) 
  {
    applyFee();
  } 
  else if (argc == 2 && strcmp(argv[1], "balance") == 0) 
  {
    checkBalance();
  } 
  else if (argc == 2 && strcmp(argv[1], "menu") == 0) {
    menu();
  } else {
    cout << "\033[36mUse ./a.out create to create a new bank account" << endl;
    cout << "Use ./a.out show to show all the bank accounts" << endl;
    cout << "Use ./a.out deposit for a deposit" << endl;
    cout << "Use ./a.out Withdraw for a Withdraw" << endl;
    cout << "Use ./a.out fee to apply a fee" << endl;
    cout << "Use ./a.out balance for a balance inquiry" << endl;
    cout << "Use ./a.out menu to access the menu\033[0m" << endl;
  }
  return 0;
}