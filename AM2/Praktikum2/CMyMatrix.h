#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "CMyVektor.h"

class CMyMatrix {
private: // m x n
    unsigned m; // Zeilen
    unsigned n; // Spalten
    double** myArray;

public:
    CMyMatrix(unsigned m, unsigned n);
    unsigned get_zeilen() const;
    unsigned get_spalten() const;
    std::string printMatrix() const;
    void set_component(unsigned m, unsigned n, double value);
    double get_component(unsigned m, unsigned n) const;
    double determinante();
    void skalareMultiplikation(double lambda);
    CMyMatrix invers();
};

CMyVektor operator*(CMyMatrix A, CMyVektor x); // Matrix-Vektor Multiplikation
CMyMatrix jacobi(CMyVektor x, CMyVektor (*funktion)(CMyVektor x));
void newtonVerfahren(CMyVektor x0, CMyVektor (*funktion)(CMyVektor x));