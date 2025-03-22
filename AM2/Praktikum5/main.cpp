#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "CMyVektor.h"
#include "CMyMatrix.h"
#include "C_DGLSolver.h"
#include "CKomplex.h"
#include "CZufall.h"
#include "CLotto.h"
#include "time.h"

using namespace std;

double monteCarloSimulation(int r, int k, int n, int N, bool typ)
{
    CLotto lotto(k, n, -1);
    int treffer = 0;

    if (typ)
    {
        // Spieler 1: Immer der gleiche Tippzettel

        std::vector<int> tippzettel = lotto.kausnZiehung(); // Willkürlichen Tippzettel ziehen
        lotto.set_tippzettel(tippzettel); // und diesen als Tippzettel setzen

        for (int i = 0; i < N; i++)
        {
            // Für jeden der N Durchläufe wird überprüft, ob genau r Richtige vorliegen
            int count = lotto.wie_viele_richtige();
            if (count == r)
            {
                // Wenn ja, Treffer um eins erhöhen
                treffer++;
            }
        }
    }
    else
    {
        // Spieler 2: Jedes Mal ein neuer Tippzettel

        for (int i = 0; i < N; i++)
        {
            // In jedem Schleifendurchlauf wird der Tippzettel neu gezogen und gesetzt
            std::vector<int> tippzettel = lotto.kausnZiehung();
            lotto.set_tippzettel(tippzettel);

            // Für jeden der N Durchläufe wird überprüft, ob genau r Richtige vorliegen
            int count = lotto.wie_viele_richtige();
            if (count == r)
            {
                // Wenn ja, Treffer um eins erhöhen
                treffer++;
            }
        }
    }

    // Die Anzahl der Richtigen in Prozent zurückgeben
    return ((double)treffer / double(N)) * 100;
}

int main()
{
    CZufall test1;

    // 1)
    cout << "a) Mit gleichem Wert fuer s" << endl;
    // Nach einem festen Seed folgt immer die gleiche Folge an "Zufallszahlen"
    for (int i = 0; i < 3; i++)
    {
        test1.initialisiere(1);
        test1.test(3,7,10000);
        cout << endl;
    }
    cout << "<=========================================>" << endl
        << "b) Mit verschiedenen Werten fuer s" << endl;
    // Bei unterschiedlichen Seeds kommt es zu unterschiedlichen Zahlenfolgen
    // aber diese bleiben bei einer neuen Programmausführung trotzdem gleich, da
    // gleicher Seed -> gleiche Folge an "Zufallszahlen"
    for (int i = 1; i <= 3; i++)
    {
        test1.initialisiere(i);
        test1.test(3,7,10000);
        cout << endl;
    }
    cout << "<=========================================>" << endl
         << "c) Vor jedem test-Aufruf wird s mit time(NULL) initialisiert" << endl;
    // time(NULL) gibt Anzahl der Sekunden seit 1970 (?) zurück
    // in der gleichen Ausführung bei kriegt man bei diesem Aufruf gleiche Werte
    // Vorteil: bei einer neuen Programmausführung kriegt man immer neue Zufallszahlen
    for (int i = 1; i <= 3; i++)
    {
        test1.initialisiere(time(NULL));
        test1.test(3,7,10000);
        cout << endl;
    }
    cout << "<=========================================>" << endl
         << "d) Vor jeder einzelnen Ziehung wird s mit time(NULL) initialisiert" << endl;
    // Gibt immer nur eine die erste "Zufallszahl" aus, da man vor jeder Ziehung
    // neu mit time(NULL) initialisiert
    for (int i = 1; i <= 3; i++)
    {
        test1.test_falsch(3,7,10000);
        cout << endl;
    }
    cout << "<=========================================>" << endl << endl;


    // 2 bzw. 3)
    CLotto test2(2, 6, -1);

    for (int i = 100; i < 1000001; i *= 10)
    {
        cout << "Die Wahrscheinlichkeit fuer Spieler 1 mit N = " << i << " betraegt: "
            << monteCarloSimulation(2, 6, 25, i, true) << "%" << endl;
    }
    cout << endl;
    for (int i = 100; i < 1000001; i *= 10)
    {
        cout << "Die Wahrscheinlichkeit fuer Spieler 2 mit N = " << i << " betraegt: "
             << monteCarloSimulation(2, 6, 25, i, false) << "%" << endl;
    }

    return 0;
}

