//
// Created by Annan Shu on 2021/1/30.
//

#include "Matrix.h"
#include <vector>
//#include <numeric>

using std::endl;
using std::cout;
using std::istream;
using std::vector;
using std::abs;
const double EPS = 1e-10;

void Matrix::initialize() { // initialize matirx
    p = new double*[row_num]; // 分配row个指针
    for (int i = 0; i <= row_num; i++)
    {
        p[i] = new double[col_num]; //为pi进行动态内存分配，大小为col
    }
}

Matrix::Matrix(int rows, int cols)
{
    row_num = rows;
    col_num = cols;
    initialize();
    for (int i = 0; i < row_num; i++)
    {
        for (int j = 0; j < col_num; j++)
        {
            p[i][j] = 0;
        }
    }
}

Matrix::Matrix(int rows, int cols, double value)
{
    row_num = rows;
    col_num = cols;
    initialize();
    for (int i = 0; i < row_num; i++)
    {
        for (int j = 0; j < col_num; j++)
        {
            p[i][j] = value;
        }
    }
}

Matrix::~Matrix()
{
    for(int i = 0; i <= row_num; ++i)
    {
        delete[] p[i];
    }
    delete[] p;
}

// copy constructor
Matrix& Matrix::operator=(const Matrix& m)
{
    if(this == &m){
        return *this;
    }

    if (row_num != m.row_num || col_num != m.col_num){
        for (int i = 0; i < row_num; ++i){
            delete[] p[i];
        }
        delete[] p;

        row_num = m.row_num;
        col_num = m.col_num;
        initialize();
    }

    for(int i = 0; i < row_num; i++){
        for(int j = 0; j < col_num; j++){
            p[i][j] = m.p[i][j];
        }
    }
    return *this;
}

