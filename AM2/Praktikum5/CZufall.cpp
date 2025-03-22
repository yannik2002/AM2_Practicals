#include "CZufall.h"

int CZufall::wert(int a, int b)
{
    return rand() % (b - a + 1) + a;
}

void CZufall::initialisiere(int s)
{
    srand(s);
}

void CZufall::test(int a, int b, int N)
{
    int size = b - a + 1;
    std::vector<int> counter(size, 0);

    // Zählen der Häufigkeitenen
    for (int i = 0; i < N; i++)
    {
        // wert generieren und dann mit (rndm - a)
        // an der richtigen Stelle vom counter um eins erhöhen
        int rndm = wert(a, b);
        counter[rndm - a]++;
    }

    // Ausgeben der häufigkeiten
    for (int i = 0; i <= b - a; i++)
    {
        std::cout << "Die Zahl "<< i + a << " kommt " << counter[i] << " mal vor." << std::endl;
    }
}

void CZufall::test_falsch(int a, int b, int N)
{
    std::vector<int> counter;
    counter.resize(b - a + 1);

    // Zählen der Häufigkeiten
    for (int i = 0; i < N; i++)
    {
        // Vor jedem einzelnen Ziehen mit time(NULL) initialisieren
        srand(time(NULL));
        int rndm = wert(a, b);
        counter[rndm - a]++;
    }

    // Ausgeben der Häufigkeiten
    for (int i = 0; i <= b - a; i++)
    {
        std::cout << "Die Zahl "<< i + a << " kommt " << counter[i] << " mal vor." << std::endl;
    }
}