#ifndef BIGINT_H
#define BIGINT_H
#include <vector>
#include <string>

using namespace std;


class BigInt
{
public:
    BigInt(string Number);
    string getNumber();

    friend BigInt operator+(BigInt& x, BigInt& y);
    friend BigInt operator-(BigInt& x, BigInt& y);

private:
    vector<char> digits;
    bool is_negative = false;

    static vector<char> getSum(vector<char> num1, vector<char> num2);
    static vector<char> getDiff(vector<char> num1, vector<char> num2);

};

#endif // BIGINT_H
