#include "bigint.h"
#include <iostream>
using namespace std;

BigInt::BigInt(string Number) {
    if(Number == "" || Number == "-") {throw invalid_argument("No number given");}

    if(Number[0] == '-') {
        this->is_negative = true;
        Number.erase(0,1);
    }

    unsigned long long i = 0;
    while(Number[i] == '0') {
        i++;
    }
    Number.erase(0,i);

    if(Number.empty()) {
        Number.push_back('0');
        this->is_negative = false;
    }

    for(unsigned long long i = Number.size(); i >= 1; i--) {
        if(isdigit(Number[i - 1])){
            this->digits.push_back(Number[i - 1]);
        } else {
            throw invalid_argument("Provided number contains non-digit symbol");
        }
    }
}

string BigInt::getNumber() {
    string number;
    if(this->is_negative){
        number.push_back('-');
    }

    for(unsigned long long i = this->digits.size(); i >= 1; i--) {
        number.push_back(this->digits[i - 1]);
    }
    return number;
}

vector<char> BigInt::getSum(vector<char> num1, vector<char> num2) {
    if(num1.size() < num2.size()) {swap(num1, num2);}

    bool shift_digit = false;
    char digit;

    for(unsigned long long i = 0; i < num2.size(); i++) {
        digit = num1[i] + num2[i] - '0';
        if(shift_digit) {
            digit++;
            shift_digit = false;
        }
        if(!isdigit(digit)) {
            digit -= 10;
            shift_digit = true;
        }
        num1[i] = digit;
    }
    for(unsigned long long i = num2.size(); i < num1.size(); i++) {
        if(shift_digit) {
            num1[i]++;
            shift_digit = false;
        }
        if(!isdigit(num1[i])) {
            num1[i] -= 10;
            shift_digit = true;
        }
    }
    if(shift_digit){num1.push_back('1');}

    return num1;
}

vector<char> BigInt::getDiff(vector<char> num1, vector<char> num2) {
    if(num1.size() < num2.size()) {
        swap(num1, num2);
    } else {
        if(num1.size() == num2.size())
            for(unsigned long long i = num1.size(); i >= 1; i--) {
                if(num1[i - 1] < num2[i - 1]) {
                    swap(num1, num2);
                    break;
                }
                if(num1[i - 1] > num2[i - 1]) {
                    break;
                }
            }
    }
    bool shift_digit = false;
    char digit;
    for(unsigned long long i = 0; i < num2.size(); i++) {
        digit = num1[i] - num2[i] + '0';
        if(shift_digit) {
            digit--;
            shift_digit = false;
        }
        if(!isdigit(digit)) {
            digit += 10;
            shift_digit = true;
        }
        num1[i] = digit;
    }
    for(unsigned long long i = num2.size(); i < num1.size(); i++) {
        if(shift_digit) {
            num1[i]--;
            shift_digit = false;
        }
        if(!isdigit(num1[i])) {
            num1[i] += 10;
            shift_digit = true;
        }
    }
    if(shift_digit) {
        num1[-1]--;
        if(num1[-1] == '0') {num1.pop_back();}
    }
    return num1;
}


BigInt operator+(BigInt& x, BigInt& y) {
    string sum_string;

    if((x.is_negative && y.is_negative) || (!x.is_negative && !y.is_negative)) {

        vector<char> sum_char = BigInt::getSum(x.digits, y.digits);
        if(x.is_negative && y.is_negative) {sum_string.push_back('-');}
        for(unsigned long long i = sum_char.size(); i >= 1; i--) {
            sum_string.push_back(sum_char[i - 1]);
        }

    } else {

        vector<char> diff_char = BigInt::getDiff(x.digits, y.digits);
        if((x.digits.size() > y.digits.size() && x.is_negative) || (y.digits.size() > x.digits.size() && y.is_negative)) {
            sum_string.push_back('-');
        } else {
            if(x.digits.size() == y.digits.size()) {
                for(unsigned long long i = x.digits.size(); i >= 1; i--) {
                    if((x.digits[i - 1] > y.digits[i - 1] && x.is_negative) || (y.digits[i - 1] > x.digits[i - 1] && y.is_negative)) {
                        sum_string.push_back('-');
                        break;
                    }
                    if((x.digits[i - 1] < y.digits[i - 1] && x.is_negative) || (y.digits[i - 1] < x.digits[i - 1] && y.is_negative)) {
                        break;
                    }
                }
            }
        }

        for(unsigned long long i = diff_char.size(); i >= 1; i--) {
            sum_string.push_back(diff_char[i - 1]);
        }
    }

    return BigInt(sum_string);
}

BigInt operator-(BigInt& x, BigInt& y) {
    y.is_negative = !y.is_negative;
    return x + y;
}

