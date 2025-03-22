#include "CMyVektor.h"

class C_DGLSolver {
private:
    bool ist_DGL_System; // true = DGL erster Ordnung, false = ist DGL n-ter Ordnung
    CMyVektor (*f_DGL_System)(CMyVektor y, double x) = nullptr;
    double (*f_DGL_nterOrdnung)(CMyVektor y, double x) = nullptr;
    CMyVektor ableitungen(CMyVektor y, double x);

public:
    // Ueberladener Konstruktor 1: DGL System
    C_DGLSolver(CMyVektor (*fp_DGL_System)(CMyVektor y, double x)) :
        f_DGL_System{fp_DGL_System}, ist_DGL_System{true} {}

    // Ueberladener Konstruktor 2: DGL hoeherer Ordnung
    C_DGLSolver(double (*fp_DGL_nterOrdnung)(CMyVektor y, double x)) :
        f_DGL_nterOrdnung{fp_DGL_nterOrdnung}, ist_DGL_System{false} {}

    // Getter und Setter für die beiden Funktionspointer
    // werden nicht gebraucht ig?
    CMyVektor (*getOption1())(CMyVektor, double){
        return f_DGL_System;
    }
    void setOption1(CMyVektor (*f)(CMyVektor, double)) {
        f_DGL_System = f;
    }

    double (*getOption2())(CMyVektor, double) {
        return f_DGL_nterOrdnung;
    }
    void setOption2(double (*f)(CMyVektor, double)) {
        f_DGL_nterOrdnung = f;
    }

    CMyVektor eulerVerfahren(double xStart, double xEnd, unsigned schritte, CMyVektor yStart);
    CMyVektor heunVerfahren(double xStart, double xEnd, unsigned schritte, CMyVektor yStart);

    CMyVektor eulerVerfahren_noCout(double xStart, double xEnd, unsigned schritte, CMyVektor yStart);
    CMyVektor heunVerfahren_noCout(double xStart, double xEnd, unsigned schritte, CMyVektor yStart);
};

