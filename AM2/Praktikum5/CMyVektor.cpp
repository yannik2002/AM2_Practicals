#include <iostream>
#include <vector>
#include <cmath>
#include "CMyVektor.h"

// Ausgabefunktion fuer Vektor
std::string CMyVektor::print_vector() {
    std::string res = "";
    if(dimension > 0) {
        res = "(";
        for(unsigned i = 0; i < dimension; i++) {
            // bei letztem Element wird Klammer an das Ende getan
            if(i == dimension-1) {
                res = res + " " + std::to_string(get_component(i)) + " )";
            }
            else {
                res = res + " " + std::to_string(get_component(i)) + ";";
            }
        }
    }
    return res;
}

// Erstellt gueltige Vektoren (d>0), Standardinit. mit Nullvektor
CMyVektor::CMyVektor(unsigned d) {
    if(d > 0) {
        dimension = d;
        myArray = new double[d];
        for(unsigned i = 0; i < dimension; i++) {
            myArray[i] = 0;
        }
    }
}

// Dimensionen returnen
unsigned CMyVektor::get_dimension() {
    return dimension;
}

// set_component(k, value) setzt den Wert v an die Stelle k
void CMyVektor::set_component(unsigned k, double value) {
    if(k < dimension) {
        myArray[k] = value;
    }
}

//returned die Komponente k
double CMyVektor::get_component(unsigned k) {
    //gleiches ding wie oben, falls k außerhalb des vektors liegt, wird 0 als platzhalter returned
    if(k < dimension) {
        return myArray[k];
    }
    return 0;
}

// Gibt Vektorlaenge zurueck
double CMyVektor::get_length(){
    double sum = 0;
    for(unsigned i = 0; i < dimension; i++){
        // Alle Komponenten quadriert und summiert
        sum += pow(myArray[i], 2);
    }
    // Am Ende Wurzel ziehen
    return sqrt(sum);
}

// Vektoraddition
CMyVektor operator+(CMyVektor a, CMyVektor b) {
    // Vektoraddition nur bei identischer Dimension moeglich, und dimension groesser als 0
    if(a.get_dimension() == b.get_dimension() && a.get_dimension() > 0) {
        // Erstelle neuen vektor, welchen man am ende returned
        CMyVektor v(a.get_dimension());
        // Gehe alle Komponenten paarweise durch, summiere und setze diese in v ein
        for(unsigned i = 0; i < v.get_dimension(); i++) {
            v.set_component(i, a.get_component(i) + b.get_component(i));
        }
        return v;
    }
    return a;
}

// *operator fuer skalare Multiplikation
CMyVektor operator*(double lambda, CMyVektor a) {
    // Erstelle neuen vektor mit gleicher dimension wie Originalvektor
    CMyVektor v(a.get_dimension());
    // Multipliziere jede Komponente mit dem lambda
    for(unsigned i = 0; i < a.get_dimension(); i++) {
        v.set_component(i, lambda*a.get_component(i));
    }
    return v;
}

    /* Gebe gradient aus für Vektor x und die Funktion funktion
     * Numerische Ableitung mit Differenzenquotienten:
	 * f(x mit der i-ten komponente addiert mit h) - f(x) und diese differenz durch h geteilt
     * Bestimmen des Gradienten ohne explizit die Ableitungen zu implementieren, denn fuehrt man
     * dies fuer alle Komponenten durch, erhaelt man numerische Approximation des Gradienten */

    // x enthaelt die einzusetzenden Werte der Variablen, in funktion wird eingesetzt
CMyVektor gradient(CMyVektor x, double (*funktion)(CMyVektor x)){
    // Erstelle Gradienten vektor, hat selbe dimension
    CMyVektor g(x.get_dimension());
    //0.00000001;
    double const h = 1e-8;
    //konstante f(x) berechnen zur benutzung in der formel
    const double f = funktion(x);
    // fuer JEDE Komponente wird numerisch abgeleitet
    for (unsigned i = 0; i < x.get_dimension(); i++) {
        // h auf die i-te Komponente addieren
        x.set_component(i, x.get_component(i)+h);
        // i-te Komponente vom gradienten berechnen nach Formel
        g.set_component(i, (funktion(x) - f) / h);
        // das h von der i-ten Stelle wieder von Subtrahieren
        x.set_component(i, x.get_component(i) - h);
    }
    return g;
}

