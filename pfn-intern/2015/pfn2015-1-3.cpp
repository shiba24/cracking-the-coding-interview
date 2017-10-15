#include "pfn2015-1.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <tuple>
#include <string>

#include <vector>
#include <numeric>
#include <cmath>
#include <stdexcept>


float DotProduct(std::vector<float> arr1, std::vector<float> arr2){
    if (arr1.size() != arr2.size()) throw std::invalid_argument("Missmatch dataset size");
    float dot = 0.0;
    for (int i = 0; i < arr1.size(); i++) dot += arr1[i] * arr2[i];
    return dot;
}

float I(float d){
    if (d >= 0) return 1.0;
    else return -1.0;
}

std::vector<float> Mul(float factor, std::vector<float> array){
    std::vector<float> mul;
    for (int i = 0; i < array.size(); i++) mul.push_back(factor * array[i]);
    return mul;
}


std::vector<float> Add(std::vector<float> arr1, std::vector<float> arr2){
    std::vector<float> sum;
    for (int i = 0; i < arr1.size(); i++) sum.push_back(arr1[i] * arr2[i]);
    return sum;
}


class Perceptron
{
// private:
//     Perceptron(void) std::cout << "Create perceptron." << std::endl;
public:
    std::vector<float> W;
    // Perceptron();
    // ~Perceptron();

    void Initialize(int ndim){for (int i = 0; i < ndim; i++) W.push_back(0.0);}

    float Learn(std::vector<std::vector<float> > data, std::vector<int> labels){
        if (data.size() != labels.size()) throw std::invalid_argument("Missmatch dataset size");
        int error = 0;
        for (int i = 0; i < labels.size(); i++){
            // std::cout << "label: " << labels[i] << ", " << I(DotProduct(W, data[i])) << std::endl;
            if (labels[i] * I(DotProduct(W, data[i])) < 0){
                W = Add(W,  Mul(labels[i], data[i]));
                error += 1;
            }
        }
        return 1.0 - float(error) / float(labels.size());
    };

    void Iterate(int num_iter, std::vector<std::vector<float> > data, std::vector<int> labels){
        for (int i = 0; i < num_iter; i++){
            float acc = Learn(data, labels);
            std::cout << "Iteration " << i << ", accuracy = " << std::fixed << std::setprecision(2) << acc << std::endl;
        }
    }
};

// Perceptron::Perceptron(void) std::cout << "Create perceptron." << std::endl;

// Perceptron::~Perceptron(void) {};
// float CrossValidate(int num_iterations, const vector<vector<float> >& data, 
//     cosnt vector<int>& labels){
// }




int main(){
    std::string fname = "./data/train.txt";
    std::tuple<std::vector<std::vector<float> >, std::vector<int> > t;
    t = pfn15::InputFileLine(fname);

    std::vector<std::vector<float> >& data = std::get<0>(t);
    std::vector<int>& labels = std::get<1>(t);

    Perceptron p;
    p.Initialize(data[0].size());

    data = pfn15::NormalizeMat(data);

    // std::vector<float> y;
    labels = pfn15::NormalizeVec(labels);
    // std::cout << labels[0] << std::endl;

    int num_iter = 5;
    p.Iterate(num_iter, data, labels);
    // float acc = p.Learn(data, labels);
    // std::cout << acc << std::endl;

   // try  
   // {  
   // }  
   // catch(invalid_argument& e)  
   // {  
   //    return -1;  
   // }  
    return 0;
}


// void CheckDim(std::vector<std::vector<float> >& data, std::vector<float>& labels){
//     if (data.size() != labels.size()) throw std::invalid_argument("Missmatch dataset size");
// }




