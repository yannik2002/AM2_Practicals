#pragma once
#include <iostream>
#include <vector>
#include <cmath>

class CMyVektor {

private:
    unsigned dimension;
    double* myArray;

public:
    CMyVektor(unsigned d);

    // Prototypen
    double get_length();
    unsigned  get_dimension();
    void set_component(unsigned k, double value);
    double get_component(unsigned k);
    std::string print_vector();
};

CMyVektor operator+(CMyVektor a, CMyVektor b);
CMyVektor operator*(double lambda, CMyVektor a);
CMyVektor gradient(CMyVektor x, double (*funktion) (CMyVektor x));
CMyVektor gradientVerfahren(CMyVektor x, double (*funktion) (CMyVektor x), double lambda = 1.0);