// Gradientenverfahren für Funktion funktion, Startvektor x und Schrittweite lambda mit default = 1.0
CMyVektor gradientVerfahren(CMyVektor x, double (*funktion) (CMyVektor x), double lambda){
    // counter für die Iterationen, bei 25 wird gestoppt
    unsigned schritt = 0;
    // Konstante fuer 2. Abbruchbedingung
    double const h = 1e-5;

    // bestimme Gradienten und weitere Werte für den ersten Schritt
    CMyVektor g = gradient(x, funktion);
    // Allgemein: x^(i+1) = x^i + lambda(i) * grad(f(x^i))
    CMyVektor x_next = x + lambda * g;
    double f = funktion(x);
    double f_next = funktion(x_next); // x1
    double laengeGradient = g.get_length();

    while(true) {
        if(schritt >= 25) { // 1. ABBRUCHBEDINGUNG
            // 25 Schritte erreicht, vorgegebene Ausgabe
            std::cout << "Ende wegen Schrittanzahl = 25" << std::endl
                    << "	 x = " << x.print_vector()
                    << "\n	 lambda = " << lambda
                    << "\n	 f(x) = " << f
                    << "\n	 grad f(x) = " << g.print_vector()
                    << "\n	 ||grad f(x)|| = " << laengeGradient << std::endl;
            return g;
        }
        else if (laengeGradient < h) { // 2. ABBRUCHBEDINGUNG
            // Laenge Gradientvektor hat 0.00001 erreicht, vorgegebene Ausgabe
            std::cout << "Ende wegen: ||gradf(x)|| < 10^-5 bei" << std::endl
                    << "	 x = " << x.print_vector()
                    << "\n	 lambda = " << lambda
                    << "\n	 f(x) = " << f
                    << "\n	 grad f(x) = " << g.print_vector()
                    << "\n	 ||grad f(x)|| = " << laengeGradient << std::endl;
            return g;
        }
        else { // Hier der eigentliche Schritt, falls noch kein Abbruch
            std::cout << "Schritt: " << schritt << ":\n"
                    << "	 x = " << x.print_vector()
                    << "\n	 lambda = " << lambda
                    << "\n" << "	 f(x) = " << f
                    << "\n	 grad f(x) = " << g.print_vector()
                    << "\n	 ||grad f(x)|| = " << laengeGradient << "\n\n";

            std::cout << "	 x_neu = " << x_next.print_vector()
                    << "\n	 f(x_neu) = " << f_next << "\n\n";

            // SCHRITTWEITENSTEUERUNG
            if(f_next > f) { // Falls f(x) kleiner als f(x_neu) test mit doppelter Schrittweite
                double lambda_test = lambda * 2;
                CMyVektor x_test = x + lambda_test * g;
                double f_test = funktion(x_test);
                std::cout << "	 Test mit doppelter Schrittweite (lambda = " << lambda_test << "):"
                        << std::endl << "	 x_test = " << x_test.print_vector()
                        << "\n	 f(x_test) = " << f_test << std::endl;
                if(f_test > f_next) { // Falls f(x_test) groesser als f(x_neu) wird Schrittweite beibehalten
                    lambda = lambda_test;
                    x_next = x_test;
                    f_next = f_test;
                    std::cout << "	 verdoppele Schrittweite!"<< std::endl << std::endl;
                }
                else { // Sonst bei alter Schrittweite bleiben
                    std::cout << "	 behalte alte Schrittweite!"<< std::endl << std::endl;
                }
            }
            else if(f_next <= f) { // falls f(x) kleiner oder gleich f(x_neu) wird Schrittweite halbiert
                while (f_next <= f) { // bis f(x_neu) groesser ist als f(x)
                    lambda = lambda * 0.5;
                    x_next = x + lambda * g;
                    f_next = funktion(x_next);
                    std::cout << "	 halbiere Schrittweite (lambda = " << lambda << "):" << std::endl << "	 x_neu = "
                              << x_next.print_vector() << "\n	 f(x_neu) = " << f_next << "\n\n";
                }
            }

            // x^i ist jetzt x^i+1, berechne die neuen Werte sowie erhöhe Schritt um 1
            x = x_next;
            g = gradient(x, funktion);
            x_next = x + lambda * g;
            f = funktion(x);
            f_next = funktion(x_next);
            laengeGradient = g.get_length();
            schritt++;
        }
    }
    return g;
}


