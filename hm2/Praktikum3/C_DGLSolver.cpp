#include "C_DGLSolver.h"

CMyVektor C_DGLSolver::ableitungen(CMyVektor y, double x){
    if(ist_DGL_System == true) { // Falls DGL System uebergeben wurde
        CMyVektor res = f_DGL_System(y,x); // an der Stelle (y;x) auswerten
        return res; // und zurueckgeben
    }

    else { // Falls DGL hoeherer Ordnung uebergeben wurde
        CMyVektor res(y.get_dimension()); // So viele Zeilen wie Anfangswerte
        for(unsigned i = 0; i < y.get_dimension() - 1; i++){ // 0 bis n-1ten komponenten sind gleich gegebener Vektor
            res.set_component(i,y.get_component(i+1));
        }
        // n-1te Komponente ist die Gleichung, ausrechnen und setzen
        double f = f_DGL_nterOrdnung(y,x);
        res.set_component(y.get_dimension()-1,f);
        return res; // res ist nun ein DGL System erster Ordnung
    }
}

// Euler-Verfahren von xStart bis xEnd mit Startwerten yStart für Schritte
CMyVektor C_DGLSolver::eulerVerfahren(double xStart, double xEnd, unsigned schritte, CMyVektor yStart) {
    double h = (xEnd - xStart) / schritte; // Schrittweite berechnen
    std::cout << "h = " << h << "\n\n\n";

    // Erstmaliges Setzen der Werte
    CMyVektor y = yStart;
    CMyVektor yStrich = ableitungen(y, xStart);
    double x = xStart;
    for(unsigned i = 0; i < schritte; i++) {
        std::cout << "Schritt " << i
                << ":\n\tx = " << x
                << "\n\ty = " << y.print_vector()
                << "\n\ty' = " << yStrich.print_vector()
                << "\n\n\n";

        // Neusetzung aller werte, y(x + h) = y(x) + h * y'(x) bzw.
        y = y + h * yStrich;    // y(x0 + h) = y0 + h * f(x0,y0)
        x = x + h;
        yStrich = ableitungen(y, x);
    }
    std::cout << "Ende bei\n\tx = " << x << "\n\ty = " << y.print_vector() << std::endl;
    return y;
}

CMyVektor C_DGLSolver::heunVerfahren(double xStart, double xEnd, unsigned schritte, CMyVektor yStart) {
    double h = double(xEnd - xStart) / schritte;
    std::cout << "h = " << h << "\n\n\n";

    // Erstmaliges Setzen der Werte
    CMyVektor y = yStart;
    CMyVektor yStrich_orig = ableitungen(y, xStart);
    CMyVektor yTest = y + h * ableitungen(y, xStart);
    CMyVektor yStrich_test = ableitungen(yTest, xStart + h);
    CMyVektor yStrich_mittel = 0.5 * (yStrich_orig + yStrich_test);
    double x = xStart;
    for(unsigned i = 0; i < schritte; i++) {
        std::cout << "Schritt " << i
                << ":\n\tx = " << x
                << "\n\ty = " << y.print_vector()
                << "\n\ty'_orig = " << yStrich_orig.print_vector()
                << "\n\n\ty_Test = " << yTest.print_vector()
                << "\n\ty'_Test = " << yStrich_test.print_vector()
                << "\n\n\ty'_Mittel = " << yStrich_mittel.print_vector() << "\n\n\n";

        x = x + h;
        y = y + h * yStrich_mittel;
        yStrich_orig = ableitungen(y, x);
        yTest = y + h * yStrich_orig;
        yStrich_test = ableitungen(yTest, x + h);
        yStrich_mittel = 0.5 * (yStrich_orig + yStrich_test);
    }
    std::cout << "Ende bei\n\tx = " << x << "\n\ty = " << y.print_vector() << std::endl;
    return y;
}



CMyVektor C_DGLSolver::eulerVerfahren_noCout(double xStart, double xEnd, unsigned schritte, CMyVektor yStart) {
    double h = double(xEnd - xStart) / schritte;
    CMyVektor y = yStart;
    CMyVektor yStrich = ableitungen(y, xStart);
    double x = xStart;
    for(unsigned i = 0; i < schritte; i++) {
        y = y + h * ableitungen(y, x);
        x = x + h;
        yStrich = ableitungen(y, x);
    }
    return y;
}


CMyVektor C_DGLSolver::heunVerfahren_noCout(double xStart, double xEnd, unsigned schritte, CMyVektor yStart) {
    double h = double(xEnd - xStart) / schritte;
    CMyVektor y = yStart;
    CMyVektor yStrich_orig = ableitungen(y, xStart);
    CMyVektor yTest = y + h * ableitungen(y, xStart);
    CMyVektor yStrich_test = ableitungen(yTest, xStart + h);
    CMyVektor yStrich_mittel = 0.5 * (yStrich_orig + yStrich_test);
    double x = xStart;
    for(unsigned i = 0; i < schritte; i++) {
        x = x + h;
        y = y + h * yStrich_mittel;
        yStrich_orig = ableitungen(y, x);
        yTest = y + h * ableitungen(y, x);
        yStrich_test = ableitungen(yTest, x + h);
        yStrich_mittel = 0.5 * (yStrich_orig + yStrich_test);
    }
    return y;
}