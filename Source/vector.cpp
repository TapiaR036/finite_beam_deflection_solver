//Ramsey Tapia, rt26465
#include <iostream>
#include <vector>
#include "vector.hpp"
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>

Vector::Vector(){}

void Vector::allocateData(int nelems){             // allocate space for nelem entries (of double type)
    nelems_ = nelems;
    vector_.resize(nelems_);
}
void Vector::initFromFile(string fileName){        // read the vector from a file
    ifstream infile;                                         
    infile.open(fileName);

    if(infile.is_open()){
        infile >> vecSize_;

        allocateData(vecSize_);
        double n;

        for (int i = 0; i < vecSize_; i++) {
            infile >> n;
            vector_[i] = n;
        }
        infile.close();
    } else {
        cout << "The file ie NOT OPEN!" << endl;
        exit(1);
    }
}
int Vector::numElems(){                            // return number of elements
    size_ = vector_.size();
    return size_;
}
double Vector::getVal(int i){                      // return the ith element
    reqVal_ = vector_[i];
    return reqVal_;
}
double Vector::l2norm(){                           // return l2 norm
    double sum = 0;
    double norm;
    for (int i = 0; i < nelems_; i++) {
        sum += pow(vector_[i], 2);
    }
    norm = sqrt(sum);
    return norm;
}
void Vector::setVal(int i, double val){            // set the ith element to val
    newVal_ = val;
    vector_[i] = newVal_;
}
void Vector::setAllVals(double val){               // set all elements of the vector to val
    for (int i = 0; i < vector_.size(); i++) {
        vector_[i] = val;
    }
}
void Vector::Print(){                              // print the vector contents to stdout
    if (vector_.size() <= 0) {
        cout << "[Error]: slow your roll and please initialize vector first" << endl;
        exit(1);
    } else {
    for (int i = 0; i < vector_.size(); i++) {
        cout  << " | " << setw(5) << vector_[i] << " | " << endl;;
        }
    }
}
void Vector::Print(string name){                   // print the vector contents to stdout with a name prefix
    if (vector_.size() <= 0) {
        cout << "[Error]: slow your roll and please initialize vector first" << endl;
        exit(1);
    } else {
    cout << name << " = ";
    for (int i = 0; i < vector_.size(); i++) {
        if (i > 0) {
            cout << setw(name.length() + 6);
        }
        cout  << " | " << setw(5) << vector_[i] << " | " << endl;
        }

    }
}
double Vector::sum(){                              // return the sum of vector elements
    double sumX = 0;
    for (int i = 0; i < vector_.size(); i++) {
        sumX += vector_[i];
    }
    return sumX;
}
double Vector::sumSquared(){                       // return the sum of (vector elements)^2
    double sumSquareX = 0;
    for (int i = 0; i < vector_.size(); i++) {
        sumSquareX += pow(vector_[i], 2);
    }
    return sumSquareX;
}
double Vector::sum(Vector y){                      // return sum of (current vector)*(y vector) elements
    double sumXY = 0;
    for (int i = 0; i < vector_.size(); i++) {
        sumXY += vector_[i] * y.vector_[i];
    }
    return sumXY;
}