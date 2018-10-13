#include <iostream> 
using namespace std; 
int main() {
    int year;
    while (cin >> year) { // cinはboolに自動変換されるので入力が読める限り ループ
        if (year % 4 == 0)
            cout << 366 << endl;
        else
            cout << 365 << endl;
    } 
}
