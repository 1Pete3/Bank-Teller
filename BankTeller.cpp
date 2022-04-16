#include <cstdio>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <random>
#include <climits>
#include <string>
#include<ctime>
using namespace std;
#define EST (-4)
time_t rawtime;
struct tm * ptm;
int createAccount();
int deleteAccount();
void continueExit();
fstream account;

class Person
{
    private: 
    char fName [15], lName[20],houseNumStreetName[20],town[20],state[3],zipcode[6];

    public: 
    /* *Buffer Overrun* can occur here if the user enters a string greater than the size of
            fName, lName
        */
    string getFirstName() 
    {
        cout << "Enter the customers first name: ";
        cin >> fName;
        return fName;
    }
    string getLastName() 
    {
        cout << "Enter the customers last name: ";
        cin >> lName;
        return lName;
    }
    string getHouseNumStreet()
    {
        cout << "Enter the house number and street name : ";
        // use ignore() to clear buffer so that cin is not skipped
        cin.ignore();
        cin.getline(houseNumStreetName,20);
        return houseNumStreetName;
    }
    string getTown()
    {        
        cout << "Enter the town: ";
        cin.getline(town,20);
        return town;
    }
    string getState()
    {
        cout << "Enter the state: ";
        cin >> state;
        return state;
    }
    string getZipcode()
    {
        cout << "Enter the zipcode: ";
        cin >> zipcode;
        return zipcode;
    }

    
};
// Taken from the inclass example of generating random numbers
    unsigned int generateAccountNumber(){
    random_device r;
    seed_seq seed {r(), r(), r(), r(), r(), r(), r(), r(), r(), r()};
    mt19937 engine{seed};
            
    // range is from 1000000000 - INT_MAX
    uniform_int_distribution<> dist(1000000000, INT_MAX);
    return dist(engine);
};



// terminal colors - https://man7.org/linux/man-pages/man5/terminal-colors.d.5.html
// https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c

// Function to create a menu 
void menu()
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

    time ( &rawtime );
    ptm = gmtime ( &rawtime );
    switch(menuSelection)
    {
        case 1: 
            createAccount();
            break;
        case 2: 
            deleteAccount();
            break;
        case 3: 
            createAccount();
            break;
        case 4: 
            createAccount();
            break;
        case 5: 
            createAccount();
            break;
        case 6: 
            createAccount();
            break;
        case 7:
            cout << "Goodbye :)"<<endl;
            exit(0);
    }

}


//Creates a csv file with the account information
int createAccount()
{
    Person obj;
    account.open("account.csv", std::ios::out);
     if(!account)
   {
       cout<<"Error in creating file!!!";
       return 0;
   }
   account << "Firstname,Lastname,Account#,Address,Town,State,Zipcode,Time(EST),Date"<<endl;
   account << obj.getFirstName();
   account << ",";
   account << obj.getLastName();
   account << ",";
   account << generateAccountNumber();
   account << ",";
   account << obj.getHouseNumStreet();
   account << ",";
   account << obj.getTown();
   account << ",";
   account << obj.getState();
   account << ",";
   account << obj.getZipcode();
   account << ",";
   //Time formated in HH:MM:SS using setw to set width to 2 and fill 0 where needed
   account << setw(2) << setfill('0') << (ptm->tm_hour+EST)%24 <<":" << setw(2) << setfill('0') << ptm->tm_min<<":" << setw(2) << setfill('0') << ptm->tm_sec;
   account << ",";
   account << setw(2) << setfill('0') << (ptm->tm_mon+1)%12 <<"/" << setw(2) << setfill('0') << ptm->tm_mday<<"/" << setw(4) << setfill('0') << ptm->tm_year+1900;

   cout<<"File created successfully."<<endl;
   account.close();
   continueExit();
   return 0;
}

int deleteAccount()
{
    Person obj;
    account.open("account.csv", std::ios::out);
     if(!account)
   {
       cout<<"Error in creating file!!!";
       return 0;
   }
   account << "Firstname,Lastname,Account#,Address,Town,State,Zipcode,Time,Date"<<endl;
   account << obj.getFirstName();
   account << ",";
   account << obj.getLastName();
   account << ",";
   account << generateAccountNumber();
   account << ",";
   account << obj.getHouseNumStreet();
   account << ",";
   account << obj.getTown();
   account << ",";
   account << obj.getState();
   account << ",";
   account << obj.getZipcode();
   cout<<"File created successfully."<<endl;
   account.close();
   continueExit();
   return 0;
}



void deposit()
{
    char depositType [6];
    do{
        cout << "Is this a cash or check deposit?: ";
        // *Buffer Overrun* can occur here if the user enters a string greater than the size of depositType 
        cin >> depositType;
        if (strcmp("cash",depositType)==0) {
            cout << "Cash deposit selected" << endl;
            cout << "Amount of cash deposited: ";
            }
        else if (strcmp("check",depositType)==0)
        {
            cout << "check deposit selected" << endl;
            cout << "Amount of cash deposited: ";
        }    
        else {
            // \033 is to change the text color, [31 - red text, 103m - yellow background for linux
            // \033[0m is to reset the text color/background             
            cout << "\033[31;103mIncorrect Input enter cash or check\033[0m" << endl;
        }
            
    }
    while((strcmp("cash",depositType)!=0)&&(strcmp("check",depositType)!=0));
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
        deposit();

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
        createAccount();
        generateAccountNumber();
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