#include <iostream>
#include <vector>
#include <cmath>
#include "CMyVektor.h"
#include "CMyMatrix.h"
#include "C_DGLSolver.h"
using namespace std;

CMyVektor function1(CMyVektor y, double x){
    CMyVektor result(2);
    double y1 = y.get_component(0); // Die Werte fuer y1 und y2 aus dem mitgelieferten Vektor nehmen
    double y2 = y.get_component(1);
    result.set_component(0,((2 * y2) - (x * y1))); // y1' = 2*y2 - x*y1
    result.set_component(1,((y1 * y2) - (2 * pow(x,3))));   // y2' = y1*y2 -2x^3
    return result;
}

double function2(CMyVektor y, double x){
    double result = 0;
    double y1 = y.get_component(0); // y
    double y2 = y.get_component(1); // y'
    double y3 = y.get_component(2); // y''
    result = (2*x*y2*y3) + (2*pow(y1,2) * y2);
    return result;
}

int main() {

    C_DGLSolver dglSystem(*function1);
    C_DGLSolver dglHoehererOrdnung(*function2);

    // Startwerte für das DGL System
    CMyVektor y1(2);
    y1.set_component(0, 0);
    y1.set_component(1, 1);
    // Startwerte für das DGL dritter Ordnung
    CMyVektor y2(3);
    y2.set_component(0, 1);
    y2.set_component(1, -1);
    y2.set_component(2, 2);

    // Euler-Verfahren an DGL1 mit xEnd = 2 und 100 Schritten
    dglSystem.eulerVerfahren(0, 2, 100, y1);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "==============================================\n";
    std::cout << std::endl;

    // Heun-Verfahren an DGL1 mit xEnd = 2 und 100 Schritten
    dglSystem.heunVerfahren(0, 2, 100, y1);

    std::cout << std::endl;
    std::cout << "======================================================\n";

    // dglHoehererOrdnung Differenzen berechnen
    { // 10 Schritte
        unsigned n = 10;
        CMyVektor erg1 = dglHoehererOrdnung.eulerVerfahren_noCout(1, 2, n, y2);
        double diff1 = -0.5 + erg1.get_component(0);
        cout << "Abweichung bei Euler bei " << n << " Schritten: " << "      " << diff1 << endl;

        CMyVektor erg2 = dglHoehererOrdnung.heunVerfahren_noCout(1, 2, n, y2);
        double diff = -0.5 + erg2.get_component(0);
        cout << "Abweichung bei Heun bei " << n << " Schritten: " << "     " << diff << endl;
    }
    { // 100 Schritte
        unsigned n = 100;
        CMyVektor erg1 = dglHoehererOrdnung.eulerVerfahren_noCout(1, 2, n, y2);
        double diff1 = -0.5 + erg1.get_component(0);
        cout << "Abweichung bei Euler bei " << n << " Schritten: " << "   " << diff1 << endl;

        CMyVektor erg2 = dglHoehererOrdnung.heunVerfahren_noCout(1, 2, n, y2);
        double diff = -0.5 + erg2.get_component(0);
        cout << "Abweichung bei Heun bei " << n << " Schritten: " << "   " << diff << endl;
    }
    { // 1000 Schritte
        unsigned n = 1000;
        CMyVektor erg1 = dglHoehererOrdnung.eulerVerfahren_noCout(1, 2, n, y2);
        double diff1 = -0.5 + erg1.get_component(0);
        cout << "Abweichung bei Euler bei " << n << " Schritten: " << "  " << diff1 << endl;

        CMyVektor erg2 = dglHoehererOrdnung.heunVerfahren_noCout(1, 2, n, y2);
        double diff = -0.5 + erg2.get_component(0);
        cout << "Abweichung bei Heun bei " << n << " Schritten: " << "  " << diff << endl;
    }
    { // 10000 Schritte
        unsigned n = 10000;
        CMyVektor erg1 = dglHoehererOrdnung.eulerVerfahren_noCout(1, 2, n, y2);
        double diff1 = -0.5 + erg1.get_component(0);
        cout << "Abweichung bei Euler bei " << n << " Schritten: " << diff1 << endl;

        CMyVektor erg2 = dglHoehererOrdnung.heunVerfahren_noCout(1, 2, n, y2);
        double diff = -0.5 + erg2.get_component(0);
        cout << "Abweichung bei Heun bei " << n << " Schritten: " << " " << diff << endl;
    }
    std::cout << "======================================================\n";
    std::cout << std::endl;

    // system("pause");
    return 0;
}