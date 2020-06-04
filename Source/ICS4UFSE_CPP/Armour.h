// Copyright (c) 2020 David Hui and Kevin Zhang. ALL RIGHTS RESERVED.

#pragma once

#include "CoreMinimal.h"
#include "Armour.generated.h"

/**
 * 
 */
USTRUCT()
struct ICS4UFSE_CPP_API FArmour
{
    GENERATED_BODY()
public:
	FArmour();
    FArmour(float T, float H);
	~FArmour();

    // gets the hardness of the armour
    float Hardness();
    // sets the hardness of the armour
    void Hardness(float Hard);

    // gets the toughness of the armour
    float Toughness();
    // sets the toughness of the armour
    void Toughness(float Tough);

    // calculates damage dealt onto the player
    float CalcDmg(float Orig);

    // deals the damage on armour and returns damage player should take
    float operator -(float Orig);

    // copy constructor and assignment operators
    FArmour(const FArmour& armour) = default;
    FArmour& operator=(const FArmour& armour) = default;

private:
    float Hard;
    float Tough;
};
