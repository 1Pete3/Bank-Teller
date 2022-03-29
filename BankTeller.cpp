// Hello GOOGLE


#include <iostream>
#include<string.h>
using namespace std;

//command line arguments for bank transaction
int main(int argc, char** argv)
{
    // selects type of transaction
	if (argc == 2 && strcmp(argv[1],"deposit")==0){
        printf("Deposit Selected\n");
    }
    else if(argc == 2 &&strcmp(argv[1],"widthdraw")==0)
    {
        printf("Widthdraw Selected\n");
    }
    else if(argc == 2 &&strcmp(argv[1],"balance")==0)
    {
        printf("Balance Selected\n");
    }
    else if(argc == 2 &&strcmp(argv[1],"overdraft")==0)
    {
        printf("overdraft Selected\n");
    }
	return 0;
}
