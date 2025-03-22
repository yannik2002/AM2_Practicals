#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "CMyVektor.h"
#include "CMyMatrix.h"

// Konstruktor, erstellt 2D Array mit [m][n]
CMyMatrix::CMyMatrix(unsigned m, unsigned n) {
    if(m >= 2 && n >= 2) {
        this->m = m;
        this->n = n;
        myArray = new double*[m];
        for(unsigned i = 0; i < m; i++) {
            myArray[i] = new double[n];
        }
        for(unsigned x = 0; x < m; x++) {
            for(unsigned y = 0; y < n; y++) {
                myArray[x][y] = 0;
            }
        }
    }
    else{
        throw "Nur Dimensionen >= 2 erlaubt!";
    }
}

unsigned CMyMatrix::get_zeilen() const {
    return m;
}

unsigned CMyMatrix::get_spalten() const {
    return n;
}

// printMatrix nach Vorbild der gegebenen Konsolenausgabe
std::string CMyMatrix::printMatrix() const {
    std::string res = "( ";
    for(unsigned x = 0; x < m; x++) {
        for(unsigned y = 0; y < n; y++) {
            if(y == n-1){
                res = res + std::to_string(myArray[x][y]) + " ";
            }
            else{
                res = res + std::to_string(myArray[x][y]) + "; ";
            }
        }
        if(x != m-1) {
            res = res + "\n                 ";
        }
    }
    res = res + ")";
    return res;
}

void CMyMatrix::set_component(unsigned zeiM, unsigned spaN, double value) {
    myArray[zeiM][spaN] = value;
}

double CMyMatrix::get_component(unsigned zeiM, unsigned spaN) const {
        return myArray[zeiM][spaN];
}


// Determinante speziell fuer 2x2 mit Regel von Sarrus, (a*d-b*c)
double CMyMatrix::determinante() {
    return ((myArray[0][0] * myArray[1][1]) - (myArray[0][1] * myArray[1][0]));
}

// Multipliziert jeden Eintrag der Matrix mit lambda
void CMyMatrix::skalareMultiplikation(double lambda) {
    for(unsigned x = 0; x < m; x++) {
        for(unsigned y = 0; y < n; y++) {
            double product = lambda * myArray[x][y];
            set_component(x,y,product);
        }
    }
}

CMyMatrix CMyMatrix::invers() {
    double det = this->determinante(); // Determinante speichern fuer spaetere Rechnung
    if(m == 2 && n == 2 && det != 0) {
        CMyMatrix inv(m,n);
        inv.myArray[0][0] = myArray[1][1]; // Werte von myArray in inv speichern nach Formel
        inv.myArray[0][1] = myArray[0][1] * (-1);
        inv.myArray[1][0] = myArray[1][0] * (-1);
        inv.myArray[1][1] = myArray[0][0];
        inv.skalareMultiplikation(1/det); // (1/det) * jeden Eintrag in der Matrix
        return inv;
    }
    else{
        throw "Falsche Dimensionen oder Determinante = 0!";
    }
}

CMyVektor operator*(CMyMatrix A, CMyVektor x) {
    if(A.get_spalten() == x.get_dimension()) {
        CMyVektor skalar(A.get_zeilen()); // Ergebnis ist ein Vektor mit so vielen Eintraegen wie die Matrix Zeilen hat
        double sum = 0;
        for(unsigned i = 0; i < A.get_zeilen(); i++) { // Zeilen durchlaufen
            for(unsigned y = 0; y < A.get_spalten(); y++) { // Spalten durchlaufen
                sum = sum + (A.get_component(i,y) * x.get_component(y)); // berechnen des jeweiligen Eintrags von skalar ueber sum
            }
            skalar.set_component(i,sum);
            sum = 0; // sum wieder auf 0 setzen
        }
        return skalar;
    }
    else {
        throw "Falsche Dimensionen!";
    }
}

CMyMatrix jacobi(CMyVektor x, CMyVektor (*funktion)(CMyVektor x)) {
    CMyVektor f = funktion(x); // Konstanten zur numerischen Berechnung
    double const h = 1e-4;
    CMyMatrix res(f.get_dimension(), x.get_dimension()); // Erstelle Ergebnis Jacobi-Matrix, hat so viele Zeilen wie Funktionen, so viele Spalten wie Variablen

    for(unsigned i = 0; i < x.get_dimension(); i++) { // Solange es Variablen gibt, Variable fuer Variable ableiten
        // h auf die i-te Komponente addieren                                        erste Variable = erste Spalte
        x.set_component(i, x.get_component(i) + h);
        // Funktionsvektor vom vektor x_h berechnen
        CMyVektor f_h = funktion(x);
        // Jede Komponente der Spalte in der Jacobi-Matrix setzen mit numerischer Ableitungsformel
        for(unsigned y = 0; y < f.get_dimension(); y++) {
            double value = ((f_h.get_component(y) - f.get_component(y)) / h);
            res.set_component(y,i,value);
        }
        // Das h von der i-ten Stelle wieder von Subtrahieren
        x.set_component(i, x.get_component(i) - h);
    }
    return res;
}

void newtonVerfahren(CMyVektor x, CMyVektor (*funktion)(CMyVektor x)) {
    if(x.get_dimension() == 2) { // Funktioniert nur fuer n = 2, zwei Funktionen und Variablen
        unsigned schritte = 0; // Abbruchbedingungen
        double const h = 1e-5;

        CMyVektor f = funktion(x); // Anfangswerte fuer den ersten Schritt
        CMyVektor delta_x(2);
        CMyMatrix f_jac = jacobi(x, funktion); // Jacobi-Matrix berechnen
        CMyMatrix f_jac_inv = f_jac.invers(); // Inverse berechnen


        while(schritte < 50 && f.get_length() >= h) {
                delta_x = f_jac_inv * (-1 * f); // -(inv.(f'(x)) * f(x))
                std::cout << "Schritt " << schritte
                << ":\n	 x = " << x.print_vector()
                << "\n	 f(x) = " << f.print_vector()
                << "\n	 f'(x) = \n	 	 " << f_jac.printMatrix()
                << "\n	 (f'(x))^(-1) = \n	 	 " << f_jac_inv.printMatrix()
                << "\n	 dx = " << delta_x.print_vector()
                << "\n	 ||f(x)|| = " << f.get_length() << "\n\n";

                x =  x + delta_x; // Xn+1 = Xn + delta_x
                f = funktion(x); // Neue Werte fuer den naechsten Schritt bestimmen
                f_jac = jacobi(x, funktion);
                f_jac_inv = f_jac.invers();
                schritte++; // nach jedem Schritt erhoehen
        }
        if(schritte == 50) { // Abbruchbedingung 1
            std::cout << "Ende wegen Schrittanzahl = 50" << std::endl
                      <<  "	 x = " << x.print_vector()
                      << "\n	 f(x) = " << f.print_vector()
                      << "\n	 ||f(x)|| = " << f.get_length() << std::endl;
            return;
        }
        else { // Abbruchbedingung 2
            std::cout << "Ende wegen ||f(x)|| < " << h << " bei" << std::endl
                      <<  "	 x = " << x.print_vector()
                      << "\n	 f(x) = " << f.print_vector()
                      << "\n	 ||f(x)|| = " << f.get_length() << std::endl;
            return;
        }
    }
    else {
        throw "Falsche Dimensionen!";
    }
}