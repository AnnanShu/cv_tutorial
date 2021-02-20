//
// Created by Annan Shu on 2021/1/30.
//

#ifndef ML_MATRIX_H
#define ML_MATRIX_H
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <cmath>



class Matrix {
public:
    Matrix(int, int);
    Matrix(int, int, double);
    virtual ~Matrix(); 
    Matrix& operator=(const Matrix&); // copy from matrix
    Matrix& operator=(const double *); // copy from array
    Matrix& operator+=(const Matrix&);
    Matrix& operator-=(const Matrix&);
    Matrix& operator*=(const Matrix&); 
    Matrix operator*(const Matrix& m) const;
    static Matrix Solve(const Matrix&, const Matrix&);//Solve Linear Equation
    void Show() const;//show matrix
    void swapRows(int, int);
    double det();//return determinant
    double Point(int i, int j) const;
    static Matrix inv(const Matrix&);//inverse matrix
    static Matrix eye(int );//return an I
    int row() const;
    int col() const;
    static Matrix T(const Matrix & m);//Matrix transpose not inplace
    Matrix gaussianEliminate();//Gaussian Elimination
    friend std::istream& operator>>(std::istream&, Matrix&);//实现矩阵的输入


private:
    int row_num, col_num;
    double **p{};
    void initialize();      // initialize a matrix
};


#endif //ML_MATRIX_H
