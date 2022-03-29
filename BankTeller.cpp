#include <iostream>
#include<string.h>
using namespace std;

// Function that asks for user input for the account number, first name, last name
void getInfo(){
    char fName [15], lname[20];
    cout << "Enter the customners first name: ";
    cin >> fName;

    cout << "Enter the customners last name: ";
    cin >> fName;
    
}

//command line arguments for bank transaction
int main(int argc, char** argv)
{
    // selects type of transaction
	if (argc == 2 && strcmp(argv[1],"deposit")==0){
        printf("Deposit Selected\n");
        getInfo();
    }
    else if(argc == 2 &&strcmp(argv[1],"widthdraw")==0)
    {
        printf("Widthdraw Selected\n");
        getInfo();
    }
    else if(argc == 2 &&strcmp(argv[1],"balance")==0)
    {
        printf("Balance Selected\n");
         getInfo();
    }
    else if(argc == 2 &&strcmp(argv[1],"overdraft")==0)
    {
        printf("overdraft Selected\n");
        getInfo();
    }
	return 0;
}
