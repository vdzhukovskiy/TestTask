#include <iostream>
#include <bigint.h>

using namespace std;

int main(int argc, char*argv[])
{
    if(argc <= 2) {return 0;}

    string number_1 = argv[1];
    string number_2 = argv[2];
    try {
        BigInt first_number = number_1;
        BigInt second_number = number_2;
        BigInt sum = first_number + second_number;
        cout << "Sum is:        " << sum.getNumber() << endl;
        BigInt diff = first_number - second_number;
        cout << "Difference is: " << diff.getNumber() << endl;

    } catch (invalid_argument &e) {
        cout <<"Exception: " << e.what() << endl;
    }

    return 0;
}
