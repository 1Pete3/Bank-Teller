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
#include <unordered_map>
#include <cctype>
#include <vector> 
#include <thread>
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
int menu();
void checkInputSize(char* input,int size );
vector< int> accountNumbers;
time_t rawtime;
struct tm * ptm;

class Person {
  private:
    const static int size = 21;
  char fName[size], lName[size], state[3], zipcode[6];
  string houseNumStreetName, town;
  public:
    unsigned int accountNumber;
  Person() {}

    ~Person() {}

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
        cout << "same account num generating new one" << endl;
      } else if (NumberofAccounts == (INT_MAX - 1000000000 + 1)) {
        cout << "Max accounts created" << endl;
        exit(0);
      }
    }
    return accountNumber;
  }
  string getFirstName() {
    cout << "Enter the customers first name: ";
    cin >> fName;
    checkInputSize(fName, size);
    return fName;
  }

  string getLastName() {
    cout << "Enter the customers last name: ";
    cin >> lName;
    checkInputSize(fName, size);
    return lName;
  }
  string getHouseNumStreet() {
    cout << "Enter the house number and street name : ";
    // use ignore() so that cin is not skipped
    cin.ignore();
    getline(cin, houseNumStreetName);
    return houseNumStreetName;
  }
  string getTown() {
    cout << "Enter the town: ";
    getline(cin, town);
    return town;
  }
  string getState() {
    cout << "Enter the state (2 letter abbrivation): ";
    cin >> state;
    checkInputSize(state, 3);
    // Capitalizes the state entered
    for (int i = 0; i < strlen(state); i++) {
      state[i] = toupper(state[i]);
    }
    return state;
  }
  string getZipcode() {
    cout << "Enter the zipcode: ";
    cin >> zipcode;
    checkInputSize(zipcode, 6);
    return zipcode;
  }
};

string encrypt(string encryptedText)
{
    for(int i=0; (i<75 && encryptedText[i]!='\0'); i++)
    {
        encryptedText[i]=encryptedText[i]+key;
    }
    return encryptedText;
}
string decrypt(string decryptedText)
{
    for(int i=0; (i<75 && decryptedText[i]!='\0'); i++)
    {
        decryptedText[i]=decryptedText[i]-key;
    }
    return decryptedText;
}

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
  } 
  else 
  {
      while (getline(textFile, tmp, '\n')) {
      try {        
        float money = stof(tmp);
        temp = money + temp;
        cout <<"temp is " << temp <<endl;
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
  }
    textFile.close();
    return temp;
}

// Checks for buffer over flow 
void checkInputSize(char * input, int size) {
  while (strlen(input) >= size) {
    cout << "\033[31;103mInput is greater than " << size - 1 << " characters try again!\033[0m" << endl;
    cin >> input;
  }

}
void createAccount()
{
    //Writes account numbers to a txt file 
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
    //Writes account numbers to a csv file 
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
        account << "Account#,Firstname,Lastname,Address,Town,State,Zipcode,Time(EST),Date" << endl;
      }
    }

    Person * person = new Person();
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
    cout << "\033[32mAccount created successfully\033[0m" << endl;
    delete person;
    
}

bool accountChecker(int checkAccountNumber)
{
    vector<int>::iterator it;
    it = find(accountNumbers.begin(), accountNumbers.end(), checkAccountNumber);
    
    if (it != accountNumbers.end())
    {
        cout << "Account found" << endl;
        return true;
    }
    else
    {
        cout << "No accounts found"<< endl;
        cout << "Returning to menu"<< endl;
        sleep(5);
        menu();
        return false;
    }

}

