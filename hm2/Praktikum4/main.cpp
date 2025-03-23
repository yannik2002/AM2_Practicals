#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "CMyVektor.h"
#include "CMyMatrix.h"
#include "C_DGLSolver.h"
#include "CKomplex.h"
using namespace std;

vector<CKomplex> werte_einlesen(const std::string dateiname)
{
    int i, N, idx;
    double re, im;
    vector<CKomplex> werte;
    // File oeffnen
    ifstream fp;
    fp.open(dateiname);
    // Dimension einlesen
    fp >> N;
    // Werte-Vektor anlegen
    werte.resize(N);
    CKomplex null(0,0);
    for (i = 0; i<N; i++)
        werte[i] = null;
    // Einträge einlesen und im Werte-Vektor ablegen
    while (!fp.eof())
    {
        fp >> idx >> re >> im;
        CKomplex a(re,im);
        werte[idx] = a;
    }
    // File schliessen
    fp.close();

    return werte;
}

void werte_ausgeben(const std::string dateiname, vector<CKomplex> werte, double epsilon=-1.0)
{
    int i;
    int N = werte.size();
    // File oeffnen
    ofstream fp;
    fp.open(dateiname);
    // Dimension in das File schreiben
    fp << N << endl;
    // Eintraege in das File schreiben
    fp.precision(10);
    for (i = 0; i < N; i++)
        if (werte[i].abs() > epsilon)
            fp << i << "\t" << werte[i].get_re() << "\t" << werte[i].get_im() << endl;
    // File schliessen
    fp.close();
}


