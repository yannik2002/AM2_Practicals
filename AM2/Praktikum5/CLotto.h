#pragma once
#include "CZufall.h"

class CLotto
{
private:

    int k, n, s;
    CZufall* tmp;
    std::vector<int> tippzettel;

public:

    CLotto(int kV, int nV, int sV);
    void set_tippzettel(std::vector<int> zettel);
    std::vector<int> kausnZiehung();
    int wie_viele_richtige();
};

