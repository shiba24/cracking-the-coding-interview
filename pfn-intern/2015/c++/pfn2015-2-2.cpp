#include "pfn2015-1.h"

#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>


class MLP
{
public:
    MLP();
    ~MLP();

    void Initialize(int n_input, int n_nodes, float eta=0.1){
        int input = n_input;
        int nodes = n_nodes;
        float eta = eta;
        for (int i = 0; i < ndim; i++) W.push_back(0.0);
    }

    std::vector<std::vector<float> > InitializeW(float initial_W=0.0){
        std::vector<std::vector<float> >  W ;

        W1 = [[initial_W for i in range(self.n_input)] for i in range(self.n_nodes)]
        b1 = [initial_b for i in range(self.n_nodes)]
        W2 = [[initial_W for i in range(self.n_nodes)] for i in range(self.n_input)]
        b2 = [initial_b for i in range(self.n_input)]
    }

    std::vector<float> Initializeb(float initial_b=0.1){
        std::vector<float> b;
        for (int i = 0; i < n_nodes; i++) b.push_back(initial_b);
        return b;
    }


    float Train(std::vector<std::vector<float> > data, std::vector<int> labels){
        if (data.size() != labels.size()) throw std::invalid_argument("Missmatch dataset size");
        int error = 0;
        for (int i = 0; i < labels.size(); i++){
            if (labels[i] * I(DotProduct(W, data[i])) < 0){
                W = Add(W,  Mul(labels[i], data[i]));
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


MLP::MLP(void){std::cout << "Create perceptron." << std::endl;}
MLP::~MLP(void) {std::cout << "Complete." << std::endl;}


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



    // def __init__(self, n_input, n_nodes=5, eta=0.1):
    //     self.n_input = n_input
    //     self.n_nodes = n_nodes
    //     self.eta = eta

    // def __call__(self, x):
    //     self.x = x
    //     self.h = affine(self.x, self.W1, self.b1)
    //     self.y = affine(self.h, self.W2, self.b2)
    //     return self.y

    // def initialize_Wb(self, initial_W=0., initial_b=0.1):
    //     self.W1 = [[initial_W for i in range(self.n_input)] for i in range(self.n_nodes)]
    //     self.b1 = [initial_b for i in range(self.n_nodes)]
    //     self.W2 = [[initial_W for i in range(self.n_nodes)] for i in range(self.n_input)]
    //     self.b2 = [initial_b for i in range(self.n_input)]

    // def forward(self, x):
    //     self.loss = rms(x, self(x)) / 2.        

    // def backward(self):
    //     gy = subtract_vector(self.y, self.x)
    //     gW2 = outer(gy, self.h)
    //     gb2 = gy
    //     gh = affine(gy, transpose(self.W2), [0] * len(self.W2[0]))
    //     gW1 = outer(gh, self.x)
    //     gb1 = gh
    //     self.W2 = subtract_vector(self.W2, multiple_scalar(gW2, self.eta))
    //     self.b2 = subtract_vector(self.b2, multiple_scalar(gb2, self.eta))
    //     self.W1 = subtract_vector(self.W1, multiple_scalar(gW1, self.eta))
    //     self.b1 = subtract_vector(self.b1, multiple_scalar(gb1, self.eta))