// 将数组值传给矩阵
Matrix & Matrix::operator=(const double *a) {
    for(int i = 0; i < row_num; i++){
        for(int j = 0; j < col_num; j++){
            p[i][j] += *(a + i * col_num + j);
        }
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix &m) {
    for(int i = 0; i < row_num; i++){
        for(int j = 0; j < col_num; j++){
            p[i][j] += m.p[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix &m) {
    for(int i = 0; i < row_num; i++){
        for(int j = 0; j < col_num; j++){
            p[i][j] -= m.p[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix &m) {
    Matrix b_M(row_num, m.col_num, 0.0);
    for(int i = 0; i < row_num; i++){
        for(int j = 0; j < m.col_num; j++){
            for(int k = 0; k < col_num; k ++){
                b_M.p[i][j] += p[i][k] * m.p[k][j];
            }
        }
    }
    *this = b_M;
    return *this;
}

Matrix Matrix::operator*(const Matrix &m) const{
    Matrix b_M(row_num, m.col_num, 0.0);
    for(int i = 0; i < row_num; i++){
        for(int j = 0; j < m.col_num; j++){
            for(int k = 0; k < col_num; k ++){
                b_M.p[i][j] += p[i][k] * m.p[k][j];
            }
        }
    }
    return b_M;
}

//解方程Ax=b
Matrix Matrix::Solve(const Matrix &A, const Matrix &b)
{
    //高斯消去法实现Ax=b的方程求解
    for (int i = 0; i < A.row_num; i++) {
        if (A.p[i][i] == 0) {

            cout << "请重新输入" << endl;
        }
        for (int j = i + 1; j < A.row_num; j++) {
            for (int k = i + 1; k < A.col_num; k++) {
                A.p[j][k] -= A.p[i][k] * (A.p[j][i] / A.p[i][i]);
                if (abs(A.p[j][k]) < EPS)
                    A.p[j][k] = 0;
            }
            b.p[j][0] -= b.p[i][0] * (A.p[j][i] / A.p[i][i]);
            if (abs(A.p[j][0]) < EPS)
                A.p[j][0] = 0;
            A.p[j][i] = 0;
        }
    }

    // 反向代换
    Matrix x(b.row_num, 1);
    x.p[x.row_num - 1][0] = b.p[x.row_num - 1][0] / A.p[x.row_num - 1][x.row_num - 1];
    if (abs(x.p[x.row_num - 1][0]) < EPS)
        x.p[x.row_num - 1][0] = 0;
    for (int i = x.row_num - 2; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < x.row_num; j++) {
            sum += A.p[i][j] * x.p[j][0];
        }
        x.p[i][0] = (b.p[i][0] - sum) / A.p[i][i];
        if (abs(x.p[i][0]) < EPS)
            x.p[i][0] = 0;
    }

    return x;
}

void Matrix::Show() const {
    for(int i = 0; i < row_num; i++){
        for(int j = 0; j < col_num; j++){
            cout << p[i][j] << " ";
        }
        cout << std::endl;
    }
    cout << std::endl;
}

// 实现行变换
void Matrix::swapRows(int a, int b) {
    a--;
    b--;
    double* temp = p[a];
    p[a] = p[b];
    p[b] = temp;
}

double Matrix::det(){
    //为计算行列式做一个备份
    double ** back_up;
    back_up=new double *[row_num];
    for(int i=0;i<row_num;i++){
        back_up[i]=new double[col_num];
    }
    for(int i=0;i<row_num;i++){
        for(int j=0;j<col_num;j++){
            back_up[i][j]=p[i][j];
        }
    }
    if(row_num!=col_num){
        std::abort();//只有方阵才能计算行列式，否则调用中断强制停止程序
    }
    double ans=1;
    for(int i=0;i<row_num;i++){
        //通过行变化的形式，使得矩阵对角线上的主元素不为0
        if(abs(p[i][i])<=EPS){
            bool flag=false;
            for(int j=0;(j<col_num)&&(!flag);j++){
                //若矩阵的一个对角线上的元素接近于0且能够通过行变换使得矩阵对角线上的元素不为0
                if((abs(p[i][j])>EPS)&&(abs(p[j][i])>EPS)){
                    flag=true;
                    //注：进行互换后,p[i][j]变为p[j][j]，p[j][i]变为p[i][i]
                    //对矩阵进行行变换
                    double temp;
                    for(int k=0;k<col_num;k++){
                        temp=p[i][k];
                        p[i][k]=p[j][k];
                        p[j][k]=temp;
                    }
                }
            }
            if(flag)
                return 0;
        }
    }
    for(int i=0;i<row_num;i++){
        for(int j=i+1;j<row_num;j++){
            for(int k=i+1;k<col_num;k++){
                p[j][k]-=p[i][k]*(p[j][i]*p[i][i]);
            }
        }
    }
    for(int i=0;i<row_num;i++){
        ans*=p[i][i];
    }
    for(int i=0;i<row_num;i++){
        for(int j=0;j<col_num;j++){
            p[i][j]=back_up[i][j];
        }
    }
    return ans;
}

double Matrix::Point(int i, int j) const {
    return this->p[i][j];
}

// inverse matrix
Matrix Matrix::inv(const Matrix& A) {
    return A;
}

Matrix Matrix::eye(int n) {
    Matrix A(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A.p[i][j] = i == j ? 1 : 0;
        }
    }
    return A;
}

int Matrix::row() const {
    return this->row_num;
}

int Matrix::col() const {
    return this->col_num;
}

// transpose a Matrix
Matrix Matrix::T(const Matrix &m) {
    Matrix mt(m.col(), m.row());
    for (int i = 0; i < m.row(); ++i) {
        for (int j = 0; j < m.col(); ++j) {
            mt.p[j][i] = m.p[i][j];
        }
    }
    return mt;
}

Matrix Matrix::gaussianEliminate()
{
    Matrix Ab(*this);
    int rows = Ab.row_num;
    int cols = Ab.col_num;
    int Acols = cols - 1;

    int i = 0; //跟踪行
    int j = 0; //跟踪列
    while (i < rows)
    {
        bool flag = false;
        while (j < Acols && !flag)
        {
            if (Ab.p[i][j] != 0) {
                flag = true;
            }
            else {
                int max_row = i;
                double max_val = 0;
                for (int k = i + 1; k < rows; ++k)
                {
                    double cur_abs = Ab.p[k][j] >= 0 ? Ab.p[k][j] : -1 * Ab.p[k][j];
                    if (cur_abs > max_val)
                    {
                        max_row = k;
                        max_val = cur_abs;
                    }
                }
                if (max_row != i) {
                    Ab.swapRows(max_row, i);
                    flag = true;
                }
                else {
                    j++;
                }
            }
        }
        if (flag)
        {
            for (int t = i + 1; t < rows; t++) {
                for (int s = j + 1; s < cols; s++) {
                    Ab.p[t][s] = Ab.p[t][s] - Ab.p[i][s] * (Ab.p[t][j] / Ab.p[i][j]);
                    if (abs(Ab.p[t][s]) <EPS)
                        Ab.p[t][s] = 0;
                }
                Ab.p[t][j] = 0;
            }
        }
        i++;
        j++;
    }
    return Ab;
}

istream& operator>>(istream& is, Matrix& m){
    for (int i = 0; i < m.row(); ++i) {
        for (int j = 0; j < m.col(); ++j) {
            is >> m.p[i][j];
        }
    }
    return is;
}

