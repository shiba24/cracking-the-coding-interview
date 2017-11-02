#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>


Eigen::MatrixXd SubtractMean(Eigen::MatrixXd mat){
    Eigen::MatrixXd mean = mat.colwise().mean();
    std::cout << mat.rows() << std::endl;
    for (int i = 0; i < mat.rows(); i++) mat.row(i) -= mean;
    return mat;
}

void ZCAWhitening(Eigen::MatrixXd &data){
    // data = SubtractMean(data);
    Eigen::Matrix2d sigma = data * data.transpose() / data.rows();
    Eigen::JacobiSVD< Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> > svd(sigma, Eigen::ComputeFullU | Eigen::ComputeFullV);

    Eigen::VectorXd s = svd.singularValues();
    // U: [M x M] eigenvectors of sigma, S: [M x 1] eigenvalues of sigma, V: [M x M] transpose of U

    double epsilon = 0.00001;
    int n = s.size();
    Eigen::VectorXd tmp = 1.0 / (s + epsilon * Eigen::VectorXd::Ones(n)).array().sqrt();
    Eigen::MatrixXd zca = svd.matrixU() * (tmp.asDiagonal() * svd.matrixU().transpose());

    data = zca * data;
    // std::cout << "singular values" << std::endl << s << std::endl;
    // std::cout << "matrix U" << std::endl << svd.matrixU() << std::endl;
    // std::cout << "matrix V" << std::endl << svd.matrixV() << std::endl;
    // std::cout << zca << std::endl;
}


int main(){
    Eigen::MatrixXd mat(2, 3);
    mat << 1, 2, 3, 7, 8, 9;

    std::cout << mat << std::endl;
    ZCAWhitening(mat);
    std::cout << mat << std::endl;
    return 0;
}

