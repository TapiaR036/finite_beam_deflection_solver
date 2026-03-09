//Ramsey Tapia, rt26465
#include <vector>
#include <string>
#pragma once
using namespace std;

//----------------------------------------------
// vector support class definition (vector.hpp)
//----------------------------------------------

class Vector
{
private:
    // <magic stuff from you>
    vector<double> vector_;
    int vecSize_;
    int size_;
    double reqVal_;
    double newVal_;
    int nelems_;


public:
    Vector();                                  // constructor
    void allocateData(int nelems);             // allocate space for nelem entries (of double type)
    void initFromFile(string fileName);        // read the vector from a file
    int numElems();                            // return number of elements
    double getVal(int i);                      // return the ith element
    double l2norm();                           // return l2 norm
    void setVal(int i, double val);            // set the ith element to val
    void setAllVals(double val);               // set all elements of the vector to val
    void Print();                              // print the vector contents to stdout
    void Print(string name);                   // print the vector contents to stdout with a name prefix

    // regression support
    double sum();         // return the sum of vector elements
    double sumSquared();  // return the sum of (vector elements)^2
    double sum(Vector y); // return sum of (current vector)*(y vector) elements
};