int main() {

    // die vorgegebenen werte aus den beiden original.txt dateien einlesen
    vector<CKomplex> list1 = werte_einlesen("Daten_original1.txt");
    vector<CKomplex> list2 = werte_einlesen("Daten_original2.txt");

    // die hintransformationen durchführen
    vector<CKomplex> res1 = fourierHintransformation(list1);
    vector<CKomplex> res2 = fourierHintransformation(list2);

    // werte aus Daten_original1.txt mit threshold zur komprimierung
    werte_ausgeben("output11.txt", res1, -1.0);
    werte_ausgeben("output12.txt", res1, 0.001);
    werte_ausgeben("output13.txt", res1, 0.01);
    werte_ausgeben("output14.txt", res1, 0.1);
    werte_ausgeben("output15.txt", res1, 1.0);

    // werte aus Daten_original2.txt mit threshold zur komprimierung
    werte_ausgeben("output21.txt", res2, -1.0);
    werte_ausgeben("output22.txt", res2, 0.001);
    werte_ausgeben("output23.txt", res2, 0.01);
    werte_ausgeben("output24.txt", res2, 0.1);
    werte_ausgeben("output25.txt", res2, 1.0);

    // die komprimierten werte aus Daten_original1.txt wieder einlesen
    // und rücktransformieren
    vector<CKomplex> res_11 = werte_einlesen("output11.txt"); // -1.0
    res_11 = fourierRuecktransformation(res_11);
    vector<CKomplex> res_12 = werte_einlesen("output12.txt"); // 0.001
    res_12 = fourierRuecktransformation(res_12);
    vector<CKomplex> res_13 = werte_einlesen("output13.txt"); // 0.01
    res_13 = fourierRuecktransformation(res_13);
    vector<CKomplex> res_14 = werte_einlesen("output14.txt"); // 0.1
    res_14 = fourierRuecktransformation(res_14);
    vector<CKomplex> res_15 = werte_einlesen("output15.txt"); // 1.0
    res_15 = fourierRuecktransformation(res_15);

    // die komprimierten werte aus Daten_original2.txt wieder einlesen
    // und rücktransformieren
    vector<CKomplex> res_21 = werte_einlesen("output21.txt"); // -1.0
    res_21 = fourierRuecktransformation(res_21);
    vector<CKomplex> res_22 = werte_einlesen("output22.txt"); // 0.001
    res_22 = fourierRuecktransformation(res_22);
    vector<CKomplex> res_23 = werte_einlesen("output23.txt"); // 0.01
    res_23 = fourierRuecktransformation(res_23);
    vector<CKomplex> res_24 = werte_einlesen("output24.txt"); // 0.1
    res_24 = fourierRuecktransformation(res_24);
    vector<CKomplex> res_25 = werte_einlesen("output25.txt"); // 1.0
    res_25 = fourierRuecktransformation(res_25);

    // abweichungen messen zwischen der original datei und
    // den rücktransformationen nach komprimierung
    std::cout << "Bei Daten_original1.txt" << std::endl;
    std::cout << "Maximale Abweichung bei Standard-Epsilon: ";
    std::cout << calc_diff(list1, res_11) << std::endl;
    std::cout << "Maximale Abweichung bei epsilon=0.001: ";
    std::cout << calc_diff(list1, res_12) << std::endl;
    std::cout << "Maximale Abweichung bei epsilon=0.01: ";
    std::cout << calc_diff(list1, res_13) << std::endl;
    std::cout << "Maximale Abweichung bei epsilon=0.1: ";
    std::cout << calc_diff(list1, res_14) << std::endl;
    std::cout << "Maximale Abweichung bei epsilon=1.0: ";
    std::cout << calc_diff(list1, res_15) << std::endl << std::endl;

    std::cout << "Bei Daten_original2.txt" << std::endl;
    std::cout << "Maximale Abweichung bei Standard-Epsilon: ";
    std::cout << calc_diff(list2, res_21) << std::endl;
    std::cout << "Maximale Abweichung bei epsilon=0.001: ";
    std::cout << calc_diff(list2, res_22) << std::endl;
    std::cout << "Maximale Abweichung bei epsilon=0.01: ";
    std::cout << calc_diff(list2, res_23) << std::endl;
    std::cout << "Maximale Abweichung bei epsilon=0.1: ";
    std::cout << calc_diff(list2, res_24) << std::endl;
    std::cout << "Maximale Abweichung bei epsilon=1.0: ";
    std::cout << calc_diff(list2, res_25) << std::endl;


    // BILDERSERIE

    /*
    std::vector<CKomplex> fh = werte_einlesen("fh_original.txt");

     // loesung1 ist der eingelesene vector für das Original nach Hintransformation
    std::vector<CKomplex> loesung1 = fourierHintransformation(fh);

     // ab hier immer mit dem jeweiligen threshold in .txt ausgeben
     // dann wieder einlesen, rücktransformieren und wieder ausgeben
     // mit den fertigen .txt dateien dann wieder bilder erstellen mit
     // image2array

    werte_ausgeben("fh_eins_koeff.txt", loesung1, 10);
    std::vector<CKomplex> res_1 = werte_einlesen("fh_eins_koeff.txt");
    res_1 = fourierRuecktransformation(res_1);
    werte_ausgeben("fh_eins.txt", res_1);

    werte_ausgeben("fh_zwei_koeff.txt", loesung1, 30);
    std::vector<CKomplex> res_2 = werte_einlesen("fh_zwei_koeff.txt");
    res_2 = fourierRuecktransformation(res_2);
    werte_ausgeben("fh_zwei.txt", res_2);

    werte_ausgeben("fh_drei_koeff.txt", loesung1, 100);
    std::vector<CKomplex> res_3 = werte_einlesen("fh_drei_koeff.txt");
    res_3 = fourierRuecktransformation(res_3);
    werte_ausgeben("fh_drei.txt", res_3);

    werte_ausgeben("fh_vier_koeff.txt", loesung1, 300);
    std::vector<CKomplex> res_4 = werte_einlesen("fh_vier_koeff.txt");
    res_4 = fourierRuecktransformation(res_4);
    werte_ausgeben("fh_vier.txt", res_4);

    werte_ausgeben("fh_fuenf_koeff.txt", loesung1, 1000);
    std::vector<CKomplex> res_5 = werte_einlesen("fh_vier_koeff.txt");
    res_5 = fourierRuecktransformation(res_5);
    werte_ausgeben("fh_vier.txt", res_5);
     */

    // system("pause");
    return 0;
}