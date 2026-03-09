//Ramsey Tapia, rt26465
#include <vector>
#include <string>
#include "vector.hpp"
#include "timer.hpp"
#pragma once

using namespace std;

//----------------------------------------------
// matrix support class definition (matrix.hpp)
//----------------------------------------------

// supported solver modes
enum solveModes {GAUSS_ELIM,JACOBI,GAUSS_SEIDEL};
enum fitModes {LINEAR=1,EXPONENTIAL=2,POWER=3};       // supported linear regression fitting modes

class Matrix

{
private:
   bool flag_ = false;
   bool turbo_;
   double tol_ = 0.00000001;
   double elapTime_;
   int rows_;
   int columns_;
   int iter_;
   int maxIters_ = 100000;
   vector <vector <double>> matrix_;
   vector <vector <double>> identMatrix_;
   vector <double> vecDiagonal_;
   Vector fit_;
   Vector x_;
   Vector y_;
   Timer atimer_;

public:
   Matrix();                                  // constructor
   void initMatrix(int rows, int columns);
   void initIdentity(int n);                  // initialize as an identity matrix of size nxn
   void initFromFile(string fileName);        // read the matrix from a file
   bool isSquare();                           // test whether matrix is square
   int numRows();                             // return number of rows
   int numCols();                             // return number of columns
   double getVal(int row, int col);           // return matrix value at given row/col location (0-indexed based)
   void setVal(int row, int col, double val); // set the matrix value at given row/col location (0-index based)
   Matrix Multiply(Matrix B);                 // post-multiply by B and return resulting matrix
   Matrix Multiply(double A);                 // multiply by a scalar and return resulting matrix
   Matrix Transpose();                        // return transpose of matrix
   vector<double> Diagonal();                 // return a vector containing diagonal elements of the matrix
   void Print();                              // print the matrix to stdout
   void Print(string name);                   // print the matrix to stdout with a name prefix

// Linear solver support
   Vector Solve(Vector b, int mode);          // return solution of [A]x=b using desired solver mode
   double getSolveTime();                     // wall clock time (in secs) required for last solve
   void setSolveDebugMode(bool flag);         // set flag to toggle debug output mode for linear solves

// Support methods for iterative methods
   void setSolveMaxIters(int iters);          // set cap on max # of iterations
   void setSolveTolerance(double tol);        // set desired stopping tolerance
   int  getSolveIters();                      // return number of iters completed from last solve

// regression support (for Nx2 matrices)
   Vector linFit(int mode);                     // linear regression fit (mode=LINEAR, EXPONENTIAL, or POWER)
   Matrix evalLinFit(int mode, Vector fit);     // evaluate linear fit - ouput is an Nx2 matrix

// additional utilities to aid in regression
   Vector extract(int col);                     // extract vector from matrix corresponding to the col index
   void saveToFile(string fileName);            // save matrix to file (same file format as initFromFile)

   void setTurbo(bool turbo);
};