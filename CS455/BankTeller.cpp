#include <iostream>
#include<string.h>
using namespace std;
//test
// Function that asks for user input for the account number, first name, last name
void getInfo(){
    char fName [15], lName[20], accountNumber[12];

    cout << "Enter the customers first name: ";
    cin >> fName;

    cout << "Enter the customers last name: ";
    cin >> lName;

    // can change this to int to show vulnerability if account number > max int value etc..
    cout << "Enter the customers account #: ";
    cin >> accountNumber;
    
}

void deposit()
{
    char depositType [6];
    do{
        cout << "Is this a cash or check deposit?: ";
        cin >> depositType;
        if (strcmp("cash",depositType)==0) {
            cout << "cash deposit" << endl;
            }
        else if (strcmp("check",depositType)==0)
        {
            cout << "check deposit" << endl;
        }    
        else {
            cout << "Incorrect Input enter cash or check" << endl;
        }
            
    }
    while((strcmp("cash",depositType)!=0)&&(strcmp("check",depositType)!=0));
    
    
}

//command line arguments for bank transaction
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
    else {
    cout << "Use ./a.out deposit for a deposit" <<endl;
    cout << "Use ./a.out widthdraw for a widthdraw" <<endl;
    cout << "Use ./a.out balance for a balance inquiry" <<endl;
    cout << "Use ./a.out overdraft to apply an overdraft fee" <<endl;
    }
	return 0;
}