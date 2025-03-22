#include <iostream>
#include <vector>
#include <cmath>
#include "CMyVektor.h"
using namespace std;

// x[0] = x; x[1] = y;
double funktion(CMyVektor x) { // Wert der Funktion an der Stelle des Vektors
    return sin(x.get_component(0)*x.get_component(1))+ sin(x.get_component(0)) + cos(x.get_component(1)); // sin(x*y) + sin(x) + cos(y)
}

// x[0] = x; x[1] = y; x[2] = z
double funktion2(CMyVektor x) { // Wert der Funktion an der Stelle des Vektors
    return -1*(2*pow(x.get_component(0),2) -2*x.get_component(0)*x.get_component(1)
               + pow(x.get_component(1),2)+pow(x.get_component(2),2)-2*x.get_component(0)-4*x.get_component(2)); // -(2x^2-2xy+y^2+z^2-2x-4z)
}

int main() {

    CMyVektor a(2);
    a.set_component(0, 0.2);
    a.set_component(1, -2.1);

    CMyVektor b(3);
    b.set_component(0, 0);
    b.set_component(1, 0);
    b.set_component(2, 0);

    double (*funk)(CMyVektor);
    funk = funktion;

    gradientVerfahren(a, funk);
    cout << "<================================================>"<< std::endl;
    funk = funktion2;
    gradientVerfahren(b, funk, 0.1);

    return 0;
}