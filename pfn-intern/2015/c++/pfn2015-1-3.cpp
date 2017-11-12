#include "pfn2015-1.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <tuple>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <vector>
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
    for (int i = 0; i < arr1.size(); i++) sum.push_back(arr1[i] + arr2[i]);
    return sum;
}


class Perceptron
{
public:
    std::vector<float> W;
    Perceptron();
    ~Perceptron();

    void Initialize(int ndim){for (int i = 0; i < ndim; i++) W.push_back(0.0);}

    void Update(int label, std::vector<float> data){
        W = Add(W,  Mul(label, data));
    }

    float Train(std::vector<std::vector<float> > data, std::vector<int> labels){
        if (data.size() != labels.size()) throw std::invalid_argument("Missmatch dataset size");
        int error = 0;
        for (int i = 0; i < labels.size(); i++){
            if (labels[i] * I(DotProduct(W, data[i])) < 0){
                Update(labels[i], data[i]);
                error += 1;
            }
        }
        return 1.0 - float(error) / float(labels.size());
    }

    float Test(std::vector<std::vector<float> > data, std::vector<int> labels){
        if (data.size() != labels.size()) throw std::invalid_argument("Missmatch dataset size");
        int error = 0;
        for (int i = 0; i < labels.size(); i++){
            if (labels[i] * I(DotProduct(W, data[i])) < 0){
                error += 1;
            }
        }
        return 1.0 - float(error) / float(labels.size());
    }

    float CrossValidate(int num_iterations, const std::vector<std::vector<float> >& data, const std::vector<int>& labels){
        float n_fold = 5.0;
        for (int iter = 0; iter < num_iterations; iter++){
            float train_acc = 0.0;
            float test_acc = 0.0;
            for (int i = 0; i < int(n_fold); i++){
                std::tuple<std::vector<std::vector<float> >, std::vector<int>, 
                std::vector<std::vector<float> >, std::vector<int> > t = SplitData(1.0 / n_fold, data, labels);

                std::vector<std::vector<float> >& X_train = std::get<0>(t);
                std::vector<int>& y_train = std::get<1>(t);
                std::vector<std::vector<float> >& X_test = std::get<2>(t);
                std::vector<int>& y_test = std::get<3>(t);

                train_acc += Train(X_train, y_train) / n_fold;
                test_acc += Test(X_test, y_test) / n_fold;
            };
            std::cout << "Iteration " << iter << ", Train accuracy: " << std::fixed << std::setprecision(2) << train_acc << 
            ", Test accuracy: " << std::fixed << std::setprecision(2) << test_acc << std::endl;
        }
        return 0.0;
    }


    std::tuple<std::vector<std::vector<float> >, std::vector<int>, 
    std::vector<std::vector<float> >, std::vector<int> > SplitData(float test_ratio,
        const std::vector<std::vector<float> >& data, const std::vector<int>& labels){

        // randomize index
        std::vector<int> indexes;
        indexes.reserve(data.size());
        for (int i = 0; i < data.size(); ++i) indexes.push_back(i);
        std::random_shuffle(indexes.begin(), indexes.end());

        // Create all shuffled arrays
        std::vector<std::vector<float> > X_train;
        std::vector<int> y_train;
        for (std::vector<int>::iterator it1 = indexes.begin(); it1 != indexes.end(); ++it1 ){
            X_train.push_back(data[*it1]);
            y_train.push_back(labels[*it1]);
        }

        // Pick up test, and create train and test arrays
        std::vector<std::vector<float> > X_test;
        std::vector<int> y_test;
        for (int i = 0; i < data.size() * test_ratio; i++){
            std::vector<float> _X = X_train.back();
            X_train.pop_back();
            X_test.push_back(_X);

            int _y = y_train.back();
            y_train.pop_back();            
            y_test.push_back(_y);

        }
        // Return tuple
        std::tuple<std::vector<std::vector<float> >, std::vector<int>, 
        std::vector<std::vector<float> >, std::vector<int> > t = std::make_tuple(X_train, y_train, X_test, y_test);
        return t;
    }


    void Iterate(int num_iter, std::vector<std::vector<float> > data, std::vector<int> labels){
        for (int i = 0; i < num_iter; i++){
            float acc = Train(data, labels);
            std::cout << "Iteration " << i << ", accuracy = " << std::fixed << std::setprecision(2) << acc << std::endl;
        }
    }
};

Perceptron::Perceptron(void){std::cout << "Create perceptron." << std::endl;}
Perceptron::~Perceptron(void) {std::cout << "Complete." << std::endl;}


int main(){
    try  
    {  
        std::string fname = "../data/train.txt";
        std::tuple<std::vector<std::vector<float> >, std::vector<int> > t;
        t = pfn15::InputFileLine(fname);

        std::vector<std::vector<float> >& data = std::get<0>(t);
        std::vector<int>& labels = std::get<1>(t);

        Perceptron p;
        p.Initialize(data[0].size());
        data = pfn15::NormalizeMat(data);
        labels = pfn15::NormalizeVec(labels);

        int num_iter = 10;
        p.CrossValidate(num_iter, data, labels);
        // p.Iterate(num_iter, data, labels);
    }  
    catch(std::invalid_argument& e)  
    {  
      return -1;  
    }  
    return 0;
}
