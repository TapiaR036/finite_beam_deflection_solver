#include <iostream>
#include <vector>
#include "matrix.hpp"
#include "vector.hpp"
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>

Matrix::Matrix(){}

void Matrix::initMatrix(int rows, int columns) {
    rows_ = rows;
    columns_ = columns;
    matrix_.resize(rows_);
    for(int j = 0; j < columns_; j++) {
        matrix_[j].resize(columns_);
    }
    for(int i = 0; i < rows_; i++) {
        for(int j = 0; j < columns_; j++) {
            matrix_[i][j] = 0;
        }
    }
}
void Matrix::initIdentity(int n) {                              // initialize as an identity matrix of size nxn
    matrix_.resize(double(n), vector<double> (n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j == i) {
                matrix_[i][j] = 1;
            }
            else {
                matrix_[i][j] = 0;
            }
        }
    }
}
void Matrix::initFromFile(string fileName) {                    // read the matrix from a file - NEED Matrix:: in the rest of the functions
    ifstream infile;                                         
    infile.open(fileName);

    if(infile.is_open()){
        infile >> rows_;
        infile >> columns_;

        double n;
        matrix_.resize(rows_, vector<double> (columns_));        // dynamically allocate "resize()" to rows_ and columns_

        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < columns_; j++) {
                infile >> n;
                matrix_[i][j] = n;
            }
        }
        infile.close();
    } else {
        cout << "The file ie NOT OPEN!" << endl;
        exit(1);
    }
}
bool Matrix::isSquare() {                                       // test whether matrix is square
    return (matrix_.size() == matrix_[0].size());
}
int Matrix::numRows() {                                         // return number of rows
    return matrix_.size();
}                            
int Matrix::numCols() {                                         // return number of columns
    return matrix_[0].size();
}
double Matrix::getVal(int row, int col) {                       // return matrix value at given row/col location (0-indexed based)
    return matrix_[row][col];
}
void Matrix::setVal(int row, int col, double val) {             // set the matrix value at given row/col location (0-index based)
    matrix_[row][col] = val;
}
Matrix Matrix::Multiply(Matrix B){                              // post-multiply by B and return resulting matrix - make sure to prepare for the dimensions to match/not match
    if (matrix_[0].size() != B.matrix_.size()) {
        cout << endl << "Make sure the inner dimensions match." << endl;
        exit(1);
    }
    double sum;
    Matrix resultMatrix_;
    int resRows = matrix_.size();                               //size doesnt technically put out an int type, so cant assign to resize()
    int resCols = B.matrix_[0].size();

    resultMatrix_.matrix_.resize(resRows, vector<double> (resCols));
    
    for (int i = 0; i < matrix_.size(); i++) {
        for (int j = 0; j < B.matrix_[0].size(); j++) {
            sum = 0;                                            //use a variable to accumulate in line 67, and right after, bring that value into resultMatrix, use setVal of the object resultMatrix    
            for (int k = 0; k < B.matrix_.size(); k++) {       
                sum += matrix_[i][k] * B.matrix_[k][j];                                            
            }
            resultMatrix_.setVal(i, j, sum);
        }
    }
    return resultMatrix_;
}
Matrix Matrix::Multiply(double A){                              // multiply by a scalar and return resulting matrix
    double scalNum;
    Matrix scalMatrix;
    int scalRows = matrix_.size();
    int scalCols = matrix_[0].size();
    
    scalMatrix.matrix_.resize(scalRows, vector<double> (scalCols));

    for (int i = 0; i < matrix_.size(); i++) {
        for (int j = 0; j < matrix_[0].size(); j++) {
            scalNum = A * matrix_[i][j];
            scalMatrix.setVal(i, j, scalNum);
        }
    }
    return scalMatrix;
}
Matrix Matrix::Transpose(){                                     // return transpose of matrix
    double transNum;
    Matrix transMatrix;
    int transRows = matrix_.size();
    int transCols = matrix_[0].size();

    transMatrix.matrix_.resize(transCols, vector<double> (transRows));

    for (int i = 0; i < matrix_[0].size(); i++) {
        for (int j = 0; j < matrix_.size(); j++) {
            transNum = matrix_[j][i];
            transMatrix.setVal(i, j, transNum);
        }
    }
    return transMatrix;
}
vector<double> Matrix::Diagonal(){                              // return a vector containing diagonal elements of the matrix
    cout << "Diagonal Vector: { ";
    for (int i = 0; i < matrix_.size(); i++) {
        for (int j = 0; j < matrix_[i].size(); j++) {
            if (i == j) {
                vecDiagonal_.push_back(matrix_[i][j]);
                cout << vecDiagonal_[i] << " ";
            }
        }
    }
    cout << "}" << endl;
    return vecDiagonal_;
}
void Matrix::Print(){                                           // print the matrix to stdout
    if (matrix_.size() <= 0 || matrix_[0].size() <= 0) {
        cout << "[Error]: slow your roll and please initialize matrix first" << endl;
        exit(1);
    } else {
    for (int i = 0; i < matrix_.size(); i++) {
            cout << " | ";
            for (int j = 0; j < matrix_[i].size(); j++) {
                cout  << setw(5) << matrix_[i][j] << " ";
            }
            cout << " | " << endl;
        }
    }
}
void Matrix::Print(string name){                                // print the matrix to stdout with a name prefix
    if (matrix_.size() <= 0 || matrix_[0].size() <= 0) {
        cout << "[Error]: slow your roll and please initialize matrix first" << endl;
        exit(1);
    } else {
    cout << name << " = ";
    for (int i = 0; i < matrix_.size(); i++) {
            if (i > 0) {
                cout << setw(name.length() + 6);
            }
            cout << " | ";
            for (int j = 0; j < matrix_[i].size(); j++) {
                cout  << setw(5) << matrix_[i][j] << setw(4);
            }
            cout << " | " << endl;
        }
    }
}
Vector Matrix::Solve(Vector b, int mode){                       // return solution of [A]x=b using desired solver mode
    atimer_.Start();

    Matrix A;
    A.matrix_.resize(rows_, vector<double> (columns_));
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns_; j++) {
            A.setVal(i, j, matrix_[i][j]);
        }
    }
    if (A.isSquare() == false) {
        cout << "Please enter a square matrix!" << endl;
        exit(1);
    }

    int bSize = b.numElems();
    Vector X;
    X.allocateData(bSize);
    Vector oldX;
    oldX.allocateData(bSize);
    Vector diffX;
    diffX.allocateData(bSize);
    iter_ = 0;
    double norm = 1;
    double tmp = 0;
    double oneSum;
    double twoSum;

    
    string solMethod;
    if (mode == 1) {
        solMethod = "[Gaussian elimination]";
    } else if (mode == 2) {
        solMethod = "[Jacobi]";
    } else if (mode == 3) {
        solMethod = "[Gauss-Seidel]";
    }


    if (bSize != matrix_[0].size()) {
        cout << "Error! Amount of equations needs to equal the amount of unknowns!" << endl;
        exit(1);
    }
    
    if (mode == 1){                                     //GAUSS_ELIM
        if (flag_ == true) {
            cout << "Solving [A]x = b using naive Gaussian Elimination:" << endl;
            cout << "Initial System: " << endl;
            A.Print("[A]");
            b.Print("b");
        }

        double f = 0;
        double mNew = 0;
        double bNew = 0;
        double xNew = 0;
        double c;

        for (int pivot = 0; pivot < bSize - 1; pivot++) {
            if (A.getVal(pivot, pivot) == 0) {
                cout << "Pivot is zero." << endl;
                exit(1);
            }

            for (int i = pivot + 1; i < rows_; i++) {
                f = A.getVal(i, pivot) / A.getVal(pivot, pivot);
                for (int j = 0; j < columns_; j++) {
                    mNew = A.getVal(i, j) - (f * A.getVal(pivot, j));
                    A.setVal(i, j, mNew);
                }
                bNew = b.getVal(i) - (f * b.getVal(pivot));
                b.setVal(i, bNew);
            }
        }
        
        for (int i = rows_ - 1; i >= 0; i--) {
            c = 0;
            for (int j = i; j < columns_; j++) {
                if (A.getVal(i, j) != 0) {
                    c += X.getVal(j) * A.getVal(i, j);
                    xNew = (b.getVal(i) - c) / A.getVal(i, i);
                    X.setVal(i, xNew);
                }
            }
        }

        if (flag_ == true) {
            cout << "Updated system after forward elimination: " << endl;
            A.Print("[A]");
            b.Print("b");
        }
        atimer_.Stop();
        return X;

    } else if (mode == 2) {                             //JACOBI
        if(flag_ == true) {
            cout << "Solving [A]x = b using Jacobi iterative method:" << endl;
        }
        while (norm > tol_ && iter_ < maxIters_) {
            iter_++;
            for (int i = 0; i < rows_; i++) {
                oneSum = 0;
                for (int j = 0; j < columns_; j++) {
                    if (j != i) {
                        oneSum += A.getVal(i, j) * oldX.getVal(j);
                    }
                }
                tmp = (b.getVal(i) - oneSum) / A.getVal(i, i);
                X.setVal(i, tmp);
                diffX.setVal(i, X.getVal(i) - oldX.getVal(i));
            }
            norm = abs(diffX.l2norm() / X.l2norm());
            if (flag_ == true) {
                cout << "  --> Iteration: " << setw(5) << iter_ << "  norm = " << norm << endl;
                if (tol_ > norm) {
                    cout << "Converged!" << endl;
                }
            }
            for (int i = 0; i < rows_; i++) {
                oldX.setVal(i, X.getVal(i));
            }
        }
        if (maxIters_ - 1 == iter_ && tol_ < norm) {
            cout << "Iterations limit reached before error criteria was met." << endl;
            exit(1);
        }
        atimer_.Stop();
        return X;
    } else if (mode == 3) {                             //GAUSS_SEIDEL
        if(flag_ == true) {
            cout << "Solving [A]x = b using Gauss-Seidel iterative method:" << endl;
        }
        while (maxIters_ > iter_ && norm > tol_) {
            iter_++;
            for (int i = 0; i < rows_; i++) {
                oneSum = 0;
                twoSum = 0;
                for (int j = 0; j < columns_; j++) {
                    if (j > i) {
                        oneSum += (A.getVal(i, j) * oldX.getVal(j));
                    } else if (j < i) {
                        twoSum += (A.getVal(i, j) * X.getVal(j));
                    }
                }
                tmp = (b.getVal(i) - oneSum - twoSum) / A.getVal(i, i);
                X.setVal(i, tmp);
                diffX.setVal(i, X.getVal(i) - oldX.getVal(i));
            }
            norm = abs(diffX.l2norm() / X.l2norm());
            for (int i = 0; i < rows_; i++) {
                    oldX.setVal(i, X.getVal(i));
                }
            if (flag_ == true) {
                cout << "  --> Iteration: " << setw(5) << iter_ << "  norm = " << norm << endl;
                if (tol_ > norm) {
                    cout << "Converged!" << endl;
                }
            }
        }
        if (maxIters_ - 1 == iter_ && tol_ < norm) {
            cout << "Iterations limit reached before error criteria was met." << endl;
            exit(1);
        }
        atimer_.Stop();
        return X;
    }else {
        cout << "Please choose a mode using 1, 2, or 3, depending on the method you want (gauss-elim, jacobi, and gauss-seidel, respectively)." << endl;
        exit(1);
    }
}
void Matrix::setTurbo(bool turbo) {
    turbo_ = turbo;
}
double Matrix::getSolveTime(){                                  // wall clock time (in secs) required for last solve
    elapTime_ = atimer_.ElapsedTime();
    return elapTime_;
}
void Matrix::setSolveDebugMode(bool flag){                      // set flag to toggle debug output mode for linear solves
    flag_ = flag;
}
void Matrix::setSolveMaxIters(int iters){                       // set cap on max # of iterations
    maxIters_ = iters;
}
void Matrix::setSolveTolerance(double tol){                     // set desired stopping tolerance
    tol_ = tol;
}
int  Matrix::getSolveIters(){                                   // return number of iters completed from last solve
    return iter_;
}
Vector Matrix::linFit(int mode){                                // linear regression fit (mode=LINEAR, EXPONENTIAL, or POWER)
    Matrix A;
    columns_ = 2;
    A.matrix_.resize(rows_, vector<double> (columns_));
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns_; j++) {
            A.setVal(i, j, matrix_[i][j]);
        }
    }
    A.rows_ = rows_;

    fit_.allocateData(2);

    x_ = A.extract(0);
    y_ = A.extract(1);
    int N = x_.numElems();

    Vector x;
    Vector y;
    x.allocateData(N);
    y.allocateData(N);

    if (mode == 1) {
        for (int i = 0; i < N; i++) {
            x.setVal(i, x_.getVal(i));
            y.setVal(i, y_.getVal(i));
        }
    }
    else if (mode == 2) {
        for (int i = 0; i < N; i++) {
            x.setVal(i, x_.getVal(i));
            y.setVal(i, log(y_.getVal(i)));
        }
    }
    else if (mode == 3) {
        for (int i = 0; i < N; i++) {
            x.setVal(i, log10(x_.getVal(i)));
            y.setVal(i, log10(y_.getVal(i)));
        }
    }

    double a1 = ( (N * x.sum(y) ) - (x.sum() * y.sum() ) ) / ( (N * x.sumSquared() ) - (x.sum() * x.sum() ) );
    fit_.setVal(1, a1);

    double a0 = (y.sum() - (a1 * x.sum() ) ) / N;
    fit_.setVal(0, a0);

    return fit_;
}
Matrix Matrix::evalLinFit(int mode, Vector fit){                // evaluate linear fit - ouput is an Nx2 matrix
    Matrix outMatrix;
    int x_Cols = 2;
    outMatrix.matrix_.resize(x_.numElems(), vector <double> (x_Cols));
    for (int i = 0; i < x_.numElems(); i++) {
        for (int j = 0; j < 2; j++) {
            outMatrix.setVal(i, j, matrix_[i][j]);
        }
    }

    double yFit;

    if (mode == 1) {
        for (int i = 0; i < x_.numElems(); i++) {
            outMatrix.setVal(i, 0, x_.getVal(i));
            yFit = fit_.getVal(0) + (fit_.getVal(1) * x_.getVal(i));
            y_.setVal(i, yFit);
            outMatrix.setVal(i, 1, yFit);
        }
    }
    else if (mode == 2) {
       for (int i = 0; i < x_.numElems(); i++) {
            outMatrix.setVal(i, 0, x_.getVal(i));
            yFit = exp(fit_.getVal(0)) * exp(fit_.getVal(1) * x_.getVal(i));
            y_.setVal(i, yFit);
            outMatrix.setVal(i, 1, yFit);
        } 
    }
    else if (mode == 3) {
        for (int i = 0; i < x_.numElems(); i++) {
            outMatrix.setVal(i, 0, x_.getVal(i));
            yFit = pow(10, fit_.getVal(0)) * pow(x_.getVal(i), fit_.getVal(1));
            y_.setVal(i, yFit);
            outMatrix.setVal(i, 1, yFit);
        }
    }
    return outMatrix;
}
Vector Matrix::extract(int col){                                // extract vector from matrix corresponding to the col index
    Vector colVec;
    colVec.allocateData(rows_);
    for (int i = 0; i < colVec.numElems(); i++) {
        colVec.setVal(i, matrix_[i][col]);
    }
    return colVec;
}
void Matrix::saveToFile(string fileName){                       // save matrix to file (same file format as initFromFile)
    ofstream outFile (fileName);
    outFile << rows_ << " " << columns_ << endl;
    for (int i = 0; i < x_.numElems(); i++) {
        outFile << setw(10) << scientific << x_.getVal(i) << " " << y_.getVal(i) << endl;
    }
}