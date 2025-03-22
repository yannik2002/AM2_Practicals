#include "CKomplex.h"
#include <cmath>

CKomplex operator+(CKomplex a, CKomplex b)
{
    // (a1 + b1*j) + (a2 + b2*j) = ((a1 + a2) + (b1 + b2)*j)
    CKomplex res(a.get_re() + b.get_re(), a.get_im() + b.get_im());
    return res;
}

CKomplex operator-(CKomplex a, CKomplex b)
{
    // (a1 + b1*j) - (a2 + b2*j) = ((a1 - a2) + (b1 - b2)*j)
    CKomplex res(a.get_re() - b.get_re(), a.get_im() - b.get_im());
    return res;
}

CKomplex operator*(CKomplex a, CKomplex b)
{
    // (a1 + b1*j) * (a2 + b2*j) = ((a1*b1 - b1*b2) + (a1*b2 + a2*b1)*j)
    double z1 = ((a.get_re() * b.get_re()) - (a.get_im()*b.get_im()));
    double z2 = ((a.get_re() * b.get_im()) + (b.get_re()*a.get_im()));
    CKomplex res(z1, z2);
    return res;
}

CKomplex operator*(double lambda, CKomplex a)
{
    // re und im jeweils mit lambda multiplizieren
    CKomplex res(a.get_re() * lambda, a.get_im() * lambda);
    return res;
}

double CKomplex::abs()
{
    // sqrt(a^2 + b^2)
    double res = sqrt((pow(this->get_re(),2)) + (pow(this->get_im(),2)));
    return res;
}

std::vector<CKomplex> fourierHintransformation(std::vector<CKomplex> a)
{
    int N = a.size();
    std::vector<CKomplex> res;
    res.resize(N);

    double lambda = (1/sqrt(N));

    // Schleife wird so oft durchlaufen, bis man alle Cn's durch hat
    for (int i = 0; i < N; i++)
    {
        // Berechnung der einzelnen Cn's, durchlaufen der fk's
        CKomplex v(0,0);
        for (int i2 = 0; i2 < N; i2++)
        {
            double phi = ((2 * M_PI * i * i2) / N);
            CKomplex temp(phi);
            temp.set_im(-1 * temp.get_im());
            v = v + (a[i2] * temp);
        }
        res[i] = lambda * v;
    }

    return res;
}

std::vector<CKomplex> fourierRuecktransformation(std::vector<CKomplex> a)
{
    int N = a.size();
    std::vector<CKomplex> res;
    res.resize(N);

    double lambda = (1/sqrt(N));

    // Schleife wird so oft durchlaufen, bis man alle fk's durch hat
    for (int i = 0; i < N; i++)
    {
        // Berechnung der einzelnen fk's, durchlaufen der Cn's
        CKomplex v(0,0);
        for (int i2 = 0; i2 < N; i2++)
        {
            CKomplex temp((2 * M_PI * i * i2) / N);
            v = v + (a[i2] * temp);
        }
        res[i] = lambda * v;
    }

    return res;
}

double calc_diff(std::vector<CKomplex> a, std::vector<CKomplex> b)
{
    int N = 1000;
    double max_diff = 0.0;

    // Max_diff suchen
    for (int i = 0; i < N; i++)
    {
        double diff_im_durchlauf = (a[i] - b[i]).abs();

        // ist das die bisher größte gefundende Differenz?
        if (diff_im_durchlauf > max_diff)
        {
            max_diff = diff_im_durchlauf;
        }
    }

    // die maximale Differenz zurückgeben
    return max_diff;
}





/*double calc_diff(std::vector<CKomplex> a, std::vector<CKomplex> b)
{
    int N = 1000;
    double max_diff_re = 0.0;
    double max_diff_im = 0.0;

    // Max_diff_re suchen
    for (int i = 0; i < N; i++)
    {
        double diff_im_durchlauf = 0.0;

        // Einträge sind gleich -> nichts tun
        if (a[i].get_re() == b[i].get_re())
        {
            // hier nichts tun
        }

        else if (a[i].get_re() > b[i].get_re())
        {
            diff_im_durchlauf = a[i].get_re() - b[i].get_re();
        }
        else {
            diff_im_durchlauf = b[i].get_re() - a[i].get_re();
        }

        // ist das die bisher größte gefundende Differenz?
        if (diff_im_durchlauf > max_diff_re)
        {
            max_diff_re = diff_im_durchlauf;
        }
    }

    // Max_diff_im suchen
    for (int i = 0; i < N; i++)
    {
        double diff_im_durchlauf = 0.0;
        // Einträge sind gleich -> nichts tun
        if (a[i].get_im() == b[i].get_im())
        {
            // hier nichts tun
        }

        else if (a[i].get_im() > b[i].get_im())
        {
            diff_im_durchlauf = a[i].get_im() - b[i].get_im();
        }
        else {
            diff_im_durchlauf = b[i].get_im() - a[i].get_im();
        }

        // ist das die bisher größte gefundende Differenz?
        if (diff_im_durchlauf > max_diff_im)
        {
            max_diff_im = diff_im_durchlauf;
        }
    }

    // die maximale Differenz zurückgeben
    double max_diff = std::max(max_diff_re,max_diff_im);
    return max_diff;
}*/