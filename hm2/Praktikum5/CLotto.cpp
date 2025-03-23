#include "CLotto.h"

CLotto::CLotto(int kV, int nV, int sV) : k{ kV }, n{ nV }
{
    if (sV < 0)
    {
        tmp->initialisiere(time(NULL));
    } else
    {
        tmp->initialisiere(s);
    }
}

void CLotto::set_tippzettel(std::vector<int> zettel)
{
    tippzettel = zettel;
}

// k aus n Lotto Ziehung
std::vector<int> CLotto::kausnZiehung()
{
    // Pot für Ziehung erstellen und Werte einlesen
    std::vector<int> topf;
    topf.resize(n);
    for (int i = 0; i < n; i++)
    {
        topf[i] = i + 1;
    }

    std::vector<int> ziehungen;
    ziehungen.resize(k);

    // Ziehungen aus dem Topf
    for (int i = 0; i < k; i++)
    {
        int zahl;

        // Solange die gezogene Zahl vorher schon gezogen wurde, wird neu gezogen
        do {
            zahl = tmp->wert(1, n);
        } while (topf[zahl - 1] == -1);

        // Zahl wird aus dem Topf entfernt
        topf[zahl - 1] = -1;
        // Zahl wird in Ziehungen eingelesen
        ziehungen[i] = zahl;
    }

    return ziehungen;
}

// Führt eine k aus n Ziehung durch und gibt die Anzahl der Richtigen zurück
// im Vergleich mit dem Tippzettel
int CLotto::wie_viele_richtige()
{
    std::vector<int> ziehung = kausnZiehung();

    int treffer = 0;
    for (int i = 0; i < ziehung.size(); i++)
    {
        for (int i2 = 0; i2 < tippzettel.size(); i2++)
        {
            if (ziehung[i] == tippzettel[i2])
            {
                treffer++;
            }
        }
    }

    return treffer;
}