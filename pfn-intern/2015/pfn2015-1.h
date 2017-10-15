#ifndef pfn2015_1
#define pfn2015_1

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <tuple>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>


namespace pfn15{
    void PrintVector(std::vector<std::vector<float> >& data){
        std::cout << data.size() << " " << data[0].size() << std::endl;
        for (int i = 0; i < data.size(); i++){
            std::cout << i + 1 << " ";
            for (int j = 0; j < data[0].size(); j++)
            std::cout << std::fixed << std::setprecision(1) << data[i][j] << " ";
            std::cout << std::endl;
        }
    };

    std::vector<float> GetInputVec(int n){
        std::vector<float> data;
        int k;
        std::cin >> k;
        for (int j = 0; j < n; j++){
            float input;
            std::cin >> input;
            data.push_back(input);
        }
        return data;
    };

    std::vector<std::vector<float> > GetInputMat(int n, int m){
        std::vector<std::vector<float> > data;
        for (int i = 0; i < n; i++){
            std::vector<float> temp = GetInputVec(m);
            data.push_back(temp);
        }
        return data;
    };

    std::tuple<std::vector<std::vector<float> >, std::vector<int> > InputFileLine(std::string filename){
        std::string line;
        std::ifstream infile(filename);

        // get size
        int n, m;
        std::getline(infile, line);
        std::istringstream iss(line);
        iss >> n >> m;

        // get X and y
        std::vector<std::vector<float> > X;
        std::vector<int> y;
        for (int i = 0; i < n; i++){
            std::getline(infile, line);
            std::istringstream iss(line);
            int _a;
            iss >> _a;
            y.push_back(_a);
            std::vector<float> temp;
            for (int j = 0; j < m; j++){
                float _b;
                iss >> _b;
                temp.push_back(_b);
            };
            X.push_back(temp);
        };
        std::tuple<std::vector<std::vector<float> >, std::vector<int> > t = std::make_tuple(X, y);
        return t;
    };


    std::vector<int> NormalizeVec(std::vector<int>& data){
        // calc mean and std
        // float mean = 0.0;
        // float var = 0.0;
        // for (int i = 0; i < data.size(); i++) mean += static_cast<float>(data[i]) / data.size();
        // for (int i = 0; i < data.size(); i++) var += pow(static_cast<float>((data[i]) - mean), 2) / data.size();
        // float sd = sqrt(var);
        // // normalize
        // // std::vector<float> std_vec;
        // for (int i = 0; i < data.size(); i++) data[i] = static_cast<int>((static_cast<float>(data[i]) - mean) / sd);

        for (int i = 0; i < data.size(); i++) data[i] = (data[i] - 1.5)  * 2;
        return data; 
    };

    std::vector<std::vector<float> > NormalizeMat(std::vector<std::vector<float> >& data){
        for (int j = 0; j < data[0].size(); j++){
            // calc mean
            float mean = 0.0;
            for (int i = 0; i < data.size(); i++) mean += data[i][j] / data.size();
            // calc std
            float var = 0.0;
            for (int i = 0; i < data.size(); i++) var += pow((data[i][j] - mean), 2) / data.size();
            float sd = sqrt(var);
            // subtract
            for (int i = 0; i < data.size(); i++) data[i][j] = (data[i][j] - mean) / sd;
        }
        return data; 
    };
}

#endif  // pfn2015_1
