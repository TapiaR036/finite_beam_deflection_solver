#include "matrix.hpp"
#include "vector.hpp"
#pragma once
using namespace std;

class Beam
{
private:
    Matrix K_;          // system stiffness matrix
    Vector f_;          // right-hand forcing vector
    // additional private vars you may need?
    int n_;
    double L_;
    double EI_;
    double q_;
    double dx_;
    bool turbo_;
    Vector x_;
    
public:
    Beam(int n, double L, double EI, double q); // constructor
    Matrix getStiffnessMatrix();                // return system stiffness matrix
    Vector getSystemRHS();                      // return system forcing vector
    Vector getExactSoln();                      // return exact solution
    Vector getApproxSoln();                     // return finit-difference solution
    Vector getCoordValues();                    // retun discretized x-coord values
    double l2norm(Vector exact, Vector approx); // return l2 error norm between exact and approx. solutions
    
    // additional method suggestions to potentially make your life easier
    int getSolveIters();                        // return number of solver iterations
    double getSolveTime();                      // return solver time (secs)
    void setTurbo(bool mode);                   // set turbo mode setting

};