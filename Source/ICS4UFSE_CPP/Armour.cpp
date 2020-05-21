// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.


#include "Armour.h"
#include <algorithm>
#include <cmath>

Armour::Armour()
{
    Tough = 0;
    Hard = 0;
}

float Armour::Hardness()
{
    return Hard;
}

void Armour::Hardness(float hard)
{
    Hard = hard;
}

float Armour::Toughness()
{
    return Tough;
}

void Armour::Toughness(float tough)
{
    Tough = tough;
}

float Armour::CalcDmg(float Orig)
{
    using namespace std;

    if (Tough < Orig)
    {
        Orig -= Tough;
        return Orig + CalcDmg(Tough);
    }

    return min(Orig * Orig * Orig * 8 / 972099 / (exp(3 * Hard) + exp(2 * Hard) * 3 + exp(Hard) * 3 + 1), Orig * 2 / (1 + exp(Hard)));
}

float Armour::operator -(float Orig)
{
    float DmgDealt = CalcDmg(Orig);
    Tough = std::max(0.0f, Tough - Orig);

    return DmgDealt;
}

Armour::~Armour()
{
}
