#include "pfn2015-1.h"

#include <iostream>
#include <vector>


std::vector<std::vector<float> > SubtractMean(std::vector<std::vector<float> > data){
    for (int j = 0; j < data[0].size(); j++){
        // calc
        float mean = 0.0;
        for (int i = 0; i < data.size(); i++) mean += data[i][j] / data.size();
        // subtract
        for (int i = 0; i < data.size(); i++) data[i][j] -= mean;
    }
    return data;
}


std::vector<std::vector<float> > NormalizeVariance(std::vector<std::vector<float> >& data){
    for (int j = 0; j < data[0].size(); j++){
        // calc mean
        float mean = 0.0;
        for (int i = 0; i < data.size(); i++) mean += data[i][j] / data.size();
        // calc std
        float var = 0.0;
        for (int i = 0; i < data.size(); i++) var += pow((data[i][j] - mean), 2) / data.size();
        float sd = sqrt(var);
        // normalize
        for (int i = 0; i < data.size(); i++) data[i][j] /= sd;
    }
    return data; 
}


int main(){
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<float> > data = pfn15::GetInputMat(n, m);
    // data = SubtractMean(data);
    // data = NormalizeVariance(data);
    pfn15::Normalize(data);
    pfn15::PrintVector(data);
    return 0;
}

