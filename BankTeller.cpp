#include<bits/stdc++.h>
#include <cctype>
#include <cstdio>
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
#include <ctime>
#include <cctype>
#include <thread>
#include <unistd.h>
#define EST (-4)
using namespace std;
int NumberofAccounts=1;
int userInput;
fstream account;
void continueExit();
void checkInputSize(char* input,int size );


vector< unsigned int> accountNumbers;
time_t rawtime;
struct tm * ptm;
class Person
{
    private:
    const static int size = 21;
    char fName [size],lName[size],state[3],zipcode[6];
    string houseNumStreetName,town;
    public:
    unsigned int accountNumber;
    Person()
    {
    } 

    ~Person()
    {
    }

    unsigned int generateAccountNumber()
    {
        random_device r;
        seed_seq seed {r(), r(), r(), r(), r(), r(), r(), r(), r(), r()};
        mt19937 engine{seed};
        // range is from 1000000000 - INT_MAX
        uniform_int_distribution<> dist(1000000000, INT_MAX);
        accountNumber = dist(engine);  
        for(int i = 0; i < accountNumbers.size();i++)
        {
            if(accountNumbers[i]==accountNumber)
            {                
                generateAccountNumber();
                cout << "same account num generating new one"<<endl;
            }
            else if(NumberofAccounts == (INT_MAX-1000000000 + 1))
            {
                cout<<"Max accounts created"<<endl;
                exit(0);
            }
        }
        return accountNumber;
    }
    string getFirstName() 
    {
        cout << "Enter the customers first name: ";
        cin >> fName;    
        checkInputSize(fName, size);  
        return fName;
    }

    string getLastName() 
    {
        cout << "Enter the customers last name: ";
        cin >> lName;
        checkInputSize(fName, size);         
        return lName;
    }
    string getHouseNumStreet()
    {
        cout << "Enter the house number and street name : ";
        // use ignore() so that cin is not skipped
        cin.ignore();
        getline(cin,houseNumStreetName);
        return houseNumStreetName;
    }
    string getTown()
    {        
        cout << "Enter the town: ";
        getline(cin,town);
        return town;
    }
    string getState()
    {
        cout << "Enter the state (2 letter abbrivation): ";
        cin >> state;
        checkInputSize(state, 3);
        // Capitalizes the state entered
        for(int i = 0; i < strlen(state);i++)
        {
           state[i] = toupper(state[i]);
        }
        
        return state;
    }
    string getZipcode()
    {
        cout << "Enter the zipcode: ";
        cin >> zipcode;
        checkInputSize(zipcode, 6);
        return zipcode;
    }
};

// Checks for buffer over flow 
void checkInputSize(char* input,int size )
    {
        while(strlen(input) >= size )
        {
            cout << "\033[31;103mInput is greater than " <<  size-1 << " characters try again!\033[0m" << endl;
            cin >> input;
        }

    }


 

