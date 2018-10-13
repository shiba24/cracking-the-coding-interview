#include <iostream>
using namespace std;

int main(){
    int A[4] = {0, 1, 2, 3, };
    for (int i=0; i<4; i++)
        cout << A[i] << endl;
}


int main() {
    int A[4] = {0, 1, 2, 3, };
    int i = 0;
    while (i<4 && A[i] != 2){
        cout << A[i] << endl;
        i++;
    }
}


double pi() {return 3.14; }
int main() {
    cout << 3.14 << endl;
    cout << pi() << endl;
}


int sum(int a, int b){return a + b; }
int main() {
    cout << 3+5 << endl;
    cout << sum(3, 5) << endl;
}
