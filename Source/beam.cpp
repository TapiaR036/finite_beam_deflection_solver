//Ramsey Tapia, rt26465

#include "beam.hpp"
#include <cmath>

Beam::Beam(int n, double L, double EI, double q) { // constructor
    n_ = n;
    L_ = L;
    EI_ = EI;
    q_ = q;
    dx_ = L / (n - 1);
}
Matrix Beam::getStiffnessMatrix() {                // return system stiffness matrix
    K_.initMatrix(n_, n_);
    for (int i = 0; i < n_ - 1; i++) {
        for (int j = 0; j < n_ - 1; j++) {
            if (i == 0) {
                K_.setVal(i, i, 1);
            }
            else if (i == j) {
                K_.setVal(i, j, -2);
                K_.setVal(i, j - 1, 1);
                K_.setVal(i, j + 1, 1);
            }
        }
    }
    K_.setVal(n_ - 1, n_ -1, 1);
    return K_;
}
Vector Beam::getSystemRHS() {                      // return system forcing vector
    f_.allocateData(n_);
    double con = (-q_ * pow(dx_, 2)) / (2 * EI_);
    f_.setVal(0, 0);
    f_.setVal(n_ - 1, 0);
    for (int i = 1; i < n_ - 1; i++) {
        f_.setVal(i, (con * (pow(x_.getVal(i), 2) - (x_.getVal(i) * L_))));
    }
    return f_;
}
Vector Beam::getExactSoln() {                      // return exact solution
    Vector exact;
    exact.allocateData(n_);
    double y = 0;
    for (int i = 1; i < n_ - 1; i++) {
        y = (-q_ / (2 * EI_) * ( (pow(x_.getVal(i), 4) / 12) - ( (L_ * pow(x_.getVal(i), 3) ) / 6 ) + ( (x_.getVal(i) * pow(L_, 3) ) / 12) ) );
        exact.setVal(i, y);
    }
    return exact;
}
Vector Beam::getApproxSoln() {                     // return finit-difference solution
    Vector approximate;
    approximate.allocateData(n_);

    if (turbo_) {                       //NEW IF 2026- set debug mode for linear solver based on turbo mode setting
        K_.setSolveDebugMode(false);
    } else {
        K_.setSolveDebugMode(true);
    }

    approximate = K_.Solve(f_, 3);
    return approximate;
}
Vector Beam::getCoordValues() {                    // retun discretized x-coord values
    x_.allocateData(n_);
    for (int i = 1; i < n_ - 1; i++) {
        x_.setVal(i, x_.getVal(i - 1) + dx_);
    }
    return x_;
}
double Beam::l2norm(Vector exact, Vector approx) { // return l2 error norm between exact and approx. solutions
    double norm;
    Vector difference;
    difference.allocateData(n_);
    for (int i = 0; i < n_; i++) {
        difference.setVal(i, exact.getVal(i) - approx.getVal(i));
    }
    norm = abs((difference.l2norm()) / exact.l2norm());
    return norm;
}
    
// additional method suggestions to potentially make your life easier
int Beam::getSolveIters() {                        // return number of solver iterations
    return K_.getSolveIters();
}
double Beam::getSolveTime() {                      // return solver time (secs)
    return K_.getSolveTime();
}
void Beam::setTurbo(bool mode) {                   // set turbo mode setting
    turbo_ = mode;
}