int menu() 
{
    int menuSelection;
    cout<<"|=============================|"<< endl;
    cout<<"|             MENU            |"<< endl;
    cout<<"|=============================|"<< endl;
    cout<<"| 1.Create an account"<<"         |"<< endl;
    cout<<"| 2.Delete an account"<<"         |"<< endl;
    cout<<"| 3.Deposit"<<"                   |"<< endl;
    cout<<"| 4.Widthdraw"<<"                 |"<< endl;
    cout<<"| 5.Check balance"<<"             |"<< endl;
    cout<<"| 6.Apply fee"<<"                 |"<< endl;
    cout<<"| 7.Exit"<<"                      |"<< endl;
    cout<<"==============================="<< endl;
    
    cout << "Enter a menu item number: ";
    cin >> menuSelection;

    
    if(menuSelection == 1)
    {
        account.open("account.csv");
        time ( &rawtime );
        ptm = gmtime ( &rawtime );
            if(account)
            {
                cout << "File account.csv exits, appending to it" << endl;          
                account.close();
                account.open("account.csv",std::ios::app);
            }
            else 
            {
                cout << "Creating file account.csv" << endl;
                account.open("account.csv", std::ios::out);
                if(!account)
                {
                    cout<<"Error in creating file!!!";
                    return 0;
                }
                else 
                {
                    account << "Account#,Firstname,Lastname,Address,Town,State,Zipcode,Time(EST),Date"<<endl;
                }   
            } 

        Person* person = new Person();
        person->generateAccountNumber();
        accountNumbers.push_back(person->accountNumber);
        cout << person->accountNumber <<endl;
        account << person->accountNumber;
        account << ",";
        account << person->getFirstName();
        account << ",";
        account << person->getLastName();
        account << ",";
        account << person->getHouseNumStreet();
        account << ",";
        account << person->getTown();
        account << ",";
        account << person->getState();
        account << ",";
        account << person->getZipcode();
        account << ",";
        //Time formated in HH:MM:SS using setw to set width to 2 and fill 0 where needed
        account << setw(2) << setfill('0') << ((ptm->tm_hour+EST)%24+24)%24 <<":" << setw(2) << setfill('0') << ptm->tm_min<<":" << setw(2) << setfill('0') << ptm->tm_sec;
        account << ",";
        account << setw(2) << setfill('0') << (ptm->tm_mon+1)%12 <<"/" << setw(2) << setfill('0') << ptm->tm_mday<<"/" << setw(4) << setfill('0') << ptm->tm_year+1900 ;
        account << "\n";
        account.close();
        cout<<NumberofAccounts++;
        cout << "\033[32mAccount created successfully\033[0m" << endl;
        delete person; 
        continueExit();
    }
    else if (menuSelection == 3) {
        string depositAccountNum;
        int depositOption;
        cout << "Enter a bank account number: ";
        cin >> depositAccountNum;
        if(accountNumbers.empty()==true)
        {
            cout << "No accounts have been created yet" << endl;
            cout << "heading back to the menu" << endl;
            sleep(5);
            menu();
        }
        else
        {
            for(int i=0;i<accountNumbers.size();i++)
            {
                if(depositAccountNum==std::to_string(accountNumbers[i]))
                {
                    cout << "Account found" << endl;
                    cout << "Press 1 for cash deposit or 2 for check deposit: ";
                    cin >> depositOption;
                    if(depositOption == 1)
                    {
                        cout << "Cash deposit selected" << endl;
                    }
                    else if (depositOption == 2)
                    {
                        cout << "Cash deposit selected" << endl;
                    }
                }
                else 
                {
                    cout << "Account not found try again" << endl;
                }            
            }
        }
        
    }
  return 0;
}

void continueExit()
{
    int continueSelection;
    cout << "\nPress 1 to return to the menu" << endl;
    cout << "Press 2 to exit"<< endl;
    cin >> continueSelection;
    if(continueSelection == 1)
        menu();
    else
        cout << "Goodbye :)\n"<<endl; 
        exit(0);
}

//command line arguments for bank transactions
// *Command Injection* can occur here if the user adds ; after deposit or any other transaction
int main(int argc, char** argv)
{
    // selects type of transaction
	if (argc == 2 && strcmp(argv[1],"deposit")==0){
        printf("Deposit Selected\n");
        Person obj;
        //deposit();

    }
    else if(argc == 2 &&strcmp(argv[1],"widthdraw")==0)
    {
        cout << "Widthdraw Selected" <<endl;
        Person obj;
   
    }
    else if(argc == 2 &&strcmp(argv[1],"balance")==0)
    {
        cout << "Balance Selected"<<endl;
        Person obj;
    
    }
    else if(argc == 2 &&strcmp(argv[1],"overdraft")==0)
    {
        cout <<"overdraft Selected"<<endl;
        Person obj;
        
    }
    else if(argc == 3&&strcmp(argv[1],"create")==0)
    {
        //createAccount();
        //generateAccountNumber();
    }
    else if(argc == 2 &&strcmp(argv[1],"delete account")==0)
    {
        Person obj;
    }
    else if(argc == 2 &&strcmp(argv[1],"menu")==0)
    {
        menu();
    }    
    else {
        cout << "\033[36mUse ./a.out create account to create a new bank account" <<endl;
        cout << "Use ./a.out delete account to delete a bank account" <<endl;
        cout << "Use ./a.out deposit for a deposit" <<endl;
        cout << "Use ./a.out widthdraw for a widthdraw" <<endl;
        cout << "Use ./a.out balance for a balance inquiry" <<endl;
        cout << "Use ./a.out fee to apply a fee" <<endl;
        cout << "Use ./a.out menu to access the menu\033[0m"<<endl;
    }
	return 0;
}