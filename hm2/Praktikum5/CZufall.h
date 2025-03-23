#pragma once
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>

class CZufall
{
    public:

        CZufall() {}
        int wert(int a, int b);
        void test(int a, int b, int N);
        void test_falsch(int a, int b, int N);
        void initialisiere(int s);
};

