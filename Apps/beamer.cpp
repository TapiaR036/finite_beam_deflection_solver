//Ramsey Tapia, rt26465
#include "matrix.hpp"
#include "vector.hpp"
#include "beam.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 5 && argc != 6) {
        cout << "---------------------------------------" << endl;
        cout << "Beam Solver 9003" << endl;
        cout << "   -> Solving a simply supported beam " << endl;
        cout << "---------------------------------------" << endl;
        cout << endl << "Usage: beam [n] [L] [EI] [q] <turbo>" << endl << endl;
        cout << "where:" << endl;
        cout << "  [n]            number of points" << endl;
        cout << "  [L]            length of the beam" << endl;
        cout << "  [EI]           (Young's modulus)*(2nd moment of interia)" << endl;
        cout << "  [q]            distributed load per unit length" << endl;
        cout << "  <turbo>        optional argument (1=turbo mode)" << endl;
        exit(1);
    }

    int n = stoi(argv[1]);
    double L = stod(argv[2]);
    double EI = stod(argv[3]);
    double q = stod(argv[4]);
    bool mode = false;

    if (argc == 6) {
        int turbo = stoi(argv[5]);
        if (turbo == 0) {
            mode = false;
        } else if (turbo == 1) {
            mode = true;
        }
    }

    Beam b = Beam(n, L, EI, q);
    b.setTurbo(mode);       //NEW LINE 2026 - set turbo mode for beam (which will pass to matrix/vector as needed)
    b.getCoordValues();
    
    Matrix K;
    K = b.getStiffnessMatrix();
    
    Vector f;
    f = b.getSystemRHS();
    
    Vector exact;
    exact = b.getExactSoln();
    
    Vector approx;
    approx = b.getApproxSoln();
    
    double norm;
    norm = b.l2norm(exact, approx);
    
    int iters = 0;
    iters = b.getSolveIters();
    
    double time = 0;
    time = b.getSolveTime();
    
    double h = L / (n - 1);

    cout << "Iterations: " << iters << endl;
    cout << "Solve Time: " << time << endl;
    cout << "l2 Error: " << norm << endl;
    cout << "Mesh Interval: " << h << endl;

    return 0;
}