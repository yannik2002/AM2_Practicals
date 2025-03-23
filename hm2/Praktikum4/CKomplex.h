#include <vector>
#include <cmath>

class CKomplex
{
private:
    double re = 0;
    double im = 0;

public:

    CKomplex() {};

    // Erstellen von komplexer Zahl mit a+bj
    CKomplex(double a, double b) :
        re{a}, im{b} {}

    // Erstellen von komplexer Zahl in Polardarstellung
    CKomplex(double phi) :
        re{cos(phi)}, im{sin(phi)} {}

    // Getter
    double get_re() { return re; }
    double get_im() { return im; }
    void set_im(double v_im) { im = v_im; }
    void set_re(double v_re) { re = v_re; }

    // Betrag einer komplexen Zahl zurückgeben
    double abs();

};

CKomplex operator+(CKomplex a, CKomplex b);
CKomplex operator-(CKomplex a, CKomplex b);
CKomplex operator*(CKomplex a, CKomplex b);
CKomplex operator*(double lambda, CKomplex a);

double calc_diff(std::vector<CKomplex> a, std::vector<CKomplex> b);

std::vector<CKomplex> fourierHintransformation(std::vector<CKomplex> a);
std::vector<CKomplex> fourierRuecktransformation(std::vector<CKomplex> a);
