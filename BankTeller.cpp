#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

// terminal colors - https://man7.org/linux/man-pages/man5/terminal-colors.d.5.html
// https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c

// Function to create a menu 
void menu()
{
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
}

// Function that asks for user input for the account number, first name, last name
void getInfo(){
    /* *Buffer Overrun* can occur here if the user enters a string greater than the size of
        fName, lName, account number
    */
    char fName [15], lName[20], accountNumber[12];

    cout << "Enter the customers first name: ";
    cin >> fName;

    cout << "Enter the customers last name: ";
    cin >> lName;

    
    cout << "Enter the customers account #: ";
    cin >> accountNumber;
    
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

//command line arguments for bank transactions
// *Command Injection* can occur here if the user adds ; after deposit or any other transaction
int main(int argc, char** argv)
{
    // selects type of transaction
	if (argc == 2 && strcmp(argv[1],"deposit")==0){
        printf("Deposit Selected\n");
        getInfo();
        deposit();

    }
    else if(argc == 2 &&strcmp(argv[1],"widthdraw")==0)
    {
        cout << "Widthdraw Selected" <<endl;
        getInfo();
    }
    else if(argc == 2 &&strcmp(argv[1],"balance")==0)
    {
        cout << "Balance Selected"<<endl;
         getInfo();
    }
    else if(argc == 2 &&strcmp(argv[1],"overdraft")==0)
    {
        cout <<"overdraft Selected"<<endl;
        getInfo();
    }
    else if(argc == 2 &&strcmp(argv[1],"overdraft")==0)
    {
        getInfo();
    }
    else if(argc == 2 &&strcmp(argv[1],"menu")==0)
    {
        menu();
    }    
    else {
        cout << "\033[36mUse ./a.out deposit for a deposit" <<endl;
        cout << "Use ./a.out widthdraw for a widthdraw" <<endl;
        cout << "Use ./a.out balance for a balance inquiry" <<endl;
        cout << "Use ./a.out overdraft to apply an overdraft fee" <<endl;
        cout << "Use ./a.out menu to access the menu\033[0m"<<endl;
    }
	return 0;
}