#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <cmath>
#include <stdexcept>

using namespace std;


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

void CheckDim(const vector<vector<float> >& data, cosnt vector<int>& labels){
    if (data.size() != labels.size()) throw invalid_argument("Missmatch dataset size");
}

float DotProduct(vector<float> arr1, vector<float> arr2){
    CheckDim(arr1, arr2);
    float dot = 0.0
    for (int i = 0; i < arr1.size(); i++) float += arr1[i] * arr2[i];
}

float I(float d){
    if (d >= 0) return 1.0;
    else return -1.0;
}


vector<float> Mul(float factor, vector<float> array){
    vector<float> mul;
    for (int i = 0; i < array.size(); i++) mul.push_back(factor * array[i]);
    return mul;
}


class Perceptron
{
public:
    vector<float> W;
    Perceptron();
    ~Perceptron();

    void Initialize(int ndim) for (int i = 0; i < ndim; i++) W.push_back(0.0);


    float Learn(const vector<vector<float> >& data, cosnt vector<int>& labels){
        CheckDim(data, labels)
        int error = 0;
        for (int i = 0; i < labels.size(); i++){
            if (labels[i] * I(DotProduct(W, data[i])) < 0){
                W = W + Mul(label[i], data[i]);
                error += 1;
            }
        }
        return 1.0 - float(error) / float(labels.size())
    }

};

Perceptron::Perceptron(void) cout << "Create perceptron." << endl;
// Perceptron::~Perceptron(void) {};


float CrossValidate(int num_iterations, const vector<vector<float> >& data, 
    cosnt vector<int>& labels){

}


int main(){

    vector<vector<float> > data;
    X = GetInput(n, m);
    y = GetInput(n);

    data = Normalize(data);
    PrintVector(data);



   try  
   {  
   }  
   catch(invalid_argument& e)  
   {  
      return -1;  
   }  
   //...  
    return 0;
}


