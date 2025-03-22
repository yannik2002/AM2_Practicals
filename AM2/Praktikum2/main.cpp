#include <iostream>
#include <vector>
#include <cmath>
#include "CMyVektor.h"
#include "CMyMatrix.h"
using namespace std;


CMyVektor funktion34(CMyVektor x) { // Beispielfunktion Jacobi-Matrix
    if(x.get_dimension() == 4) {
        CMyVektor res(3);
        double a = x.get_component(0);
        double b = x.get_component(1);
        double c = x.get_component(2);
        double d = x.get_component(3);
        res.set_component(0,(a*b*exp(c))); // x1*x2*e^x3
        res.set_component(1,(b*c*d)); // x2*x3*x4
        res.set_component(2,(d)); // x4
        return res;
    }
    else{
        throw "falsche dimensionen";
    }
}

CMyVektor funktion22(CMyVektor a) { // Beispielfunktion newtonVerfahren
    if(a.get_dimension() == 2) {
        CMyVektor res(2);
        double x = a.get_component(0);
        double y = a.get_component(1);
        res.set_component(0,((pow(x,3) * pow(y,3)) - (2*y))); // x^3*y^3 - 2y
        res.set_component(1,(x - 2)); // x - 2
        return res;
    }
    else{
        throw "falsche dimensionen";
    }
}


int main() {

    CMyVektor values(4);
    values.set_component(0,1);
    values.set_component(1,2);
    values.set_component(2,0);
    values.set_component(3,3);
    CMyVektor (*funk1)(CMyVektor x);
    funk1 = funktion34;
    CMyMatrix jac = jacobi(values, funk1);
    std::cout << "Jacobi-Matrix mit Beispielfunktion:\n";
    std::cout << jac.printMatrix() << std::endl << std::endl;

    CMyVektor x_start(2); // Startwert fuer das Newtonverfahren ist (1,1)
    x_start.set_component(0,1);
    x_start.set_component(1,1);

    CMyVektor (*funk2)(CMyVektor);
    funk2 = funktion22;
    newtonVerfahren(x_start, funk2);

    // system("PAUSE");
    return 0;
}