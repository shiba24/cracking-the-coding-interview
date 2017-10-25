#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>


Eigen::MatrixXd SubtractMean(Eigen::MatrixXd mat){
    Eigen::MatrixXd mean = mat.colwise().mean();
    std::cout << mat.rows() << std::endl;
    for (int i = 0; i < mat.rows(); i++) mat.row(i) -= mean;
    return mat;
}

void ZCAWhitening(Eigen::Matrix2d & data){
    data = SubtractMean(data);
    Eigen::Matrix2d sigma = data * data.transpose() / data.rows();

    Eigen::JacobiSVD< Eigen::Matrix<float, 2, 3> > svd(data, Eigen::ComputeFullU | Eigen::ComputeFullV);
    // std::cout << "singular values" << std::endl << svd.singularValues() << std::endl;
    // std::cout << "matrix U" << std::endl << svd.matrixU() << std::endl;
    // std::cout << "matrix V" << std::endl << svd.matrixV() << std::endl;
}

// [U,S,V] = svd(sigma);


// MatrixXd mat(10, 4);
// for (int i = 0; i < 10; i++)
//   mat.row(i) = Eigen::VectorXd::Map(&data[i][0],data[i].size());
    
int main(){
    Eigen::MatrixXd mat(2, 3);
    mat << 1, 2, 3, 7, 8, 9;

    std::cout << mat << std::endl;
    mat = SubtractMean(mat);
    std::cout << mat << std::endl;
    // std::cout << mean << std::endl;
    return 0;
}



