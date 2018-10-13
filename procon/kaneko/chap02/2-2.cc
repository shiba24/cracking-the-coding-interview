#include <iostream>
// #include <algorithm>
// #include <vector>
// #include <numeric>

using namespace std;

int main(){
    int n;

    while (1){
        cin >> n;
        if (n == 0) break;
        int sum = 0;
        int M = 0;
        int m = 0;
        int i;

        for (int i=0; i<n; i++){
            cin >> i;
            sum += i;
            if (i == max(i, M)) M = i;
            if (i == min(i, m)) m = i;
        }
        float ans = (sum - M - m) / (n - 2);

        cout << ans << endl;
    }

    // int endzero;
    // cin >> endzero;
}






