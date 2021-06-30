#include <iostream>
#include <string>
#include <vector>
#include "calc.hpp"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    char op;
    TLongNumbers num1;
    TLongNumbers num2;
    while (cin >> num1 >> num2 >> op) {
        if (op == '+') {
            cout << num1 + num2 << "\n";
        } else if (op == '-') {
            if (num2 > num1) {
                cout << "Error\n";
            } else {
                cout << num1 - num2 << "\n";
            }
        } else if (op == '>') {
            if (num1 > num2) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        } else if (op == '<') {
            if (num1 < num2) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        } else if (op == '=') {
            if (num1 == num2) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        } else if (op == '*') {
            cout << num1 * num2 << "\n";
        } else if (op == '/') {
            if (num2.Null()) {
                cout << "Error\n";
            } else {
                cout << num1 / num2 << "\n";
            }
        } else if (op == '^') {
            if (num2.Null() && num1.Null()) {
                cout << "Error\n";
            } else {
                cout << (num1 ^ num2) << "\n";
            }
        }
    }
    return 0;
}