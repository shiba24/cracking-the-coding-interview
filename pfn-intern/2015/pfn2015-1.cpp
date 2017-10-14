#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

void PrintVector(vector<vector<float> >& data){
    cout << data.size() << " " << data[0].size() << endl;
    for (int i = 0; i < data.size(); i++){
        cout << i + 1 << " ";
        for (int j = 0; j < data[0].size(); j++)
        cout << fixed << setprecision(1) << data[i][j] << " ";
        cout << endl;
    }
}


vector<vector<float> > SubtractMean(vector<vector<float> > data){
    for (int j = 0; j < data[0].size(); j++){
        // calc
        float mean = 0.0;
        for (int i = 0; i < data.size(); i++) mean += data[i][j] / data.size();
        // subtract
        for (int i = 0; i < data.size(); i++) data[i][j] -= mean;
    }
    return data;
}


vector<vector<float> > NormalizeVariance(vector<vector<float> >& data){
    for (int j = 0; j < data[0].size(); j++){
        // calc mean
        float mean = 0.0;
        for (int i = 0; i < data.size(); i++) mean += data[i][j] / data.size();
        // calc std
        float var = 0.0;
        for (int i = 0; i < data.size(); i++) var += pow((data[i][j] - mean), 2) / data.size();
        float std = sqrt(var);
        // normalize
        for (int i = 0; i < data.size(); i++) data[i][j] /= std;
    }
    return data; 
}


vector<vector<float> > Normalize(vector<vector<float> >& data){
    for (int j = 0; j < data[0].size(); j++){
        // calc mean
        float mean = 0.0;
        for (int i = 0; i < data.size(); i++) mean += data[i][j] / data.size();
        // calc std
        float var = 0.0;
        for (int i = 0; i < data.size(); i++) var += pow((data[i][j] - mean), 2) / data.size();
        float std = sqrt(var);
        // subtract
        for (int i = 0; i < data.size(); i++) data[i][j] = (data[i][j] -= mean) / std;
    }
    return data; 
}


vector<float> GetInputVec(int n){
    vector<float> data;
    int k;
    cin >> k;
    for (int j = 0; j < n; j++){
        float input;
        cin >> input;
        data.push_back(input);
    }
    return data;
}


vector<vector<float> > GetInputMat(int n, int m){
    vector<vector<float> > data;
    for (int i = 0; i < n; i++){
        vector<float> temp = GetInputVec(m);
        data.push_back(temp);
    }
    return data;
}


int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<float> > data = GetInputMat(n, m);
    // data = SubtractMean(data);
    // data = NormalizeVariance(data);
    data = Normalize(data);
    PrintVector(data);
    return 0;
}

