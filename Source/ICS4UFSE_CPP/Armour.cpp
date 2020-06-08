// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.


#include "Armour.h"
#include <algorithm>
#include <cmath>

FArmour::FArmour()
{
    Tough = 0;
    Hard = 0;
}

FArmour::FArmour(float T, float H)
{
    Tough = T;
    Hard = H;
}

float FArmour::Hardness()
{
    return Hard;
}

void FArmour::Hardness(float hard)
{
    Hard = hard;
}

float FArmour::Toughness()
{
    return Tough;
}

void FArmour::Toughness(float tough)
{
    Tough = tough;
}

float FArmour::CalcDmg(float Orig)
{
    using namespace std;

    if (Tough < Orig)
    {
        Orig -= Tough;
        return Orig + CalcDmg(Tough);
    }
    // Return a damage value based on the current armour state
    return min(Orig * Orig * Orig * 8 / (exp(3 * Hard) + exp(2 * Hard) * 3 + exp(Hard) * 3 + 1), Orig * 2 / (1 + exp(Hard)));
}

float FArmour::operator -(float Orig)
{
    float DmgDealt = CalcDmg(Orig);
    Tough = std::max(0.0f, Tough - Orig);

    return DmgDealt;
}

FArmour::~FArmour()
{
}