void deposit()
{
   bool keyExists = false;
   int depositAccountNum;
   float depositAmount; 
   cout << "Enter a bank account number: ";
   cin >> depositAccountNum;
   if(accountChecker(depositAccountNum)==true)
   {
       //creates a directory called deposits
       if (mkdir("deposits", 0777) == -1)
        cerr << "Error: deposits directory already exists"<< endl;

    else
        cout << "Directory created" << endl;
   

        char yesNo;
        //directory/filename.txt
        string fileName = "deposits/"+encrypt(to_string(depositAccountNum))+"Deposit.txt";
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
        cout << "Enter the deposit amount: ";
        cin >> depositAmount;
        while (depositAmount < 0||depositAmount > 100000) 
        {           
            cin.clear ();    // Restore input stream to working state
            cin.ignore ( 9 , '\n' );
            cout << "Invalid input. Try again: ";
            cin >> depositAmount;
        }
        depositFile << fixed<< setprecision(2)<<depositAmount<<endl;
        cout << "Enter an other deposit for this account?"<< endl;
        cout << "Enter y for yes, n for no and return to the menu"<<endl;
        cin >> yesNo;
        while(yesNo == 'y')
        {
            cout << "Enter the deposit amount: ";
            cin >> depositAmount;
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
        //read the values stored in the text file and add them all
        readAddFiles("deposits/"+encrypt(to_string(depositAccountNum))+"Deposit.txt");
        //store the total deposit value in a map with the key value being the depositAccountNum
        map <unsigned int, float> depositMap;
        std::map<unsigned int, float>::iterator it;
        //if key doesn't exist add the key and element
        if(depositMap.find(depositAccountNum)==depositMap.end())
        {
            keyExists = false;
            depositMap.emplace(depositAccountNum,readAddFiles("deposits/"+encrypt(to_string(depositAccountNum))+"Deposit.txt"));
        }
        //if the key already exists, erase the contents and add the newest value
        else
        {
          keyExists = true;  
          cout << keyExists << endl;
        }
        cout << "map value: "<<depositMap.at(depositAccountNum)<<endl;
        menu();
    }
}
void widthdraw()
{
    bool keyExists;
    int widthdrawAccountNum;
   float widthdrawAmount; 
   cout << "Enter a bank account number: ";
   cin >> widthdrawAccountNum;
   if(accountChecker(widthdrawAccountNum)==true)
   {
       //creates a directory called deposits
       if (mkdir("widthdraws", 0777) == -1)
        cerr << "Error: widthdraws directory already exists"<< endl;

    else
        cout << "Directory created" << endl;
   

        char yesNo;
        //directory/filename.txt
        string fileName = "widthdraws/"+encrypt(to_string(widthdrawAccountNum))+"Widthdraw.txt";
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
        cout << "Enter the widthdraw amount: ";
        cin >> widthdrawAmount;
        while (widthdrawAmount < 0||widthdrawAmount > 100000) 
        {           
            cin.clear ();    // Restore input stream to working state
            cin.ignore ( 9 , '\n' );
            cout << "Invalid input. Try again: ";
            cin >> widthdrawAmount;
        }
        depositFile << fixed<< setprecision(2)<<widthdrawAmount<<endl;
        cout << "Enter an other widthdraw for this account?"<< endl;
        cout << "Enter y for yes, n for no and return to the menu"<<endl;
        cin >> yesNo;
        while(yesNo == 'y')
        {
            cout << "Enter the widthdraw amount: ";
            cin >> widthdrawAmount;
            while (widthdrawAmount < 0||widthdrawAmount > 100000) 
            {           
                cin.clear ();    // Restore input stream to working state
                cin.ignore ( 9, '\n' );
                cout << "Invalid input. Try again: ";
                cin >> widthdrawAmount;
            }
            depositFile << fixed<< setprecision(2)<<widthdrawAmount<<endl;
            cout << "Enter an other widthdraw for this account?"<< endl;
            cout << "Enter y for yes, n for no and return to the menu"<<endl;
            cin >> yesNo;
        }
        depositFile.close();
        //read the values stored in the text file and add them
        readAddFiles("widthdraws/"+encrypt(to_string(widthdrawAccountNum))+"Widthdraw.txt");      
        //store the total widthdraw value in a map with the key value being the depositAccountNum
        map <unsigned int, float> widthdrawMap;
        std::map<unsigned int, float>::iterator it;
        //if key doesn't exist add the key and element
        if(widthdrawMap.find(widthdrawAccountNum)==widthdrawMap.end())
        {
            keyExists = false;
            widthdrawMap.emplace(widthdrawAccountNum,readAddFiles("widthdraws/"+encrypt(to_string(widthdrawAccountNum))+"Widthdraw.txt"));
        }
        //if the key already exists, erase the contents and add the newest value
        else
        {
          keyExists = true;  
          cout << keyExists << endl;
        }
        cout << "map value: "<<widthdrawMap.at(widthdrawAccountNum)<<endl;  
        menu();
    }
}
void applyFee()
{
    
}

int menu() {
  int menuSelection;
  cout << "|=============================|" << endl;
  cout << "|             MENU            |" << endl;
  cout << "|=============================|" << endl;
  cout << "| 1.Create an account" << "         |" << endl;
  cout << "| 2.Show accounts" << "             |" << endl;
  cout << "| 3.Deposit" << "                   |" << endl;
  cout << "| 4.Widthdraw" << "                 |" << endl;
  cout << "| 5.Apply fee" << "             |" << endl;
  cout << "| 6.Check balance" << "                 |" << endl;
  cout << "| 7.Exit" << "                      |" << endl;
  cout << "===============================" << endl;

  cout << "Enter a menu item number: ";
  cin >> menuSelection;

  if (menuSelection == 1) 
  {
    createAccount();
    continueExit();
  } 
  else if (menuSelection == 2) 
  {
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
    widthdraw();
  } 
  else if (menuSelection == 5) 
  {
    applyFee();
  } 
  return 0;

}

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
// *Command Injection* can occur here if the user adds ; after deposit or any other transaction
int main(int argc, char ** argv) {
  time( & rawtime);
  ptm = gmtime( & rawtime);
   string tmp;
  textFile.open("accounts.txt", ios::in );
  if (!textFile) {
    cout << "No such file";
  } else {
    while (getline(textFile, tmp, '\n')) {
      try {
        cout << decrypt(tmp) << endl;         
        int num = stoi(decrypt(tmp));
        if (num >= 1000000000 && num <= INT_MAX) {
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
  }
  
  // selects type of transaction
  if (argc == 2 && strcmp(argv[1], "deposit") == 0) {
    printf("Deposit Selected\n");
    Person obj;
    //deposit();

  } else if (argc == 2 && strcmp(argv[1], "widthdraw") == 0) {
    cout << "Widthdraw Selected" << endl;
    Person obj;

  } else if (argc == 2 && strcmp(argv[1], "balance") == 0) {
    cout << "Balance Selected" << endl;
    Person obj;

  } else if (argc == 2 && strcmp(argv[1], "overdraft") == 0) {
    cout << "overdraft Selected" << endl;
    Person obj;

  } else if (argc == 3 && strcmp(argv[1], "create") == 0) {
    //createAccount();
    //generateAccountNumber();
  } else if (argc == 2 && strcmp(argv[1], "menu") == 0) {
    menu();
  } else {
    cout << "\033[36mUse ./a.out create account to create a new bank account" << endl;
    cout << "Use ./a.out delete account to delete a bank account" << endl;
    cout << "Use ./a.out deposit for a deposit" << endl;
    cout << "Use ./a.out widthdraw for a widthdraw" << endl;
    cout << "Use ./a.out balance for a balance inquiry" << endl;
    cout << "Use ./a.out fee to apply a fee" << endl;
    cout << "Use ./a.out menu to access the menu\033[0m" << endl;
  }
  return 0;
}